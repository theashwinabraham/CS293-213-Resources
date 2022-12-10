#ifndef TRIE_CPP
#define TRIE_CPP

#ifndef STD_HEADERS
#include "std_headers.h"
#endif

#ifndef DICTIONARY_H
#include "dictionary.h"
#endif

#ifndef TRIE_H
#include "Trie.h"
#endif

using namespace std;

#define MAGIC_STRING "###"

Trie::Trie(Dictionary<int> *nameToIndex) {
  nameDict = nameToIndex;
  root = new TrieNode();
  if (root == nullptr) {
    cout << "Memory allocation failure." << endl;
    exit(-1);
  }
}

Trie::~Trie() {
  recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node) {
  if (node == nullptr) {
    return;
  }
  else {
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      recursiveDelete(currNode);
      node->branch[i] = nullptr;
    }
    if (node != root) {
      delete node;
    }
    return;
  }
}

bool Trie::insert(string wordInName, int indexOfName) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      TrieNode *newNode = new TrieNode();
      if (newNode == nullptr) {
	cout << "Memory allocation failure" << endl;
	return false;
      }
      currNode->branch[letter] = newNode;
      currNode->numNonNullBranches++;
    }
    currNode = currNode->branch[letter];
  }

  currNode->isWord = true;
  listOfObjects<int> *currIndices = currNode->indices;
  while (currIndices != nullptr) {
    if (currIndices->object == indexOfName) {
      cout << "Insertion already done in the past." << endl;
      return true;
    }
    else {
      currIndices = currIndices->next;
    }
  }
  // Need to insert indexOfName in currNode->indices
  listOfObjects<int> *newEntry = new listOfObjects<int> (indexOfName);
  if (newEntry == nullptr) {
    cout << "Memory allocation failure." << endl;
    return false;
  }
  else {
    newEntry->next = currNode->indices;
    currNode->indices = newEntry;
    return true;
  }
}

bool Trie::del(string wordInName, string name) {
  TrieNode *currNode = root;
  TrieNode *lastBranchNode = nullptr;
  int lastBranchChar = -1;
  int len = wordInName.length();

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      cout << "Couldn't find " << wordInName << " in " << name << endl;
      return false;
    }

    if (currNode->numNonNullBranches > 1) {
      lastBranchNode = currNode;
      lastBranchChar = i;
    }
    currNode = currNode->branch[letter];
    
  }

  if (!currNode->isWord) {
    cout << "Couldn't find " << wordInName << " in " << name << endl;
    return false;
  }

  listOfObjects<int> *currIndex = currNode->indices;
  listOfObjects<int> *prevIndex = nullptr;
  while (currIndex != nullptr) {
    if (nameDict->getKeyAtIndex(currIndex->object) == name) {
      if (prevIndex == nullptr) {
	currNode->indices = currIndex->next;
      }
      else {
	prevIndex->next = currIndex->next;
      }
      delete currIndex;
      if (currNode->indices != nullptr)  {
	// There is at least one other full name for which one of
	// of its component words brings us to the current leaf node
	// in the trie.
	// So we'll have to leave this leaf node as is.
	return true;
      }
      else { // currNode->indices == nullptr
	currNode->isWord = false;

	// There are no more full names represented by this node.
	// If there are branches going out of this node, then this
	// node has to be preserved.  Otherwise, we have to delete
	// this node and all its predecessors until the last
	// branching point

	if (currNode->numNonNullBranches > 0) {
	  return true;
	}

	// There are no more full names represented by this node.
	// Neither are there branches going out of this node.
	
	if (lastBranchNode != nullptr) {
	  int lastBranchIndex = toupper(wordInName.at(lastBranchChar)) - 'A';
	  currNode = lastBranchNode->branch[lastBranchIndex];
	  lastBranchNode->branch[lastBranchIndex] = nullptr;
	  lastBranchNode->numNonNullBranches--;
	}
	else {
	  // The only path from the root has to be deleted
	  int rootBranchIndex = toupper(wordInName.at(0)) - 'A';
	  currNode = root->branch[rootBranchIndex];
	  root->branch[rootBranchIndex] = nullptr;
	  root->numNonNullBranches--;
	  lastBranchChar = 0;
	}
	TrieNode *prevNode;
	for (int i = lastBranchChar+1; i < len; i++) {
	  int letter = toupper(wordInName.at(i)) - 'A';
	  prevNode = currNode;
	  currNode = currNode->branch[letter];
	  delete prevNode;
	}
	return true;
      }
    }
    else {
      prevIndex = currIndex;
      currIndex = currIndex->next;
    }
  }

  return false;
}

listOfObjects<string> * Trie::completions(string prefix) {
  TrieNode *currNode = root;
  int len = prefix.length();
  // Creating a list of completions with a dummy first element
  listOfObjects<string> *currCompletions = new listOfObjects<string> (MAGIC_STRING);
  if (currCompletions == nullptr) {
    cout << "Memory allocation failure." << endl;
    return nullptr;
  }
  
  for (int i = 0; i < len; i++) {
    int letter = toupper(prefix.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      // No completions;
      delete currCompletions;
      return nullptr;
    }
    currNode = currNode->branch[letter];
  }

  bool status = recursiveAddCompletions(currNode, currCompletions);
  if (!status) {
    freeCompletionList(currCompletions);
    return nullptr;
  }
  else {
    return currCompletions;
  }
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (node->isWord) {
    if (!addCompletions(node, currCompletions)) {
      return false;
    }
  }

  TrieNode *currNode = node;
  for (int i = 0; i < NUM_CHARS; i++) {
    if (currNode->branch[i] != nullptr) {
      if (!recursiveAddCompletions(currNode->branch[i], currCompletions)) {
	return false;
      }
    }
  }

  return true;
}

bool Trie::addCompletions(TrieNode *node, listOfObjects<string> *currCompletions) {
  if (!node->isWord) {
    return true;
  }

  listOfObjects<int> *currIndex = node->indices;
  while (currIndex != nullptr) {
    string fullName = nameDict->getKeyAtIndex(currIndex->object);
    if (!isPresentInCompletions(currCompletions, fullName)) {
      if (currCompletions != nullptr) {
	// Check if the only entry in currCompletions is the dummy entry
	// we initialized it with.  If so, replace MAGIC_STRING in the
	// dummy entry with fullName
	if (currCompletions->object == MAGIC_STRING) {
	  currCompletions->object = fullName;
	}
	else {
	  // Add the new completion to currCompletion after making a copy of
	  // the existing currCompletion, and set up the next links appropriately
	  listOfObjects<string> *newCompletion = new listOfObjects<string> (currCompletions->object);
	  if (newCompletion == nullptr) {
	    cout << "Memory allocation failure." << endl;
	    return false;
	  }
	  newCompletion->next = currCompletions->next;
	  currCompletions->object = fullName;
	  currCompletions->next = newCompletion;
	}
      }
      else {
	cout << "Exceptional condition encountered" << endl;
	return false;
      }
    }
    currIndex = currIndex->next;
  }

  return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name) {
  listOfObjects<string> *currCompletion = completions;
  bool isPresent = false;
  while (currCompletion != nullptr) {
    if (currCompletion->object == name) {
      isPresent = true;
      break;
    }
    currCompletion = currCompletion->next;
  }
  return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions) {
  listOfObjects<string> *currCompl = completions;
  while (currCompl != nullptr) {
    listOfObjects<string> *toDeleteCompl = currCompl;
    currCompl = currCompl->next;
    delete toDeleteCompl;
  }
  return;
}

bool Trie::isPresent(string wordInName) {
  TrieNode *currNode = root;
  int len = wordInName.length();

  for (int i = 0; i < len; i++) {
    int letter = toupper(wordInName.at(i)) - 'A';

    if (currNode->branch[letter] == nullptr) {
      return false;
    }
    currNode = currNode->branch[letter];
  }

  return currNode->isWord;
  
}

// Edit version 1: Added printTrie and recursivePrintTrie functions
// to help in debugging

void Trie::printTrie()
{
  recursivePrintTrie(root, "", -1, false);
}

// Adapted from Adrian Schneider's code on StackOverflow
// Basically a variation of the function we've been using
// print binary search trees in previous labs

void Trie::recursivePrintTrie(TrieNode *node, const string& prefix, int branchId, bool siblingsToRight)
{
  if (node != nullptr) {
    cout << prefix;
    
    cout << ((branchId == 0) ? "|-" : (branchId == -1)? " *":"|_" ) << (char) ((branchId != -1) ? 'A'+branchId: '*');
    cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*':'_');
    
    // If this trie node has isWord set to true, print "(isWord)" and
    // also the list of complete station names (accessed through indices
    // in nameDict) associated with this trie node.
    if (node->isWord) {
      cout << "(isWord)";
      listOfObjects<int> *currIndices = node->indices;
      while (currIndices != nullptr) {
	cout << endl << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
	currIndices = currIndices->next;
      }
    }
    else {
      cout << "()";
    }
    cout << endl;
    for (int i = 0; i < NUM_CHARS; i++) {
      TrieNode *currNode = node->branch[i];
      bool childrenToRight = false;
      for (int j = i+1; j < NUM_CHARS; j++) {
	if (node->branch[j] != nullptr) {
	  childrenToRight = true;
	  break;
	}
      }
      if (currNode != nullptr) {
	recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
      }
    }
  }
}
// End edit version 1

#endif
