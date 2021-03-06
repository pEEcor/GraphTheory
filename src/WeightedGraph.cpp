//
//  WeightedGraph.cpp
//  GraphTheory
//
//  Created by Paavo Becker on 17.05.16.
//  Copyright © 2016 Paavo Becker. All rights reserved.
//

#include "WeightedGraph.hpp"

// constructor
WeightedGraph::WeightedGraph(const std::vector<Vertex*>& vertices) : Graph(vertices) {}

//class method, which creates a graph from a given stream
WeightedGraph* WeightedGraph::getGraphFromStream(std::ifstream &file) {
    
    // buffer for lines in graphfile
    std::string buffer;
    // regex to filter neighbors in line, which must be integers
    std::regex neighborPattern("([0-9]+)");
    // regex to filter weihts in line, which can be either floats or integers
    std::regex weightPattern("([0-9]+\\.[0-9]+|[0-9]+)");
    
    // empty vertices vector
    std::vector<Vertex*> vertices;
    // vertices counter
    int i = 1;
    // indicator for either neighbor line or weight line
    bool neighborLine = true;
    
    while(getline(file, buffer)) {
        
        // detect end of file
        std::smatch m;
        if (std::regex_search(buffer, m, std::regex("end"))) {
            break;
        }
        
        if (neighborLine) {
            //vector for neighbours
            std::vector<int> neighbors;
            
            // find all neighbors of i in line (2i - 1)
            std::sregex_iterator next(buffer.begin(), buffer.end(), neighborPattern);
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
            
            // toggle line indicator
            neighborLine = !neighborLine;
        }
        else {
            //vector for weights
            std::vector<float> weights;
            
            // find all neighbors of i in line (2i - 1)
            std::sregex_iterator next(buffer.begin(), buffer.end(), weightPattern);
            std::sregex_iterator end;
            while (next != end) {
                std::smatch match = *next;
                // push match into weights vector
                weights.push_back(stof(match.str()));
                next++;
            }
            
            // put weights into previously created vertex
            vertices.at(i-1)->setWeights(weights);
            
            // toggle line indicator
            neighborLine = !neighborLine;
            // increase i for number of next vertex
            i++;
        }
    }
    // return new graph, created by the vertices vector
    return new WeightedGraph(vertices);
}

// implementation of dijsktra, can not handle negative weights
auto WeightedGraph::getShortestPath(unsigned int source, unsigned int destination) -> double {
    // minDistance vector which will contain the minimum distance from start to every other vertex
    std::vector<float> minDistance(getNumberOfVertices()+1, std::numeric_limits<double>::max());
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