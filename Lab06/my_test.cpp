#include <iostream>
#include <string>
using namespace std;
// returns H Matrix, where H[i] = fail(i) = longest proper suffix of [pattern[0], ... pattern[i]] that is a prefix of it
// empty string is also considered a proper suffix and a proper prefix
// clearly 0 <= H[i] <= i
int *computeHMatrixForKMP(string pattern)
{
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

int KMPMatch(string text, int *hMatrix, string pattern)
{
    int num_matches = 0;
    for(int i = 0, j = 0; i < text.length();)
    {
        if(text[i] == pattern[j])
        {
            if(i == text.length() - 1)
            {
                if(j == pattern.length() - 1)
                {
                    ++num_matches;
                }
                break;
            }
            else
            {
                if(j == pattern.length() - 1)
                {
                    ++num_matches;
                    j = hMatrix[j];
                }
                else
                {
                    ++j;
                }
                ++i;
            }
        }
        else
        {
            if(j == 0) ++i;
            else j = hMatrix[j-1];
        }
    }
    return num_matches;
}

int main(int argc, char** argv)
{
    cout << KMPMatch(argv[2], computeHMatrixForKMP(argv[1]), argv[1]) << '\n';
}