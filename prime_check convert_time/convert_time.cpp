/*This is a short program that converts seconds into
 *hours, minutes and seconds respectively. The program
 *displays the number of seconds a user enters rounded 
 *to the nearest whole number of seconds into hours minutes 
 *and seconds using the following format:
 *"X SECONDS --> HH:MM:SS".
 *To compile, use: g++ convert_time.cpp
 *To run, use: ./a.out
 *Version 1.0
 *Author: Pranav Rajan
 *Date: 01/10/2019
 */

#include <iostream>
#include <cmath>
#include <cstdio>

int main()
{
    double userInput; //variable that stores the user input as a double
    int time; //variable that stores user input rounded accordingly to the decimal place
    int hours; 
    int minutes;
    int seconds;
    int remainder; //variable that stores the remainder when computing time in hours, minutes and seconds

    std::cout << "Enter a time in seconds: ";
    std::cin >> userInput;

    time = round(userInput);

    //compute time
    hours = time / 3600;
    remainder = time % 3600;
    minutes = remainder / 60;
    seconds = remainder % 60;

    printf("%d %s %02d : %02d : %02d\n", time, "seconds -->", hours, minutes, seconds); //Display result with appropriate number of zeros
}
