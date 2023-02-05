#ifndef SORTING_SORTING_H
#define SORTING_SORTING_H

namespace zk::sorting{
    namespace comparasions{
        template<class T>bool less(T &a,T &b){return a<b;}
        template<class T>bool more(T &a,T &b){return a>b;}
        template<class T>bool lessorequal(T &a,T &b){return a<=b;}
        template<class T>bool moreorequal(T &a,T &b){return a>=b;}
    }
    template<class T> void insertion(T*,T*,bool(*)(T&,T&) = zk::sorting::comparasions::less);
    template<class T> void bubble(T*,T*,bool(*)(T&,T&) = zk::sorting::comparasions::less);
    template<class T> void selection(T*,T*,bool(*)(T&,T&) = zk::sorting::comparasions::less);
    template<class T> void merge(T*,T*,bool(*)(T&,T&) = zk::sorting::comparasions::less);
    template<class T> void quick_first(T*,T*,bool(*)(T&,T&) = zk::sorting::comparasions::less);
    template<class T> void quick_last(T*,T*,bool(*)(T&,T&) = zk::sorting::comparasions::less);
    template<class T> void quick_middle(T*,T*,bool(*)(T&,T&) = zk::sorting::comparasions::less);
    template<class T> void quick_random(T*,T*,bool(*)(T&,T&) = zk::sorting::comparasions::less);
    template<class T> void heap(T*,T*,bool(*)(T&,T&) = zk::sorting::comparasions::less);
}

#include"sorting.cpp"
#endif //SORTING_SORTING_H