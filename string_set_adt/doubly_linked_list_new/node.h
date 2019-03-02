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
  
  class node
  {
    friend class string_set;   // This allows functions in string_set to access
			       //   private data (and constructor) within this class.
 
    private:
      node(const std::string & data);  // Constructor (changed to take a reference to avoid a copy)
      ~node();                         // Destructor
      std::string data;     // Variable to hold the element
      node *next;    // Variable to point to the next node in the list

	public:
		static long long constructor_count(); // returns the number of calls to the node constructor
		static long long destructor_count(); // returns the number of calls to the node destructor_count
	
	private:
		static long long constructor_counter; // counter for keeping track of the number of calls to the node constructor
		static long long destructor_counter; // counter for keeping track of the number of calls to the node destructor
  };
}

#endif
