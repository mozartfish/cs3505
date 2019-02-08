/* This node class is used to build linked lists for the
 * string_set class.
 *
 * Peter Jensen
 * January 29, 2019
 */

#include "node.h"
#include "string_set.h"
// We're not in a namespace.  We are not in any class.  Symbols defined
//   here are globally available.  We need to qualify our function names
//   so that we are definining our cs3505::node class functions.
//
// Note that we could also use the namespace cs3505 { } block.  This would
//   eliminate one level of name qualification.  The 'using' statement will
//   not help in this situation.  
// 
// Keep it as shown here for node.cpp.  I show the other way in string_set.cpp.

/*******************************************************
 * node member function definitions
 ***************************************************** */

/** Constructor:  Creates a node containing
  *   an element.  It is initialized to
  *   not point to any other node.
  */
cs3505::node::node(const std::string & s, string_set & set)
  : next(NULL),  // This syntax is used to call member variable constructors (or initialize them).
    data(s)      // This calls the copy constructor - we are making a copy of the string.
{
  // No other work needed - the initializers took care of everything.
  set_pointer = & set;

  //CASE 1: We are entering the first element in the hash table
  if (set.head == NULL)
  {
    set.head = this;
    set.tail = this;
  }
  //CASE 2: We are entering more than one element into the hashtable
  else
  {
    set.tail->fore = this;
    this->back = set.tail;
   set.tail = this;
  }

}

  
/** Destructor:  release any memory allocated
  *   for this object.
  */
cs3505::node::~node()
{
  // I'm not convinced that the recursive delete is the
  //   best approach.  I'll keep it (and you'll keep it too).

  node * temp = NULL;
  //CASE 1: REMOVING THE HEAD OF THE DOUBLY LINKED LIST
  if (set_pointer->head == this)
  {
    temp = this->fore;
    temp->back = NULL;
    set_pointer->head = temp;
  }
  //CASE 2: REMOVING THE TAIL OF THE DOUBLY LINKED LIST
  else if (set_pointer->tail == this)
  {
    temp = this->fore;
    set_pointer->tail = temp;
  }
  //Remove a node from the doubly linked list
  else
  {
    this->back->fore = this->fore;
    this->fore->back = this->back;
  }

  if (this->next != NULL)
    delete this->next;

  // Invalidate the entry so that it is not accidentally used.

  this->next = NULL;      
}
