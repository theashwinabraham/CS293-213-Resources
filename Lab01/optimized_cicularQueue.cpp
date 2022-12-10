/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#include "queue.h"
#include <cstring>

// is the queue empty?
// In the circular queue, we always have tail == (head + size)%N
// if tail == head, we either have size == 0 or size == N (either queue is empty or queue is full)
// given the head and tail alone, we cannot in general figure out whether the queue is full or empty, without knowing it's previous history
// Therefore, when tail becomes head - 1 (or when tail == N-1 and head == 0), we immediately grow the array
// hence isFull is never true
template <typename T>
inline bool DynamicQueue<T>::isEmpty()
{
    return head == tail;
}

// is the queue full?
// In the circular queue, we always have tail == (head + size)%N
// if tail == head, we either have size == 0 or size == N (either queue is empty or queue is full)
// given the head and tail alone, we cannot in general figure out whether the queue is full or empty, without knowing it's previous history
// Therefore, when tail becomes head - 1 (or when tail == N and head == 0), we immediately grow the array
// hence isFull is never true
template <typename T>
inline bool DynamicQueue<T>::isFull()
{
    return false;
}

// grow the queue to its next size
// creates a larger array on the heap and copies the contents of the old array to the new array
// in such a way that, the entire queue is stored contiguously starting at 0
template <typename T>
void DynamicQueue<T>::grow()
{
    unsigned int nN = nextSize();
    A = reinterpret_cast<T*>(realloc(A, nN*sizeof(T)));
    if(tail < head)
    {
        unsigned int min = (nN - N < tail ? nN - N : tail);
        memmove(A+N, A, min*sizeof(T));
        if(nN - N <= tail)
        {
            memmove(A, A+nN-N, (tail-nN+N)*sizeof(T));
            tail-=(nN-N);
        }
        else tail+=N;
    }
    N = nN;
}

// return the current number of elements in the queue
template <typename T>
unsigned int DynamicQueue<T>::size()
{
    return tail < head ? N+tail-head : tail-head;
}

// insert given element at tail of the queue; grow array size as necessary
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    if(tail == head-1 || (head == 0 && tail == N-1))
    {
        grow();
        A[tail] = x;
        tail = (tail+1)%N;
    }
    else
    {
        A[tail] = x;
        tail = (tail+1)%N;
    }
}

// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
template <typename T>
bool DynamicQueue<T>::QDelete(T* x)
{
    if(head == tail) return false;
    *x = A[head];
    head = (1+head)%N;
    return true;
}