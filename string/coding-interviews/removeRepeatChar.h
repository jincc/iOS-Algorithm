//
//  removeRepeatChar.h
//  string
//
//  Created by junl on 2020/5/18.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef removeRepeatChar_h
#define removeRepeatChar_h

namespace codinginterviews {
void removeRepeatChar(char *s){
    if (s == NULL) return ;
    
    bool hashMap[256];
    memset(hashMap, false, sizeof(hashMap));
    
    char *ptr0 , *ptr1;
    ptr0 = ptr1 = s;
    while (*ptr1 != '\0') {
        if (!hashMap[*ptr1]) {
            hashMap[*ptr1] = true;
            *ptr0++ = *ptr1;
        }
        ptr1++;
    }
    *ptr0 = '\0';
}
void test_removeRepeatChar(){
    printf("test_removeRepeatChar\n");
    char s[] = "google";
    removeRepeatChar(s);
    puts(s);
}
}

#endif /* removeRepeatChar_h */
