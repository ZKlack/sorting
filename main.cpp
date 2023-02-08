#include"sorting.h"
#include<iostream>
#include<vector>
#include<map>
#include<ctime>
#include<chrono>
#include<fstream>
#include<filesystem>

template<class T> long long speedTest(void(*)(T*,T*,bool(*)(T&,T&)),std::vector<T>&,bool(*)(T&,T&) = zk::sorting::comparasions::less);
template<class T> bool sortTest(void(*)(T*,T*,bool(*)(T&,T&)),std::vector<T>&,bool(*)(T&,T&) = zk::sorting::comparasions::less);
template<class T> bool isSorted(std::vector<T>&,bool(*)(T&,T&) = zk::sorting::comparasions::less);

int main()
{
    std::cout<<"program started\n";
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
    if(std::filesystem::exists("random_arrays.txt"))
        std::filesystem::remove("random_arrays.txt");
    std::ofstream fout("random_arrays.txt",std::fstream::out);
    size_t maxsize=1<<14,minsize=1,samplesize=maxsize-minsize+1;
    fout<<samplesize<<'\n';
    for(size_t i=minsize;i<=maxsize;++i)
    {
        fout<<i<<'\n';
        for(size_t j=0;j<i;++j)
            fout<<rand()<<' ';
        fout<<'\n';
    }
    fout.close();
    for(const auto &function:functions)
    {
        if(!std::filesystem::is_directory(function.first))
            std::filesystem::create_directory(function.first);
        if(std::filesystem::exists(function.first+"\\sorted_arrays.txt"))
            std::filesystem::remove(function.first+"\\sorted_arrays.txt");
        if(std::filesystem::exists(function.first+"\\speeds.txt"))
            std::filesystem::remove(function.first+"\\speeds.txt");
        std::cout<<"started "<<function.first;
        std::ofstream arrays(function.first+"\\sorted_arrays.txt",std::fstream::out);
        std::ofstream speeds(function.first+"\\speeds.txt",std::fstream::out);
        std::ifstream fin("random_arrays.txt",std::fstream::in);
        size_t enteries;
        fin>>enteries;
        arrays<<enteries<<'\n';
        speeds<<enteries<<'\n';
        while(enteries--)
        {
            size_t size;
            fin>>size;
            arrays<<size<<'\n';
            speeds<<size<<' ';
            std::vector<int> arr(size);
            for(size_t i=0;i<size;++i)
                fin>>arr[i];
            unsigned long long speed=speedTest(function.second,arr);
            speeds<<speed<<' ';
            if(!isSorted(arr))
            {
                std::cout<<"\narray not sorted:\n\t-sort: "<<function.first<<"\n\t-size: "<<size;
                return 1;
            }
            speed=speedTest(function.second,arr);
            speeds<<speed<<'\n';
            for(size_t i=0;i<size;++i)
                arrays<<arr[i]<<' ';
            arrays<<'\n';
            if(enteries%500==0)
                std::cout<<"\n\t"<<enteries<<" enteries left...";
        }
        arrays.close();
        speeds.close();
        fin.close();
        std::cout<<"\nDone!\n";
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
    algo(arr.data(),arr.data()+arr.size(),comp);
    bool sorted=true;
    for(size_t i=1;i<arr.size()&&sorted;++i)
        sorted&=!comp(arr[i],arr[i-1]);
    return sorted;
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
