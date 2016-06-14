//
//  Task.hpp
//  GraphTheory
//
//  Created by Paavo Becker on 08/06/16.
//  Copyright © 2016 Paavo Becker. All rights reserved.
//

#ifndef Task_hpp
#define Task_hpp

#include <vector>

class Task {
public:
    Task(int n, int d, int p);
    int number;
    int deadline;
    int penalty;
};

#endif /* Task_hpp */
