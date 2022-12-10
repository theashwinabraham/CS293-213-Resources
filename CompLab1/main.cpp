#ifndef STD_HEADERS_H
#include "std_headers.h"
#endif

using namespace std;

#ifndef GRAPH_BST_CPP
#include "Graph.cpp"
#endif

int main(int argc, char **argv)
{
    Graph *myGraph;

    if (argc != 4)
    {
        cerr << "Usage: " << argv[0] << " numNodes numEdges graphFile" << endl;
    }

    int numNodes = stoi(argv[1]);
    int numEdges = stoi(argv[2]);
    string graphFileName = argv[3];

    myGraph = new Graph(numNodes, numEdges, graphFileName);
    if (myGraph == nullptr)
    {
        cerr << "Memory allocation failure." << endl;
        exit(-1);
    }

    myGraph->modifiedDFS();
    myGraph->printResults();

    return 0;
}
