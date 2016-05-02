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
    int getDegree() const;
    std::vector<int>& getNeighbors();
    void addNeigbor(unsigned int);
    unsigned long getNumber() const;
    bool checkForNeighbor(int vertex) const;
    unsigned int getColor() const;
    void setColor(unsigned int color);
    
private:
    std::vector<int> neighbors;
    unsigned int number;
    unsigned int color;
};

#endif /* Vertex_hpp */


