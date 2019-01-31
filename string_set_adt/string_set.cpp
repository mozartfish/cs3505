/* A 'string set' is defined as a set of strings stored
 * in a hashtable that uses chaining to resolve collisions.
 *
 * Peter Jensen
 * January 29, 2019
 */

#include "string_set.h"
#include "node.h"
#include <iostream>  // For debugging, if needed.
#include <string>
#include <vector>    // Needed for the assignment.

namespace cs3505
{
  /*******************************************************
   * string_set member function definitions
   ***************************************************** */
  
  /** Constructor:  The parameter indicates the
    *   size of the hashtable that should be used
    *   to keep this set.
    */
  string_set::string_set(int capacity)
  {
    // Set up a hashtable of the specified capacity.

    this->table = new node*[capacity];
    this->capacity = capacity;
    this->size = 0;

    // The array must be cleared -- it will have bogus values in it.
    //   (NULL means 'no linked list chain in this entry')

    for (int i = 0; i < capacity; i++)
      table[i] = NULL;
  }

  
  /** Copy constructor:  Initialize this set
    *   to contain exactly the same elements as
    *   another set.
    */
  string_set::string_set (const string_set & other)
  {
    // Give initial values to ensure the object is well-formed.

    table = NULL;
    size = 0;
    capacity = 0;

    // Use our assignment operator to complete this step.
    //   (Dereference this, then assign to that instance.)
 
    *this = other;
  }


  /** Destructor:  release any memory allocated
    *   for this object.
    */
  string_set::~string_set()
  {
    // Use a helper function to do all the work.

    clean();
  }


  /** Releases any memory that was allocated by
    *   this object.  This effectively destroys the
    *   set, so it should only be called if this object
    *   is destructing, or is being assigned.
    */
  void string_set::clean()
  {
    // Clean up the table (if any)

    if (table != NULL)
    {
      // Clean up (deallocate) any chains in the table.

      for (int i = 0; i < capacity; i++)
        if (table[i] != NULL)
	{
          delete table[i];
          table[i] = NULL;  // Not needed, but a good idea
        }

      // Release the table's memory.

      delete [] table;
    }

    // When 'this' object has been cleaned, it has no array.
    //   Set the fields appropriately.

    table = NULL;
    size = 0;
    capacity = 0;
  }


  /** Computes a table index for a given string.
    *   If two strings have the same contents, their
    *   hash code (table index) will be identical.
    * The hash code is guaranteed to be in the
    *   range [0..capacity).
    */  
  int string_set::hash (const std::string & s) const
  {
    // A well-known hash algorithm.  Do not change!!!

    long long hash = 0;
    for (int i = 0; i < s.length(); i++)
      hash = ((hash*2237) + s[i]) % capacity;

    return static_cast<int>(hash);
  }


  /** Adds the specified element to this set.  If the element
    *   is already in this set, no action is taken.
    */
  void string_set::add (const std::string & target)
  {
    // Determine which table entry chain might contain this string.

    int index = hash(target);

    // Walk the chain (the linked list).  Check each entry for the
    //   string.  If we find it, just bail out.  (No duplicates allowed.)

    node *current = table[index];
    while (current != NULL)
    {
      if (current->data == target)
        return;
      current = current->next;
    }

    // Make a new node, then link it in to the beginning of the chain.

    node *n = new node(target); // The node is created, but points nowhere.
    n->next = table[index];     // Point the node to the head node of the chain.
    table[index] = n;           // Point the head of the chain to our new node.
   
    // We added a string - count it.

    size++;
  }


  /** Removes the specified target element from this set.  If the
    *   target element is not in the set, no action is taken.
    */
  void string_set::remove (const std::string & target)
  {
    // Requirement:  When an element is removed, its
    //   enclosing node must be unlinked from that
    //   linked list, and then the node must be deleted
    //   to free up its memory.  The linked list and/or
    //   table must be appropriately updated.

    // To be completed as part of the assignment.
  }


  /** Returns true if the specified target element in in this set,
    *   false otherwise.
    */
  bool string_set::contains (const std::string & target) const
  {    
    // To be completed as part of the assignment.

    return false;  // Stub - update/change as needed.
  }


  /** Returns a count of the number of elements
    *   in this set.
    */
  int string_set::get_size() const
  {
    return this->size;
  }


  /*** Assignment operator ***/
  
  /** This function overloads the assignment operator.  It
    *   clears out this set, builds an empty table, and copies
    *   the entries from the right hand side (rhs) set into
    *   this set.
    */
  string_set & string_set::operator= (const string_set & rhs)
  {
    // If we are assigning this object to this object,
    //   do nothing.  (This is important!)

    if (this == &rhs)  // Compare addresses (not object contents)
      return *this;  // Do nothing if identical

    // Wipe away anything that is stored in this object.
    
    clean();
    
    // Create a new set (new table) and populate it with the entries
    //   from the set in rhs.  Use the capacity from rhs.  Hint:
    //   see the first constructor above (but you cannot call it).
    
    // Requirement:  Do not permanently point to arrays or nodes in rhs.  
    //   When rhs is destroyed, it will delete its array and nodes, 
    //   and we cannot count on their existence.  Instead, you will
    //   create a new array for this object, traverse rhs,
    //   and add one entry to this set for every entry in rhs.
    
    
    // To be completed as part of the assignment.
    

    // Done with assignment operator.

    return *this;
  }
}
