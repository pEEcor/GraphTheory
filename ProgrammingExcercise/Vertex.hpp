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

class Vertex {
public:
    // constructor
    Vertex(const int, const std::vector<int> &);
    // destructor
    virtual ~Vertex();

    // methods
    int getDegree() const;
    std::vector<int>& getNeighbors();
    unsigned long getNumber() const;
    bool checkForNeighbor(int vertex) const;
    
private:
    std::vector<int> neighbors;
    unsigned long number;
};

#endif /* Vertex_hpp */


