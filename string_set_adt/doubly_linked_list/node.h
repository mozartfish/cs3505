/* This node class is used to build linked lists for the
 * string_set class.
 *
 * Peter Jensen
 * January 29, 2019
 *
 *Pranav Rajan
 *February 4, 2019
 */

#ifndef NODE_H
#define NODE_H

#include <string>

namespace cs3505
{
  class string_set;
  // We're in a namespace - declarations will be within this namespace.
  //   (There are no definitions here.)

  /* Node class for holding elements. */
  
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
    node        *back;    // Variable to point to the previous node in the doubly linked list
  };
}

#endif
