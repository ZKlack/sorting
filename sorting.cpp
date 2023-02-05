#include"sorting.h"
#include<iostream>

template<class T> void zk::sorting::insertion(T *begin, T *end, bool (*comp)(T &, T &)) {
    for(T *i=begin;i!=end;++i)
        for(T *j=i;j!=begin&&comp(*j,*(j-1));--j)
            std::swap(*j,*(j-1));
}

template<class T> void zk::sorting::bubble(T *begin, T *end, bool (*comp)(T &, T &)) {
    if(end-begin<=1)
        return;
    for(T *i=begin;i!=end;++i)
        for(T *j=end-1;j!=begin;--j)
            if(comp(*j,*(j-1)))
                std::swap(*j,*(j-1));
}

template<class T> void zk::sorting::selection(T *begin, T *end, bool (*comp)(T &, T &)) {
    for(T *i=begin,*j,*m;i!=end;++i){
        for(j=i,m=i;j!=end;++j)
            if(comp(*j,*m))
                m=j;
        std::swap(*i,*m);
    }
}

template<class T> void zk::sorting::merge(T *begin, T *end, bool (*comp)(T &, T &)) {
    size_t size=end-begin,hsize=size>>1;
    if(size<=1)
        return;
    zk::sorting::merge(begin,begin+hsize,comp);
    zk::sorting::merge(begin+hsize,end,comp);
    T cop[size];
    for(size_t i=0;i<size;++i)
        cop[i]=begin[i];
    T *copb=&(cop[0]), *copm=copb+hsize, *cope=copb+size;
    for(size_t i=0, j=0, k=0;i<size;++i)
    {
        while(j==copm-copb&&k<cope-copm)
            begin[i++]=copm[k++];
        while(k==cope-copm&&j<copm-copb)
            begin[i++]=copb[j++];
        if(i>=size)
            break;
        if(comp(copm[k],copb[j]))
            begin[i]=copm[k++];
        else
            begin[i]=copb[j++];
    }
}

template<class T> void zk::sorting::quick_first(T *begin, T *end, bool (*comp)(T &, T &)) {
    if(end-begin<=1)
        return;
    T *p=begin, *l=begin+1, *r=end-1;
    while(l<r)
    {
        while(!comp(*p,*l)&&l<r)
            ++l;
        while(comp(*p,*r)&&l<r)
            --r;
        std::swap(*l,*r);
    }
    while(comp(*p,*l))
        --l;
    std::swap(*l,*p);
    p=l;
    zk::sorting::quick_first(begin,p,comp);
    zk::sorting::quick_first(p+1,end,comp);
}

template<class T> void zk::sorting::heap(T *begin, T *end, bool (*comp)(T &, T &)) {
    size_t size=end-begin;
    for(size_t i=size;i>0;--i)
    {
        size_t j=i;
        bool heapify;
        do{
            size_t p=j,l=j<<1,r=(j<<1)+1;
            if(l<=size&&comp(begin[p-1],begin[l-1]))
                p=l;
            if(r<=size&&comp(begin[p-1],begin[r-1]))
                p=r;
            heapify=p!=j;
            if(heapify)
            {
                std::swap(begin[p-1],begin[j-1]);
                j=p;
            }
        }while(heapify);
    }
    while(begin<end)
    {
        std::swap(*begin,*(--end));
        --size;
        size_t j=1;
        bool heapify;
        do{
            size_t p=j,l=j<<1,r=(j<<1)+1;
            if(l<=size&&comp(begin[p-1],begin[l-1]))
                p=l;
            if(r<=size&&comp(begin[p-1],begin[r-1]))
                p=r;
            heapify=p!=j;
            if(heapify)
            {
                std::swap(begin[p-1],begin[j-1]);
                j=p;
            }
        }while(heapify);
    }
}

template<class T> void zk::sorting::quick_last(T *begin, T *end, bool (*comp)(T &, T &)) {
    if(end-begin<=1)
        return;
    T *p=end-1, *l=begin, *r=end-2;
    while(l<r)
    {
        while(!comp(*p,*l)&&l<r)
            ++l;
        while(comp(*p,*r)&&l<r)
            --r;
        std::swap(*l,*r);
    }
    while(comp(*r,*p))
        ++r;
    std::swap(*r,*p);
    p=r;
    zk::sorting::quick_last(begin,p,comp);
    zk::sorting::quick_last(p+1,end,comp);
}

template<class T> void zk::sorting::quick_middle(T *begin, T *end, bool (*comp)(T &, T &)) {
    size_t size=end-begin;
    if(size<=1)
        return;
    T p=begin[size>>1], *l=begin, *r=end-1;
    while(l<r)
    {
        while(!comp(p,*l)&&l<r)
            ++l;
        while(comp(p,*r)&&l<r)
            --r;
        std::swap(*l,*r);
    }
    l=begin;
    while(p!=*l)
        ++l;
    zk::sorting::quick_last(begin,l,comp);
    zk::sorting::quick_last(l+1,end,comp);
}

template<class T> void zk::sorting::quick_random(T *begin, T *end, bool (*comp)(T &, T &)) {
    size_t size=end-begin;
    if(size<=1)
        return;
    T p=begin[rand()%size], *l=begin, *r=end-1;
    while(l<r)
    {
        while(!comp(p,*l)&&l<r)
            ++l;
        while(comp(p,*r)&&l<r)
            --r;
        std::swap(*l,*r);
    }
    l=begin;
    while(p!=*l)
        ++l;
    zk::sorting::quick_last(begin,l,comp);
    zk::sorting::quick_last(l+1,end,comp);
}