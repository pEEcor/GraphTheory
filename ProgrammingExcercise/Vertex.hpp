//
//  Vertex.hpp
//  ProgrammingExcercises
//
//  Created by Paavo Becker on 11.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#ifndef Vertex_hpp
#define Vertex_hpp

#include <vector>

template <typename T>
class Vertex {
public:
    // constructor
    Vertex(const int, const std::vector<T> &);
    // destructor
    virtual ~Vertex();

    // methods
    int getDegree() const;
    std::vector<T>& getNeighbours() const;
    
private:
    std::vector<T> neighbours;
    int number;
};

// constructor
template <typename T>
Vertex<T>::Vertex(const int number, const std::vector<T> &neighbours) : number(number), neighbours(neighbours) {}

// destructor
template <typename T>
Vertex<T>::~Vertex() {}

// public method, which returns the number of neighbours
template <typename T>
int Vertex<T>::getDegree() const {
    return int(neighbours.size());
}

// public method, which return a vector of neighbours
template  <typename T>
std::vector<T>& Vertex<T>::getNeighbours() const {
    return neighbours;
};

#endif /* Vertex_hpp */


