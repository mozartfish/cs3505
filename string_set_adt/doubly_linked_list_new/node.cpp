/* This node class is used to build linked lists for the
 * string_set class.
 *
 * Peter Jensen
 * January 29, 2019
 */

#include "node.h"

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

/**
 * Initialize the constructor and destructor counters
 */
long long cs3505::node::constructor_counter = 0;
long long cs3505::node::destructor_counter = 0;

/** Constructor:  Creates a node containing
  *   an element.  It is initialized to
  *   not point to any other node.
  */
cs3505::node::node(const std::string & s, string_set &set)
  : next(NULL),  // This syntax is used to call member variable constructors (or initialize them).
    fore(NULL),
    back(NULL),
    set_ref(set),
    data(s)      // This calls the copy constructor - we are making a copy of the string.
{
  // No other work needed - the initializers took care of everything.
  cs3505::node::constructor_counter++;
}

  
/** Destructor:  release any memory allocated
  *   for this object.
  */

cs3505::node::~node()
{
  // I'm not convinced that the recursive delete is the
  //   best approach.  I'll keep it (and you'll keep it too).

  cs3505::node::destructor_counter++;

  if (this->next != NULL)
    delete this->next;

  // Invalidate the entry so that it is not accidentally used.

  this->next = NULL;      
}

long long cs3505::node::node_get_constructor_count()
{
  return cs3505::node::constructor_counter;
}

long long cs3505::node:: node_get_destructor_count()
{
  return cs3505::node::destructor_counter;
}
