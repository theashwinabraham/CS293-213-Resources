#include <iostream>
#include <vector>
#include <utility>
#include <cstdint>
#include <string>
#include <array>
#include <list>

// Key = Phone Number, Value = Name
// NIL represented by ""
// If a phone number already exists, insert returns false

class UnorderedListImp { // Useful when insertion is the most common operation (if we don't impose uniqueness, insertion is O(1)) (log sheets)
    private:
        std::list<std::pair<uint64_t, std::string>> list; // Array of Key-Value Pairs (Memory O(n), Construction O(1))

    public:
        bool insert(uint64_t pn, const std::string& name) // Insertion O(n)
        {
            for(std::list<std::pair<uint64_t, std::string>>::iterator it = list.begin(); it != list.end(); ++it)
            {
                if(it->first == pn) return false;
            }
            list.push_back(std::pair<uint64_t, std::string>(pn, name)); // actual insertion is only O(1)
            return true;
        }

        std::string remove(uint64_t pn) // deletion O(n)
        {
            for(std::list<std::pair<uint64_t, std::string>>::iterator it = list.begin(); it != list.end(); ++it)
            {
                if(it->first == pn)
                {
                    std::string s = it->second;
                    list.erase(it);
                    return s;
                }
            }
            return "";
        }

        std::string get(uint64_t pn) // retrieval O(n)
        {
            for(std::list<std::pair<uint64_t, std::string>>::iterator it = list.begin(); it != list.end(); ++it)
            {
                if(it->first == pn)
                {
                    return it->second;
                }
            }
            return "";
        }
};

class OrderedListImp { // Usefull when searching is the most common operation (lookup tables)
    private:
        std::vector<std::pair<uint64_t, std::string>> list; // Array of Key-Value Pairs (Memory O(n), Construction O(1))

    public:
        bool insert(uint64_t pn, const std::string& name) // Insertion O(n)
        {
            int range = list.size();
            int pos = 0;
            while(range > 0)
            {
                if(list[pos + range/2].first < pn)
                {
                    pos += 1 + range/2;
                    range = (range - range/2 - 1);
                }
                range /= 2;
            }
            if(pos < list.size() && list[pos].first == pn) return false;
            list.insert(list.begin()+pos, std::pair<uint64_t, std::string>(pn, name));
            return true;
        }

        std::string remove(uint64_t pn) // deletion O(n)
        {
            int range = list.size();
            int pos = 0;
            while(range > 0)
            {
                if(list[pos + range/2].first < pn)
                {
                    pos += 1 + range/2;
                    range = (range - range/2 - 1);
                }
                range /= 2;
            }
            if(pos < list.size() && list[pos].first == pn)
            {
                std::string s = list[pos].second;
                list.erase(list.begin()+pos);
                return s;
            }
            return "";
        }

        std::string get(uint64_t pn) // retrieval O(log n)
        {
            int range = list.size();
            int pos = 0;
            while(range > 0)
            {
                if(list[pos + range/2].first < pn)
                {
                    pos += 1 + range/2;
                    range = (range - range/2 - 1);
                }
                range /= 2;
            }
            if(pos < list.size() && list[pos].first == pn) return list[pos].second;
            return "";
        }
};

#define num_poss 10000000000ul
class TrivialHashImpl { // Direct Addressing method (Huge Waste Of Memory)
    private:
        std::array<std::string, num_poss> arr;
    
    public:
        TrivialHashImpl() // Construction O(total), Memory O(total)
        {
            arr.fill("");
        }

        bool insert(uint64_t pn, const std::string& name) // Insertion O(1)
        {
            if(arr[pn] != "") return false;
            arr[pn] = name;
            return true;
        }

        std::string remove(uint64_t pn) // Deletion O(1)
        {
            std::string s = arr[pn];
            arr[pn] = "";
            return s;
        }

        std::string get(uint64_t pn) // Retrieval O(1)
        {
            return arr[pn];
        }
};

int main()
{
    return 0;
}