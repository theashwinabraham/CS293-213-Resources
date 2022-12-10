/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void red()
{
    printf("\033[1;31m");
}

void reset()
{
    printf("\033[0m");
}

// returns fail array (size m + 1)
// fail[i] becomes the longest proper suffix of {pattern[0] ... pattern[i-1]} that is a prefix of it
// note that fail[i] < i, always
int* preprocessing(const char* pattern)
{
    int m = strlen(pattern);
    int* fail = malloc((1+m)*sizeof(int));
    for(int i = 0; i < (1+m); ++i)
    {
        if(i == 0)
        {
            fail[i] = -1; // never used
            continue;
        }
        if(i == 1)
        {
            fail[i] = 0;
            continue;
        }
        // We run a variant of the KMP algorithm on the string itself
        fail[i] = -1;
        int x;
        for(x = fail[i - 1]; pattern[x] != pattern[i-1]; x = fail[x])
        {
            if(x == 0)
            {
                fail[i] = 0;
                break;
            }
        }
        if(fail[i] == -1) fail[i] = 1+x;
    }
    /* preprocessing */
    return fail;
}

int* first_match(const char* pattern, const char* text, int* numptr)
{
    int m = strlen(pattern), n = strlen(text);
    int* fail = preprocessing(pattern); // now fail[i] is the failure function of the ith element of pattern
    int* indices = malloc(4*sizeof(int));
    int size_alloc = 4;
    *numptr = 0;
    int findex = -1;
    for(int iptr = 0, jptr = 0; jptr < n;)
    {
        if(pattern[iptr] == text[jptr])
        {
            ++iptr;
            ++jptr;
            if(iptr == m)
            {
                findex = jptr - m; // will always be >= 0 and < n
                ++(*numptr);
                iptr = fail[iptr];
                if((*numptr) > size_alloc)
                {
                    size_alloc *= 2;
                    indices = realloc(indices, size_alloc*sizeof(int));
                }
                indices[(*numptr) - 1] = findex;
            }
        }
        else
        {
            if(iptr == 0)
            {
                ++jptr;
            }
            else
            {
                iptr = fail[iptr];
            }
        }
        if(m - iptr > n - jptr) break;
    }
    free(fail);
    return indices;
}

int main(int argc, char** argv)
{
    if(argc != 3)
    {
        printf("Usage: ./executable pattern text\n");
        return 0;
    }

    int m = strlen(argv[1]), n = strlen(argv[2]);
    int num_occ;
    int* numptrs = first_match(argv[1], argv[2], &num_occ);

    if(num_occ == 0)
    {
        printf("%s\n", argv[2]);
        free(numptrs);
        return 0;
    }
    for(int i = 0, j = 0, k = 0; i<n; ++i)
    {
        if(i == numptrs[j])
        {
            red();
            ++j;
        }
        if(i == numptrs[k] + m)
        {
            ++k;
            if(k >= j) reset();
        }
        printf("%c", argv[2][i]);
    }
    reset();
    printf("\n");
    printf("%d\n", num_occ);
    free(numptrs);
    return 0;
}