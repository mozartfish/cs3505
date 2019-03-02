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
    fore(NULL),
    back(NULL),
    string_ref(set),
    data(s)      // This calls the copy constructor - we are making a copy of the string.
{
  // No other work needed - the initializers took care of everything.


  //CASE 1: ADDING THE VERY FIRST ELEMENT INTO THE HASHTABLE
  if (string_ref.head == NULL)
  {
    string_ref.head = this;
    string_ref.head->back = NULL;
    string_ref.tail = this;
    string_ref.tail->fore = NULL;
  }
  //CASE 2: ADDING MORE ELEMENTS AFTER THE FIRST ELEMENT
  else
  {
    string_ref.tail->fore = this;
    this->back = string_ref.tail;
    set.tail = this;
    string_ref.tail->fore = NULL;
  }
}

  
/** Destructor:  release any memory allocated
  *   for this object.
  */
cs3505::node::~node()
{
  // I'm not convinced that the recursive delete is the
  //   best approach.  I'll keep it (and you'll keep it too).

  //CASE 1: THERE IS ONLY 1 ELEMENT IN THE HASHTABLE
  if (string_ref.get_size() == 1)
  {
    string_ref.head->fore = NULL;
    string_ref.head->back = NULL;
    string_ref.head = NULL;
    string_ref.tail->fore = NULL;
    string_ref.tail = NULL;
  }
  //CASE 2: REMOVING THE HEAD NODE OF THE DOUBLY LINKED LIST
  else if (string_ref.head == this)
  {
    node *temp = string_ref.head->fore;
    temp->back = NULL;
    string_ref.head = temp;
  }
  //CASE 3: REMOVING THE TAIL NODE OF THE DOUBLY LINKED LIST
  else if (string_ref.tail == this)
  {
    node *temp = string_ref.tail->back;
    temp->fore = NULL;
    string_ref.tail = temp;
  }
  //CASE 4: WHEN THERE ARE NO MORE ELEMENTS IN THE SET
  else if (string_ref.get_size() == 0)
  {
    string_ref.head->fore = NULL;
    string_ref.head->back = NULL;
    string_ref.head = NULL;
    string_ref.tail->fore = NULL;
    string_ref.tail = NULL;
  }
  //CASE 5: REMOVING A NODE FROM THE MIDDLE OF THE LINKED LIST
  else
  {
    this->back->fore = this->fore;
    this->fore->back = this->back;
  }
  string_ref.size--;

  if (this->next != NULL)
    delete this->next;

  // Invalidate the entry so that it is not accidentally used.

  this->next = NULL;      
}
