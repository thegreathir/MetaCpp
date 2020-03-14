
template <int... i>
struct seq
{};

template<int n, int i0, int... i>
struct head
{
    template<int... j>
    struct ret : head<n-1, i...>::template ret<j..., i0>
    {};
};

template<int i0, int... i>
struct head<0, i0, i...>
{
    template<int... j>
    struct ret : seq<j...>
    {};
};


template<int n, int i0, int... i>
struct tail : tail<n - 1, i...>
{};


template<int i0, int... i>
struct tail<0, i0, i...> : seq<i0, i...>
{};

template<int i0>
struct tail<1, i0> : seq<>
{};

template<template<int...> class c, int... i>
c<i...> proxy(seq<i...>) {
}

template<class none, template<class, int...> class c, int... i>
c<none, i...> proxy_none(seq<i...>) {
}


template<int i0, int...i>
struct first {
    static const int v = i0;
};


namespace merge {

template<int ...i>
struct a
{

    template<class none, int ...j>
    struct b
    {
        template<class if_none, bool>
        struct if_merge;

        template<int ...k>
        struct ret : if_merge<none,
                         (first<i...>::v < first<j...>::v)
                     >::template if_ret<k...>
        {
        };

        template<class if_none>
        struct if_merge<if_none, true> {
            template<int... kk>
            struct if_ret : decltype(proxy<a>(tail<1, i...>()))::
                                template b<if_none, j...>::
                                    template ret<kk..., first<i...>::v>
            {};
        };

        template<class if_none>
        struct if_merge<if_none, false> {
            template<int... kk>
            struct if_ret : a<i...>::
                                decltype(proxy_none<if_none, b>(tail<1, j...>()))::
                                    template ret<kk..., first<j...>::v>
            {};
        };
    };

    template<class none>
    struct b<none> {
        template<int ...k>
        struct ret : seq<k..., i...>
        {
        };
    };

};

template<>
struct a<> {
    template<class none, int ...j>
    struct b
    {
        template<int ...k>
        struct ret : seq<k..., j...>
        {};
    };

};
};

template<int ...i>
struct sort : decltype(proxy_none<
                      void, 
                decltype(proxy<merge::a>(
                    decltype(proxy<sort>(typename head<sizeof...(i)/2, i...>:: template ret<>()))()
                )):: template b
                >(
                    decltype(proxy<sort>(tail<sizeof...(i)/2, i...>()))()
                ))::template ret<>
{};

template<int i>
struct sort<i> : seq<i>
{};


#include <type_traits>
static_assert(std::is_base_of<seq<-1000, 1, 2, 3, 4, 4, 4, 5, 9, 10>, sort<9,10,5,4,1,3,2,4,4,-1000>>::value);
static_assert(std::is_base_of<seq<-73, -72, -59, -56, -52, -50, -45, -19, -17, 53, 64, 99>, sort<-56, 99, -72, -52, -17, 53, -45, -19, 64, -59, -73, -50>>::value);
static_assert(std::is_base_of<seq<-98, -97, -34, -31, -21, -21, -3, 1, 31, 61, 65, 78>, sort<65, -97, 78, -21, 31, -3, 61, -31, 1, -98, -34, -21>>::value);
static_assert(std::is_base_of<seq<-92, -73, -32, -5, -3, 5, 15, 21, 67, 89>, sort<-92, -5, 21, 67, -73, -3, 89, 5, -32, 15>>::value);
static_assert(std::is_base_of<seq<-94, -70, -50, -36, 44, 48, 55, 65>, sort<-50, 55, 48, 44, 65, -36, -94, -70>>::value);
static_assert(std::is_base_of<seq<-76, -66, -60, -57, -12, -10, -9, 41, 42, 73, 78, 83, 94, 97>, sort<-10, -9, 78, -57, -66, 83, 42, 73, -12, 94, 41, 97, -76, -60>>::value);
static_assert(std::is_base_of<seq<-92, -86, -63, -59, -20, -18, -3, -2, 25, 28, 32, 39, 75, 76>, sort<-92, -20, -3, -18, -63, -86, -2, 25, -59, 39, 28, 76, 32, 75>>::value);
static_assert(std::is_base_of<seq<-85, -84, -49, 28, 72, 83, 88, 91, 95, 100>, sort<100, 95, 72, -85, -84, 88, 91, 83, -49, 28>>::value);
static_assert(std::is_base_of<seq<-80, -63, -45, -38, -16, -5, 48, 57, 60, 80, 86>, sort<80, -80, -5, 48, 57, -38, 60, -45, -16, 86, -63>>::value);
static_assert(std::is_base_of<seq<-89, -86, -66, -64, -32, -6, 34, 37, 46, 66, 93>, sort<-6, -66, 34, 66, 46, -89, -64, -32, 93, -86, 37>>::value);
static_assert(std::is_base_of<seq<-58, -50, -28, -2, 14, 30, 32, 39, 52, 77, 80, 92>, sort<14, -2, 32, 80, 30, 39, 92, -50, 77, -28, 52, -58>>::value);
static_assert(std::is_base_of<seq<-69, -66, -53, -19, 16, 25, 26, 46, 62, 66, 72, 94, 95>, sort<-66, 16, 25, 72, 62, -19, -69, 66, -53, 94, 46, 26, 95>>::value);
static_assert(std::is_base_of<seq<-78, -71, -54, -21, -19, 16, 17, 33, 37, 49, 84>, sort<33, -21, 16, -19, -71, 84, 49, -78, 37, 17, -54>>::value);
static_assert(std::is_base_of<seq<-44, -30, -9, 17, 23, 27, 30, 33, 54, 71>, sort<-30, -44, 23, 33, -9, 17, 71, 54, 27, 30>>::value);
static_assert(std::is_base_of<seq<-96, -60, -52, -51, -44, -27, -14, -13, 6, 58, 68, 77, 98>, sort<-60, -52, -51, 58, -96, -27, 77, 68, -13, -44, 98, -14, 6>>::value);
static_assert(std::is_base_of<seq<-80, -77, -39, -25, -14, -8, 3, 9, 22, 30, 30>, sort<-14, -8, 22, -80, 30, -25, 30, 9, -39, -77, 3>>::value);
int main(){}
