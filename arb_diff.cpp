#include "ArbDualNum.hpp"


//f(x)
template <typename T>
T func(T x)
{
    return tan(1/(2*x)) * "1.1";
}

int main()
{
    Matrix x="0.3",fx;

    // fx = f(x + ε)
    fx = func(x + DualNumber());

    //xを出力
    printf("x:\n");
    show_arb(x.Get_RN());

    //(x+ε)を出力
    // printf("x+ε:\n");
    // show_mat(x + DualNumber());

    // f(x)を出力
    printf("f(x):\n");
    // fxの要素[0,0]を出力
    show_arb(fx.Get_RN());

    // f'(x)を出力
    printf("f'(x):\n");
    // fxの要素[0,1]を出力
    show_arb(fx.Get_DN());

    return 0;
}