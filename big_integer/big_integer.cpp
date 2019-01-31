/*This files defines big integer objects that allow for the computation of very large integers using different 
 *mathematical functions including addition,subtraction, multiplication, division and modulo. The mathematical functions
 *implement the standard grade school algorithms for long addition, long subtraction, long multiplication, and long division.
 *SOME THINGS TO NOTE:
 * For the subtraction function, if the difference between two big integers is less than zero the result will be zero 
 * For the the division function, if the divisor is greater than the dividend the result will be zero.
 * To compile: g++ big_integer.cpp tester.cpp
 * To run: ./a.out
 *Version 1.0
 *Authors: Pranav Rajan, Professor Peter Jensen
 *Date: January 23, 2019
 */

#include <iostream>
#include <cstdlib>
#include<string>
#include "big_integer.h"

/*
 *The default constructor
 */
big_integer::big_integer()
{
  this-> s = "0";
}

/*
 *Constructor that takes a single string parameter representing a non-negative integer
 */
big_integer::big_integer(std::string s)
{
  this-> s = s;
}

/*
 *The public copy constructor
 */
big_integer::big_integer(const big_integer & bigInt2)
{
  this-> s = bigInt2.s;
}

/*
 *The public accesor that returns the returns the string representation of the integer within the object
 */
std::string big_integer::get_value() const
{
  return this->s;
}

/*
 *The equality operator overloaded
 */
big_integer & big_integer::operator= (const big_integer & bigInt2)
{
  s = bigInt2.get_value();
  return *this;
}

/*
 * Returns a boolean whether the left integer is larger when compared to the right integer
 */
bool big_integer::compare_two_strings(std::string left, std::string right)
{
  bool result;
  while (left.size() > 1 && left[0] == '0')
  {
    left.erase(0, 1);
  }
  while (right.size() > 1 && right[0] == '0')
  {
    right.erase(0, 1);
  }
    
  if (left.length() < right.length())
  {
    result = false;
    return result;
  }
  else if (left.length() > right.length())
  {
    result = true;
    return result;
  }
  else
  {
    int index = 0; // start at index zero
    while (index < left.length())
    {
        int i = left[index] - '0';
        int j = right[index] - '0';
        if (i > j)
        {
            result = true;
            break;
        }
        else if (i < j)
        {
            result = false;
            break;
        }
        else
        {
            index++;
        }
    }
    return result;
  }
}

/*
 * Adds two integers stored in strings, building a string result.
 *Author: Professor Peter Jensen
 */
std::string big_integer::add_two_strings (std::string left, std::string right)
{
  // Start with an empty string, then build up a string to contain the result.
  
  std::string result = "";

  // We'll go through digits right-to-left, so start at the end.
  while (left.size() > 1 && left[0] == '0')
  {
    left.erase(0, 1);
  }
  while (right.size() > 1 && right[0] == '0')
  {
    right.erase(0, 1);
  }

  int left_pos  = left.size()  - 1;
  int right_pos = right.size() - 1;

  // Loop, adding columns until no more digits or carry remain.

  int carry = 0;
  while (left_pos >= 0 || right_pos >= 0 || carry > 0)
  {
    // Calculate the sum for one column of digits.  (Digits remain
    //    so long as positions are not less than zero.)

    int sum = 0;
    
    if (left_pos >= 0)
      sum += left[left_pos] - '0';  // Remove the ASCII bias as we add
    if (right_pos >= 0)
      sum += right[right_pos] - '0';  // Remove the ASCII bias as we add

    sum += carry;

    // Determine if there is now a carry, confine the sum to a single digit.

    carry = sum / 10;
    sum   = sum % 10;

    // Put the sum into the new string (at the left side)

    result.insert (0, 1, (char)('0'+sum) );  // Add in an ASCII bias before storing the char

    // Move the positions to the prior column of each number.  (Negative positions indicate we've
    //   taken care of all the columns in some number.)


    left_pos--;
    right_pos--;
  }

  // Strip out any leading 0's from our result (but leave at least one digit).
  //   (Only useful for subtraction, but I'm giving it to you here.)

  while (result.size() > 1 && result[0] == '0')
    result.erase(0, 1);
  
  return result;
}

/*
 *The addition operator overloaded
 */
const big_integer big_integer::operator+ (const big_integer & bigInt2) const
{
  big_integer sum = add_two_strings(s, bigInt2.s);

  return sum;
}

/*
 *Subtracts two integers stored in strings and builds the result as a string 
 *Authors: Pranav Rajan and Professor Peter Jensen
 */
std::string big_integer::subtract_two_strings (std::string left,  std::string right)
{
   // Start with an empty string, then build up a string to contain the result.
  
  std::string result = "";
  if (!compare_two_strings(left, right))
  {
    return result = "0";
  }

  // We'll go through digits right-to-left, so start at the end.
  while (left.size() > 1 && left[0] == '0')
  {
    left.erase(0, 1);
  }
  while (right.size() > 1 && right[0] == '0')
  {
    right.erase(0, 1);
  }

  int left_pos  = left.size()  - 1;
  int right_pos = right.size() - 1;

  // Loop, adding columns until no more digits or carry remain.

  int carry = 0;
  while (left_pos >= 0 || right_pos >= 0 || carry > 0)
  {
    // Calculate the difference for one column of digits.  (Digits remain
    //    so long as left string  positions are not less than zero.)

    int difference = 0;
    int i = 0; // variable that stores the integer located at a specified index in the left string
    int j = 0; // variable that stores the integer located at a specified index in the right string
    
    if (left_pos >= 0)
      i = left[left_pos] - '0';  // Remove the ASCII bias as we add
    if (right_pos >= 0)
      j =  right[right_pos] - '0';  // Remove the ASCII bias as we add
    if (right_pos < 0) // if the right string has no more characters left and the
                       // the left string does then we have to subtract zeros in order to make the subtraction work correctly
      j = 0;

    difference = i - j - carry;

    // Determine if there is now a carry, confine the difference to a positive number.

    if (difference < 0)
    {
      difference = difference + 10;
      carry = 1;
    }
    else 
    {
      carry = 0;
    }

    // Put the difference into the new string (at the left side)

    result.insert (0, 1, (char)('0'+difference));  // Add in an ASCII bias before storing the char

    // Move the positions to the prior column of each number.  (Negative positions indicate we've
    //   taken care of all the columns in some number.)

    left_pos--;
    right_pos--;
  }

  // Strip out any leading 0's from our result (but leave at least one digit).
  //   (Only useful for subtraction, but I'm giving it to you here.)

  while (result.size() > 1 && result[0] == '0')
    result.erase(0, 1);
  
  return result;
}

/*
 *The subtraction operator overloaded
 */
const big_integer big_integer::operator- (const big_integer & bigInt2) const
{
    big_integer difference = subtract_two_strings(s, bigInt2.s);

    return difference;
}

/*
 * Multiplies two integers stored in strings, building a string result.
 * The algorithm is long multiplication, starting with the most significant
 * digit of the multiplier.
 *
 * Note:  It is safe to modify the parameter objects below because they
 *   are local variables and local string instances.  They are not
 *   references.  I don't do that here this year, but you could change
 *   the number or multiplier as you go.  They're copies of whatever was
 *   passed in.
 * Author: Professor Peter Jensen
 */
std::string big_integer::multiply_two_strings (std::string number,std:: string multiplier) 
{
  // Perform long multiplication.  The result is the working sum and
  //   will be the product.  Do a small example on paper to see this
  //   algorithm work.

  std::string product = "0";

  // Loop through the digits of the multiplier in MSD to LSD order.

  for (int multiplier_pos = 0; multiplier_pos < multiplier.size(); multiplier_pos++)
  {
    // Multiply the product by 10.

    product.append("0");

    // Add in the correct number of copies of the number.  (Slow algorithm.)
    //   Notice that I count in ASCII.  ;)

    for (int i = '0'; i < multiplier[multiplier_pos]; i++)
      product = add_two_strings(product, number);
  }

  return product;
}

/*
 *The multiplication operator overloaded
 */
const big_integer big_integer::operator* (const big_integer & bigInt2) const
{
  big_integer product = multiply_two_strings(s, bigInt2.s);
  
  return product;
}

/*
 *Divides two integers stored in strings and builds the result as a string
 */
std::string big_integer::divide_two_strings(std::string left,std::string right)
{
  std::string divisor = right;
  std::string dividend = left;

  if (compare_two_strings(divisor, dividend)) // check to see if the divisor is greater than the dividend
  {
    return "0";
  }
  
  while (dividend.size() > 1 && dividend[0] == '0') // get rid of leading zeros for left string
  {
    dividend.erase(0, 1);
  }
  while (divisor.size() > 1 && divisor[0] == '0') // get rid of leading zeros for right string
  {
    divisor.erase(0, 1);
  }

  int j = 0; // variable for keeping track of where to start division
  int p = 0;// variable for keeping track of which index to begin at for looping through the remaining digits in the dividend
  std::string start; //a variable that stores the first spot where we need to begin division
  while (compare_two_strings(divisor, start))
  {
    start +=dividend[j++];
    p = j - 1;
  }

  std::string product; // variable that stores a product between divisor and mult_val for use in division
  std::string mult_val; // variable that stores the number of times a number goes into another number
  std::string quotient;
  while (p < dividend.length())
  {
    int count = 0; // variable that stores the number of times an integer goes into another number
    std::string start_original_val = start; // a variable for keeping track of where start began in order to do division properly
    start = add_two_strings(start, "1"); // increase start by 1 since we are removing 1 from count and then appending count to the final result
    while (compare_two_strings(start, "0"))
    {
      start = subtract_two_strings(start, divisor);
      count++;
    }
    count = count - 1; // this is to make sure that we do not accidently add one too many times to our count
    quotient = quotient + (char)(count + '0');
    mult_val = std::string(1,(char)(count+ '0'));
    product = multiply_two_strings(divisor, mult_val);
    start_original_val = subtract_two_strings(start_original_val, product);
    start_original_val += dividend[++p];
    start = start_original_val;
  }

  return quotient;
}

/*
 *The division operator overloaded
 */
const big_integer big_integer::operator/ (const big_integer & bigInt2) const
{
  big_integer quotient = divide_two_strings(s, bigInt2.s);
  
  return quotient;
}

/*
 * Computes the remainder when two integers stored in strings are divided and builds the result as a string
 */
std::string big_integer::mod_two_strings (std::string left,std::string right) 
{
  std::string remainder; // variable that stores the remainder 
  std::string quotient; // variable that stores the quotient for use in multiplication
  std::string product; // variable that stores the product for use in subtraction to calculate the remainder

  quotient = divide_two_strings(left, right);
  product = multiply_two_strings(quotient, right);
  remainder = subtract_two_strings(left, product);
  
  return remainder;
}

/*
 *The mod operator overloaded
 */
const big_integer big_integer::operator% (const big_integer & bigInt2) const
{
  big_integer remainder = mod_two_strings(s, bigInt2.s);
  return remainder;
}



