/*
 * Assignment 04 -- An exploration of polymorphism in multiple
 * inheritance.  This code is instrumented to allow the user to see
 * function calls as they happen.  
 *
 * Students need to supply the missing class declarations, constructors,
 * and destructors, as well as any missing or otherwise required functions.
 * When you're done, the output should match the sample output --exactly--.
 * 
 * Find the TODO: comments, and replace them with the relevant code.  Do not
 * make changes to existing code (unless there is a TODO comment).
 *
 * Note that while this code is motivated by a particular problem, 
 * much of the functionality is missing.  Students should not try to 
 * implement observer functionality or remote connections.
 *
 * Additionally, while you can make multiple inheritance compile, its much
 * tougher to make it work properly.  Students should not fix the 
 * deficient design here.  Get the code to compile and match the given
 * design.  Later, you will describe possible fixes in essay questions.
 *
 * Peter Jensen  // TODO -- change this or lose a point.
 * March 28, 2019
 */

#include <iostream>
#include <vector>

using namespace std;

class observer;  // Never defined or used.

/******************
 * My value class *
 ******************/

// TODO:  Declare the value class and define the constructor and destructor.
//   (The body of the constructor and destructor will just have two
//   statements each for printing out that they are starting / ending
//   execution.  Use the same indentation and style as shown in the 
//   example output and the set and get functions below.)
//
// Do NOT use a .h file.  Just put the declaration of the class above
//   the definitions (right here).  In other words, keep it simple.


void value::set (int v)
{
  cout << "      ==> value::set" << endl;

  this->v = v;

  cout << "      <-- value::set" << endl;
}

int value::get ()
{
  cout << "      ==> value::get" << endl;
  cout << "      <-- value::get" << endl;
  return v;
}


/*************************
 * My remote value class *
 *************************/

// TODO:  Declare the remote class and define the constructor and destructor.
//   (The body of the constructor and destructor will just have two
//   statements each for printing out that they are starting / ending
//   execution.  Use the same indentation and style as shown in the 
//   example output and the set and get functions below.)
//
// Do NOT use a .h file.  Just put the declaration of the class above
//   the definitions (right here).  In other words, keep it simple.



void remote::set (int v)
{
  cout << "    ==> remote::set" << endl;

  // Update the remote value and keep it as well.

  this->set_remote_value (v);
  value::set(v);              // Change superclass field

  cout << "    <-- remote::set" << endl;
}

int remote::get ()
{
  cout << "    ==> remote::get" << endl;

  // If the remote value has changed, we'll update this
  // object to the remote value before returning it.

  // To avoid setting the remote value, only set the value
  //   in the superclass.  (Don't use the 'set' function in
  //   this class, or it will set the remote value to what we
  //   just got remotely, which is a waste of time.)
  
  if (remote_has_changed())
    value::set(this->get_remote_value());

  // Just get the value (from the superclass) and return it.

  int result = value::get();

  cout << "    <-- remote::get" << endl;

  return result;
}

bool remote::remote_has_changed()
{
  cout << "    ==> remote::remote_has_changed" << endl;
  cout << "    <-- remote::remote_has_changed" << endl;

  return false;  // Just a stub -- assume that true might be returned.
}

int remote::get_remote_value()
{
  cout << "    ==> remote::get_remote_value" << endl;
  cout << "    <-- remote::get_remote_value" << endl;

  return 42;  // Just a stub -- an appropriate integer may be returned.
}

void remote::set_remote_value(int v)
{
  cout << "    ==> remote::set_remote_value" << endl;
  cout << "    <-- remote::set_remote_value" << endl;
}


/***********************
 * My observable class *
 ***********************/

// TODO:  Declare the observable class and define the constructor and destructor.
//   (The body of the constructor and destructor will just have two
//   statements each for printing out that they are starting / ending
//   execution.  Use the same indentation and style as shown in the 
//   example output and the set and get functions below.)
//
// Do NOT use a .h file.  Just put the declaration of the class above
//   the definitions (right here).  In other words, keep it simple.



void observable::set (int new_value)
{
  cout << "    ==> observable::set" << endl;

  // Only change the value and send out notifications 
  //   if the new value is different than the current value in 'this'.

  if (  ) // TODO:  Fix this condition to match the comment above.
    {
      // TODO:  Change superclass field, keep the new value 

      notify_observers ();
    }

  cout << "    <-- observable::set" << endl;
}

void observable::notify_observers ()
{
  cout << "    ==> observable::notify_observers" << endl;
  cout << "    <-- observable::notify_observers" << endl;
}


void observable::register_observer (observer *)
{
  cout << "    ==> observable::register_observer" << endl;
  cout << "    <-- observable::register_observer" << endl;
}


/**************************
 * My task_priority class *
 **************************/

// TODO:  Declare the task_priority class and define the constructor and destructor.
//   (The body of the constructor and destructor will just have two
//   statements each for printing out that they are starting / ending
//   execution.  Indent two spaces.)
//
// Do NOT use a .h file.  Just put the declaration of the class above
//   the definitions (right here).  In other words, keep it simple.

// TODO:  Additionally, you will need to override a function to make it work.
//   This is not shown in the class diagram, you are to figure out what
//   you need (and why).  There will only be a couple of actually useful
//   statements (and the debugging output statements, indented two spaces).


// TODO:  Nothing else is needed beyond this point.  Do not change main at all.

/********************
 * My main (tester) *
 ********************/

int main ()
{
  // Make one of our objects.

  cout << "Creating a task_priority object:" << endl;
  cout << "--------------------------------" << endl;

  task_priority * task = new task_priority(50);

  cout << endl;
  
  // Add our task's pointer to a few vectors.  This
  // will demonstrate polymorphism.

  vector<task_priority*> vector_t;
  vector<remote*>        vector_r;
  vector<observable*>    vector_o;
  vector<value*>         vector_v;

  vector_t.push_back(task);
  vector_r.push_back(task);
  vector_o.push_back(task);
  vector_v.push_back(task);

  // Use the pointer from each vector.  Set a value,
  //   then get the value.  Because of polymorphism,
  //   this will result in the exact same sequence
  //   of function calls.

  int result;

  // First, use a task_priority pointer.

  cout << "Setting the priority to 60 (through a task_priority *):" << endl;
  cout << "-------------------------------------------------------" << endl;

  task_priority *t = vector_t[0];
  t->set(60);

  cout << endl;

  result = t->get();

  cout << endl;
  cout << "Priority is now " << result << "." << endl; 
  cout << endl;

  // Next, use a remote pointer

  cout << "Setting the priority to 30 (through a remote *):" << endl;
  cout << "------------------------------------------------" << endl;

  remote *r = vector_r[0];
  r->set(30);

  cout << endl;

  result = r->get();

  cout << endl;
  cout << "Priority is now " << result << "." << endl; 
  cout << endl;

  // Next, use an observable pointer

  cout << "Setting the priority to 75 (through an observable *):" << endl;
  cout << "-----------------------------------------------------" << endl;

  observable* o = vector_o[0];
  o->set(75);

  cout << endl;

  result = o->get();

  cout << endl;
  cout << "Priority is now " << result << "." << endl; 
  cout << endl;

  // Finally, use a value pointer

  cout << "Setting the priority to 22 (through a value *):" << endl;
  cout << "-----------------------------------------------" << endl;

  value* v = vector_v[0];
  v->set(22);

  cout << endl;

  result = v->get();

  cout << endl;
  cout << "Priority is now " << result << "." << endl; 
  cout << endl;

  // Done.  Delete our object (once only).  For fun, delete it
  //   using one of the base class pointers.  (We should still
  //   see all the destructors called.)
 
  cout << "Cleaning up:" << endl;
  cout << "------------" << endl;

  delete v;

  cout << endl;

  return 0;
}


