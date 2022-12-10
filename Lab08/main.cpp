#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_CPP
#include "dictionary.cpp"
#endif

#ifndef TRIE_CPP
#include "Trie.cpp"
#endif

#ifndef KMP_CPP
#include "kmp.cpp"
#endif

#ifndef PLANNER_CPP
#include "planner.cpp"
#endif

#ifndef QUICKSORT_CPP
#include "quicksort.cpp"
#endif

#ifndef HEAP_CPP
#include "Heap.cpp"
#endif

using namespace std;

int main(int argc, char **argv) {

  if (argc != 2) {
    cerr << "Usage: " << argv[0] << " <log_file_name>" << endl;
    return -1;
  }

  Planner *myPlanner = new Planner(argv[1]);
  if (myPlanner == nullptr) {
    cerr << "Memory allocation failure." << endl;
    return -1;
  }
  
  myPlanner->displayWelcomeMessage();

  do {
    bool continueMenu = myPlanner->displayMenuAndAct();

    if (!continueMenu) {
      delete myPlanner;
      return 0;
    }
    else {
      continue;
    }
  } while (true);
}

