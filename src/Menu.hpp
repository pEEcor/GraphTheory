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
#include "Graph.hpp"

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
    // selection for graph types
    std::vector<std::string> graphTypes {"Exit", "Graph from File", "Random Graph"};
    // selection for options
    std::vector<std::string> options {"Exit", "MaxDeg", "AverageDeg", "NumOfVertices", "NumberOfVerticesWithDeg", "NumOfVerticesWithoutNeighbors", "NumOfK3", "NumberOfK4", "Greedy Coloring", "Approximation für X(G)", "Apply All"};
    void _printMenu(const std::vector<std::string>&);
    
    bool _dataTypeHandler();
    bool _optionHandler(int choice = -1);
    
    Graph* graph = NULL;
};

#endif /* Menu_hpp */
