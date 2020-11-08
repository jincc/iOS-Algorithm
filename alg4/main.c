//
//  main.c
//  alg4
//
//  Created by junl on 2020/8/18.
//  Copyright © 2020 junl. All rights reserved.
//

#include <stdio.h>
#include "unionfind.h"
#include "weightedQuickUnion.h"
int main(int argc, const char * argv[]) {
    // insert code here...
    test_unionfind();
    printf("\n");
    test_wq_unionfind();
    return 0;
}
