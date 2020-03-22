all:
	gcc -o ./bouncer b_main.c -I../ffmpeg/include -L../ffmpeg/lib/ `pkg-config --cflags --libs libavformat libavcodec libswresample libswscale libavutil`

clean:
	rm -f bouncer *.o *.mp4 *.cool	*.mp2
movie:
	ffmpeg -i bounce%03d.cool -i bounce_audio.mp2 movie.mp4
