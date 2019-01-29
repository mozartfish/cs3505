/*Header file that specifies the functions and internal structure for big_integer objects
 *
 *Version 1.0
 *Author:Pranav Rajan
 *Date: January 23, 2019
 */

 #include <string>

 #ifndef BIG_INTEGER_H
 #define BIG_INTEGER_H

 class big_integer 
 {
     private:
     std::string s; // the internal representation of an integer for a big_integer object
     static bool compare_two_strings (const std::string left, const std::string right);
     static std::string add_two_strings (std::string left, std::string right);
     static std::string subtract_two_strings (std::string left, std::string right);
     static std::string multiply_two_strings (std::string left,std::string right);
     static std::string divide_two_strings (std::string left, std::string right);
     static std::string mod_two_strings (std::string left, std::string right);
     
     public:
     big_integer ();
     big_integer (std::string s); 
     big_integer (const big_integer &bigInt);
     std::string get_value() const;
     big_integer &     operator= (const big_integer & bigInt);
     const big_integer operator+ (const big_integer & bigInt) const;
     const big_integer operator- (const big_integer & bigInt) const;
     const big_integer operator* (const big_integer & bigInt) const;
     const big_integer operator/ (const big_integer & bigInt) const;
     const big_integer operator% (const big_integer & bigInt) const; 
 };
 #endif
