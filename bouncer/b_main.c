/*
  Authors: Thomas Ady and Pranav Rajan
  3/18/19
  FFMPEG Checkpoint 3

  This file serves as the entry point for the bouncer application
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/frame.h>
#include <libavutil/samplefmt.h>

/* check that a given sample format is supported by the encoder 
 * Source: http://ffmpeg.org/doxygen/trunk/encode_audio_8c-example.html
 */
static int check_sample_fmt(const AVCodec *codec, enum AVSampleFormat sample_fmt)
{
    const enum AVSampleFormat *p = codec->sample_fmts;
    while (*p != AV_SAMPLE_FMT_NONE) {
        if (*p == sample_fmt)
            return 1;
        p++;
    }
    return 0;
}
/* just pick the highest supported samplerate
 * Source: http://ffmpeg.org/doxygen/trunk/encode_audio_8c-example.html
 */
static int select_sample_rate(const AVCodec *codec)
{
    const int *p;
    int best_samplerate = 0;
    if (!codec->supported_samplerates)
        return 44100;
    p = codec->supported_samplerates;
    while (*p) {
        if (!best_samplerate || abs(44100 - *p) < abs(44100 - best_samplerate))
            best_samplerate = *p;
        p++;
    }
    return best_samplerate;
}
/* select layout with the highest channel count
 * Source: http://ffmpeg.org/doxygen/trunk/encode_audio_8c-example.html
 */
static int select_channel_layout(const AVCodec *codec)
{
    const uint64_t *p;
    uint64_t best_ch_layout = 0;
    int best_nb_channels   = 0;
    if (!codec->channel_layouts)
        return AV_CH_LAYOUT_STEREO;
    p = codec->channel_layouts;
    while (*p) {
        int nb_channels = av_get_channel_layout_nb_channels(*p);
        if (nb_channels > best_nb_channels) {
            best_ch_layout    = *p;
            best_nb_channels = nb_channels;
        }
        p++;
    }
    return best_ch_layout;
}

/* Encodes the audio frames
 * Source: http://ffmpeg.org/doxygen/trunk/encode_audio_8c-example.html
 */
static void encode(AVCodecContext *ctx, AVFrame *frame, AVPacket *pkt,
                   FILE *output)
{
    int ret;
    /* send the frame for encoding */
    ret = avcodec_send_frame(ctx, frame);
    if (ret < 0) {
        fprintf(stderr, "Error sending the frame to the encoder\n");
        exit(1);
    }
    /* read all the available output packets (in general there may be any
     * number of them */
    while (ret >= 0) {
        ret = avcodec_receive_packet(ctx, pkt);
        if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
            return;
        else if (ret < 0) {
            fprintf(stderr, "Error encoding audio frame\n");
            exit(1);
        }
        fwrite(pkt->data, 1, pkt->size, output);
        av_packet_unref(pkt);
    }
}


/*
 * Draws a ball onto a copy of the source frame, at some y coordinate 
 * based on what image frame is currently ready to be encoded
 */
void draw_ball_on_frame(AVFrame * source, int frame_num, int height, int width) {

  int x;
  int y;
  int x_light;
  int y_light;
  int h;
  int w;
  int radius;
  int radius_light;
  int frame_translate;
  uint8_t* data;

  data = (uint8_t *)source->data[0];

  // Get y coord translate equal to 1/60 of the height, multiplied by the frame num % 60
  // To get simulated movement
  frame_translate = (height / 60) * (frame_num % 60);
  y = (int)fabs((double)(height / 2 - frame_translate)) + height / 2;
  
  // X and radius are middle of screen and 10% of the smaller dimension, respectively
  x = width / 2;
  radius = fmin(height, width) / 10;
  
  //Calculate the circle values for the highlight
  x_light = x -(int)(radius/(2*sqrt(2)));
  y_light = y -(int)(radius/(2*sqrt(2)));
  
  // Iterate over the data as if it were 2D, drawing the circle where necessary
  for (h = 0; h < height; h++)
    for (w = 0; w < width; w++) {
      
      int dist = (int)sqrt(pow((double)(x-w), 2) + pow((double)(y-h), 2));
      int dist_light = (int)sqrt(pow((double)(x_light-w), 2) + pow((double)(y_light-h), 2));
      
      // Either shade highlight or red if within radius of either circle or leave as background color
      if (dist_light <= radius / 6) 
	//*data = 0xFE7A; // Pink highlight
	{
	*data = 0xFF; // Red color
	*(data + 1) = 0xAA;
	*(data + 2) = 0xAA;
	}
      else if (dist_light <= radius / 4) 
	//*data = 0xFD6A; // Pink highlight
	{
	*data = 0xFF; // Red color
	*(data + 1) = 0x8D;
	*(data + 2) = 0x8D;
	}
      else if (dist_light <= radius / 3) 
	//*data = 0xFA5A; // Pink highlight
	{
	*data = 0xFF; // Red color
	*(data + 1) = 0x4F;
	*(data + 2) = 0x4F;
	}
      else if (dist <= radius)
	{
	*data = 0xFF; // Red color
	*(data + 1) = 0x00;
	*(data + 2) = 0x00;
	}
      data += 3;
      
    }
 
}

/*
 * Writes the given frame to a .cool file with the name bounce000, where 000 is some frame number
 * Source: http://dranger.com/ffmpeg/tutorial01.html, http://ffmpeg.org/doxygen/trunk/encode_video_8c-example.html
 */
void save_frame(AVCodecContext * enc_context, AVFrame *pFrame, int width, int height, int iFrame) {
  FILE *outfile;
  AVPacket * packet;
  char szFilename[32];
  int ret;
  
  // Open file
  sprintf(szFilename, "bounce%03d.cool", iFrame);
  outfile=fopen(szFilename, "wb");
  if(outfile==NULL)
    return;

    // Allocate the packet for use in encoding
    packet = av_packet_alloc();
    if (!packet) {
      printf("Cannot allocate packet");
      exit(-1);
    }
  
  // send the frame to the encoder 
  if (pFrame)
    printf("Send frame %3"PRId64"\n", pFrame->pts);
  ret = avcodec_send_frame(enc_context, pFrame);
  if (ret < 0) {
    fprintf(stderr, "Error sending a frame for encoding\n");
    exit(1);
    }

  // Get the encoded data
  while (ret >= 0) {
    ret = avcodec_receive_packet(enc_context, packet);

    if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
      return;
    else if (ret < 0) {
      fprintf(stderr, "Error during encoding\n");
      exit(1);
      }

    printf("Write packet %3"PRId64" (size=%5d)\n", packet->pts, packet->size);
    fwrite(packet->data, 1, packet->size, outfile);
    av_packet_unref(packet);
  }

  // Close file
  fclose(outfile);
}

/*
 * The entry point for the program, calls helper functions to write an input jpg as
 * 300 frames of the same impage but with a ball overlayed on top
 */
int main(int argv, char ** argc) {

  // Check num of args
  if (argv < 2) {
    printf("ERR: Needs file input\n");
    return 1;
  }
  else if (argv > 2) {
    printf("ERR: Too many arguments, provide a single file only\n");
    return 1;
  }

  // Get command line arg filename
  char* filename = argc[1];
  int file_length = 0;

  //Loop to find size of file name
  while (filename[++file_length] != NULL); 

  // make sure file is of proper naming for a .jpg
  if (file_length < 5 || filename[file_length - 4] != '.' || filename[file_length - 3] != 'j' 
      || filename[file_length - 2] != 'p' || filename[file_length - 1] != 'g') {
    printf("ERR: Improper file extension, must have a name ending in .jpg\n");
    return 1;
  }

  char* out_filename = "bounce";
  int frame_count = 0;
  AVFormatContext *pFormatCtx = NULL;
  int i;
  int stream_index = -1;
  AVCodec *codec;
  AVCodec *encoder;
  AVCodecContext *dec_context = NULL;
  AVCodecContext *enc_context = NULL;
  FILE *f;
  AVFrame *frame;
  AVFrame *frameRGB;
  AVFrame *frameCanvas;
  uint8_t* buffer;
  uint8_t* canvasBuf;
  int num_bytes;
  uint8_t *data;
  size_t   data_size;
  int ret;
  struct SwsContext *sws_ctx = NULL;
  int frameFinished;
  AVPacket *packet;


  // Opening input and stream info getting from http://dranger.com/ffmpeg/
  // Register all codecs
  avcodec_register_all();

  // Open video file
  if(avformat_open_input(&pFormatCtx, filename, NULL, NULL)!=0)
    return -1; // Couldn't open file

  // Retrieve stream information
  if(avformat_find_stream_info(pFormatCtx, NULL)<0)
    return -1; // Couldn't find stream information

  // Dump information about file onto standard error
  av_dump_format(pFormatCtx, 0, filename, 0);

  // Get the index for where the stream should begin, and get the codec initialized
  stream_index = av_find_best_stream(pFormatCtx, AVMEDIA_TYPE_VIDEO, -1, -1, &codec, 0);
  if (stream_index < 0) {
    printf("Stream index error");
    return 1;
  }

  //Get the codec params to initialize with the Context
  AVCodecParameters *params = pFormatCtx->streams[stream_index]->codecpar;

  // Allocate the context, source: http://ffmpeg.org/doxygen/trunk/encode_video_8c-example.html
  dec_context = avcodec_alloc_context3(codec);
  if (!dec_context) {
    fprintf(stderr, "Could not allocate video codec context\n");
    exit(1);
  }

   //Set the parameters of the codec context from the stream
  if(avcodec_parameters_to_context(dec_context, params) < 0) {
    printf("Could  not set context params");
    return 1; 
   }

  // Open codec
  if(avcodec_open2(dec_context, codec, NULL)<0)
    return -1; // Could not open codec

  // Allocating various needed pointers from http://dranger.com/ffmpeg/

  // Allocate a frame for decoding
  frame = av_frame_alloc();

  // Allocate an AVFrame for converted color
  frameRGB=av_frame_alloc();
  if(!frameRGB || !frame)
    return -1;

  // Allocate the packet
  packet = av_packet_alloc();
  if (!packet) {
    printf("Cannot allocate packet");
    return -1;
  }

  // Determine required buffer size and allocate buffer
  num_bytes=av_image_get_buffer_size(AV_PIX_FMT_RGB24, dec_context->width,
				       dec_context->height, 4);
  buffer=(uint8_t *)av_malloc(num_bytes*sizeof(uint8_t));

  // Fill the frame for encoding
  avpicture_fill((AVPicture *)frameRGB, buffer, AV_PIX_FMT_RGB24,
                dec_context->width, dec_context->height);

  frameRGB->height = dec_context->height;
  frameRGB->width = dec_context->width;
  frameRGB->format = AV_PIX_FMT_RGB24;

    
  // initialize SWS context for software scaling
  sws_ctx = sws_getContext(dec_context->width, dec_context->height, dec_context->pix_fmt, dec_context->width, 
			  dec_context->height, AV_PIX_FMT_RGB24, SWS_BILINEAR, NULL, NULL, NULL);

 
  // Reading in packets to a frame inspired by http://dranger.com/ffmpeg/
  // Read in packets to send to a frame
  while(av_read_frame(pFormatCtx, packet)>=0) {

    // Decode video frame, atore data in frame
    avcodec_send_packet(dec_context, packet);
    avcodec_receive_frame(dec_context, frame);
  }
  
  // Free the packet that was allocated by av_read_frame
  av_packet_free(&packet);

 
  

  // Find the encoder for COOL encoding
  encoder = avcodec_find_encoder(AV_CODEC_ID_COOL);
  if (!encoder) {
    printf("Could not find COOL encoder");
    return -1;
  }

   // Allocate the context for the encoder
   enc_context = avcodec_alloc_context3(encoder);
   if (!dec_context) {
       fprintf(stderr, "Could not allocate video codec context\n");
       exit(1);
   }

  // Set fields for encode context
  enc_context->time_base = (AVRational){1, 25};
  enc_context->framerate = (AVRational){25, 1};
  enc_context->height = dec_context->height;
  enc_context->width = dec_context->width;
  enc_context->pix_fmt = AV_PIX_FMT_RGB24;

  // Open codec
  if(avcodec_open2(enc_context, encoder, NULL)<0)
    return -1; // Could not open codec

  // Write 300 frames of the movie
  while (frame_count < 300) {

    // Converting frame from http://dranger.com/ffmpeg/
  // Convert the image from its native format to RGB
  sws_scale(sws_ctx, (uint8_t const * const *)frame->data,
	   frame->linesize, 0, dec_context->height,
	   frameRGB->data, frameRGB->linesize);

    // Draw the ball onto the canvas frame using data in frameRGB
  draw_ball_on_frame(frameRGB, frame_count, enc_context->height, enc_context->width);
    
    // Write the frame to a file using the COOL format, inspired by http://dranger.com/ffmpeg/
    save_frame(enc_context, frameRGB, enc_context->width, 
	       enc_context->height, frame_count++);
  }

  // Free up all memory allocated
  av_freep(&buffer);
  avformat_close_input(&pFormatCtx);
  avcodec_free_context(&dec_context);
  av_frame_free(&frameRGB);
  av_frame_free(&frame);
  av_packet_free(&packet); 





  // Enocde the audio

  const char *au_name;
  const AVCodec *au_codec;
  AVCodecContext *au_context= NULL;
  AVFrame *au_frame;
  AVPacket *au_pkt;
  int a, b, c, ret2;
  FILE *au_file;
  uint16_t *samples;
  float t, tincr;
  
  au_name = "bounce_audio.mp2";
  /* find the WAV encoder */


  // Encoding audio from : http://ffmpeg.org/doxygen/trunk/encode_audio_8c-example.html
  au_codec = avcodec_find_encoder(AV_CODEC_ID_MP2);
  if (!codec) {
    fprintf(stderr, "Codec not found\n");
    exit(1);
    }
    au_context = avcodec_alloc_context3(au_codec);
    if (!au_context) {
        fprintf(stderr, "Could not allocate audio codec context\n");
        exit(1);
    }
    /* put sample parameters */
    au_context->bit_rate = 64000;
    /* check that the encoder supports s16 pcm input */
    au_context->sample_fmt = AV_SAMPLE_FMT_S16;
    if (!check_sample_fmt(au_codec, au_context->sample_fmt)) {
        fprintf(stderr, "Encoder does not support sample format %s",
                av_get_sample_fmt_name(au_context->sample_fmt));
        exit(1);
    }
    /* select other audio parameters supported by the encoder */
    au_context->sample_rate    = select_sample_rate(au_codec);
    au_context->channel_layout = select_channel_layout(au_codec);
    au_context->channels       = av_get_channel_layout_nb_channels(au_context->channel_layout);
    /* open it */
    if (avcodec_open2(au_context, au_codec, NULL) < 0) {
        fprintf(stderr, "Could not open codec\n");
        exit(1);
    }
    au_file = fopen(au_name, "wb");
    if (!au_file) {
        fprintf(stderr, "Could not open %s\n", au_name);
        exit(1);
    }
    /* packet for holding encoded output */
    au_pkt = av_packet_alloc();
    if (!au_pkt) {
        fprintf(stderr, "could not allocate the packet\n");
        exit(1);
    }
    /* frame containing input raw audio */
    au_frame = av_frame_alloc();
    if (!au_frame) {
        fprintf(stderr, "Could not allocate audio frame\n");
        exit(1);
    }
    au_frame->nb_samples     = au_context->frame_size;
    au_frame->format         = au_context->sample_fmt;
    au_frame->channel_layout = au_context->channel_layout;
    /* allocate the data buffers */
    ret2 = av_frame_get_buffer(au_frame, 0);
    if (ret2 < 0) {
        fprintf(stderr, "Could not allocate audio data buffers\n");
        exit(1);
    }
    /* encode a single tone sound */
    t = 0;
    tincr = 2 * M_PI  / au_context->sample_rate;
    for (a = 0; a < 385; a++) {
        /* make sure the frame is writable -- makes a copy if the encoder
         * kept a reference internally */
        ret2 = av_frame_make_writable(au_frame);
        if (ret2 < 0)
            exit(1);

	double freq = (440 - 100 * cos(a)) * tincr;


        samples = (uint16_t*)au_frame->data[0];

	// WRITES THE AUDIO IN SAMPLES
        for (b = 0; b < au_context->frame_size; b++) {
            samples[2*b] = (int)(sin(t) * 10000);
	     for (c = 1; c < au_context->channels; c++)
	       samples[2*b + c] = samples[2*b];
            t += freq;
        }
        encode(au_context, au_frame, au_pkt, au_file);
    }
    /* flush the encoder */
    encode(au_context, NULL, au_pkt, au_file);
    fclose(au_file);
    av_frame_free(&au_frame);
    av_packet_free(&au_pkt);
    avcodec_free_context(&au_context);







  return 0;
}
