/*
* AUTHOR: ASHWIN ABRAHAM
*/

#ifndef QUEUE_HPP
#define QUEUE_HPP
#include <vector>
#include <iostream>

namespace cpp_STL {
    template <typename T>
    class Queue {
    private:
        std::vector<T> queue;
        unsigned int front;
        unsigned int size;
    public:
        Queue(): front(0), queue(0), size(0){}

        void enqueue(const T& obj)
        {
            if(size == queue.size()) queue.insert(front == 0? queue.end():(queue.begin()+front-1));
            else queue[(front+size)%queue.size()] = obj;
            ++size;
        }

        T dequeue()
        {
            if(size == 0) throw "Empty Queue";
            --size;
            T val = queue[front];
            front = (1+front)%queue.size();
            return val;
        }

        const T& operator[](int i) const
        {
            if(i>=size || i < -size) throw "Index out of Bounds";
            if(i < 0) i+=size;
            return queue[(front+i)%queue.size()]
        }

        T& operator[](int i)
        {
            if(i>=size || i < -size) throw "Index out of Bounds";
            if(i < 0) i+=size;
            return queue[(front+i)%queue.size()]
        }
    };
}
#endif