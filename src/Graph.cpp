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
    int i = 1;

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

// FIXME need better random distribution
// average deg of n=10000 and p=0.1 is only 908 instead of 999
Graph *Graph::getRandomGraph(unsigned int numOfKnots, float EdgeProb) {
    // generate vertices vector
    std::vector<Vertex*> vertices;
    for (int i = 1; i <= numOfKnots; ++i) {
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
        // +1 cause we dont want to add vertex itself to its neighbors
        for (int j = (int)vertex->getNumber()+1; j < numOfKnots; ++j) {
            if (uniDistribution(g) == 0) {
                vertex->addNeigbor((unsigned int)j);
                vertices.at(j-1)->addNeigbor((unsigned int)vertex->getNumber());
            }
        }
    }
    // return new graph, created by the vertices vector
    return new Graph(vertices);
}

// private method which returns the greatest degree of the graph
auto Graph::getMaxDeg() const -> unsigned int {

    int max{0};
    for(auto ival : vertices) {
        if(ival->getDegree() > max) {
            max = ival->getDegree();
        }
    }
    return max;
}

// method which returns the number of vertices
auto Graph::getNumberOfVertices() const -> unsigned int {
    return static_cast<unsigned int>(vertices.size());
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
auto Graph::getAverageDeg() const -> float{
    float numOfEdges = 0;
    for (auto ival : vertices) {
        numOfEdges += ival->getDegree();
    }
    return numOfEdges / (float)getNumberOfVertices();
}

auto Graph::getNumberOfVerticesWithoutNeighbors() const -> unsigned int {
    unsigned int numberOfVerticesWithoutNeighbors = 0;
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
                if (ival > (vertex->getNumber())) {
                    // now check if vertex and neighbor have a same neighbor
                    for (auto i : getVertex(ival)->getNeighbors()) {
                        if (i > ival && vertex->checkForNeighbor(i)) {
                            std::vector<unsigned int>* x = new std::vector<unsigned int>();
                            x->push_back((unsigned int)vertex->getNumber());
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
                if (i > (vertex->getNumber())) {
                    // now check if vertex and neighbor have a same neighbor
                    for (auto j : getVertex(i)->getNeighbors()) {
                        if (j > i && vertex->checkForNeighbor(j)) {
                            for (auto k : getVertex(j)->getNeighbors()) {
                                if (k > j
                                    && vertex->checkForNeighbor(k)
                                    && vertex->checkForNeighbor(j)
                                    && getVertex(i)->checkForNeighbor(k)) {
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

auto Graph::getNumberOfK3() const -> unsigned int {
    // the graph file counts the vertices starting with 1
    // a.e. the vector addressing has to be shifted by 1
    unsigned int numberOfTriangles{0};
    for (auto vertex : vertices) {
        // only take vertices with more than one neighbor into concideration
        if (vertex->getDegree() > 1) {
            for (auto ival : vertex->getNeighbors()) {
                // only check for neighbors with higher number, to prevent Triangles to be detected more than once
                if (ival > vertex->getNumber()) {
                    // now check if vertex and neighbor have a same neighbor
                    for (auto i : getVertex(ival)->getNeighbors()) {
                        if (vertex->checkForNeighbor(i) && i > ival) {
                            numberOfTriangles++;
                        }
                    }
                }
            }
        }
    }
    return numberOfTriangles;
}

// apply greedy coloring algorithm to graph with standat sequence [1,...,n]
auto Graph::applyGreedyColoring() -> void {
    // erase the current coloring first
    eraseColoring();
    // traverse trough each vertex of the graph
    for (auto vertex : vertices) {
        std::vector<unsigned int> N;
        // for each vertex get the colors of its neighbors
        for (auto jval : vertex->getNeighbors()) {
            if (getVertex(jval)->getColor() != 0
                && std::find(N.begin(), N.end(), getVertex(jval)->getColor()) == N.end()) {
                // store colors of neighbors in N if not stored yet
                N.push_back(getVertex(jval)->getColor());
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
        vertex->setColor(color);
    }
    return;
}

// provide a sequence in which order the greedy coloring algorithm shall be applied
auto Graph::applyGreedyColoringWithSequence(std::vector<unsigned int> &seq) -> void {
    // erase the current coloring first
    eraseColoring();
    // traverse trough each vertex of the graph
    for (auto i : seq) {
        std::vector<unsigned int> N;
        // for each vertex get the colors of its neighbors
        for (auto jval : getVertex(i)->getNeighbors()) {
            // check if neighbor has already been colored and add color to N
            if (getVertex(jval)->getColor() != 0 &&
                std::find(N.begin(), N.end(), getVertex(jval)->getColor()) == N.end()) {
                // store colors of neighbors in N if not stored yet
                N.push_back(getVertex(jval)->getColor());
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
        getVertex(i)->setColor(color);
    }
    return;
}

auto Graph::getNumberOfColors() const -> unsigned int{
    unsigned int numberOfColors{0};
    for (const auto ival : vertices) {
        if (ival->getColor() > numberOfColors) {
            numberOfColors = ival->getColor();
        }
    }
    return numberOfColors;
}

auto Graph::getMinNumberOfColors(unsigned int n) -> unsigned int{
    std::vector<unsigned int> numOfColors;
    // sequence to be used as random index for Vertex selection
    std::vector<unsigned int> sequence;
    // put values into sequence
    for (int k = 1; k <= vertices.size(); k++) {
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

auto Graph::eraseColoring() -> void{
    for (auto ival : vertices) {
        ival->setColor(0);
    }
    return;
}

auto Graph::getVertex(unsigned int number) const -> Vertex* {
    if (deletionHadBeenApplied) {
        return *std::find_if(vertices.begin(), vertices.end(), [number] (Vertex* v)->bool {return v->getNumber() == number;});
    }
    else {
        return vertices.at(number -1);
    }
}

auto Graph::sizeOfMaxConnectedComponent() -> unsigned int {
    // apply a breadth-first search as long as all vertices haven't beed found
    // erase old visiting information first
    eraseVisiting();
    erasePredecessor();
    // var to store number of connected component size
    unsigned int sizeOfConnectedComponent{0};
    unsigned int VertexCounter{0};
    // search queue
    std::queue<unsigned int> Q;
    
    // traverse though all the vertices, order isn't necessary here
    for (unsigned int i{0}; i < vertices.size(); i++) {
        // if vertex had not been visited yet, start a new search
        if (vertices.at(i)->getVisited() == false) {
            Q.push(i);
            vertices.at(i)->setVisited(true);
            // breadth-first search with vertex at i
            while (!Q.empty()) {
                unsigned int v{Q.front()};
                auto currentNeighbors = vertices.at(Q.front())->getNeighbors();
                Q.pop();
                VertexCounter++;
                // add all neighbors to the queue that have not been visited
                for (auto neighbor : currentNeighbors) {
                    // if not visited yet
                    if (!(getVertex(neighbor)->getVisited())) {
                        Q.push(neighbor);
                        getVertex(neighbor)->setVisited(true);
                        getVertex(neighbor)->predecessor = vertices.at(v)->getNumber();
                    }
                }
            }
            // check if current connected component is bigger than the previous one
            if (VertexCounter > sizeOfConnectedComponent) {
                sizeOfConnectedComponent = VertexCounter;
            }
            // reset vertexCounter
            VertexCounter = 0;
        }
    }
    // at least every single vertex is connected to itself, thus the smallest connected
    // component is one
    return sizeOfConnectedComponent + 1;
}

auto Graph::eraseVisiting() -> void {
    for (auto vertex : vertices) {
        vertex->setVisited(false);
    }
}

auto Graph::erasePredecessor() -> void {
    for (auto vertex : vertices) {
        vertex->predecessor = 0;
    }
}

// implementation of dijsktra, can not handle negative weights
auto Graph::getShortestPath(unsigned int source, unsigned int destination) -> double {
    // minDistance vector which will contain the minimum distance from start to every other vertex
    std::vector<float> minDistance(vertices.size()+1, std::numeric_limits<double>::max());
    // distance to source is 0
    minDistance.at(source) = 0;
    
    std::set<std::pair<float, unsigned int>> activeVertices;
    
    activeVertices.insert({0, source});
    
    while (!activeVertices.empty()) {
        unsigned int x = activeVertices.begin()->second;
        if (x == destination) {
            return minDistance.at(x);
        }
        activeVertices.erase(activeVertices.begin());
        for (auto neighbor : getVertex(x)->getNeighbors()) {
            if (minDistance.at(neighbor) > minDistance.at(x) + getVertex(x)->getWeightTo(neighbor)) {
                activeVertices.erase({minDistance.at(neighbor), neighbor});
                minDistance.at(neighbor) = minDistance.at(x) + getVertex(x)->getWeightTo(neighbor);
                activeVertices.insert({minDistance.at(neighbor), neighbor});
                getVertex(neighbor)->predecessor = x;
            }
        }
    }
    return std::numeric_limits<double>::max();
}

auto Graph::getPathChain(unsigned int source, unsigned int destination) -> std::vector<unsigned int>* {
    
    auto result = new std::vector<unsigned int>;
    unsigned int tmp{destination};
    result->push_back(tmp);
    
    while(source != tmp) {
        if (getVertex(tmp)->predecessor == 0) {
            return NULL;
        }
        tmp = getVertex(tmp)->predecessor;
        result->push_back(tmp);
    }
    
    std::reverse(result->begin(), result->end());
    return result;
}

auto Graph::getWeightOfMinimalSpanningTree() -> double {
    // weight
    double weight{0};

    return weight;
}

