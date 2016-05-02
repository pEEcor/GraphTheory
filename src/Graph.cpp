//
//  Graph.cpp
//  GraphTheory
//
//  Created by Paavo Becker on 06.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#include "Graph.hpp"

// constructor
Graph::Graph(const std::vector<Vertex*>& vertices) : vertices(vertices) {}

// destructor
Graph::~Graph() {
    while (!vertices.empty()) {
        // delete each Vertex
        delete vertices.back();
        // and pop their pointer from the vertices vector
        vertices.pop_back();
    };
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

        //vector for neighbours
        std::vector<int> neighbors;

        // find all matches in line
        std::sregex_iterator next(buffer.begin(), buffer.end(), pattern);
        std::sregex_iterator end;
        while (next != end) {
            std::smatch match = *next;
            // push match into neighbours vector
            neighbors.push_back(stoi(match.str()));
            next++;
        }
        //put new Vertex into vertices vector, initialized with its number and
        //neighbours
        vertices.push_back(new Vertex(i, neighbors));

        // increase i for number of next vertex
        i++;
    }
    // return new graph, created by the vertices vector
    return new Graph(vertices);
}

Graph *Graph::getRandomGraph(unsigned int numOfKnots, float EdgeProb) {
    // generate vertices vector
    std::vector<Vertex*> vertices;
    for (int i = 0; i < numOfKnots; ++i) {
        std::vector<int> neighbors;
        vertices.push_back(new Vertex(i, neighbors));
    }
    // determine neighbors and put them into vertices
    // generate some randomness
    std::random_device seed;
    std::mt19937 g(seed());
    // get distribution according to specified probability p
    std::uniform_int_distribution<int> uniDistribution(0, 1/EdgeProb);
    for (auto vertex : vertices) {
        for (int j = (int)vertex->getNumber(); j < numOfKnots; ++j) {
            if (uniDistribution(g) == 0) {
                vertex->addNeigbor((unsigned int)j);
                vertices.at(j-1)->addNeigbor((unsigned int)vertex->getNumber()+1);
            }
        }
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

// method which returns the number of vertices
unsigned long Graph::getNumberOfVertices() const {
    return vertices.size();
}

// methed to return the number of vertices with a given deg
auto Graph::getNumberOfVerticesWithDeg(const int deg) const -> unsigned int {
    unsigned int counter{0};
    for (auto ival : vertices) {
        if (ival->getNeighbors().size() == deg) {
            counter++;
        }
    }
    return counter;
}

// method which returns the average degree ot the graph
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

auto Graph::getTriangles() const -> std::vector<std::vector<unsigned int>*>* {
    std::vector<std::vector<unsigned int>*>* vec;
    vec = new std::vector<std::vector<unsigned int>*>;
    for (auto vertex : vertices) {
        // only take vertices with more than one neighbor into concideration
        if (vertex->getDegree() > 1) {
            for (auto ival : vertex->getNeighbors()) {
                // only check for neighbors with higher number, to prevent Triangles to be detected more than once
                if (ival > (vertex->getNumber()+1)) {
                    // now check if vertex and neighbor have a same neighbor
                    for (auto i : vertices.at((unsigned long) ival-1)->getNeighbors()) {
                        if (i > ival && vertex->checkForNeighbor(i)) {
                            std::vector<unsigned int>* x = new std::vector<unsigned int>();
                            x->push_back((unsigned int)vertex->getNumber()+1);
                            x->push_back((const unsigned int &) ival);
                            x->push_back((const unsigned int &) i);
                            vec->push_back(x);
                        }
                    }
                }
            }
        }
    }
    return vec;
}

auto Graph::getNumberOfK4() const -> unsigned int {
    // the graph file counts the vertices starting with 1
    // a.e. the vector addressing has to be shifted by 1
    unsigned int numberOfK4{0};
    for (auto vertex : vertices) {
        // only take vertices with more than one neighbor into concideration
        if (vertex->getDegree() > 2) {
            for (auto i : vertex->getNeighbors()) {
                // only check for neighbors with higher number, to prevent Triangles to be detected more than once
                if (i > (vertex->getNumber()+1)) {
                    // now check if vertex and neighbor have a same neighbor
                    for (auto j : vertices.at((unsigned long) (i-1))->getNeighbors()) {
                        if (j > i && vertex->checkForNeighbor(j)) {
                            for (auto k : vertices.at((unsigned long) (j-1))->getNeighbors()) {
                                if (k > j
                                    && vertex->checkForNeighbor(k)
                                    && vertex->checkForNeighbor(j)
                                    && vertices.at((unsigned long) (i-1))->checkForNeighbor(k)) {
                                        numberOfK4++;
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return numberOfK4;
}

unsigned int Graph::getNumberOfK3() const {
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
                    for (auto i : vertices.at((unsigned long) (ival-1))->getNeighbors()) {
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
    // traverse trough each vertex of the graph
    for (int i = 0; i < vertices.size(); i++) {
        std::vector<unsigned int> N;
        // for each vertex get the colors of its neighbors
        for (auto jval : vertices.at((unsigned long) i)->getNeighbors()) {
            if (jval < i+1) {
                // store colors of neighbors in N
                N.push_back(vertices.at((unsigned long) (jval-1))->getColor());
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
            // starting with 1, compare color with colors in N, the first occurance,
            // where color is not equal to its counterpart in N, thats the minimum
            // color which can be used to color the current vertex
            if (color == ival) {
                color++;
            }
            // break loop, when minimum has been found
            else {
                break;
            }
        }
         // color current vertex with minimum color
        vertices.at((unsigned long) i)->setColor(color);
    }
    return;
}

// provide a sequence in which order the greedy coloring algorithm shall be applied
void Graph::applyGreedyColoringWithSequence(std::vector<unsigned int> &seq) {
    // erase the current coloring first
    eraseColoring();
    // traverse trough each vertex of the graph
    for (auto i : seq) {
        std::vector<unsigned int> N;
        // for each vertex get the colors of its neighbors
        for (auto jval : vertices.at(i)->getNeighbors()) {
            // check if neighbor has already been colored and add color to N
            if (vertices.at(jval-1)->getColor() != 0) {
                // check if color is not in N yet
                if (std::find(N.begin(), N.end(), vertices.at(jval-1)->getColor()) == N.end()) {
                    // store colors of neighbors in N if not stored yet
                    N.push_back(vertices.at(jval-1)->getColor());
                }
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
            // break loop, when minimum has been found
            else {
                break;
            }
        }
        // color current vertex with minimum color
        vertices.at((unsigned long) i)->setColor(color);
    }
    return;
}

unsigned int Graph::getNumberOfColors() const {
    unsigned int numberOfColors{0};
    for (const auto ival : vertices) {
        if (ival->getColor() > numberOfColors) {
            numberOfColors = ival->getColor();
        }
    }
    return numberOfColors;
}

unsigned int Graph::getMinNumberOfColors(unsigned int n) {
    std::vector<unsigned int> numOfColors;
    // sequence to be used as random index for Vertex selection
    std::vector<unsigned int> sequence;
    // put values into sequence
    for (int k = 0; k < vertices.size(); k++) {
        sequence.push_back((unsigned int) k);
    }
    for (int i = 0; i < n; i++) {
        // generate random number for shuffle algorithm
        std::random_device seed;
        // mersenne twister engine with common input parameters
        std::mt19937 g(seed());
        // shuffle the sequence randomly
        std::shuffle(sequence.begin(), sequence.end(), g);
        // apply greedy coloring with sequence
        applyGreedyColoringWithSequence(sequence);
        // determine number of colors
        numOfColors.push_back(getNumberOfColors());
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

