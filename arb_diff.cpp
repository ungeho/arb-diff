#include "ArbDualNum.hpp"

template <typename T>
T func(T x)
{
    return tan(1/(2*x));
}

int main()
{
    Matrix x="0.3",fx;

    // fx = f(x + ε)
    fx = func(x + DualNumber());

    printf("x:\n");
    // 2x2の行列xを出力
    show_mat(x);
    printf("f(x):\n");
    // fxの要素[0,0]を出力
    show_arb(fx.Get_RN());
    printf("f'(x):\n");
    // fxの要素[0,1]を出力
    show_arb(fx.Get_DN());

    return 0;
}