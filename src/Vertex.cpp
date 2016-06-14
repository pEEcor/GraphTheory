//
//  Vertex.cpp
//  GraphTheory
//
//  Created by Paavo Becker on 11.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#include "Vertex.hpp"

// constructor
Vertex::Vertex(const int number, const std::vector<int> &neighbors) : number(number), color(0) {
    for (int i = 0; i < neighbors.size(); i++) {
        edge kante;
        kante.to = neighbors.at(i);
        kante.from = number;
        edges.push_back(kante);
    }
}

// destructor
Vertex::~Vertex() {}

auto Vertex::setWeights(const std::vector<float> &weights) -> void {
    if (edges.size() != weights.size()) {
        // do some error stuff
    }
    else {
        for (int i = 0; i < weights.size(); i++) {
            this->edges.at(i).weight = weights.at(i);
        }
    }
}

auto Vertex::getWeightTo(unsigned int other) -> float {
    int i{0};
    for (auto edge : edges) {
        if (other == edge.to) {
            return edge.weight;
        }
        i++;
    }
    return -1;
}

// public method, which returns the number of neighbours
auto Vertex::getDegree() const -> unsigned int{
    return int(edges.size());
}

auto Vertex::getEdges() -> std::vector<edge> & {
    return edges;
}

// public method, which returns a vector of neighbours
auto Vertex::getNeighbors() -> std::vector<int>& {
    std::vector<int> *neighbors = new std::vector<int>;
    for (int i = 0; i < edges.size(); i++) {
        neighbors->push_back(edges.at(i).to);
    }
    return *neighbors;
}

auto Vertex::getNumber() const -> unsigned int{
    return number;
}

auto Vertex::checkForNeighbor(int vertex) const ->bool {
    for (auto ival : edges) {
        if (vertex == ival.to) {
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
    auto result = std::find_if(edges.begin(), edges.end(), [newNeighbor] (edge e)->bool { return e.to == newNeighbor;});
    if (result == edges.end()) {
        edge kante;
        kante.to = newNeighbor;
        kante.from = number;
        edges.push_back(kante);
    }
}

auto Vertex::setVisited(bool a) -> void {
    visited = a;
}

auto Vertex::getVisited() const -> bool {
    return visited;
}