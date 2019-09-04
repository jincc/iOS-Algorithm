//
//  bucketSort.h
//  sort
//
//  Created by junlongj on 2019/9/2.
//  Copyright © 2019 junl. All rights reserved.
//

#ifndef bucketSort_hpp
#define bucketSort_hpp

#include <stdio.h>
#include <vector>

void test_bucketsort(){
    using namespace std;
    int ages[] = {15,78,24,26,67,90,1,56,78};
    const int bucket_cout = 100;
    int buckets[bucket_cout];//创建100个桶，代表0-99个年龄
    memset(buckets, 0, sizeof(buckets));
    for (auto &age : ages) {
        buckets[age]+=1;
    }
    
    //依次从桶里面读出
    printf("test_bucketsort starting.........\n");
    for (int i=0; i<bucket_cout; i++) {
        while (buckets[i]>0) {
            printf("%i,",i);
            buckets[i]-=1;
        }
    }
    printf("\n");
}



#endif /* bucketSort_hpp */
