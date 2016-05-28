//
//  WeightedGraph.hpp
//  GraphTheory
//
//  Created by Paavo Becker on 17.05.16.
//  Copyright © 2016 Paavo Becker. All rights reserved.
//

#ifndef WeightedGraph_hpp
#define WeightedGraph_hpp

#include "Graph.hpp"

class WeightedGraph : public Graph{
    
public:
    // constructor
    WeightedGraph(const std::vector<Vertex*>& vertices);
    
    // static methods
    static WeightedGraph* getGraphFromStream(std::ifstream &);
    
    // return the cost for the shortest path from source vertex to desination vertex
    auto getShortestPath(unsigned int source, unsigned int destination) -> double;
};

#endif /* WeightedGraph_hpp */
