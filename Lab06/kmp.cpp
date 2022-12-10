/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#ifndef KMP_CPP
#define KMP_CPP
#include <string.h>
#include <string>
#ifndef PLANNER_H
#include "planner.h"
#endif

using namespace std;

// returns H Matrix, where H[i] = fail(i) = longest proper suffix of [pattern[0], ... pattern[i]] that is a prefix of it
// empty string is also considered a proper suffix and a proper prefix
// clearly 0 <= H[i] <= i
int *Planner::computeHMatrixForKMP(string pattern)
{
    for(int i = 0; i<pattern.length(); ++i) pattern[i] = toupper(pattern[i]);

    int* HMatrix = new int [pattern.length()];
    for(int i = 0; i<pattern.length(); ++i)
    {
        if(i == 0)
        {
            HMatrix[i] = 0;
            continue;
        }
        // given H[0], ... H[i-1] we can compute H[i]
        // [0] ................. [i-1] [i]
        //          [0] ........ [x-1] [x]
        HMatrix[i] = 0;
        for(int x = HMatrix[i-1]; ; x = HMatrix[x-1])
        {
            if(pattern[x] == pattern[i])
            {
                HMatrix[i] = 1 + x;
            }
            if(x == 0) break;
        }
    }
    return HMatrix;
}

int Planner::KMPMatch(string text, int *hMatrix, string pattern)
{
    for(int i = 0; i<text.length(); ++i) text[i] = toupper(text[i]);
    for(int i = 0; i<pattern.length(); ++i) pattern[i] = toupper(pattern[i]);
    //int num_matches = 0;
    for(int i = 0, j = 0; i < text.length();)
    {
        if(text[i] == pattern[j])
        {
            if(i == text.length() - 1)
            {
                if(j == pattern.length() - 1)
                {
                    return i - pattern.length() + 1;
                }
                break;
            }
            else
            {
                if(j == pattern.length() - 1)
                {
                    return i - pattern.length() + 1;
                    j = hMatrix[j];
                }
                else ++j;
                ++i;
            }
        }
        else
        {
            if(j == 0) ++i;
            else j = hMatrix[j-1];
        }
    }
    return -1;
}

#endif
