//
//  Graph.hpp
//  GraphTheory
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
#include <set>
#include <queue>
#include <random>
#include <algorithm>

#include "Vertex.hpp"

class Graph {
public:
    // constructor
    Graph(const std::vector<Vertex*>&);
    // destructor
    ~Graph();

    static Graph* getGraphFromStream(std::ifstream &);
    static Graph* getRandomGraph(unsigned int numOfKnots, float EdgeProb);
    auto getMaxDeg() const -> unsigned int;
    auto getNumberOfVertices() const -> unsigned int;
    auto getNumberOfVerticesWithDeg(const int) const -> unsigned int;
    auto getAverageDeg() const -> float;
    auto getNumberOfVerticesWithoutNeighbors() const -> unsigned int;
    auto getTriangles() const -> std::vector<std::vector<unsigned int>*>*;
    // returns the number of triangles within the graph
    auto getNumberOfK3() const -> unsigned int;
    auto getNumberOfK4() const -> unsigned int;
    
    // apply the greedy coloring algorithm to the graph and store corresponding
    // color into each node
    auto applyGreedyColoring() -> void;
    
    // apply the greedy coloring algorithm to the graph and store corresponding
    // color into each node, using sequence to apply the algorithm in a given
    // order
    auto applyGreedyColoringWithSequence(std::vector<unsigned int> &) -> void;
    
    // return the amount of colors needed for the greedy coloring
    auto getNumberOfColors() const -> unsigned int;
    
    // this just approximates the minimum number of colors, by applying the
    // greedy algorithm n (100 default) times using a random sequence of vertices each
    // time
    auto getMinNumberOfColors(unsigned int n = 100) -> unsigned int;
    
    // return the number of nodes within the biggest connected component
    auto sizeOfMaxConnectedComponent() -> unsigned int;
    
    // return the cost for the shortest path from source vertex to desination vertex
    auto getShortestPath(unsigned int source, unsigned int destination) -> double;
    
    // get path chain
    auto getPathChain(unsigned int source, unsigned int destination) -> std::vector<unsigned int>*;
    
    // get weight of minimal spanning tree, assuming the entire graph is connected
    auto getWeightOfMinimalSpanningTree() -> double;

private:
    // set colors back to 0
    auto eraseColoring() -> void;
    // set visiting status back to false
    auto eraseVisiting() -> void;
    // set predecessor entries of each vertex to 0
    auto erasePredecessor() -> void;
    // get pointer to a vertex by its number
    auto getVertex(unsigned int number) const -> Vertex*;
    
    // set to 0 if a deletion of a vertex had beed applied to the graph
    bool deletionHadBeenApplied{false};
    //vector containing
    std::vector<Vertex*> vertices;
};

#endif /* Graph_hpp */
