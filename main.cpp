/*
 * Title: prim.cpp Homework 6
 * Abstract: This program reads in an input file and constructs a graph from
 * which it implements prim's algorithm on.
 * Author: Christopher Piwarski
 * ID: 0026
 * Date: February 23, 2020
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/*
 * One object of class Edge represents a weighted edge on a graph.
 */
class Edge {
    int vertA;
    int vertB;
    int weight;

public:
    /*
     * This function is the initializer for class Edge.
     */
    void init(int begin, int end, int edgeWeight) {
        vertA = begin;
        vertB = end;
        weight = edgeWeight;
    }

    void init2(int* edgeArray) {
        vertA = edgeArray[0];
        vertB = edgeArray[1];
        weight = edgeArray[2];
    }

public:
    // This function returns the weight for the edge.
    int getWeight() {
        return weight;
    }

    // This function returns the first terminating Vertex.
    int getStart() {
        return vertA;
    }

    // This function returns the second terminating vertex.
    int getEnd() {
        return vertB;
    }

    void printEdge() {
        cout << "Edge Start | End | Weight: " << vertA << " ";
        cout << vertB << " " << weight;
        cout << endl;
    }
};

/*
 * One object of class Vertex represents a Vertex on a graph G.
 */
class Vertex {
    int edgeCount;
    int vertexNum;
    vector<Edge> connectedEdges;

public:
    void init(int name) {
        vertexNum = name;
    }

    int getVNum() {
        return vertexNum;
    }

    /*
     * This method prints all the Vertex objects that points to this vertex
     * on the digraph. Primarily used for debugging.
     */
    void printConnectedEdges() {
        if (edgeCount == 0) {
            return;
        }
        for (int i = 0; i < edgeCount; i++) {
            connectedEdges[i].printEdge();
        }
        cout << endl;
    }
};

int main() {

    int startingVertex;
    int vertCount;
    int edgeCount;
    vector<Edge> edges;
    vector<Vertex> vertices;

    string filename;
    ifstream file;

    // get default user information
    cout << "Enter a file name: ";
    cin >> filename;
    cout << "Enter the first vertex to start: ";
    cin >> startingVertex;

    // parse file
    file.open(filename);
    if (file.is_open()) {
        string line;
        getline(file, line);
        vertCount = stoi(line);

        for (int i = 0; i < vertCount; i++) {
            Vertex newNode;
            newNode.init(i);
            vertices.push_back(newNode);
        }

        getline(file, line);
        edgeCount = stoi(line);

        // Process edge information
        for (int i = 0; i < edgeCount; i++) {
            getline(file, line);
            stringstream sstream (line);
            int value = 0;
            int* edgeInfo = new int[vertCount - 1];
            int j = 0;
            while (sstream >> value) {
                edgeInfo[j] = value;
                j++;
            }
            Edge newEdge;
            newEdge.init2(edgeInfo);
            edges.push_back(newEdge);
        }
    } else {
        cout << "Failure to open file. Program ending.";
        return 1;
    }
    file.close();

    for (int i = 0; i < vertices.size(); i++) {
        cout << vertices[i].getVNum() << " ";
    }
    cout << endl;

    for (int i = 0; i < edges.size(); i++) {
        edges[i].printEdge();
    }
    cout << endl;

    return 0;
}
