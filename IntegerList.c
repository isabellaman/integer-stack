//-----------------------------------------------------------------------------
// IntegerList.c
// Array based implementation of Integer List ADT in C (with array doubling)
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include"IntegerList.h"

// Private Types and Functions ------------------------------------------------

// InitialSize
static const int InitialSize = 1;

// IntegerListObj
typedef struct IntegerListObj{
   int* item;         // array of IntegerList items
   int numItems;      // number of items in this IntegerList
   int physicalSize;  // current length of underlying array
} IntegerListObj;

// doubleItemArray
// Doubles the physical size of the underlying array L->item.
void doubleItemArray(IntegerList L){
   int i;
   int* newArray;
   int* oldArray = L->item;
   L->physicalSize *= 2;
   newArray = calloc(L->physicalSize, sizeof(int));
   for( i=0; i<(L->numItems); i++){
      newArray[i] = oldArray[i];
   }
   L->item = newArray;
   free(oldArray);
}

// arrayIndex()
// transforms an IntegerList index to an Array index
int arrayIndex(int listIndex){
   return listIndex-1;
}


// Constructors-Destructors ---------------------------------------------------

// newIntegerList()
// Constructor for the IntegerList ADT
IntegerList newIntegerList(){
   IntegerList L = malloc(sizeof(IntegerListObj));
   L->item = calloc(InitialSize, sizeof(int));
   L->numItems = 0;
   L->physicalSize = InitialSize;
   return L;
}

// freeIntegerList()
// Destructor for the List ADT
void freeIntegerList(IntegerList* pL){
   if( pL!=NULL && *pL!=NULL ){
      free((*pL)->item);
      free(*pL);
      *pL = NULL;
   }
}


// ADT operations -------------------------------------------------------------

// isEmpty()
// Returns 1 (true) if List L is empty, 0 (false) otherwise
int isEmpty(IntegerList L){
   if( L==NULL ){
      fprintf(stderr, "IntegerList Error: isEmpty() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }

   return (L->numItems == 0);
}

// size()
// Returns the number of elements in L
int size(IntegerList L){
   if( L==NULL ){
      fprintf(stderr, "IntegerList Error: size() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }

   return L->numItems;
}

// get()
// pre: 1 <= index <= size(L)
// Returns int at position index in L
int get(IntegerList L, int index){
   if( L==NULL ){
      fprintf(stderr, "IntegerList Error: get() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }
   if( index<1 || index>L->numItems ){
      fprintf(stderr, "IntegerList Error: get() called with index out of bounds");
      exit(EXIT_FAILURE);
   }

   return L->item[arrayIndex(index)];
}

// add()
// Inserts int x into L at position index
// pre: 1 <= index <= size(L)+1
void add(IntegerList L, int index, int x){
   int i;
   if( L==NULL ){
      fprintf(stderr, "IntegerList Error: add() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }
   if( index<1 || index>(L->numItems+1) ){
      fprintf(stderr, "IntegerList Error: add(,) called with index out of bounds");
      exit(EXIT_FAILURE);
   }

   // increase physical size of array if necessary
   if( (L->numItems)==(L->physicalSize) ){
      doubleItemArray(L);
   }

   // make room to the right of index
   for( i=(L->numItems); i>=index; i--){ 
      L->item[arrayIndex(i+1)] = L->item[arrayIndex(i)];
   }
   L->item[arrayIndex(index)] = x;
   L->numItems++;
}  

// delete()
// Deletes int from position index
// pre: 1 <= index <= size(L)
void delete(IntegerList L, int index){
   int i;
   if( L==NULL ){
      fprintf(stderr, "IntegerList Error: delete() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }
   if( index<1 || index>(L->numItems) ){
      fprintf(stderr, "IntegerList Error: delete() called with index out of bounds");
      exit(EXIT_FAILURE);
   }

   for( i=index+1; i<=(L->numItems); i++){
      L->item[arrayIndex(i-1)] = L->item[arrayIndex(i)];
   }
   L->numItems--;
}

// deleteAll()
// Reset L to the empty state
void deleteAll(IntegerList L){
   if( L==NULL ){
      fprintf(stderr, "IntegerList Error: deleteAll() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }

   L->numItems = 0;
}


// Other Operations -----------------------------------------------------------

// printIntegerList()
// Prints a space separated list of items in L to file stream pointed to by out
void printIntegerList(FILE* out, IntegerList L){
   int i;
   if( L==NULL ){
      fprintf(stderr, "IntegerList Error: printIntegerList() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }

   for( i=1; i<=(L->numItems); i++){
      fprintf(out, "%d ", L->item[arrayIndex(i)] );
   }
   fprintf(out, "\n");
}

// equals()
// Returns true (1) if L and R are matching sequences of integers, false (0) 
// otherwise
int equals(IntegerList L, IntegerList R){
   int i, eq;
   if( L==NULL || R==NULL ){
      fprintf(stderr, "IntegerList Error: equals() called on NULL IntegerList reference");
      exit(EXIT_FAILURE);
   }

   eq = ( (L->numItems)==(R->numItems) );
   for( i=1; eq && i<=(L->numItems); i++){
      eq = ( (L->item[arrayIndex(i)])==(R->item[arrayIndex(i)]) );
   }
   return eq;
}

