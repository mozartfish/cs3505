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
        cout << "Test 01: Tests the functionality of the contains function with a set that contains an element" << endl;

        //create a new string_set with a hashtable containing 1000 spots
        cs3505::string_set contains_set(1000);
        contains_set.add("Live");
        contains_set.add("Life");
        contains_set.add("Elevated");
        contains_set.add("Utah");

        string p = "Utah";

        ok = contains_set.contains(p);

        if (ok)
        {
            cout << "Test 01 passed" << endl;
        }
        else
        {
            cout << "Test 01 failed. Expected the set to contain " << p << endl;
        }
    }
    
    //Test 02: Test Contains Functionality
    {
        cout << "Test 02: Tests the functionality of the contains function with a set that does not contain an element" << endl;

        //create a new string_set with a hashtable containing 1000 spots
        cs3505::string_set contains_set(1000);
        contains_set.add("Live");
        contains_set.add("Life");
        contains_set.add("Elevated");
        contains_set.add("Utah");

        string p = "hello";

        ok = contains_set.contains(p);

        if (!ok)
        {
            cout << "Test 02 passed" << endl;
        }
        else
        {
            cout << "Test 02 failed. Expected the set to not contain " << p << endl;
        }
    }
    
    //Test 03: Test Contains Functionality
    {
        cout << "Test 03: Tests the functionality of the contains function using Yankee.txt" << endl;

        set<string> stl_set; // The built-in set class - no constructor parameters
        cs3505::string_set contains_set(1000);

        ifstream contain_add("Yankee.txt");

        while (true)
        {
            string word;
           contain_add >> word;

            if (contain_add.fail())
            {
                break;
            }
            
            contains_set.add(word);
            stl_set.insert(word);
        }

       contain_add.close();

        ifstream contain_contains("Yankee.txt");

        while (true)
        {
            string word;
            contain_contains >> word;

            if (contain_contains.fail())
            {
                break;
            }
            
            ok = contains_set.contains(word);

            if (!ok)
            {
                break;
            }
        }

        contain_contains.close();

        if (ok)
        {
            cout << "Test 03 passed" << endl;
        }

        if (!ok)
        {
            cout << "Test 03 failed. Expected the contains_set to contain all the words in stl_set" << endl;

            for (set<string>::iterator it = stl_set.begin(); it != stl_set.end(); it++)
            {
                string word = *it;
                cout << word << endl;
            }
        }
    }

    //Test 04: Test get_size() Functionality
    {
        cout << "Test 04: Tests the functionality of the get_size() function with a small set" << endl;

        //create a new string_set with a hashtable containing 1000 spots
        cs3505::string_set size_set(1000);
        size_set.add("Live");
        size_set.add("Life");
        size_set.add("Elevated");
        size_set.add("Utah");

        ok = (size_set.get_size() == 4);

        if (ok)
        {
            cout << "Test 04 passed" << endl;
        }
        else
        {
            cout << "Test 04 failed. Expected the set to have size 4." << endl;
            cout <<"Actual size was " << size_set.get_size() << endl;
        }
    }

    //Test 05: Test get_size() Functionality
    {
        cout << "Test 05: Tests the functionality of the get_size() function using Yankee.txt" << endl;

        set<string> stl_set; // The built-in set class - no constructor parameters
        cs3505::string_set size_set(1000);

        ifstream in("Yankee.txt");

        while (true)
        {
            string word;
            in >> word;

            if (in.fail())
            {
                break;
            }
            
            size_set.add(word);
            stl_set.insert(word);
        }

        in.close();

        
        ok = (stl_set.size() == size_set.get_size());

        if (ok)
        {
	  cout << "Test 05 passed" << endl;
        }
        else
        {
            cout << "Test 05 failed. Expected size_set to have the same size as stl_set." << endl;
            cout <<"Actual size of size_set was " << size_set.get_size() << endl;
            cout << "Actual size of stl_set was " << stl_set.size() << endl;
        }
    }
    
    //Test 06: Test Remove Functionality
    {
        cout << "Test 06: Tests the functionality of the remove function with a small set" << endl;

        //create a new string_set with a hashtable containing 1000 spots
        cs3505::string_set remove_set(1000);
        
        remove_set.add("Live");
        remove_set.add("Life");
        remove_set.add("Elevated");
        remove_set.add("Utah");

        remove_set.remove("Live");
        remove_set.remove("Life");
        remove_set.remove("Elevated");       
        remove_set.remove("Utah");

        ok = (remove_set.get_size() == 0);

        if (ok)
        {
            cout << "Test 06 passed" << endl;
        }
        else
        {
            cout << "Test 06 failed. Expected the set to have size 0." << endl;
            cout <<"Actual size was " << remove_set.get_size() << endl;
        }
    }

    //Test 07: Test Remove Functionality
    {
        cout << "Test 07: Tests the functionality of the remove function using Yankee.txt" << endl;

        cs3505::string_set remove_set(1000);
	set<string> stl_set; // The built-in set class - no constructor parameters

        ifstream remove_add("Yankee.txt");

        while (true)
        {
            string word;
            remove_add >> word;

            if (remove_add.fail())
            {
                break;
            }
            
            remove_set.add(word);
	    stl_set.insert(word);
        }

        remove_add.close();
	//cout << remove_set.get_size() << endl;
	//cout << stl_set.size() << endl;

        ifstream remove_remove("Yankee.txt");

        while (true)
        {
            string word;
            remove_remove >> word;

            if (remove_remove.fail())
            {
                break;
            }
            
            remove_set.remove(word);
        }

        remove_remove.close();

        ok = (remove_set.get_size() == 0);

        if (ok)
        {
            cout << "Test 07 passed" << endl;
        }
        else
        {
            cout << "Test 07 failed. Expected the set to have a size of zero" << endl;
            cout << "Actual size of the set was " << remove_set.get_size() << endl;
        }
    }

    //Test 08: Test Assignment Operator Functionality
    {
        cout << "Test 08: Tests the functionality of the overriden operator = with a small set" << endl;

        //create a new string_set with a hashtable containing 1000 spots
        cs3505::string_set string_set(1000);
        
        string_set.add("Live");
        string_set.add("Life");
        string_set.add("Elevated");
        string_set.add("Utah");

        cs3505::string_set copy_set = string_set;

        ok = (string_set.get_size() == copy_set.get_size());

        if (ok)
        {
            cout << "Test 08 passed" << endl;
        }
        else
        {
            cout << "Test 08 failed. Expected the copy set to have a size of 4." << endl;
            cout << "Actual size of copy set was " << copy_set.get_size() << endl;
            cout << "Actual size of original set was " << string_set.get_size() << endl;
        }
    }

   //Test 09: Test Assignment Operator Functionality
   //Author: Professor Peter Jensen
  // Open up another block.  This way, when the block ends,
  // variables local to the block will be destroyed, but main
  // will still be running.  (Did you know that you can open
  // up a block at any time to control local variable scope and
  // lifetime?)
  {
      cout << "Test 09: Tests the functionality of overriden operator = using Professor Peter Jensen Sample Test Case" << endl;
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

     cs3505::string_set copy_set = our_set;

     ok = (copy_set.get_size() == stl_set.size());

     if (ok)
     {
         cout << "Test 09 passed" << endl;
     }
     else
     {
         cout << "Test 09 failed. Expected copy_set size to have the same size as stl_set" << endl;
         cout <<"Actual size of copy_set was " << copy_set.get_size() << endl;
         cout << "Actual size of stl_set was " << stl_set.size() << endl;
     }
  }

    //Test 10: Test Remove Functionality
    {
        cout << "Test 10: Tests the functionality of the remove function with a small set when the set does not "
             << "contain the element we want to remove" << endl;

        //create a new string_set with a hashtable containing 1000 spots
        cs3505::string_set remove_set(1000);
        
        remove_set.add("Live");
        remove_set.add("Life");
        remove_set.add("Elevated");
        remove_set.add("Utah");

        remove_set.remove("hello");

        ok = (remove_set.get_size() == 4);

        if (ok)
        {
            cout << "Test 10 passed" << endl;
        }
        else
        {
            cout << "Test 10 failed. Expected the set to have size 4." << endl;
            cout <<"Actual size was " << remove_set.get_size() << endl;
        }
    }

    //Test 11: Test Copy Constructor Functionality
    {
        cout << "Test 11: Tests the functionality of the copy constructor using a small set." << endl;

        //create a new string_set with a hashtable containing 1000 spots
        cs3505::string_set string_set(1000);

	string_set.add("Live");
	string_set.add("Life");
	string_set.add("Elevated");
	string_set.add("Utah");
	
	cs3505::string_set copy_set(string_set);
	
	ok = (copy_set.get_size() == string_set.get_size());
	
	if(ok)
	{
	  cout << "Test 11 passed" << endl;
	}
        else
        {
	  cout << "Test 11 failed. Assumed copy_set would have a size of 4." << endl;
	  cout << "Actual size of string_set: " << string_set.get_size() << endl;
	  cout << "Actual size of copy_set: " << copy_set.get_size() << endl;
        }
    }

  //Test 12: Test Assignment Operator Functionality
   //Author: Professor Peter Jensen
  // Open up another block.  This way, when the block ends,
  // variables local to the block will be destroyed, but main
  // will still be running.  (Did you know that you can open
  // up a block at any time to control local variable scope and
  // lifetime?)
  {
      cout << "Test 12: Tests the functionality of the copy constructor using Professor Peter Jensen Sample Test Case" << endl;
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

    cs3505::string_set copy_set(our_set);

     ok = (copy_set.get_size() == stl_set.size());

     if (ok)
     {
         cout << "Test 12 passed" << endl;
     }
     else
     {
         cout << "Test 12 failed. Expected copy_set size to have the same size as stl_set" << endl;
         cout <<"Actual size of copy_set was " << copy_set.get_size() << endl;
         cout << "Actual size of stl_set was " << stl_set.size() << endl;
     }
  }

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
        stl_elements.push_back(word);
        //cout << word << endl;
    }

    for (int i = 0; i < stl_set_elements.size(); i++)
    {
        if (!string_set_elements.at(i) == stl_set_elements.at(i))
        {
            ok = false;
        }
    }
	
	if(ok)
	{
	  cout << "Test 13 passed" << endl;
	}
        else
        {
	  cout << "Test 13 failed. Assumed string_set_elements and stl_set_elements had the same elements in the same order and the same size." << endl;
	  cout << "Actual size of string_set_elements: " << string_set.size() << endl;
	  cout << "Actual size of stl_set_elements: " << stl_set_elements.size() << endl;
      cout <<"The contents for string_set_elements" << endl;
      for (int j = 0; j < string_set_elements.size(); j++)
      {
          cout << string_set_elements.at(j) << endl;
      }
      cout << "The contents for stl_set_elements" << endl;
      for (int k =0; k < stl_set_elements; k++)
      {
          cout << stl_set_elements.at(k) << endl;
      } 
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
