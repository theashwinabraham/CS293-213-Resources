/*
 * IMPLEMENTED BY: ASHWIN ABRAHAM
 */

#ifndef GRAPH_BST_H
#define GRAPH_BST_H

#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

template <typename T>
struct List {
    T obj;
    List<T>* next;

    List(const T& Obj): obj(Obj) {}
};

// template<typename T>
// struct List {
//     public:
//         listobj<T>* start;
//         listobj<T>* end;

//         List(): start(nullptr), end(nullptr) {}

//         insert(T obj)
//         {
//             if(start == nullptr)
//             {
//                 start = new listobj
//             }
//         }
// }

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int x): val(x), left(nullptr), right(nullptr) {}
};

class BST {
    // Add your own field and members here

    // Feel free to use the printBST function used earlier
    public:
        TreeNode* root;

        BST(TreeNode* ptr = nullptr): root(ptr) {}

        void insert(int x)
        {
            if(root == nullptr) root = new TreeNode(x);
            else
            {
                if(x <= root->val)
                {
                    if(root->left == nullptr) root->left = new TreeNode(x);
                    else BST(root->left).insert(x);
                }
                else
                {
                    if(root->right == nullptr) root->right = new TreeNode(x);
                    else BST(root->right).insert(x);
                }
            }
        }

        void printBST(const string& prefix, bool isLeft =false)
        {
            if( root != nullptr )
            {
                cout << prefix;

                cout << (isLeft ? "|--" : "|__" );

                // print the value of the node
                cout << root->val << endl;
                TreeNode *curr = root;
                root = root->left;
                // enter the next tree level - left and right branch
                printBST( prefix + (isLeft ? "│   " : "    "), true);
                root = curr->right;
                printBST( prefix + (isLeft ? "│   " : "    "), false);
                root = curr;
            }
        }
};

struct Pair {
    int val;
    bool allowed;

    Pair(int x): val(x), allowed(true) {}
};

class Node
{
    public:
        int value;

        // insert other fields and methods as appropriate
        List<Pair> *neighbours;

};

class Graph
{
    int numNodes;
    int numEdges;
    fstream graphFile;

    Node *nodes;

    // Add appropriate fields as necessary for your implementation
    List<BST*> *bsts;
    int num_connected;

    int* visit_count;
    bool* in_cycle;
    int* parents;

    public:
        Graph(int nNodes, int nEdges, string gFileName): bsts(nullptr), num_connected(0)
        {
            numNodes = nNodes;
            numEdges = nEdges;
            graphFile.open(gFileName, ios::out);
            if (!graphFile.is_open())
            {
                cerr << "Couldn't open graph file " << gFileName << ". Aborting ..." << endl;
                exit(-1);
            }

            graphFile << numNodes << endl;
            graphFile << numEdges << endl;

            nodes = new Node[numNodes];
            visit_count = new int[numNodes];
            in_cycle = new bool[numNodes];
            parents = new int[numNodes];
            for(int i = 0; i<numNodes; ++i)
            {
                visit_count[i] = 0;
                in_cycle[i] = false;
                parents[i] = -1;
            }

            if (nodes == nullptr)
            {
                cerr << "Memory allocation failure." << endl;
                exit(-1);
            }

            for (int i = 0; i < numNodes; i++)
            {
                nodes[i].value = i + 1;
            }

            srand(time(0));
            int n1, n2;
            int countEdges = 0;

            while (countEdges < numEdges)
            {
                // do
                // {
                //     n1 = rand() % numNodes;
                //     n2 = rand() % numNodes;
                //     // std::cout << n1 << " LMAO " << n2 << std::endl;
                // } while (n1 == n2);
                if(countEdges == 0)
                {
                    n1 = 0;
                    n2 = 1;
                }
                else if(countEdges == 1)
                {
                    n1 = 1;
                    n2 = 2;
                }
                else if(countEdges == 2)
                {
                    n1 = 2;
                    n2 = 3;
                }
                else if(countEdges == 3)
                {
                    n1 = 3;
                    n2 = 1;
                }
                else if(countEdges == 4)
                {
                    n1 = 1;
                    n2 = 4;
                }
                else if(countEdges == 5)
                {
                    n1 = 4;
                    n2 = 5;
                }
                else if(countEdges == 6)
                {
                    n1 = 5;
                    n2 = 1;
                }
                else break;

                // Create an undirected edge from n1 to n2 and store in appropriate
                // adjacency list(s).  If an undirected edge from n1 to n2 (or
                // equivalently from n2 to n1) already exists, you shouldn't add
                // an edge.  Only if such an undirected edge didn't exist earlier,
                // should you add the edge and increment countEdges; otherwise,
                // do not increment countEdges;
                // Every time an edge is created, we also add that information to
                // graphFile
                bool present = false;
                for(List<Pair>* val = nodes[n1].neighbours; val != nullptr; val = val->next)
                {
                    if(val->obj.val == n2)
                    {
                        present = true;
                        break;
                    }
                }
                if(!present)
                {
                    List<Pair> *old = nodes[n1].neighbours;
                    nodes[n1].neighbours = new List<Pair>(n2);
                    nodes[n1].neighbours->next = old;

                    old = nodes[n2].neighbours;
                    nodes[n2].neighbours = new List<Pair>(n1);
                    nodes[n2].neighbours->next = old;

                    graphFile << n1 + 1 << " " << n2 + 1 << endl;
                    countEdges++;
                }
            }

            // Add appropriate code as necessary for your implementation
        }

        ~Graph()
        {
            if (graphFile.is_open())
            {
                graphFile.close();
            }
            delete[] nodes;
            // Add appropriate code as necessary for your implementation
        }

        // Add appropriate method declarations as necessary for your implementation

        void modifiedDFS(int start = 0);
        void printResults();
};

#endif
