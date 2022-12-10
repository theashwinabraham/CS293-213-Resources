/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#include "queue.h"
#include <cstring>

// is the queue empty?
// In the linear queue, we have head =< tail, at all times
// head == tail, iff the queue is empty
template <typename T>
inline bool DynamicQueue<T>::isEmpty()
{
    return head == tail;
}

// is the queue full?
// The linear queue is full, iff every element in the current array is occupied
// The number of elements in the linear queue is tail - head, and the array size is N
// hence we get the condition to be N == (tail-head)
template <typename T>
inline bool DynamicQueue<T>::isFull()
{
    return N == (tail - head);
}

// grow the queue to its next size
// creates a larger array on the heap and copies the contents of the old array to the new array
template <typename T>
void DynamicQueue<T>::grow()
{
    N = nextSize();
    A = reinterpret_cast<T*>(realloc(A, N*sizeof(T)));
}

// return the current number of elements in the queue
// number of elements in the queue is tail - head
template <typename T>
inline unsigned int DynamicQueue<T>::size()
{
    return tail - head;
}

// insert given element at tail of the queue; grow array size as necessary
template <typename T>
void DynamicQueue<T>::QInsert(T x)
{
    // if there is space at the back of the array, we add at the back
    if(tail < N)
    {
        A[tail] = x;
        ++tail;
    }
    else
    {
        // if there is no space at the back, but space at the front, we shift all elements to the front
        // then add at the back
        if(head > 0)
        {
            memmove(A, A+head, (tail-head)*sizeof(T));
            tail-=head;
            head = 0;
            A[tail] = x;
            ++tail;
        }
        else
        {
            // if there is no space in the array, we grow the array, then add at the back
            grow();
            A[tail] = x;
            ++tail;
        }
    }
}

// delete element at head of the queue and place it in *T; returns false if queue is empty, true otherwise
template <typename T>
bool DynamicQueue<T>::QDelete(T* x)
{
    if(head == tail) return false;
    *x = A[head];
    ++head;
    return true;
}