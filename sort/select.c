//
//  select.c
//  sort
//
//  Created by junl on 2020/12/1.
//  Copyright © 2020 junl. All rights reserved.
//

#include "sort.h"
void sort_select(ItemType a[], int l, int r){
    int i, j, min;
    for (i = l; i <= r; i++) {
        min = i;
        for (j = i+1; j <= r; j++) {
            if (less(a[j], a[min]))
                min = j;
        }
        exch(a[min], a[i]);
    }
}
