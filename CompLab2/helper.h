/*
 * AUTHOR: ASHWIN ABRAHAM
 */

template <typename T>
struct ListObject {
    T obj;
    ListObject<T>* next;

    ListObject(const T &obj): obj(obj), next(nullptr) {}
};

template <typename T>
struct List {
    ListObject<T>* head;
    unsigned int size;

    List(): head(nullptr), size(0) {}

    void insert(const T& obj)
    {
        if(head == nullptr)
        {
            head = new ListObject<T>(obj);
        }
        else
        {
            ListObject<T>* old_head = head;
            head = new ListObject<T>(obj);
            head->next = old_head;
        }
        ++size;
    }

    // ~List()
    // {
    //     for(ListObject<T>* ptr = head; ptr != nullptr; ptr = ptr->next)
    //     {
    //         delete ptr;
    //     }
    // }
};

struct Pair {
    unsigned int x, y;

    Pair(unsigned int a, unsigned int b): x(a), y(b) {}
};