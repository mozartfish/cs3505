/* This node class is used to build linked lists for the
 * string_set class.
 *
 * Peter Jensen
 * January 29, 2019
 */

#ifndef NODE_H
#define NODE_H

#include <string>

namespace cs3505
{
  // We're in a namespace - declarations will be within this namespace.
  //   (There are no definitions here.)

  /* Node class for holding elements. */

  class string_set; //forward declare the string_set

  class node
  {
    friend class string_set;   // This allows functions in string_set to access
			       //   private data (and constructor) within this class.
 
    private:
    node(const std::string & data, string_set &set);  // Constructor (changed to take a reference to avoid a copy)
      ~node();                         // Destructor
      std::string data;     // Variable to hold the element
      node        *next;    // Variable to point to the next node in the list
    node *fore; // Variable to point to the next node in the doubly linked list
    node *back; // Variable to point to the previous node in the doubly linked list
     static long long constructor_counter; // Counter for keeping track of the number of constructor calls
     static long long destructor_counter; // Destructor for keeping track of the number of destructor calls
    string_set &set_ref; // Variable to hold a reference to the set

    public:
     static long long node_get_constructor_count(); // Returns the number of times that the constructor has been called
     static long long node_get_destructor_count(); // Returns the number of times the destructor has been called
  };
}

#endif
