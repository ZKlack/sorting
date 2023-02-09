#include"sorting.h"
#include<iostream>
#include<vector>
#include<map>
#include<ctime>
#include<chrono>
#include<fstream>
#include<filesystem>

#define type uint8_t
const size_t sizeStart = 100;
const size_t sizeLimit = SIZE_MAX-101;
const size_t sizeIncrm = sizeStart;

template<class T> long long speedTest(void(*)(T*,T*,bool(*)(T&,T&)),std::vector<T>&,bool(*)(T&,T&) = zk::sorting::comparasions::less);
template<class T> bool sortTest(void(*)(T*,T*,bool(*)(T&,T&)),std::vector<T>&,bool(*)(T&,T&) = zk::sorting::comparasions::less);
template<class T> bool isSorted(std::vector<T>&,bool(*)(T&,T&) = zk::sorting::comparasions::less);

int main()
{
    std::cout<<"program started\n";
    srand(time(NULL));
    std::vector<std::pair<std::string,void(*)(type*,type*,bool(*)(type&,type&))> > functions{
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
    if(std::filesystem::exists("random_arrays.txt"))
        std::filesystem::remove("random_arrays.txt");
    std::ofstream fout("random_arrays.txt",std::fstream::out);
    for(size_t i=sizeStart;i<=sizeLimit;i+=sizeIncrm)
    {
        fout<<i<<'\n';
        for(size_t j=0;j<i;++j)
            fout<<(type)rand()<<' ';
        fout<<'\n';
    }
    fout.close();
    for(const auto &function:functions)
    {
        if(!std::filesystem::is_directory(function.first))
            std::filesystem::create_directory(function.first);
        if(std::filesystem::exists(function.first+"\\speeds.txt"))
            std::filesystem::remove(function.first+"\\speeds.txt");
        std::cout<<"started "<<function.first;
        std::ofstream speeds(function.first+"\\speeds.txt",std::fstream::out);
        std::ifstream fin("random_arrays.txt",std::fstream::in);
        while(!fin.eof())
        {
            size_t size;
            fin>>size;
            speeds<<size<<' ';
            std::vector<type> arr(size);
            for(auto &i:arr)
                fin>>i;
            unsigned long long speed=speedTest(function.second,arr);
            speeds<<speed<<' ';
            if(!isSorted(arr))
            {
                std::cout<<"\narray not sorted:\n\t-sort: "<<function.first<<"\n\t-size: "<<size;
                system("PAUSE");
            }
            speed=speedTest(function.second,arr);
            speeds<<speed<<' ';
            speed=speedTest(function.second,arr,zk::sorting::comparasions::more);
            speeds<<speed<<'\n';
            std::cout<<"size "<<size<<" done\n";
        }
        speeds.close();
        fin.close();
        std::cout<<'\n'<<function.first<<" finished\n";
    }
    std::cout<<"Done!\n";
    system("PAUSE");
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
    algo(arr.data(),arr.data()+arr.size(),comp);
    return isSorted(arr,comp);
}

template<class T> bool isSorted(
        std::vector<T>& arr,
        bool(*comp)(T&,T&)
)
{
    bool sorted=true;
    for(size_t i=1;i<arr.size()&&sorted;++i)
        sorted&=!comp(arr[i],arr[i-1]);
    return sorted;
}
