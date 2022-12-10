/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <iostream>
#include <array>
#include <queue>
#include <deque>

struct Student {
    unsigned int Hostel;
    int id;
};

class MessQueue {
    private:
        const unsigned int hostel_num;
        std::vector<std::queue<int>> ind_queues;
        std::deque<unsigned int> overall_queue;
        unsigned int size;

    public:
        MessQueue(unsigned int hnum): hostel_num(hnum), ind_queues(hnum), size(0) {}

        void push(Student s)
        {
            ++size;
            ind_queues.push_back(s.id);
            for(int i = 0; i<overall_queue.size(); ++i) if(overall_queue[i] == s.Hostel) return;
            overall_queue.push_back(s.Hostel);
        }

        Student pop()
        {
            if(overall_queue.size() == 0) throw "Empty Queue Error";
            --size;
            Student s;
            s.Hostel = overall_queue[0];
            s.id = ind_queues[overall_queue[0]].pop();
            if(ind_queues[overall_queue[0]].size() == 0) overall_queue.pop_front();
            return s;
        }

        Student front()
        {
            if(overall_queue.size() == 0) throw "Empty Queue Error";
            return {overall_queue[0], ind_queues[overall_queue[0]].front()};
        }

        unsigned int size()
        {
            return size;
        }
};

int main()
{
    return 0;
}