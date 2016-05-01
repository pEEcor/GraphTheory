//
//  Menu.cpp
//  GraphTheory
//
//  Created by Paavo Becker on 01/05/16.
//  Copyright © 2016 Paavo Becker. All rights reserved.
//

#include "Menu.hpp"



void Menu::show() {
    _init();
    _start();
}

void Menu::_init() {
    struct winsize w;
    ioctl(0, TIOCGWINSZ, &w);
    // if size is not accessable set window to default size of col: 80, row: 40
    if (w.ws_row != 0 && w.ws_col != 0) {
        _windowRow = w.ws_row;
        _windowCol = w.ws_col;
    }
    else {
        _windowRow = 40;
        _windowCol = 80;
    }
    return;
}

void Menu::_start() {
    _printMenu(graphTypes);
    while(_dataTypeHandler() != false) {
        _printMenu(options);
        while (_optionHandler() != false) {
        }
    }
}

void Menu::_end() {
    
}

bool Menu::_dataTypeHandler() {
    unsigned int choice{1};
    std::cout << "Graph Source: ";
    std::cin >> choice;
    
    switch (choice) {
        case 0:
            return false;
            
        case 1: {
            std::string name;
            std::cout << "File: ";
            std::cin >> name;
            
            // create file stream and open a file
            std::ifstream file;
            std::cout << "Opening File...";
            file.open(name, std::ios::in);
            std::cout << "Done" << std::endl;
            
            // check if opening the file was successfull
            if(file.good()) {
                std::cout << "Creating Graph...";
                graph = Graph::getGraphFromStream(file);
                std::cout << "Done" << std::endl;
                // close file
                if(file.is_open()) {
                    std::cout << "Closing File...";
                    file.close();
                    std::cout << "Done" << std::endl;
                }
            }
            else {
                std::cerr << "Invalid Filename" << std::endl;
            }
        };
            return true;
            
        case 2: {
            // generating random Graph
            unsigned int vertices{0};
            std::cout << "Number of Vertices for Random Graph [Integer]: ";
            std::cin >> vertices;
            float probability{1};
            std::cout << "Probability for an Edge to exist [Float]: ";
            std::cin >> probability;
            std::cout << "Creating Graph..." << std::endl;
            graph = Graph::getRandomGraph(vertices, probability);
            std::cout << "Done" << std::endl;
        }
            return true;
            
        default: {
            std::cout << "Invalid choice!" << std::endl;
        }
            return true;
    }
}

bool Menu::_optionHandler(int choice) {
    if (choice == -1) {
        std::cout << "Option: ";
        std::cin >> choice;
    }
    switch (choice) {
        case 0:
            return false;
        case 1: {
            std::cout << "Greatest degree: ";
            std::cout << graph->getMaxDeg() << std::endl;
        }
            return true;
        case 2: {
            std::cout << "Average degree: ";
            std::cout << graph->getAverageDeg() << std::endl;
        }
            return true;
        case 3: {
            std::cout << "Number of vertices: ";
            std::cout << graph->getNumberOfVertices() << std::endl;
        }
            return true;
        case 4: {
            std::cout << "Degree [Integer]: ";
            unsigned int grad{0};
            std::cin >> grad;
            std::cout << "Number of vertices with degree " << grad << ": ";
            std::cout << graph->getNumberOfVerticesWithDeg(grad) << std::endl;
        }
            return true;
        case 5: {
            std::cout << "Number of vertices without neighbors: ";
            std::cout << graph->getNumberOfVerticesWithoutNeighbors() << std::endl;
        }
            return true;
        case 6: {
            std::cout << "Number of K3: ";
            std::cout << graph->getNumberOfK3() << std::endl;
        }
            return true;
        case 7: {
            std::cout << "Number of K4: " << graph->getNumberOfK4() << std::endl;
        }
            return true;
        case 8: {
            graph->applyGreedyColoring();
            if (graph->getNumberOfColors()) {
                std::cout << "Colors needed for Greedy coloring (one run): ";
                std::cout << graph->getNumberOfColors() << std::endl;
            }
        }
            return true;
        case 9: {
            std::cout << "Number of runs to apply greedy with random seq.: ";
            unsigned int n{0};
            std::cin >> n;
            int result = graph->getMinNumberOfColors(n);
            std::cout << "Approximation für chi(G) with " << n << " random seq: ";
            std::cout << result << std::endl;
        }
            return true;
        case 10: {
            for (int i = 1; i < 10; i++) {
                _optionHandler(i);
            }
        }
        default: {
            std::cout << "Invalid choice!" << std::endl;
        }
            return true;
    }
}

void Menu::_printMenu(const std::vector<std::string>& data) {
    // find biggest entry
    unsigned int sizeOfOption{0};
    for (auto option : data) {
        if (option.size() > sizeOfOption) {
            sizeOfOption = (unsigned int)option.size();
        }
    }
    sizeOfOption++;
    // calculate possible options per line
    int possibleOptions = (int)(_windowCol / sizeOfOption);
    // print options
    for (int i = 0; i < data.size(); i++) {
        unsigned int optionCount{0};
        if (optionCount < possibleOptions) {
            optionCount++;
            // get size of current entry
            unsigned int sizeOfCurrentOption = (unsigned int) data.at(i).size();
            int diff = sizeOfOption - sizeOfCurrentOption;
            std::cout << "[" << i << "] " << data.at(i);
            for (int j = 0; j < diff; j++) {
                std::cout << " ";
            }
        }
        else {
            optionCount = 0;
            std::cout << std::endl;
        }
    }
    std::cout << std::endl;
}