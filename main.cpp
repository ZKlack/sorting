#include<iostream>
#include"sorting.h"
#include<vector>
#include<map>
#include<time.h>
#include<chrono>

bool less(int&a,int&b){return a<b;}

int main()
{
    srand(time(NULL));
    std::map<std::string,void(*)(int*,int*,bool(*)(int&,int&))> functions={
            {"insertion sort",  zk::sorting::insertion<int>},
            {"bubble sort",     zk::sorting::bubble<int>},
            {"selection sort",  zk::sorting::selection<int>},
            {"merge sort",      zk::sorting::merge<int>},
            {"quick sort",      zk::sorting::quick<int>},
            {"heap sort",       zk::sorting::heap<int>}
    };
    std::vector<int> Arr(10000);
    for (int &i: Arr)
        i = rand();
    for(auto algo:functions) {
        std::vector<int> arr(Arr);
        int sw=0;
        do{
            auto start = std::chrono::high_resolution_clock::now();
            algo.second(arr.data(), arr.data() + arr.size(),less);
            auto stop = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
            std::cout<<algo.first<< " took " << duration.count() << " microseconds\n";
        }while(++sw&1);
    }
}