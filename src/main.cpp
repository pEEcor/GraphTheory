//
//  main.cpp
//  Excercise_1.5
//
//  Created by Paavo Becker on 06.04.16.
//  Copyright © 2016 xcor. All rights reserved.
//

#include <iostream>
#include "Graph.hpp"
#include "WeightedGraph.hpp"
#include <fstream>

auto exercise15() -> void;
auto exercise25() -> void;
auto exercise34() -> void;
auto exercise45() -> void;
auto exercise54() -> void;
auto exercise65() -> void;
auto exercise75() -> void;

int main(int argc, const char * argv[]) {
    std::cout << "Starting...\n\n";
    
    //exercise15();
    //exercise25();
    //exercise34();
    //exercise45();
    //exercise54();
    //exercise65();
    exercise75();
    
    std::cout << "DONE" << std::endl;
    
    return 0;
}

auto exercise15() -> void {
    
    Graph* graph = NULL;
    
    // create file stream and open graph15.txt
    std::ifstream file;
    std::cout << "Opening File...";
    file.open("graph15.txt", std::ios::in);
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
    
    std::cout << "Greatest degree: ";
    std::cout << graph->getMaxDeg() << std::endl;
}

auto exercise25() -> void {
    
    Graph* graph = NULL;
    
    // create file stream and open graph15.txt
    std::ifstream file;
    std::cout << "Opening File...";
    file.open("graph25.txt", std::ios::in);
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
    
    std::cout << "Number of vertices: ";
    std::cout << graph->getNumberOfVertices() << std::endl;
    
    std::cout << "Average degree: ";
    std::cout << graph->getAverageDeg() << std::endl;
    
    std::cout << "Number of vertices without neighbors: ";
    std::cout << graph->getNumberOfVerticesWithoutNeighbors() << std::endl;
    
    std::cout << "Number of K3: ";
    std::cout << graph->getNumberOfK3() << std::endl;
}

auto exercise34() -> void {
    Graph* graph = NULL;
    
    // create file stream and open graph15.txt
    std::ifstream file;
    std::cout << "Opening File...";
    file.open("graph34.txt", std::ios::in);
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
    
    graph->applyGreedyColoring();
    if (graph->getNumberOfColors()) {
        std::cout << "Colors needed for Greedy coloring (one run): ";
        std::cout << graph->getNumberOfColors() << std::endl;
    }
    
    int result = graph->getMinNumberOfColors(1000);
    std::cout << "Approximation für chi(G) with 1000 random seq: ";
    std::cout << result << std::endl;
}

auto exercise45() -> void {
    
    for(double i = 1e-3; i < 1; i *=10) {
        
        Graph *graph = Graph::getRandomGraph(10000, i);
        
        // Durchschnittsgrad
        std::cout << "Average degree: ";
        std::cout << graph->getAverageDeg() << std::endl;
        // Dreiecke
        std::cout << "Number of K3: ";
        std::cout << graph->getNumberOfK3() << std::endl;
        // Farben
        int result = graph->getMinNumberOfColors(100);
        std::cout << "Approximation für chi(G) with 100 random seq: ";
        std::cout << result << std::endl;
        
        delete graph;
    }
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

auto exercise65() -> void {
    
    WeightedGraph* graph = NULL;
    
    // create file stream and open graph15.txt
    std::ifstream file;
    std::cout << "Opening File...";
    file.open("graph65.txt", std::ios::in);
    std::cout << "Done" << std::endl;
    
    // check if opening the file was successfull
    if(file.good()) {
        std::cout << "Creating Graph...";
        graph = WeightedGraph::getGraphFromStream(file);
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
    
    double result = graph->getShortestPath(1, 2);
    std::cout << "Shortest path from 1 to 2 costs: " << result << std::endl;
    
    std::cout << "PathChain: ";
    for (auto vertex : *graph->getPathChain(1, 2)) {
        std::cout << vertex << " ";
    }
    std::cout << std::endl;
}

auto exercise75() -> void {
    
    WeightedGraph* graph = NULL;
    
    // create file stream and open graph15.txt
    std::ifstream file;
    std::cout << "Opening File...";
    file.open("testgraph.txt", std::ios::in);
    std::cout << "Done" << std::endl;
    
    // check if opening the file was successfull
    if(file.good()) {
        std::cout << "Creating Graph...";
        graph = WeightedGraph::getGraphFromStream(file);
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
    
    auto result = graph->getWeightOfMinimalSpanningTree();
    std::cout << "Weight of minimal spanning tree: " << result << std::endl;
    
    
}