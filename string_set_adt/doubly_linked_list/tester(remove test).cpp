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
//Test 13: Test Add Functionality for the Doubly Linked List For a Small Set
    {
        cout << "Test 13: Tests the functionality of the add function for the doubly linked list for a small set." << endl;

        //create a new string_set with a hashtable containing 1000 spots
        cs3505::string_set string_set(1000);
        set<string> stl_set; // The built-in set class - no constructor parameters

    string_set.add("Live");
    string_set.add("Life");
    string_set.add("Elevated");
    string_set.add("Utah");

    stl_set.insert("Live");
    stl_set.insert("Life");
    stl_set.insert("Elevated");
    stl_set.insert("Utah");

    vector<string> string_set_elements = string_set.get_elements();
    vector<string>stl_set_elements;

    for (set<string>::iterator it = stl_set.begin(); it != stl_set.end(); it++)
    {
        string word = *it;
	stl_set_elements.push_back(word);
	// cout << word << endl;
    }

    for (int i = 0; i < stl_set_elements.size(); i++)
    {
      // cout <<"string_set_elements: The element at index " << i << " " << string_set_elements.at(i) << endl;
      // cout <<"st1_set_elements: The element at index " << i  << " " << stl_set_elements.at(i) << endl;
      
    }

    string_set.remove("Life");
    vector<string>set_elements = string_set.get_elements();
    
    for (int i = 0; i < set_elements.size(); i++)
    {
      cout <<"string_set_elements: The element at index " << i << " " << set_elements.at(i) << endl;
      // cout <<"st1_set_elements: The element at index " << i  << " " << stl_set_elements.at(i) << endl;
      
    }
    
    

    }
	

  return 0;
}
