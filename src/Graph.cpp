//
//  Graph.cpp
//  GraphTheory
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
                    // now check if vertex and neighbor have a same neighbor
                    for (auto i : vertices.at(ival-1)->getNeighbors()) {
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

// apply greedy coloring algorithm to graph with standat sequence [1,...,n]
void Graph::applyGreedyColoring() {
    // erase the current coloring first
    eraseColoring();
    for (int i = 0; i < vertices.size(); i++) {
        std::vector<unsigned int> N;
        for (auto jval : vertices.at(i)->getNeighbors()) {
            if (jval < i+1) {
                N.push_back(vertices.at(jval-1)->getColor());
            }
            if (jval > i+1) {
                break;
            }
        }
        // determine the minimum color in N which can be assigned to the current
        // vertex, colors starting with index 1
        unsigned int color = 1;
        std::sort(N.begin(), N.end());
        for(const auto ival : N) {
            // starting with 1, compare color with colors in N, the first occurance,
            // where color is not equal to its counterpart in N, thats the minimum
            // color which can be used to color the current vertex
            if (color == ival) {
                color++;
            }
            else {
                break;
            }
        }
         // color current vertex with minimum color
        vertices.at(i)->setColor(color);
    }
    return;
}

// provide a sequence in which order the greedy coloring algorithm shall be applied
void Graph::applyGreedyColoringWithSequence(std::vector<unsigned int> &seq) {
    // erase the current coloring first
    eraseColoring();
    // traverse trough each vertex of the graph
    for (int i = 0; i < vertices.size(); i++) {
        std::vector<unsigned int> N;
        // for each vertex get the colors of its neighbors
        for (auto jval : vertices.at(seq.at(i))->getNeighbors()) {
            if (jval < i+1) {
                // store colors of neighbors in N
                N.push_back(vertices.at(seq.at(jval-1))->getColor());
            }
            // if neighbor (j) is greater than current vertex (i), break the inner for loop,
            // cause neighbors are sorted and greater ones have not been colored yet
            if (jval > i+1) {
                break;
            }
        }
        // determine the minimum color in N which can be assigned to the current
        // vertex, colors starting with index 1
        unsigned int color = 1;
        std::sort(N.begin(), N.end());
        for(const auto ival : N) {
            if (color == ival) {
                color++;
            }
        }
        // color current vertex with minimum color
        vertices.at(i)->setColor(color);
    }
    return;
}

unsigned int Graph::getNumberColors() const {
    unsigned int numberOfColors{0};
    for (const auto ival : vertices) {
        if (ival->getColor() > numberOfColors) {
            numberOfColors = ival->getColor();
        }
    }
    return numberOfColors;
}

unsigned int Graph::getMinNumberOfColors() {
    std::vector<unsigned int> numOfColors;
    // sequence to be used as random index for Vertex selection
    std::vector<unsigned int> sequence;
    // put values into sequence
    for (int k = 0; k < vertices.size(); k++) {
        sequence.push_back(k);
    }
    for (int i = 0; i < 1000; i++) {
        // generate random number for shuffle algorithm
        std::random_device rd;
        std::mt19937 g(rd());
        // shuffle the sequence randomly
        std::shuffle(sequence.begin(), sequence.end(), g);
        // apply greedy coloring with sequence
        this->applyGreedyColoringWithSequence(sequence);
        // determine number of colors
        numOfColors.push_back(this->getNumberColors());
    }
    unsigned int minNumOfColors = numOfColors.at(0);
    for (auto ival : numOfColors) {
        if (ival < minNumOfColors) {
            minNumOfColors = ival;
        }
    }
    return minNumOfColors;
}


void Graph::eraseColoring() {
    for (auto ival : vertices) {
        ival->setColor(0);
    }
    return;
}

