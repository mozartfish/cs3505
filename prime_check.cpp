/*This is a short program that determines whether a number is prime
 *using command line arguments.The program prints 'prime' if there is one
 *argument that can be parsed as an integer that is prime, otherwise the 
 *program prints 'not prime'.
 *To compile, use: g++ prime_check.cpp
 *To run, use: ./a.out followed by the number you want to check if it is prime
 *Version 1.0
 *Author: Pranav Rajan
 *Date: 01/10/2019
 */

#include <iostream>
#include <cmath>
#include <cstdlib>

int main (int argc, char ** argv)
{
    bool isPrime = true; //boolean that stores whether a number is prime or not. Default value is true

    int num = atoi(argv[1]); //parse character argument into an integer

    if (num != 2 && num % 2 == 0) //check for divisibility by 2
    {
        isPrime = false;
    }
    else
    {
        for (int i = 3; i*i <= num); i += 2) //loop until the square root of the number to see if the number has any factors
        {
            if (num % i == 0)
            {
                isPrime = false;
            }
        }
    }

    if (isPrime)
    {
        std::cout << "prime" << std::endl;
    }
    else
    {
        std::cout << "not prime" << std::endl;
    }

    return 0;
}
