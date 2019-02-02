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
 * Peter Jensen
 * January 29, 2019
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

  // Open up another block.  This way, when the block ends,
  // variables local to the block will be destroyed, but main
  // will still be running.  (Did you know that you can open
  // up a block at any time to control local variable scope and
  // lifetime?)
  
  {
    // Create the two sets.  Declaring the local variables constructs the objects.
  
    set<string>         stl_set;  // The built-in set class - no constructor parameters.

    cs3505::string_set  our_set(1000);  // Our set class, with a hashtable of 1000 slots.
  
    // Open the file stream for reading.  (We'll be able to use it just like
    //   the keyboard stream 'cin'.)

    ifstream in("Yankee.txt");

    // Loop for reading the file.  Note that it is controlled
    //   from within the loop (see the 'break').
    
    while (true)
    {
      // Read a word (don't worry about punctuation)
      
      string word;
      in >> word;

      // If the read failed, we're probably at end of file
      //   (or else the disk went bad).  Exit the loop.
      
      if (in.fail())
	break;

      // Word successfully read.  Add it to both sets.
      
      stl_set.insert(word);
      our_set.add(word);
    }

    // Close the file.

    in.close();

    // Print out all the words in the reference solution.

    for (set<string>::iterator it = stl_set.begin(); it != stl_set.end(); it++)
    {
      string word = *it;
      cout << word << endl;
    }

    // Print out the number of words found in each set.

    cout << "STL set contains " << stl_set.size() << " unique words.\n";
    cout << "Our set contains " << our_set.get_size() << " unique words.\n"; 
    
    // Done.  Notice that this code block ends below.  Any local
    // variables declared within this block will be automatically
    // destroyed.  Local objects will have their destructors
    // called.  (Blocks are great for controlling scope/lifetime.)
  }

  //Test 01: Test Contains Functionality
  {
    cout << "Test 01: Tests the functionality of the contains helper method with a set that contains an element" << endl;

    //create a new string_set with a hashtable containing 1000 slots
    cs3505::string_set contains_set(1000);

    contains_set.add("Live");
    contains_set.add("Life");
    contains_set.add("Elevated");
    contains_set.add("Utah");
    
    string p = "Utah";
    ok = contains_set.contains(p);
    
    if (ok)
    {
      cout << "Test 01 passed" << endl;;
    }
    else
    {
      cout << "Test 01 failed. Expected the set to contain " << p  << endl;
    }
  }
   //Test 02: Test Contains Functionality
  {
    cout << "Test 02: Tests the functionality of the contains helper method with a set that does not contain an element" << endl;

    //create a new string_set with a hashtable containing 1000 slots
    cs3505::string_set contains_set(1000);

    contains_set.add("Live");
    contains_set.add("Life");
    contains_set.add("Elevated");
    contains_set.add("Utah");
    
    string p = "hello";
    ok = contains_set.contains(p);
    
    
    if (ok == false)
    {
      cout << "Test 02 passed" << endl;;
    }
    else
    {
      cout << "Test 02 failed. Expected the set to not contain " << p  << endl;
    }
  }

  //Test 03: Test Size functionality
  {
    cout << "Test 03: Tests the functionality of the size function to determine whether the set contains "
	 << "the correct number of elements" << endl;
    //create a new string_set with a hashtable containing 1000 slots
    cs3505::string_set size_set(1000);
    size_set.add("Live");
    size_set.add("Life");
    size_set.add("Elevated");
    size_set.add("Utah");
    
    ok = (size_set.get_size() == 4);
    
    
    if (ok)
    {
      cout << "Test 03 passed" << endl;;
    }
    else
    {
      cout << "Test 03 failed. Expected the size to be " << size_set.get_size() << endl;
    }
  }




 

  

  // I really should test here to make sure that memory got cleaned up (that the
  // nodes and tables were deleted appropriately).  There is no such test here.
  // It's simple to construct a test that counts objects:
  //   Add a public static int variable to each class declaration
  //   Add corresponding static int definitions to the .cpp file, set the variable to 0
  //   An each constructor, increment once
  //   An each destructor, decrement once
  //   Check counts here to make sure every created object has been destroyed.
  
  return 0;
}
