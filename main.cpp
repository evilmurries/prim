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
    int vertexNum;
    vector<Edge> connectedEdges;

public:

    /*
     * This method initializes a new Vertex object.
     */
    void init(int name) {
        vertexNum = name;
    }

    /*
     * This method receives an edge and stores it within the vertex object.
     */
    void addEdge(Edge e) {
        connectedEdges.push_back(e);
    }
    /*
     * This method returns the integer name of the Vertex.
     */
    int getVNum() {
        return vertexNum;
    }

    /*
     * This method prints all the Vertex objects that points to this vertex
     * on the digraph. Primarily used for debugging.
     */
    void printConnectedEdges() {
//        if (connectedEdges.size() == 0) {
//            return;
//        }
        cout << "Vertex: " << getVNum();
        cout << endl;
        for (int i = 0; i < connectedEdges.size(); i++) {
            connectedEdges[i].printEdge();
        }
        cout << endl;
    }
};

/*
 * Function main governs the general operation of prim.cpp
 */
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
            newNode.init(i + 1);
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

    // Link edges to vertices
    for (int i = 0; i < vertices.size(); i++) {
        for (int j = 0; j < edges.size(); j++) {
            if (vertices[i].getVNum() == edges[j].getStart() ||
            vertices[i].getVNum() == edges[j].getEnd()) {
                vertices[i].addEdge(edges[j]);
            }
        }
    }

    return 0;
}
