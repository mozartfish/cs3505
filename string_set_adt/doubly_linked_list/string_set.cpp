/* A 'string set' is defined as a set of strings stored
 * in a hashtable that uses chaining to resolve collisions.
 *
 * Authors: Pranav Rajan and Professor Peter Jensen
 * Version 1.0
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
    * Author: Professor Peter Jensen
    */
  string_set::string_set(int capacity)
  {
    // Set up a hashtable of the specified capacity.

    this->table = new node*[capacity];
    this->capacity = capacity;
    this->size = 0;
    this->head = NULL;
    this->tail = NULL;

    // The array must be cleared -- it will have bogus values in it.
    //   (NULL means 'no linked list chain in this entry')

    for (int i = 0; i < capacity; i++)
      table[i] = NULL;
  }

  
  /** Copy constructor:  Initialize this set
    *   to contain exactly the same elements as
    *   another set.
    * Author: Professor Peter Jensen
    */
  string_set::string_set (const string_set & other)
  {
    // Give initial values to ensure the object is well-formed.

    table = NULL;
    size = 0;
    capacity = 0;
    head = NULL;
    tail = NULL;

    // Use our assignment operator to complete this step.
    //   (Dereference this, then assign to that instance.)
 
    *this = other;
  }


  /** Destructor:  release any memory allocated
    *   for this object.
    * Author: Professor Peter Jensen
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
    * Author: Professor Peter Jensen
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
    * Authors: Professor Peter Jensen and some really smart computer scientists
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
    * Author: Professor Peter Jensen
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

    node *n = new node(target, *this); // The node is created, but points nowhere.
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

   // Determine which table entry chain might contain this string.

    int index = hash(target);


    node *previous = NULL; // declare a pointer to keep track of the previous node
    node *current = table[index]; // declare a pointer to keep track of the current node
    while (current != NULL)
    {
      if (current->data == target)
      {
	//CASE 1: REMOVE THE FIRST NODE IN THE LINKED LIST
	if (previous == NULL)
	{
	 node *temp = current->next; // set a temp node to the node that next to points to for the current node
	  delete current; // delete the current node
	  table[index] = temp; // have the table index now point to  the temp node
	}
	
	//CASE 2: REMOVE THE LAST NODE IN THE LINKED LIST
	else if (current->next == NULL)
	{
	  previous->next = NULL; // since previous points to the node before current we can point it to null
	  delete current; // delete the current node to release memory
	}
	
	//CASE 3: REMOVE A NODE IN THE MIDDLE OF THE LINKED LIST
	else
	{
	  node *temp = current->next; // set temp to the node that next points to for the current node;
	  delete current; // delete the current node
	  previous->next = temp; // since previous points to the node before current we can point it to temp
	}
	return;
      }
      previous = current;
      current = current->next;
    }
 

  }


  /** Returns true if the specified target element in in this set,
    *   false otherwise.
    * Authors:Pranav Rajan and Professor Peter Jensen
    */
  bool string_set::contains (const std::string & target) const
  {
    // Determine which table entry chain might contain this string.

    int index = hash(target);

    // Walk the chain (the linked list).  Check each entry for the
    //   string.  If we find it, just bail out.  (No duplicates allowed.)

    node *current = table[index];
    while (current != NULL)
    {
      if (current->data == target)
        return true;
      current = current->next;
    }

    return false;
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
    * Authors: Pranav Rajan and Professor Peter Jensen
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

     // Set up a hashtable of the specified capacity.

    this->table = new node*[rhs.capacity];
    this->capacity = rhs.capacity;
    this->size = 0;

    // The array must be cleared -- it will have bogus values in it.
    //   (NULL means 'no linked list chain in this entry')

    for (int i = 0; i < capacity; i++)
      table[i] = NULL;

    //populate the new table
    for (int i = 0; i < capacity; i++)
    {
      node *current = rhs.table[i];
      while (current != NULL)
      {
	add(current->data);
	current = current->next;
      }
    }
    
    return *this;
  }

/** This function populates and returns a std::vector<std::string>
    * with all the elements in this set.  The strings in the vector will be in the
    * order that they were inserted into to this set, v[0] was added first, etc.
    * (Note:  Attempting to add a duplicate string does not count or
    * change this ordering.)
    * The size of the return vector will be the size of this string_set.
    */
  std::vector<std::string> string_set::get_elements() const
  {
    std::vector<std::string>elements;
    node *current = head;
    while (current != NULL)
    {
      elements.push_back(current->data);
      current = current->fore;
    }
    
    return elements;
}

}
