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
#include <map>
#include <queue>
#include <random>
#include <algorithm>

#include "Vertex.hpp"

class Graph {
public:
    // constructor
    Graph(const std::vector<Vertex*>&, bool = false);
    // destructor
    ~Graph();
    
    // creates an unweighted graph from a given input stream
    static Graph* getGraphFromStream(std::ifstream &);
    
    // create a random graph with numOfKnots vertices and a probability of EdgeProb for
    // an Edge to exist
    static Graph* getRandomGraph(unsigned int numOfKnots, float EdgeProb);
    
    // return a vector of trees which are all connected component from one graph
    auto getConnectedComponentGraph() -> std::vector<Graph *>;
    
    // return a vector of all edges
    auto getEdges() -> std::vector<edge>*;
    
    // get pointer to a vertex by its number
    auto getVertex(unsigned int number) const -> Vertex*;
    
    // get the number of vertices in the entire graph
    auto getNumberOfVertices() const -> unsigned int;
    
    // get the maximum vertex degree from the entire graph
    auto getMaxDeg() const -> unsigned int;
    
    // get the number of vertices which have the given degree
    auto getNumberOfVerticesWithDeg(const int) const -> unsigned int;
    
    // get the average degree of all vertices
    auto getAverageDeg() const -> float;
    
    // get the number of vertices which don't have any neighbor
    auto getNumberOfVerticesWithoutNeighbors() const -> unsigned int;
    
    // get all triangles which occur in the graph
    auto getTriangles() const -> std::vector<std::vector<unsigned int>*>*;
    
    // get the number of K3 in the graph
    auto getNumberOfK3() const -> unsigned int;
    
    // get the number of K4 in the graph
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
    
    // get the number of nodes within the biggest connected component
    auto getNumberOfMaxConnectedComponent() -> unsigned int;
    
    // get shortest path, assuming each edge has a weight of 1
    auto virtual getShortestPath(unsigned int source, unsigned int destination) -> double;
    
    // get path chain
    auto getPathChain(unsigned int source, unsigned int destination) -> std::vector<unsigned int>*;
    
    // get spanning tree with maximum weight
    auto getWeightOfMaxSpanningTree() -> double;
    
    // get minimum weight of spanning tree
    auto getWeightOfMinSpanningTree() -> double;
    
    // get matching
    auto getGreedyMatching() -> std::vector<edge>&;

private:
    // set colors back to 0
    auto eraseColoring() -> void;
    // set visiting status back to false
    auto eraseVisiting() -> void;
    // set predecessor entries of each vertex to 0
    auto erasePredecessor() -> void;
    
    // set to 0 if a deletion of a vertex had beed applied to the graph
    bool deletionHadBeenApplied{false};
    //vector containing
    std::vector<Vertex*> vertices;
};

#endif /* Graph_hpp */
