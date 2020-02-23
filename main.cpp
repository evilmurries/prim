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
    bool usageFlag;

public:
    /*
     * This method is an initializer for class Edge.
     */
    void init(int* edgeArray) {
        vertA = edgeArray[0];
        vertB = edgeArray[1];
        weight = edgeArray[2];
        usageFlag = false;
    }

public:
    // This method returns the weight for the edge.
    int getWeight() {
        return weight;
    }

    /*
     * This method sets the inMST bool to true.
     */
    void addToMST() {
        usageFlag = true;
    }

    /*
     * Returns whether the edge is in the MST already or not.
     */
    bool isUsedAlready() {
        return usageFlag;
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
    int edgeCount;
    bool visited = false;
    vector<Edge> connectedEdges;

public:

    /*
     * This method initializes a new Vertex object.
     */
    void init(int name) {
        vertexNum = name;
    }

    /*
     * This method returns a boolean representing the visited status of the
     * Vertex.
     */
    bool wasVisited() {
        return visited;
    }

    /*
     * This method receives a boolean and sets that as the wasVisited status
     * for the Vertex.
     */
    void setVisited() {
        visited = true;
    }

    /*
     * This method returns the edges connected to the Vertex.
     */
    vector<Edge> getEdges() {
        return connectedEdges;
    }

    /*
     * This method receives an edge and stores it within the vertex object.
     */
    void addEdge(Edge e) {
        connectedEdges.push_back(e);
        edgeCount++;
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
    Vertex workingNode;
    vector<Edge> edges;
    vector<Vertex> vertices;
    vector<Edge> MST;

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
            newEdge.init(edgeInfo);
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
    // Implement Prim's algorithm
    int visitedNodes = 0;
    int currentNode = startingVertex - 1;
    while (visitedNodes < vertCount - 1) {
        visitedNodes++;
        int minWeight = 100000;
        Vertex nodeCandidate;
        vector<Edge> nodeEdges = vertices[currentNode].getEdges();
        Edge edgeCandidate;

        // examine each edge
        for (auto & edge : edges) {
            // if the edge is not used, and the weight is lowest thus far,
            // record the edge and accompanying vertex details
            Vertex start = vertices[edge.getStart() - 1];
            Vertex end = vertices[edge.getEnd() - 1];
            Vertex destination;

            if (start.getVNum() == vertices[currentNode].getVNum() || end.getVNum() == vertices[currentNode].getVNum()) {
                if (end.getVNum() == vertices[currentNode].getVNum()) {
                    destination = start;
                } else {
                    destination = end;
                }
                // destination cannot be already visited, edge has to be the minimum thus far, and not used.
                if (!destination.wasVisited() && (edge.getWeight() < minWeight) && !edge.isUsedAlready()) {
                    minWeight = edge.getWeight();
                    edgeCandidate = edge;
                    nodeCandidate = destination;
                }
            }
        }

        // Lowest weight edge found. Record data.
        vertices[currentNode].setVisited();
        MST.push_back(edgeCandidate);
        edgeCandidate.addToMST();
        cout << "New edge: " << edgeCandidate.getStart() << ",";
        cout << edgeCandidate.getEnd() << " - cost ";
        cout << edgeCandidate.getWeight() << endl;
        edgeCandidate.addToMST();
        currentNode = nodeCandidate.getVNum() - 1;
    }

    return 0;
}
