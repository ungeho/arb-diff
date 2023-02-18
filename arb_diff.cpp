#include "ArbDualNum.hpp"

template <typename T>
T func(T x)
{
    return sqrt(x);
}

int main()
{
    Matrix x=4,y=0,z;

    z = 6;

    z = func(z + DualNumber());

    z.show();

    return 0;
}