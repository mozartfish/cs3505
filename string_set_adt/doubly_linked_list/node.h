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
	// (There are no definitions here.)
	/*Node class for holding elements. */
	
	class string_set; // forward declaration for the string_set class
	
	class node 
	{
		node (const std::string & data, string_set & set); // Copy constructor (changed to take a reference to avoid a copy)
		~node(); // Destructor
		std::string data; // variable to contain node data
		node *next; // Variable to point to the next node in the singly linked list
		node *fore; // Variable to point to the next node in the doubly linked list
		node *back; // Variable to point to the previous node in the doubly linked list
		string_set & string_ref; // Variable to hold the reference to the string_set reference
		
		public:
			static long long constructor_count(); // function for getting the number of times the constructor has been called
			static long long destructor_count(); // function for getting the number of times the destructor has been called
		
		private:
			static long long constructor_counter; // variable to keep track of the number of constructor calls
			static long long destructor_counter; // variable to keep track of the number of destructor calls
	};
}

#endif
