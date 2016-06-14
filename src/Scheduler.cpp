//
//  Scheduler.cpp
//  GraphTheory
//
//  Created by Paavo Becker on 08/06/16.
//  Copyright © 2016 Paavo Becker. All rights reserved.
//

#include "Scheduler.hpp"

Scheduler::Scheduler(const std::vector<Task*>& t) : tasks(t) {}

Scheduler* Scheduler::getTasksFromStream(std::ifstream &file) {
    // buffer for lines in graphfile
    std::string buffer;
    // regex to filter numbers in line
    std::regex pattern("([0-9]+)");
    
    // empty vertices vector
    std::vector<Task*> tasks;
    
    while(getline(file, buffer)) {
        
        std::smatch m;
        if (std::regex_search(buffer, m, std::regex("end"))) {
            break;
        }
        
        //vector for task number, deadline and penalty
        std::vector<int> entities;
        
        // find all matches in line
        std::sregex_iterator next(buffer.begin(), buffer.end(), pattern);
        std::sregex_iterator end;
        while (next != end) {
            std::smatch match = *next;
            // push match into neighbours vector
            entities.push_back(stoi(match.str()));
            next++;
        }
        //put new Vertex into vertices vector, initialized with its number and
        //neighbours
        
        tasks.push_back(new Task(entities.at(0), entities.at(1), entities.at(2)));
        
    }
    // return new graph, created by the vertices vector
    return new Scheduler(tasks);
}

auto Scheduler::schedule() -> long {
    
    std::vector<Task*> schedulable;
    std::vector<Task*> notSchedulable;
    
    std::sort(tasks.begin(), tasks.end(), [](Task *t1, Task *t2)->bool
              {return t1->penalty > t2->penalty;});
    
    int counter{0};
    for (auto task : tasks) {
        counter++;
        schedulable.push_back(task);
        // check if tasks can be scheduled and put it into notSchedulable if not
        std::sort(schedulable.begin(), schedulable.end(), [](Task *t1, Task *t2)->bool
                  {return t1->deadline < t2->deadline;});
        for(int i = 0; i < schedulable.size(); i++) {
            if (schedulable.at(i)->deadline < i+1) {
                // find last inserted task
                auto lastInsertedTask = std::find(schedulable.begin(), schedulable.end(), task);
                notSchedulable.push_back(*lastInsertedTask);
                schedulable.erase(lastInsertedTask);
            }
        }
    }
    
    long penalty{0};
    for (auto task : notSchedulable) {
        penalty += task->penalty;
    }
    
    return penalty;
}
