//
//  Graph.cpp
//  ProgrammingExcercises
//
//  Created by Paavo Becker on 06.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#include "Graph.hpp"

//constructor
Graph::Graph(const std::vector<Vertex*>& vertices) : vertices(vertices) {}
//destructor
Graph::~Graph() {
    //delete[] vertices;
}

//class method, which creates a graph from a given stream
Graph* Graph::getGraphFromStream(std::ifstream &file) {

    // buffer for lines in graphfile
    std::string buffer;
    // regex to filter numbers in line
    std::regex pattern("([0-9]+)");

    // empty vertices vector
    std::vector<Vertex*> vertices;
    // vertices counter
    int i = 0;

    while(getline(file, buffer)) {
        
        std::smatch m;
        if (std::regex_search(buffer, m, std::regex("end"))) {
            break;
        }

        //vector for neigbours
        std::vector<int> neighbours;

        // find all matches in line
        std::sregex_iterator next(buffer.begin(), buffer.end(), pattern);
        std::sregex_iterator end;
        while (next != end) {
            std::smatch match = *next;
            // push match into neighbours vector
            neighbours.push_back(stoi(match.str()));
            next++;
        }
        //put new Vertex into vertices vector, initialized with its number and
        //neighbours
        vertices.push_back(new Vertex(i, neighbours));

        // increase i for number of next vertex
        i++;
    }
    // return new graph, created by the vertices vector
    return new Graph(vertices);
}

// private method which returns the greatest degree of the graph
int Graph::getMaxDeg() const {

    int temp{0};
    int max{0};
    for(auto ival : vertices) {
        if((temp = ival->getDegree()) > max) {
            max = temp;
        }
    }
    return max;
}

// private method which returns the number of vertices
unsigned long Graph::getNumberOfVertices() const {
    return vertices.size();
}

// private method which returns the average degree ot the graph
// sum of all edges / number of nodes
double Graph::getAverageDeg() const {
    double numOfEdges = 0;
    for (auto ival : vertices) {
        numOfEdges += ival->getDegree();
    }
    return numOfEdges / getNumberOfVertices();
}

unsigned long Graph::getNumberOfVerticesWithoutNeighbors() const {
    unsigned long numberOfVerticesWithoutNeighbors = 0;
    for (auto ival : vertices) {
        if (ival->getDegree() == 0) {
            numberOfVerticesWithoutNeighbors++;
        }
    }
    return numberOfVerticesWithoutNeighbors;
}

unsigned int Graph::getNumberOfTriangles() const {
    // the graph file counts the vertices starting with 1
    // a.e. the vector addressing has to be shifted by 1
    unsigned int numberOfTriangles{0};
    for (auto vertex : vertices) {
        // only take vertices with more than one neighbor into concideration
        if (vertex->getDegree() > 1) {
            for (auto ival : vertex->getNeighbors()) {
                // only check for neighbors with higher number, to prevent Triangles to be detected more than once
                if (ival > (vertex->getNumber()+1)) {
                    Vertex *neighbor = vertices.at(ival-1);
                    // now check if vertex and neighbor have a same neighbor
                    for (auto i : neighbor->getNeighbors()) {
                        if (vertex->checkForNeighbor(i) && i > ival) {
                            numberOfTriangles++;
                            //std::cout << vertex->getNumber()+1 << " " << ival << " " << i << std::endl;
                        }
                    }
                }
            }
        }
    }
    return numberOfTriangles;
}






