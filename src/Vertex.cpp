//
//  Vertex.cpp
//  GraphTheory
//
//  Created by Paavo Becker on 11.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#include "Vertex.hpp"

// constructor
Vertex::Vertex(const int number, const std::vector<int> &neighbors) : number( number), neighbors(neighbors) , color(0) {}

// destructor
Vertex::~Vertex() {}

// public method, which returns the number of neighbours
int Vertex::getDegree() const {
    return int(neighbors.size());
}

// public method, which return a vector of neighbours
std::vector<int>& Vertex::getNeighbors() {
    return neighbors;
}

unsigned long Vertex::getNumber() const {
    return number;
}

bool Vertex::checkForNeighbor(int vertex) const {
    for (auto ival : neighbors) {
        if (vertex == ival) {
            return true;
        }
    }
    return false;
};

unsigned int Vertex::getColor() const {
    return color;
}

void Vertex::setColor(unsigned int color) {
    this->color = color;
}

void Vertex::addNeigbor(unsigned int newNeighbor) {
    auto result = std::find(neighbors.begin(), neighbors.end(), newNeighbor);
    if (result == neighbors.end()) {
        neighbors.push_back(newNeighbor);
    }
}