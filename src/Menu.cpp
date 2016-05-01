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
    _printOptions();
    return;
}

void Menu::_start() {
    _handler();
    
}

void Menu::_end() {
    
}



void Menu::_printOptions() {
    // find biggest entry
    unsigned int sizeOfOption{0};
    for (auto option : options) {
        if (option.size() > sizeOfOption) {
            sizeOfOption = (unsigned int)option.size();
        }
    }
    sizeOfOption++;
    // calculate possible options per line
    int possibleOptions = (int)(_windowCol / sizeOfOption);
    // print options
    for (int i = 0; i < options.size(); i++) {
        unsigned int optionCount{0};
        if (optionCount < possibleOptions) {
            optionCount++;
            // get size of current entry
            unsigned int sizeOfCurrentOption = (unsigned int) options.at(i).size();
            int diff = sizeOfOption - sizeOfCurrentOption;
            std::cout << "[" << i << "] " << options.at(i);
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

void Menu::_handler() {
    
}