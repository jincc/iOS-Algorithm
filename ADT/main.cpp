//
//  main.cpp
//  ADT
//
//  Created by junl on 2020/7/14.
//  Copyright © 2020 junl. All rights reserved.
//

#include <iostream>
#include "max_priority_queue.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    max_priority_queue queue(4);
    queue.insert(1);
    printf("max = %d\n", queue.max());
    queue.insert(7);
    printf("max = %d\n", queue.max());
    queue.insert(3);
    printf("max = %d\n", queue.max());
    queue.insert(5);
    printf("max = %d\n", queue.max());
    int v ;
    v = queue.remove_max();
    printf("before max = %d, now max = %d\n",v, queue.max());
    v = queue.remove_max();
    printf("before max = %d, now max = %d\n",v, queue.max());
    v = queue.remove_max();
    printf("before max = %d, now max = %d\n",v, queue.max());
    return 0;
}
