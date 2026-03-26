#include <iostream>


template <int N,int I>
struct IsPrimeHelper
{
    constexpr static bool value = (N%I!=0)&& IsPrimeHelper<N,I-1>::value;
};

template <int N>
struct IsPrimeHelper<N,1>
{
    constexpr static bool value = true;
};

template <int N>
struct IsPrime
{
    constexpr static bool value = IsPrimeHelper<N,N/2>::value;
};

int main()
{

    static_assert(IsPrime<5>::value);
    std::cout<<IsPrime<17>::value<<std::endl;



    return 0;
}