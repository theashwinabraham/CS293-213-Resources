#ifndef DICTIONARY_CPP
#define DICTIONARY_CPP

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

using namespace std;

template<typename T>
Dictionary<T>::Dictionary(){
    N = DICT_SIZE;
    numFilled = 0;
    A = new Entry<T>[N];
    if (A == nullptr) {
      cout << "Memory allocation failure." << endl;
    }
    else {
      Entry<T> init_object;
      for(int i = 0; i < N; i++){
	A[i] = init_object;
      }
    }
};

template<typename T>
int Dictionary<T>::hashValue(string key){
  int size = key.length();

  int hashValue = 0;
  int x = 33;
  for(int i = size - 1; i >= 0; i--){
    // Edit version 1: Changed the way val is calculated
    int val = (int)(key.at(i));
    // End edit version 1
    hashValue = (val + x * hashValue) % N;
  }
  return hashValue;
}

template<typename T>
int Dictionary<T>::findFreeIndex(string key){
    int hash = hashValue(key);
    
    for(int i = 0; i < N; i++){
        int index = (hash + i)%N;

	if (A[index].key == "") {
	  return index;
	}
        else if (A[index].key == "__TOMBSTONE__") {
	  return index;
        }
    }
    return -1;
}

template<typename T>
Entry<T> *Dictionary<T>::get(string key){
  int hash = hashValue(key);
  
  for(int i = 0; i < N; i++){
    int index = (hash + i)%N;
    
    if (A[index].key == "") {
      return nullptr;
    }
    
    if (A[index].key == key) {
      return &A[index];
    } 
  }
  
  return nullptr;
}

template<typename T>
bool Dictionary<T>::put(Entry<T> e) {
  int freeIndex = findFreeIndex(e.key);
  if(freeIndex == -1){
    return false;
  }
  else{
    A[freeIndex] = e;
    numFilled++;
    return true;
  }
}
 
template<typename T>
bool Dictionary<T>::remove(string key){
  Entry<T> *e = get(key);
  
  if (e == nullptr) {
    return false;
  }
  else if (e->key == "") {
    return false;
  }
  else{
    e->key = "__TOMBSTONE__";
    numFilled--;
    return true;
  }
}

#endif
