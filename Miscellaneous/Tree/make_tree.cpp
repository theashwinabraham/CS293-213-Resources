/*
 * AUTHOR: ASHWIN ABRAHAM
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <set>

class BTree {
    private:
        int value;
        BTree* left;
        BTree* right;

    public:
        BTree(int val, BTree* l = nullptr, BTree* r = nullptr): left(l), right(r) {}

        void set_left(BTree* tree)
        {
            left = tree;
        }

        void set_right(BTree* tree)
        {
            right = tree;
        }

        void preorder()
        {
            std::cout << value << ' ';
            if(left != nullptr) left->preorder();
            if(right != nullptr) right->preorder();
        }

        void inorder()
        {
            if(left != nullptr) left->inorder();
            std::cout << value << ' ';
            if(right != nullptr) right->inorder();
        }

        void postorder()
        {
            if(left != nullptr) left->postorder();
            if(right != nullptr) right->postorder();
            std::cout << value << ' ';
        }
};

BTree prein(const std::string::iterator& pre_begin, const std::string::iterator& pre_end, const std::string::iterator& in_begin, const std::string::iterator& in_end)
{
    std::string::iterator pos = std::find(in_begin, in_end, *pre_begin);
    BTree b(*pre_begin);
    b.set_left(pre_begin)
}