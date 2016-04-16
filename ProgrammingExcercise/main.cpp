//
//  main.cpp
//  Excercise_1.5
//
//  Created by Paavo Becker on 06.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"
#include <fstream>

int main(int argc, const char * argv[]) {
    std::cout << "Starting...\n\n";

    std::string name;
    std::cout << "Datei zum Lesen öffnen: ";
    std::cin >> name;

    // create file stream and open a file
    std::ifstream file;
    std::cout << "Öffne Datei...";
    file.open("graph25.txt", std::ios::in);
    std::cout << "Done" << std::endl;

    Graph* graph = NULL;

    // check if opening the file was successfull
    if(file.good()) {
        std::cout << "Erstelle Graphen...";
        graph = Graph::getGraphFromStream(file);
        std::cout << "Done" << std::endl;
        // close file
        if(file.is_open()) {
            std::cout << "Schließe Datei...";
            file.close();
            std::cout << "Done" << std::endl;
        }
    }
    else {
        std::cerr << "Datei konnte nicht geöffnet werden!" << std::endl;
    }

    if (graph != NULL) {
        std::cout << "The greatest degree is: " << graph->getMaxDeg() << std::endl;
        std::cout << "Anzahl der Knoten ist: " << graph->getNumberOfVertices() << std::endl;
        std::cout << "Durchschittsgrad ist: " << graph->getAverageDeg() << std::endl;
        std::cout << "Anzahl der Knoten ohne Nachbarn: " << graph->getNumberOfVerticesWithoutNeighbors() << std::endl;
        std::cout << "Anzahl an Dreiecken: " << graph->getNumberOfTriangles() << std::endl;
    }
    
    return 0;
}
