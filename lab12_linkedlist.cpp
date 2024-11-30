#include<iostream>
#include<cstdlib>
#include<cstring>
using namespace std;

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
  void Print();
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

// Pay special attention to the Print() function. Here is a recursion
// This Print() function, printf () the tag first and then reach to recursion part
// in this case, printf("%s ->", tag) prints playa 22 first, then evaluate if (next != NULL), it is true now, 
// so it goes to next -> Print(), the 'next' points to the playa 21, so it print playa 21
// and so on
// until the playa 1. the 'next' of playa 1 is NULL, the Print() function ends at playa 1
void Playa::Print(){
    printf("%s ->", tag); // print the tag first
    if (next != NULL)  // traverse the linkedlist from the last element to the first element
    { 
        next -> Print();
    }
}


int main() {

   // every thing is a pointer here 
    Playa* p;
    char strbuf[64];
    Playa* playas = NULL; // 'playas' denotes a list, We can think 'playas' as the head of the linkedlist.
                          // initialize it to NULL. 

    for (int i = 0; i < 23; i ++){
        sprintf(strbuf, "%s.%d","Playa", i); // sprintf store strings into a buffer, here the buffer named 'strbuf'
        // the following step is a typical process to create a linkedlist. There are four step to create a linkedlist
        p = new Playa; // intialize the pointer, make it to a new instance in the heap 
        p->TagSet(strbuf); // set values to the new instance
        p->NextSet(playas); // make the pointer variable 'next' of the intance points to the head of the linkedlist
        playas = p; // update the head of the linkedlist to the new instance.
    }
    playas ->Print();
    cout << endl; 
    cout << "test" << endl;
    
    int n;
    for ( n = 0,p = playas; p!=NULL; p = p->NextGet()) //
        {n++;}

    cout << "There are " << n << "playas in the list" << endl;
    return 0;
}
