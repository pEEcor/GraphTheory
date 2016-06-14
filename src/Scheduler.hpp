//
//  Scheduler.hpp
//  GraphTheory
//
//  Created by Paavo Becker on 08/06/16.
//  Copyright © 2016 Paavo Becker. All rights reserved.
//

#ifndef Scheduler_hpp
#define Scheduler_hpp

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <regex>

#include "Task.hpp"

class Scheduler {
public:
    Scheduler(const std::vector<Task*>&);
    static Scheduler* getTasksFromStream(std::ifstream &file);
    auto schedule() -> long;
    
    std::vector<Task*> tasks;
};

#endif /* Scheduler_hpp */
