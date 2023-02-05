#include"sorting.h"
#include<iostream>
#include<vector>
#include<map>
#include<ctime>
#include<chrono>

template<class T> long long speedTest(void(*)(T*,T*,bool(*)(T&,T&)),std::vector<T>&,bool(*)(T&,T&) = zk::sorting::comparasions::less);
template<class T> bool sortTest(void(*)(T*,T*,bool(*)(T&,T&)),std::vector<T>&,bool(*)(T&,T&) = zk::sorting::comparasions::less);

int main()
{
    srand(time(NULL));
    std::vector<std::pair<std::string,void(*)(int*,int*,bool(*)(int&,int&))> > functions{
            {"insertion sort",                  zk::sorting::insertion},
            {"bubble sort",                     zk::sorting::bubble},
            {"selection sort",                  zk::sorting::selection},
            {"heap sort",                       zk::sorting::heap},
            {"merge sort",                      zk::sorting::merge},
            {"quick sort (first element)",      zk::sorting::quick_first},
            {"quick sort (last element)",       zk::sorting::quick_last},
            {"quick sort (middle element)",     zk::sorting::quick_middle},
            {"quick sort (random element)",     zk::sorting::quick_random}
    };
    std::vector<int> Arr(1<<12);
    for(auto &i:Arr)
        i=rand();
    for(int i=0;i<functions.size();++i)
    {
        std::vector<int> arr(Arr);
        std::cout<<functions[i].first<<": "<<speedTest(functions[i].second,arr)<<" microseconds\n";
    }
}

template<class T> long long speedTest(
        void(*algo)(T*,T*,bool(*)(T&,T&)),
        std::vector<T>& arr,
        bool(*comp)(T&,T&)
                )
{
    auto start = std::chrono::high_resolution_clock::now();
    algo(arr.data(),arr.data()+arr.size(),comp);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    return duration.count();
}

template<class T> bool sortTest(
        void(*algo)(T*,T*,bool(*)(T&,T&)),
        std::vector<T>& arr,
        bool(*comp)(T&,T&)
                )
{
    algo(arr.data(),arr.data()+arr.size(),zk::sorting::comparasions::less);
    bool sorted=true;
    for(size_t i=1;i<arr.size()&&sorted;++i)
        sorted&=!comp(arr[i],arr[i-1]);
    return sorted;
}