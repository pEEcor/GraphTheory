//
//  Menu.hpp
//  GraphTheory
//
//  Created by Paavo Becker on 01/05/16.
//  Copyright © 2016 Paavo Becker. All rights reserved.
//

#ifndef Menu_hpp
#define Menu_hpp

#include <vector>
#include <iostream>
#include <string>
#include <sys/ioctl.h>

#define CHARS_PER_SECTION 30

class Menu {
    
public:
    void show();
    
private:
    void _init();
    void _start();
    void _end();
    unsigned int _windowCol = 0;
    unsigned int _windowRow = 0;
    std::vector<std::string> options {"Exit", "MaxDeg", "AverageDeg", "NumOfVertices", "NumberOfVerticesWithDeg", "NumOfVerticesWithoutNeighbors", "NumOfK3", "NumberOfK4", "Greedy Coloring", "Approximation für X(G)", "Apply All"};
    
    void _printOptions();
    void _printDataChoice();
    
    void _handler();
};

#endif /* Menu_hpp */
