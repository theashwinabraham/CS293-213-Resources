#ifndef DICTIONARY_H
#define DICTIONARY_H

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

// Can change this value for debugging
#define DICT_SIZE 64

template <typename T> class listOfObjects {
 public:
  T object;
  listOfObjects<T> *next;

  // Constructor
  listOfObjects(T initValue) {object = initValue; next = nullptr;}

  // Destructor
  ~listOfObjects() {;}
};

// JourneyCodeReview * will be the entry type for our dictionary
class JourneyCodeReview {
 public:
  int jCode;
  listOfObjects<string> *reviews;
  
  // Constructor
  JourneyCodeReview() {jCode = -1; reviews = nullptr;}
  void reset() {
    jCode = -1;
    reviews = nullptr;
  }

  ~JourneyCodeReview() {;}
};

template <typename T> class Entry {
 public:
  string key;
  T value;

  Entry() {key = "";}
  Entry(T initValue) {key = ""; value = initValue;}
  ~Entry() {;}
};
  
template <typename T> class Dictionary {
 private:
  int N; // size of array A
  int numFilled; // number of used array elements
  Entry<T> *A; // Array of dictionary entries

 public:

  // Return the hash value (between 0 and N-1) of the given string; assume string is null terminated and of max length 32
  int hashValue(string key);

  // Find the position where given key can be inserted (after resolving hash collision if any); return value between 0 and N-1 if free location present; return -1 if no free location
  int findFreeIndex(string key);
  
  // Default constructor
  Dictionary();

  // Default destructor
  ~Dictionary() {;}
  
  // Return the entry corresponding to given key, or NULL if the given key does not exist in the dictionary
  Entry<T> *get(string key);

  // Add the given entry in the appropriate location (using hashing) in the dictionary; return true if success, false if failure (array is full)
  bool put(Entry<T> entry);

  // Remove the given key; return true if success, false if failure (given key not present)
  bool remove(string key);

  string getKeyAtIndex(int index) { return A[index].key; } 
};

#endif
