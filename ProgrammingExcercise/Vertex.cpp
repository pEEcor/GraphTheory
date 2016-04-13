//
//  Vertex.cpp
//  ProgrammingExcercises
//
//  Created by Paavo Becker on 11.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#include "Vertex.hpp"

// constructor
Vertex::Vertex(const int number, const std::vector<int> &neighbours) : number(number), neighbours(neighbours) {}

// destructor
Vertex::~Vertex() {}

// public method, which returns the number of neighbours
int Vertex::getDegree() const {
    return int(neighbours.size());
}

// public method, which return a vector of neighbours
std::vector<int>& Vertex::getNeighbours() {
    return neighbours;
};