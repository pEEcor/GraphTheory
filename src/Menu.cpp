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
    _dataTypeHandler();
    _optionHandler();
}

void Menu::_end() {
    
}

void Menu::_dataTypeHandler() {
    // generate Graph
    unsigned int choice{1};
    
    while (choice != 0) {
        _printMenu(graphTypes);
        std::cout << "Choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 0:
                break;
                
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
                        std::cout << "Closing Datei...";
                        file.close();
                        std::cout << "Done" << std::endl;
                    }
                }
                else {
                    std::cerr << "Invalid Filename" << std::endl;
                }
            }
                break;
                
            case 2: {
                // generating random Graph
                unsigned int vertices{0};
                std::cout << "Number of Vertices for Random Graph [Integer]: ";
                std::cin >> vertices;
                float probability{1};
                std::cout << "Probability for an Edge to exist [Float]: ";
                std::cin >> probability;
                std::cout << "Creating Graph...";
                //graph = Graph::getRandomGraph(vertices, probability);
                std::cout << "Done" << std::endl;
            }
                break;
                
            default: {
                std::cout << "Invalid choice!" << std::endl;
            }
                break;
        }
    }
}

void Menu::_optionHandler() {
    std::cout << "test" << std::endl;
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