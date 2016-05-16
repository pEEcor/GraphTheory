//
//  main.cpp
//  Excercise_1.5
//
//  Created by Paavo Becker on 06.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"
#include "Menu.hpp"
#include <fstream>

auto exercise54() -> void;

int main(int argc, const char * argv[]) {
    std::cout << "Starting...\n\n";
    
    // Menu menu;
    // menu.show();
    
    exercise54();
    
    return 0;
}

auto exercise54() -> void {
    // Exercise 5.4
    for (int i = 1; i <= 300; i++) {
        
        double p = i*5*pow(10, -6);
        std::cout << "Probability: " << p << std::endl;
        
        Graph *graph = Graph::getRandomGraph(10000, p);
        std::cout << "Average Deg: " << graph->getAverageDeg() << std::endl;
        
        std::cout << "Biggest connected component: " << graph->sizeOfMaxConnectedComponent() << std::endl;
        delete graph;
        }
}
