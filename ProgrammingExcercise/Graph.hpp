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

#include "Vertex.hpp"

class Graph {
public:
    //constructor
    Graph(const std::vector<Vertex<int>*>&);
    //destructor
    virtual ~Graph();

    static Graph* getGraphFromStream(std::ifstream &);
    int getMaxDeg();

private:
    //vector containing
    std::vector<Vertex<int>*> vertices;
};

#endif /* Graph_hpp */
