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
    size_t size=end-begin;
    if(size<=1)
        return;
    T cop[size],*copbig=cop,*copend=cop+size,*copmid=cop+(size/2);
    for(size_t i=0;i<size;++i)
        cop[i]=begin[i];
    zk::sorting::merge(copbig,copmid,comp);
    zk::sorting::merge(copmid,copend,comp);
    for(T *i=begin,*j=copbig,*k=copmid;i!=end;++i)
        if(j==copmid)
            *i=*(k++);
        else if(k==end)
            *i=*(j++);
        else if(comp(*k,*j))
            *i=*(k++);
        else
            *i=*(j++);
}

template<class T> void zk::sorting::quick(T *begin, T *end, bool (*comp)(T &, T &)) {
    if(end-begin<=1)
        return;
    T p=*begin,*l=begin,*r=end-1;
    while(l<r)
    {
        if(comp(p,*r))
            --r;
        else if(comp(*l,p))
            ++l;
        else
            std::swap(*(l++),*r);
    }
    zk::sorting::quick(begin,l,comp);
    zk::sorting::quick(l+1,end,comp);
}