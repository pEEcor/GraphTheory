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
};

#endif /* WeightedGraph_hpp */
