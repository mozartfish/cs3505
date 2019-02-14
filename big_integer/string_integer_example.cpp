/* Peter Jensen
 * January 16, 2019
 *
 * An example of addition and multiplication algorithms
 * for unsigned large integers stored in strings.  The algorithms below
 * may be used as a starting point for your code, but it is up to
 * you to make sure they work in all cases.  Note:  This is not robust.
 * Care should be taken to ensure that the strings only have numeric
 * digits within them.
 *
 * If you'd like to see how the algorithms work, add some cout statements
 * to them.  (That is the primary reason for using strings for integer
 * storage, they're easy to print out in the middle of an algorithm.  You'd
 * normally use arrays of ints and base 2^32 digits for big integers.)
 */

#include <iostream>  // If you don't print out anything, don't bother with this
#include <string>    // Sometimes all you need to import is this one

// The following is a convenience.  Otherwise, we'd have to qualify all
//   of the std library identifiers like this:  std::string or std::cout
// Note:  Never say 'using namespace' in a .h file.  Qualify your
//   identifiers instead.  Ask about this in class.

using namespace std;

// Forward declarations - everything must be declared before it is used.

string add_two_strings (string left, string right);
string multiply_two_strings (string left, string right);

// Main - the application entry point
int main ()
{
  // A quick test or two.  I've specifically left this testing
  //   woefully incomplete.  Students should test their own code.
  
  cout << "Hello" << endl;

  cout << multiply_two_strings("9389475933475987349857983453", "837948759837459879387983749875983487") << endl;

  cout << multiply_two_strings("214", "9870") << endl;

  // Inform the shell that the program terminated without errors by
  //   returning a 0.  (We don't make use of this error code.)
  
  return 0;
}

/*
 * Adds two integers stored in strings, building a string result.
 */
string add_two_strings (string left, string right)
{
  // Start with an empty string, then build up a string to contain the result.
  
  string result = "";

  // We'll go through digits right-to-left, so start at the end.

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
 * Multiplies two integers stored in strings, building a string result.
 * The algorithm is long multiplication, starting with the most significant
 * digit of the multiplier.
 *
 * Note:  It is safe to modify the parameter objects below because they
 *   are local variables and local string instances.  They are not
 *   references.  I don't do that here this year, but you could change
 *   the number or multiplier as you go.  They're copies of whatever was
 *   passed in.
 */
string multiply_two_strings (string number, string multiplier)
{
  // Perform long multiplication.  The result is the working sum and
  //   will be the product.  Do a small example on paper to see this
  //   algorithm work.

  string product = "0";

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

// Other really useful helper functions you will want to write

//is_bigger (a, b)
//subtract (a, b)
//divide (a, b)
//mod (a, b)

