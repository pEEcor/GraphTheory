//
//  Graph.hpp
//  ProgrammingExcercises
//
//  Created by Paavo Becker on 06.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#ifndef Graph_hpp
#define Graph_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <regex>
#include <vector>
#include <array>
#include <random>
#include <algorithm>

#include "Vertex.hpp"

class Graph {
public:
    //constructor
    Graph(const std::vector<Vertex*>&);
    //destructor
    virtual ~Graph();

    static Graph* getGraphFromStream(std::ifstream &);
    int getMaxDeg() const;
    unsigned long getNumberOfVertices() const;
    double getAverageDeg() const;
    unsigned long getNumberOfVerticesWithoutNeighbors() const;
    unsigned int getNumberOfTriangles() const;
    
    // apply the greedy coloring algorithm to the graph and store corresponding
    // color into each node
    void applyGreedyColoring();
    
    // apply the greedy coloring algorithm to the graph and store corresponding
    // color into each node, using sequence to apply the algorithm in a given
    // order
    void applyGreedyColoringWithSequence(std::vector<unsigned int> &);
    
    // return the amount of colors needed for the greedy coloring
    unsigned int getNumberColors() const;
    
    // this just approximates the minimum number of colors, by applying the
    // greedy algorithm 1000 time withs using a random sequence of vertices each
    // time
    unsigned int getMinNumberOfColors();
    

private:
    // set colors back to 0
    void eraseColoring();
    //vector containing
    std::vector<Vertex*> vertices;
};

#endif /* Graph_hpp */
