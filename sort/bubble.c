//
//  sort.c
//  sort
//
//  Created by junl on 2020/12/1.
//  Copyright © 2020 junl. All rights reserved.
//

#include "sort.h"
void sort_bubble(ItemType a[], int l, int r){
    int i, j, changed;
    for (i = l ; i < r; i++) {
        for (j = r, changed = 0; j > i; j--) {
            if (less(a[j], a[j-1])) {
                exch(a[j], a[j-1]);
                changed = 1;
            }
        }
        if (!changed) break;
    }
}
