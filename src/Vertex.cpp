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
auto Vertex::getDegree() const -> unsigned int{
    return int(neighbors.size());
}

// public method, which return a vector of neighbours
auto Vertex::getNeighbors() -> std::vector<int>&{
    return neighbors;
}

auto Vertex::getNumber() const -> unsigned int{
    return number;
}

auto Vertex::checkForNeighbor(int vertex) const ->bool {
    for (auto ival : neighbors) {
        if (vertex == ival) {
            return true;
        }
    }
    return false;
};

auto Vertex::getColor() const -> unsigned int{
    return color;
}

auto Vertex::setColor(unsigned int color) -> void {
    this->color = color;
}

auto Vertex::addNeigbor(unsigned int newNeighbor) -> void {
    auto result = std::find(neighbors.begin(), neighbors.end(), newNeighbor);
    if (result == neighbors.end()) {
        neighbors.push_back(newNeighbor);
    }
}

auto Vertex::setVisited(bool a) -> void {
    visited = a;
}

auto Vertex::getVisited() const -> bool {
    return visited;
}