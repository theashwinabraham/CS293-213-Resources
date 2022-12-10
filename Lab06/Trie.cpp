/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

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

#include <cassert>

using namespace std;

Trie::Trie(Dictionary<int> *nameToIndex)
{
    nameDict = nameToIndex;
    root = new TrieNode();
    if (root == nullptr)
    {
        cout << "Memory allocation failure." << endl;
        exit(-1);
    }
}

Trie::~Trie()
{
    recursiveDelete(root);
}

void Trie::recursiveDelete(TrieNode *node)
{
    if (node == nullptr)
    {
        return;
    }
    else
    {
        for (int i = 0; i < NUM_CHARS; i++)
        {
            TrieNode *currNode = node->branch[i];
            recursiveDelete(currNode);
            node->branch[i] = nullptr;
        }
        if (node != root)
        {
            delete node;
        }
        return;
    }
}

bool Trie::insert(string wordInName, int indexOfName)
{
    TrieNode *currNode = root;
    int len = wordInName.length();

    // Insert your code here
    for(int i = 0; i < len; ++i)
    {
        if((currNode->branch)[wordInName[i] - 'A'] == nullptr)
        {
            ++(currNode->numNonNullBranches);
            (currNode->branch)[wordInName[i] - 'A'] = new TrieNode;
        }
        currNode = (currNode->branch)[wordInName[i] - 'A'];
    }

    currNode->isWord = true;
    if(currNode->indices == nullptr)
    {
        currNode->indices = new listOfObjects<int>(indexOfName);
    }
    else
    {
        listOfObjects<int>* ptr = currNode->indices;
        if(ptr->object == indexOfName) return false;
        while(ptr->next != nullptr)
        {
            ptr = ptr->next;
            if(ptr->object == indexOfName) return false;
        }
        ptr->next = new listOfObjects<int>(indexOfName);
    }
    return true;
}

bool Trie::del(string wordInName, string name)
{
    //nameDict->remove(name);
    TrieNode *currNode = root;
    TrieNode *lastBranchNode = root;
    int lastBranchChar = wordInName[0] - 'A';
    int len = wordInName.length();
    //listOfObjects<TrieNode*>* path = nullptr; 
    // Insert your code here
    // listOfObjects<TrieNode*>* path = new listOfObjects<TrieNode*>(currNode);
    for(int i = 0; i<len; ++i)
    {
        /*if(path == nullptr)
        {
            path = new listOfObjects<TrieNode*>(currNode);
        }
        else
        {
            listOfObjects<TrieNode*>* temp = path;
            path = new listOfObjects<TrieNode*>(currNode);
            path->next = temp;
        }*/
        if(currNode->numNonNullBranches > 1 || currNode->isWord)
        {
            lastBranchNode = currNode;
            lastBranchChar = wordInName[i] - 'A';
        }

        if((currNode->branch)[wordInName[i] - 'A'] == nullptr) return false;
        currNode = (currNode->branch)[wordInName[i] - 'A'];
    }
    if(currNode->isWord)
    {
        listOfObjects<int>* ptr = currNode->indices;
        listOfObjects<int>* prev = nullptr;
        for(; ptr != nullptr; ptr = ptr->next)
        {
            if(nameDict->getKeyAtIndex(ptr->object) == name)
            {
                if(ptr == currNode->indices)
                {
                    currNode->indices = ptr->next;
                }
                else
                {
                    prev->next = ptr->next;
                }
                break;
            }
            prev = ptr;
        }
        if(ptr == nullptr) return false;
        if(currNode->indices == nullptr)
        {
            currNode->isWord = false;
            if(currNode->numNonNullBranches == 0)
            {
                recursiveDelete((lastBranchNode->branch)[lastBranchChar]);
                (lastBranchNode->branch)[lastBranchChar] = nullptr;
            }
            --(lastBranchNode->numNonNullBranches);
        }
        return true;
    }
    return false;
}

/*void Trie::append_to_list(TrieNode* tr, listOfObjects<string>* &list)
{
    if(tr->isWord)
    {
        if(list == nullptr)
        {
            list = new listOfObjects<string>(nameDict->getKeyAtIndex(tr->indices->object));
            for(listOfObjects<int>* ptr = tr->indices->next; ptr != nullptr; ptr = ptr->next)
            {
                listOfObjects<string>* temp = list->next;
                list->next = new listOfObjects<string>(nameDict->getKeyAtIndex(ptr->object));
                list->next->next = temp;
            }
        }
        else
        {
            for(listOfObjects<int>* ptr = tr->indices; ptr != nullptr; ptr = ptr->next)
            {
                listOfObjects<string>* temp = list->next;
                list->next = new listOfObjects<string>(nameDict->getKeyAtIndex(ptr->object));
                list->next->next = temp;
            }
        }
    }
    else
    {
        for(int i = 0; i<NUM_CHARS; ++i)
        {
            if((tr->branch)[i] != nullptr)
            {
                append_to_list((tr->branch)[i], list);
            }
        }
    }
}*/

listOfObjects<string> *Trie::completions(string prefix)
{
    TrieNode *currNode = root;
    int len = prefix.length();
    listOfObjects<string> *currCompletions = nullptr;
    for(int i = 0; i<len; ++i)
    {
        if((currNode->branch)[prefix[i] - 'A'] == nullptr) return nullptr;
        currNode = (currNode->branch)[prefix[i] - 'A'];
    }
    recursiveAddCompletions(currNode, currCompletions);
    // Insert your code here
    return currCompletions;
}

bool Trie::recursiveAddCompletions(TrieNode *node, listOfObjects<string>* &list)
{
    if (node->isWord)
    {
        addCompletions(node, list);
        return true;
    }

    for (int i = 0; i < NUM_CHARS; i++)
    {
        if ((node->branch)[i] != nullptr)
        {
            recursiveAddCompletions((node->branch)[i], list);
        }
    }

    return true;
}

bool Trie::addCompletions(TrieNode *tr, listOfObjects<string>* &list)
{

    // Insert your code here
    assert(tr != nullptr);
    assert(tr->isWord);
    if(list == nullptr)
    {
        list = new listOfObjects<string>(nameDict->getKeyAtIndex(tr->indices->object));
        for(listOfObjects<int>* ptr = tr->indices->next; ptr != nullptr; ptr = ptr->next)
        {
            listOfObjects<string>* temp = list->next;
            list->next = new listOfObjects<string>(nameDict->getKeyAtIndex(ptr->object));
            list->next->next = temp;
        }
    }
    else
    {
        for(listOfObjects<int>* ptr = tr->indices; ptr != nullptr; ptr = ptr->next)
        {
            listOfObjects<string>* temp = list->next;
            list->next = new listOfObjects<string>(nameDict->getKeyAtIndex(ptr->object));
            list->next->next = temp;
        }
    }
    return true;
}

bool Trie::isPresentInCompletions(listOfObjects<string> *completions, string name)
{
    listOfObjects<string> *currCompletion = completions;
    bool isPresent = false;
    while (currCompletion != nullptr)
    {
        if (currCompletion->object == name)
        {
            isPresent = true;
            break;
        }
        currCompletion = currCompletion->next;
    }
    return isPresent;
}

void Trie::freeCompletionList(listOfObjects<string> *completions)
{
    listOfObjects<string> *currCompl = completions;
    while (currCompl != nullptr)
    {
        listOfObjects<string> *toDeleteCompl = currCompl;
        currCompl = currCompl->next;
        delete toDeleteCompl;
    }
    return;
}

bool Trie::isPresent(string wordInName)
{
    TrieNode *currNode = root;
    int len = wordInName.length();

    for (int i = 0; i < len; i++)
    {
        int letter = toupper(wordInName.at(i)) - 'A';

        if (currNode->branch[letter] == nullptr)
        {
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

void Trie::recursivePrintTrie(TrieNode *node, const string &prefix, int branchId, bool siblingsToRight)
{
    if (node != nullptr)
    {
        cout << prefix;

        cout << ((branchId == 0) ? "|-" : (branchId == -1) ? " *"
                                                           : "|_")
             << (char)((branchId != -1) ? 'A' + branchId : '*');
        cout << ((branchId == 0) ? '-' : (branchId == -1) ? '*'
                                                          : '_');

        // If this trie node has isWord set to true, print "(isWord)" and
        // also the list of complete station names (accessed through indices
        // in nameDict) associated with this trie node.
        if (node->isWord)
        {
            cout << "(isWord)";
            listOfObjects<int> *currIndices = node->indices;
            while (currIndices != nullptr)
            {
                cout << endl
                     << prefix << "     " << nameDict->getKeyAtIndex(currIndices->object);
                currIndices = currIndices->next;
            }
        }
        else
        {
            cout << "()";
        }
        cout << endl;
        for (int i = 0; i < NUM_CHARS; i++)
        {
            TrieNode *currNode = node->branch[i];
            bool childrenToRight = false;
            for (int j = i + 1; j < NUM_CHARS; j++)
            {
                if (node->branch[j] != nullptr)
                {
                    childrenToRight = true;
                    break;
                }
            }
            if (currNode != nullptr)
            {
                recursivePrintTrie(currNode, prefix + ((siblingsToRight) ? "│   " : "    "), i, childrenToRight);
            }
        }
    }
}
// End edit version 1

#endif
