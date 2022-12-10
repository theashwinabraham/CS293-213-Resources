#ifndef KMP_CPP
#define KMP_CPP

#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

int *Planner::computeHMatrixForKMP(string pattern) {
  int len = pattern.length();

  int *hMatrix = new int[len];
  if (hMatrix == nullptr) {
    cout << "Memory allocation failure." << endl;
    return nullptr;
  }

  int k = 0;
  hMatrix[0] = 0;

  int indexInPattern = 1;
  while (indexInPattern < len) {
    if (pattern.at(indexInPattern) == pattern.at(k)) {
      k++;
      hMatrix[indexInPattern] = k;
      indexInPattern++;
    }
    else {
      if (k != 0) {
	k = hMatrix[k - 1];
      }
      else {
	hMatrix[indexInPattern] = 0;
	indexInPattern++;
      }
    }
  }
      
  return hMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern) {
  int lenText = text.length();
  int lenPat = pattern.length();

  int indexInText, indexInPat;

  indexInText = indexInPat = 0;

  while ((lenText - indexInText) >= (lenPat - indexInPat)) {
    if (pattern.at(indexInPat) == text.at(indexInText)) {
      indexInPat ++;
      indexInText ++;
    }
    if (indexInPat == lenPat) {
      int startMatch = indexInText - lenPat;
      logFile << "Found match at index " << startMatch << endl;
      return startMatch;
    }
    else {
      if ((indexInText < lenText) && (pattern.at(indexInPat) != text.at(indexInText))) {
	if (indexInPat != 0) {
	  indexInPat = hMatrix[indexInPat - 1];
	}
	else {
	  indexInText = indexInText + 1;
	}
      }
    }
  }
  return -1;
}

#endif
