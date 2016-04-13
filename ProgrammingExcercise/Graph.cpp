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

        // check if end has been reached
        if (buffer == "end") {
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
    }
    // return new graph, created by the vertices vector
    return new Graph(vertices);
}

// private method which returns the greatest degree of the graph
int Graph::getMaxDeg() {

    int temp{0};
    int max{0};
    for(auto ival : vertices) {
        if((temp = ival->getDegree()) > max) {
            max = temp;
        }
    }
    return max;
}






