#ifndef SORTING_SORTING_H
#define SORTING_SORTING_H

namespace zk::sorting{
    template<class T> void insertion(T*,T*,bool(*)(T&,T&));
    template<class T> void bubble(T*,T*,bool(*)(T&,T&));
    template<class T> void selection(T*,T*,bool(*)(T&,T&));
    template<class T> void merge(T*,T*,bool(*)(T&,T&));
    template<class T> void quick(T*,T*,bool(*)(T&,T&));
}

#include"sorting.cpp"
#endif //SORTING_SORTING_H