#include "ArbDualNum.hpp"

template <typename T>
T func(T x)
{
    return tan(1/(2*x));
}

int main()
{
    arb_ptr rn,dn;
    arb_t re,fx,fdx;
    arb_init(re);
    arb_init(fx);
    arb_init(fdx);
    Matrix x;

    if(arb_set_str(re,"0.3",prec))
    {
        printf("x:代入失敗\n");
    }

    x = re;

    // f(x)
    rn = func(x + DualNumber()).Get_RN();
    arb_set(fx,rn);
    // f'(x)
    dn = func(x + DualNumber()).Get_DN();
    arb_set(fdx, dn);


    printf("fx:\n");
    arb_printd(rn,digit);
    printf("\n");
    printf("fdx:\n");
    arb_printd(dn, digit);
    printf("\n");

    arb_clear(re);
    arb_clear(fx);
    arb_clear(fdx);
    return 0;
}