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

  // Lab 7 specific
  listOfObjects<T> *prev;
  // End lab 7 specific
  
  // Constructor
  
  // Lab 7 specific
  // Modified to initialize prev, compared to constructor in lab 6
  listOfObjects(T initValue) {object = initValue; next = prev = nullptr;}
  // End lab 7 specific
  
  // Destructor
  ~listOfObjects() {;}
};

// Lab 7 specific
// Train information per station
class TrainInfoPerStation {
public:
  int journeyCode; // same as train number
  unsigned short stopSeq; // sequence of this station's stop in
                          // itinerary of train, i.e. 1st stop in journey
                          // or 2nd stop in journey or ...
  bool daysOfWeek[7]; // Days of week when this train travels
                      // to/from this station
  int arrTime;  // Arrival time at station; -1 if train starts from here
  int depTime;  // Departure time from station; -1 if train ends here

public:
  TrainInfoPerStation(int jCode, unsigned short stpSq, int aTm, int dTm)
  {
    journeyCode = jCode;
    stopSeq = stpSq;
    arrTime = aTm;
    depTime = dTm;
    for (int i = 0; i < 7; i++) { daysOfWeek[i] = false;}
  }

  ~TrainInfoPerStation() {;}

  void setDayOfWeek(int i) { if ((0 <= i) && (i < 7)) daysOfWeek[i] = true; }
  void resetDayOfWeek(int i) { if ((0 <= i) && (i < 7)) daysOfWeek[i] = false; }
    
};
// End lab 7 specific
  
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
