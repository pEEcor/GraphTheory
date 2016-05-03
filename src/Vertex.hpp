//
//  Vertex.hpp
//  GraphTheory
//
//  Created by Paavo Becker on 11.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <vector>

class Vertex {
public:
    // constructor
    Vertex(const int, const std::vector<int> &);
    // destructor
    virtual ~Vertex();

    // methods
    auto getDegree() const -> unsigned int;
    auto getNeighbors() -> std::vector<int>&;
    auto addNeigbor(unsigned int) -> void;
    auto getNumber() const -> unsigned int;
    auto checkForNeighbor(int vertex) const -> bool;
    auto getColor() const -> unsigned int;
    auto setColor(unsigned int color) -> void;
    // setter for visiting status
    auto setVisited(bool) -> void;
    // getter for visition status
    auto getVisited() const -> bool;
    
private:
    std::vector<int> neighbors;
    unsigned int number;
    unsigned int color;
    bool visited = false;
};

#endif /* Vertex_hpp */


