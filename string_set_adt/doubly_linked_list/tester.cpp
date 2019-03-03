/*
 * This is a tester that I started to write in class.  It reads
 * words from a text file, then adds the words to two sets: A built-in
 * set class, and our string_set class.  After reading the file, it
 * prints out all the words stored in the STL set object.  At the end
 * of the test, it prints out the sizes of both sets to see that they
 * are the same.
 *
 *
 * If the comments wrap lines, widen your emacs window.
 *
 * Professor Peter Jensen
 * January 29, 2019
 * Version 1.0
 *
 *
 * This is a testing testing program to test the functionality of the string_set.
 * Added in more tests for the cases that Professor Peter Jensen did not address with his original tester
 * Author: Pranav Rajan
 * Version 1.1
 */

#include <iostream>
#include <fstream>
#include <set>
#include <iterator>
#include "string_set.h"
#include "node.h"

// For convenience only:

using namespace std;

// Note:  Our classes were declared in a cs3505 namepsace.
//        Instead of 'using namespace cs3505', I qualified the class names 
//        below with cs3505::
//        I did this for clarity.

int main ()
{
  bool ok = true;

// Note:  Our classes were declared in a cs3505 namepsace.
//        Instead of 'using namespace cs3505', I qualified the class names 
//        below with cs3505::
//        I did this for clarity.



 //Test 13: Test the Remove Function and get_elements
  {
    cout << "Test 13: Tests the functionality of the remove function and get_elements when removing the head node." << endl;

    //create a new string_set with a hashtable containing 1000 spots
    cs3505::string_set contains_set(1000);
    contains_set.add("Live");
    contains_set.add("Life");
    contains_set.add("Elevated");
    contains_set.add("Utah");

    contains_set.remove("Live");
        
    vector<string>set_elements = contains_set.get_elements();
    
    for (int i = 0; i < set_elements.size(); i++)
    {
      cout <<"string_set_elements: The element at index " << i << " " << set_elements.at(i) << endl;
    }

    ok = contains_set.contains("Live");
    if (!ok)
    {
      cout << "Test 13 passed" << endl;
    }
    else
    {
      cout << "Test 13 failed. Expected the set to not contain " << "Live" << endl;
    }


 //Test 14: Test the Remove Function and get_elements
  {
    cout << "Test 14: Tests the functionality of the remove function and get_elements when removing the tail node." << endl;

    //create a new string_set with a hashtable containing 1000 spots
    cs3505::string_set contains_set(1000);
    contains_set.add("Live");
    contains_set.add("Life");
    contains_set.add("Elevated");
    contains_set.add("Utah");

    contains_set.remove("Utah");
        
    vector<string>set_elements = contains_set.get_elements();
    
    for (int i = 0; i < set_elements.size(); i++)
    {
      cout <<"string_set_elements: The element at index " << i << " " << set_elements.at(i) << endl;
    }

    ok = contains_set.contains("Utah");
    if (!ok)
    {
      cout << "Test 14 passed" << endl;
    }
    else
    {
      cout << "Test 14 failed. Expected the set to not contain " << "Utah" << endl;
    }
  }


 //Test 15: Test the Remove Function and get_elements
  {
    cout << "Test 15: Tests the functionality of the remove function and get_elements when removing a node from the middle of the linked list." << endl;

    //create a new string_set with a hashtable containing 1000 spots
    cs3505::string_set contains_set(1000);
    contains_set.add("Live");
    contains_set.add("Life");
    contains_set.add("Elevated");
    contains_set.add("Utah");

    contains_set.remove("Elevated");
        
    vector<string>set_elements = contains_set.get_elements();
    
    for (int i = 0; i < set_elements.size(); i++)
    {
      cout <<"string_set_elements: The element at index " << i << " " << set_elements.at(i) << endl;
    }

    ok = contains_set.contains("Elevated");
    if (!ok)
    {
      cout << "Test 15 passed" << endl;
    }
    else
    {
      cout << "Test 15 failed. Expected the set to not contain " << "Elevated" << endl;
    }
  }

 }

 
 return 0;
}
