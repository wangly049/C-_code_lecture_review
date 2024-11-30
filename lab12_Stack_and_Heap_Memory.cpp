/*
The first part of this code (line to ) gives explanation and comparison between stack memory and heap memory
    Stack and Heap are two memory parts in computer memory. 
    On the stack, memory allocation and deallocation are automatically by Operating System;
    On the heap, we need "new" operator to allocate memory on heap and need "delete" operation to relinquish
        the heap memory Manually.

Note some basic concepts: 
pointer is a variable, its values is an address
when we say "a pointer points to someplace", it means the value stored in the pointer is the address of someplace
*/

#include<iostream> 
#include<cstdlib> 
#include<cstring>
using namespace std;

// Here we declare a Self-Referential class. Recall class is a valid aggregation type in C++
// Self-Referential class is a special class, specially for Linkedlist implementation
// Note: To Create a Self-Referential Class, 
// we need to declare a data member as a pointer, which points to an object of the same class

class Playa
{
  char * tag;
  int sernum;
  Playa * next; // 'next' is pointer. It points to the address of the instance of Playa
                // i.e. 'next' stores the address of the instance Playa
  
                  
public: 
  Playa(); // initialize instance of the Playa
  ~Playa(); // disstructor
  void TagSet(char * ); // set the tag for an instance of Playa. Note the parameter is a char *
  char * TagGet(); // get the tag of an instance of Playa. Note the return type is a char *, because the 'tag' is a char *
  void NextSet(Playa * x); // This function sets the value of 'next', i.e. makes 'next' store the address of the next instance of Playa
  Playa * NextGet(); // This function gets the value of 'next', i.e. returns the address of the next instance of Playa
};



Playa::Playa() // construct 
{
  static int n = 1;
  sernum = n++;

  next = NULL; // for every instance of Playa, make sure the initial value of its 'next' should be NULL.
  tag = new char[128]; // 'new' operator is used for allocate something from the HEAP
                       // here we use 'new' to find some memory in the heap, and store the address to pointer 'tag'
                       // 'tag' is a pointer  

  strcpy (tag, "-Mna_serei-"); // copy string "-Mna_serei-" to tag. 
                               // Here note: the parameters in strcpy() should be pointers
                               // Here 'tag' is a pointer and "-Mna_serei-" is also a pointer
}

Playa::~Playa() // in disstructor, we need to use 'delete' operation to relinquish the memory we have allocated in the heap 
{               // Here the memory we have allocated in the heap refers to "tag = new char[128]" in constructor
  cout << "Plays: " << sernum << " bub---bye..." << endl;
  delete [] tag; // So here we need to delete the whole tag array
}

void Playa::TagSet(char * newtag)
{
  strcpy(tag, newtag);
}

char * Playa::TagGet()
{
  return tag;
}

void Playa::NextSet (Playa * x) // Note the parameter in the function.The parameter is a Playa pointer, Playa *
{ 
  next = x; 
}

Playa * Playa::NextGet() // Note the return type in the function.The return type is a Playa pointer, Playa *
{
  return next;
}



int main()
{
  
  // Here we create an instance of Playa p0. p0 is on the STACK
  // the memory allocation and deallocation on stack are both automatical. 
  // the memory of p0 will be deallocated automatically when the funtion main() dies. 
  Playa p0; 
  // we can see the tag of the P0. Note here p0 is not a pointer. It is an instance of Playa.
  printf("Tag of p0: %s\n\n", p0.TagGet()); 



  // declare a poniter named p1. Its type is Playa *, i.e. it points to an instance of Playa 
  // Note that p1 is on the STACK
  Playa * p1;             
  // declare two more pointers p2 and plays. The meaning is the same as p1
  Playa * p2;           
  Playa * playas; 

  // Here Note: 'new' operator finds some memory in the heap, this memory stores an new instance of Playa
  p1 = new Playa; 
  // we can see the tag of the new instance. Here note: p1 is a pointer
  printf("Tag of P1 using ->: %s\n", p1->TagGet()); // to dereferring a pointer, we can use pointer->
  printf("Tag of P1 using deference: %s\n\n", (*p1).TagGet());// to dereferring a pointer, we can also use (*pointer).
                                              
  p1->TagSet((char *)"p1p1p1"); // (char *) cast "p1p1p1" to be a pointer. 
  printf("Tag of P1 after TagSet() using ->: %s\n", p1->TagGet()); // to dereferring a pointer, we can use pointer->
  printf("Tag of P1 after TagSet() using deference: %s\n\n", (*p1).TagGet());// to dereferring a pointer, we can also use (*pointer).



  // This code shows until now 'p1' and 'playas' points to different address
  // we use "playas = p1;" to make 'p1' and 'playas' points to the same address
  printf("Address p1 points to : %p address that playas points to : %p\n", p1, playas); // Here the two address are different
  playas = p1; // assign the values in p1 (i.e. the address p1 points to) to the values of playas 
               // i.e. make p1 and playa point to the same address.
  printf("Address p1 points to : %p address that playas points to : %p\n\n", p1, playas); // Here two address are the same
 
  // create a new instance p2 and make p1 link to p2
  p2 = new Playa(); // here use the constructor to create a new instance
  (*p2).TagSet((char*)"p2p2p2p2"); // cast char constant to char pointer
  p1->NextSet(p2); // recall the implemtation in NextSet() funcion. we take an address as input and assign this address the 
                   // the pointer 'next' 
                   // what we do here is store the address of p2 into variable 'next' of p1
  // we can get P2 tag through p1                 
  char * s1 = p1 -> NextGet()-> TagGet(); // p1-> NextGet() get the value of 'next' of p1, i.e. the address of p2
                                          // because the 'next' of p1 is a pointer, it points to the p2
                                          // we can use ->TagGet() is equivalent to p2 -> TagGet() 
  printf ("Tag of p2 through p1: %s\n", s1);
  char * s2 = playas -> NextGet()-> TagGet(); // because p1 and playas point to the same place. we also can access the p2 through playas
  printf ("Tag of p2 through playas: %s\n\n", s2); 

  p2 = NULL; // if we declare a pointer, we should make it point to NULL. Don't leave wild pionter around. 

  delete p1; // relinquish p1 memory backt to os
             // here we first manually delete p1
  cout << "test" << endl;
  return 0;  // When the function finishes, p0 will be relinquished automatically
}
