//
//  ST.h
//  find
//
//  Created by junl on 2020/12/2.
//  Copyright © 2020 junl. All rights reserved.
//

#ifndef ST_h
#define ST_h

template <class Key, class Value>
class ST {
public:
    ST();
    void put(Key key, Value value);
    Value get(Key key);
    void remove(Key key);
    bool contains(Key key) {
        return get(key);
    };
    bool isEmpty();
    int size();
    virtual ~ST(){}
};

#endif /* ST_h */
