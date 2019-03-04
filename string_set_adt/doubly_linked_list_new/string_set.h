/* A 'string set' is defined as a set of strings stored
 * in a hashtable that uses chaining to resolve collisions.
 *
 * Peter Jensen
 * January 29, 2019
 */

#ifndef STRING_SET_H
#define STRING_SET_H

#include "node.h"
#include <vector>

namespace cs3505
{

  class string_set
    {
      // Default visibility is private.

      node** table;  // The hashtable, a pointer to a node pointer
                     //   (which will really be an array of node pointers)
      int capacity;  // The size of the hashtable array
      int size;      // The number of elements in the set

    public:
      string_set(int capacity = 100);        // Constructor.  Notice the default parameter value.
      string_set(const string_set & other);  // Copy constructor
      ~string_set();                         // Destructor

      void add      (const std::string & target);        // Not const - modifies the object
      void remove   (const std::string & target);        // Not const - modifies the object
      bool contains (const std::string & target) const;  // Const - does not change the object
      int  get_size () const;                            // Const - does not change object

      string_set & operator= (const string_set & rhs);   // Not const - modifies this object
      std::vector<std::string> get_elements() const; // Const - does not change the object
      static long long get_set_constructor_count(); // Returns the number of times that the set constructor is called
      static long long get_set_destructor_count(); // Returns the number of times that the set destructor is called
      

    private:
      int  hash (const std::string & s) const;           // Const - does not change this object
      void clean ();                                     // Not const - modifies the object
      static long long constructor_counter; // COunter for keeping track of the number of calls to the set constructor
      static long long destructor_counter; // COunter for keeping track of the number of calls to the set destructor
  };

}

#endif
