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

  class string_set; // forward declaration for the string_set class
  
  class node
  {
    friend class string_set;   // This allows functions in string_set to access
			       //   private data (and constructor) within this class.
 
    private:
    node(const std::string & data, string_set & set);  // Constructor (changed to take a reference to avoid a copy)
      ~node();                         // Destructor

      std::string data;     // Variable to hold the element
      node        *next;    // Variable to point to the next node in the list
     node        *fore;     // Variable to point to the next node in the doubly linked list
    node *back; // Variable to point to the previous node in the doubly linked list
    string_set & string_ref; // A variable to hold the string_set reference
  };
}

#endif
