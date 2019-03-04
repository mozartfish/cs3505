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
  class string_set;
  //TEST 01: THE MOST BASIC TEST
  {
    cs3505::string_set set(1000);
    ifstream in("Yankee.txt");
    while (true)
    {
      string word;
      in >> word;
      if (in.fail())
      {
	break;
      }
      set.add(word);
    }
    in.close();
    // cout << "Sets created : " << cs3505::string_set::get_set_constructor_count() << endl;
    // cout << "Nodes created: " << cs3505::node::node_get_constructor_count() << endl;
    vector<string> elements = set.get_elements();
    for (int i = 0; i < elements.size(); i++)
    {
      // set.remove(elements.at(i));
    }
    // cout << "Nodes deleted: " << cs3505::node::node_get_destructor_count() << endl;
  }
  
  cout << "Sets created : " << cs3505::string_set::get_set_constructor_count() << endl;
  cout << "Sets deleted: " << cs3505::string_set::get_set_destructor_count() << endl;
  cout << "Nodes created: " << cs3505::node::node_get_constructor_count() << endl;
  cout << "Nodes deleted: " << cs3505::node::node_get_destructor_count() << endl;
  return 0;
}
