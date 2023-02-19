#include "arb.h"
#include "arb_mat.h"

// 行,列
slong r=2,c=2;
// 精度
slong prec=53;
// 表示桁数
slong digit=17;


slong factrial(slong n) {
    if (n > 0)
    {
        return n * factrial(n - 1);
    }
    else
    {
        return 1;
    }
}


class Matrix
{
    arb_mat_t mat;
    public:
        //名前忘れた
        ~Matrix(void){};

        // 定義したとき(代入なし)
        Matrix(void)
        {
            // 2行2列のゼロ行列に初期化
            arb_mat_init(mat, r, c);
        }

        // 定義したときの代入(0代入)
        Matrix(const int obj)
        {
            Matrix tmp;
            // 行列初期化
            arb_mat_init(this->mat, r, c);
            // 単位行列
            arb_mat_one(tmp.mat);
            // 行列*スカラー(signed long)
            arb_mat_scalar_mul_si(this->mat, tmp.mat, obj, prec);
        }
        // 定義したときの代入(整数)
        Matrix(const slong obj)
        {
            Matrix tmp;
            // 行列初期化
            arb_mat_init(this->mat, r, c);
            // 単位行列
            arb_mat_one(tmp.mat);
            // 行列*スカラー(signed long)
            arb_mat_scalar_mul_si(this->mat,tmp.mat,obj,prec);
        }
        // 定義したときの代入(arb_t)
        Matrix(const arb_t obj)
        {
            Matrix tmp;
            // 行列初期化
            arb_mat_init(this->mat, r, c);
            // 単位行列
            arb_mat_one(tmp.mat);
            // 行列*スカラー(signed long)
            arb_mat_scalar_mul_arb(this->mat, tmp.mat, obj, prec);
        }
        // 定義したときの代入(char*)
        Matrix(const char* obj)
        {
            Matrix tmp;
            arb_t arb_obj;
            arb_init(arb_obj);
            // 行列初期化
            arb_mat_init(this->mat, r, c);
            // 単位行列
            arb_mat_one(tmp.mat);
            if (arb_set_str(arb_obj, obj, prec))
            {
                printf("定義時の代入失敗\n");
            }
            arb_mat_scalar_mul_arb(this->mat, tmp.mat, arb_obj, prec);
            arb_clear(arb_obj);
        }


        // +x
        inline const Matrix operator+(void) const
        {
            return *this;
        }
        // -x
        const Matrix operator-(void) const
        {
            Matrix res;
            // 単位行列を作り res = res * -1
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_si(res.mat, res.mat, -1, prec);

            res = res * (*this);

            return res;
        }

        // 右辺と左辺の要素
        // 行列
        // スカラー(整数 slong)
        // スカラー(実数 arb_t)
        // スカラー(実数 char*)
        // TODO:arb_tとchar*のみ両辺arb_tと両辺char*も実装しておきたい。

        // 掛け算
        // 行列*行列
        friend const Matrix operator*(const Matrix lhs,const Matrix rhs)
        {
            Matrix res;
            arb_mat_mul(res.mat, lhs.mat, rhs.mat, prec);
            return res;
        }
        // 行列*整数(int)
        friend const Matrix operator*(const Matrix lhs, const int rhs)
        {
            Matrix res;
            arb_mat_scalar_mul_si(res.mat, lhs.mat, rhs, prec);
            return res;
        }
        // 整数（int）*行列
        friend const Matrix operator*(const int lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_scalar_mul_si(res.mat, rhs.mat, lhs, prec);
            return res;
        }
        // 行列*整数(slong)
        friend const Matrix operator*(const Matrix lhs, const slong rhs)
        {
            Matrix res;
            arb_mat_scalar_mul_si(res.mat, lhs.mat, rhs, prec);
            return res;
        }
        // 整数（slong）*行列
        friend const Matrix operator*(const slong lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_scalar_mul_si(res.mat, rhs.mat, lhs, prec);
            return res;
        }
        // 行列*実数(arb_t)
        friend const Matrix operator*(const Matrix lhs, const arb_t rhs)
        {
            Matrix res;
            arb_mat_scalar_mul_arb(res.mat, lhs.mat, rhs, prec);
            return res;
        }
        // 実数（arb_t）*行列
        friend const Matrix operator*(const arb_t lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_scalar_mul_arb(res.mat, rhs.mat, lhs, prec);
            return res;
        }
        // 行列*実数(char*)
        friend const Matrix operator*(const Matrix lhs, const char* rhs)
        {
            Matrix res;
            arb_t arb_rhs;
            arb_init(arb_rhs);
            if (arb_set_str(arb_rhs, rhs, prec))
            {
                printf("*演算時の代入失敗( lhs(Matrix) * rhs(char*) )\n");
            }
            arb_mat_scalar_mul_arb(res.mat, lhs.mat, arb_rhs, prec);
            arb_clear(arb_rhs);
            return res;
        }
        // 実数（char*）*行列
        friend const Matrix operator*(const char* lhs, const Matrix rhs)
        {
            Matrix res;
            arb_t arb_lhs;
            arb_init(arb_lhs);
            if (arb_set_str(arb_lhs, lhs, prec))
            {
                printf("*演算時の代入失敗( lhs(char*) * rhs(Matrix) )\n");
            }
            arb_mat_scalar_mul_arb(res.mat, rhs.mat, arb_lhs, prec);
            arb_clear(arb_lhs);
            return res;
        }

        // 足し算
        // 行列+行列
        friend const Matrix operator+(const Matrix lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_add(res.mat, lhs.mat, rhs.mat, prec);
            return res;
        }
        // 行列(int)+整数
        friend const Matrix operator+(const Matrix lhs, const int rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_si(res.mat, res.mat, rhs, prec);
            arb_mat_add(res.mat, lhs.mat, res.mat, prec);
            return res;
        }
        // 整数(int)+行列
        friend const Matrix operator+(const int lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_si(res.mat, res.mat, lhs, prec);
            arb_mat_add(res.mat, res.mat, rhs.mat, prec);
            return res;
        }
        // 行列+整数
        friend const Matrix operator+(const Matrix lhs, const slong rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_si(res.mat,res.mat,rhs,prec);
            arb_mat_add(res.mat, lhs.mat,res.mat, prec);
            return res;
        }
        // 整数+行列
        friend const Matrix operator+(const slong lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_si(res.mat, res.mat, lhs, prec);
            arb_mat_add(res.mat, res.mat, rhs.mat, prec);
            return res;
        }
        // 行列+実数(arb_t)
        friend const Matrix operator+(const Matrix lhs, const arb_t rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_arb(res.mat, res.mat, rhs, prec);
            arb_mat_add(res.mat, lhs.mat, res.mat, prec);
            return res;
        }
        // 実数(arb_t)+行列
        friend const Matrix operator+(const arb_t lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_arb(res.mat, res.mat, lhs, prec);
            arb_mat_add(res.mat, res.mat, rhs.mat, prec);
            return res;
        }
        // 行列+実数(char*)
        friend const Matrix operator+(const Matrix lhs, const char* rhs)
        {
            Matrix res;
            arb_t arb_rhs;
            arb_init(arb_rhs);
            if (arb_set_str(arb_rhs, rhs, prec))
            {
                printf("演算時の代入失敗( lhs(Matrix) + rhs(char*) )\n");
            }
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_arb(res.mat, res.mat, arb_rhs, prec);
            arb_mat_add(res.mat, lhs.mat, res.mat, prec);
            arb_clear(arb_rhs);
            return res;
        }
        // 実数(char*)+行列
        friend const Matrix operator+(const char* lhs, const Matrix rhs)
        {
            Matrix res;
            arb_t arb_lhs;
            arb_init(arb_lhs);
            if (arb_set_str(arb_lhs, lhs, prec))
            {
                printf("演算時の代入失敗( lhs(char*) + rhs(Matrix) )\n");
            }
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_arb(res.mat, res.mat, arb_lhs, prec);
            arb_mat_add(res.mat, res.mat, rhs.mat, prec);
            arb_clear(arb_lhs);
            return res;
        }

        // 引き算
        // 行列-行列
        friend const Matrix operator-(const Matrix lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_sub(res.mat, lhs.mat, rhs.mat, prec);
            return res;
        }
        // 行列-整数(int)
        friend const Matrix operator-(const Matrix lhs, const int rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_si(res.mat, res.mat, rhs, prec);
            arb_mat_sub(res.mat, lhs.mat, res.mat, prec);
            return res;
        }
        // 整数(int)-行列
        friend const Matrix operator-(const int lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_si(res.mat, res.mat, lhs, prec);
            arb_mat_sub(res.mat, res.mat, rhs.mat, prec);
            return res;
        }
        // 行列-整数
        friend const Matrix operator-(const Matrix lhs, const slong rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_si(res.mat, res.mat, rhs, prec);
            arb_mat_sub(res.mat, lhs.mat, res.mat, prec);
            return res;
        }
        // 整数-行列
        friend const Matrix operator-(const slong lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_si(res.mat, res.mat, lhs, prec);
            arb_mat_sub(res.mat, res.mat, rhs.mat, prec);
            return res;
        }
        // 行列-実数(arb_t)
        friend const Matrix operator-(const Matrix lhs, const arb_t rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_arb(res.mat, res.mat, rhs, prec);
            arb_mat_sub(res.mat, lhs.mat, res.mat, prec);
            return res;
        }
        // 実数(arb_t)-行列
        friend const Matrix operator-(const arb_t lhs, const Matrix rhs)
        {
            Matrix res;
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_arb(res.mat, res.mat, lhs, prec);
            arb_mat_sub(res.mat, res.mat, rhs.mat, prec);
            return res;
        }
        // 行列-実数(char*)
        friend const Matrix operator-(const Matrix lhs, const char* rhs)
        {
            Matrix res;
            arb_t arb_rhs;
            arb_init(arb_rhs);
            if (arb_set_str(arb_rhs, rhs, prec))
            {
                printf("演算時の代入失敗( lhs(Matrix) - rhs(char*) )\n");
            }
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_arb(res.mat, res.mat, arb_rhs, prec);
            arb_mat_sub(res.mat, lhs.mat, res.mat, prec);
            arb_clear(arb_rhs);
            return res;
        }
        // 実数(char*)-行列
        friend const Matrix operator-(const char* lhs, const Matrix rhs)
        {
            Matrix res;
            arb_t arb_lhs;
            arb_init(arb_lhs);
            if (arb_set_str(arb_lhs, lhs, prec))
            {
                printf("演算時の代入失敗( lhs(char*) - rhs(Matrix) )\n");
            }
            arb_mat_one(res.mat);
            arb_mat_scalar_mul_arb(res.mat, res.mat, arb_lhs, prec);
            arb_mat_sub(res.mat, res.mat, rhs.mat, prec);
            arb_clear(arb_lhs);
            return res;
        }

        // 割り算
        // 行列/行列
        friend const Matrix operator/(const Matrix lhs, const Matrix rhs)
        {
            Matrix res;
            if (arb_mat_inv(res.mat,rhs.mat, prec)) {
                arb_mat_mul(res.mat,lhs.mat,res.mat,prec);
            } else {
                printf("厳密な逆行列を求めることが出来ません。\n");
            }
            return res;
        }
        // 行列/整数(int)
        friend const Matrix operator/(const Matrix lhs, const int rhs)
        {
            Matrix res;
            arb_t tmp;
            // 1/rhs
            arb_init(tmp);
            arb_set_si(tmp, rhs);
            arb_inv(tmp, tmp, prec);
            // lhs/rhs
            arb_mat_scalar_mul_arb(res.mat, lhs.mat, tmp, prec);
            // clear tmp
            arb_clear(tmp);
            return res;
        }
        // 整数（int）/行列
        friend const Matrix operator/(const int lhs, const Matrix rhs)
        {
            Matrix res;
            if (arb_mat_inv(res.mat, rhs.mat, prec))
            {
                arb_mat_scalar_mul_si(res.mat, res.mat, lhs, prec);
            }
            else
            {
                printf("厳密な逆行列を求めることが出来ません。\n");
            }
            return res;
        }
        // 行列/整数(slong)
        friend const Matrix operator/(const Matrix lhs, const slong rhs)
        {
            Matrix res;
            arb_t tmp;
            // 1/rhs
            arb_init(tmp);
            arb_set_si(tmp,rhs);
            arb_inv(tmp,tmp,prec);
            // lhs/rhs
            arb_mat_scalar_mul_arb(res.mat,lhs.mat,tmp,prec);
            // clear tmp
            arb_clear(tmp);
            return res;
        }
        // 整数（slong）/行列
        friend const Matrix operator/(const slong lhs, const Matrix rhs)
        {
            Matrix res;
            if(arb_mat_inv(res.mat,rhs.mat,prec)) {
                arb_mat_scalar_mul_si(res.mat, res.mat, lhs, prec);
            } else {
                printf("厳密な逆行列を求めることが出来ません。\n");
            }
            return res;
        }
        // 行列/実数(arb_t)
        friend const Matrix operator/(const Matrix lhs, const arb_t rhs)
        {
            Matrix res;
            arb_t  tmp;
            // 1/rhs
            arb_init(tmp);
            arb_inv(tmp,rhs, prec);
            // lhs/rhs
            arb_mat_scalar_mul_arb(res.mat, lhs.mat, rhs, prec);
            // clear
            arb_clear(tmp);
            return res;
        }
        // 実数（arb_t）/行列
        friend const Matrix operator/(const arb_t lhs, const Matrix rhs)
        {
            Matrix res;
            if (arb_mat_inv(res.mat, rhs.mat, prec))
            {
                arb_mat_scalar_mul_arb(res.mat, rhs.mat, lhs, prec);
            } else {
                printf("厳密な逆行列を求めることが出来ません。\n");
            }
            return res;
        }
        // 行列/実数(char*)
        friend const Matrix operator/(const Matrix lhs, const char* rhs)
        {
            Matrix res;
            arb_t tmp;
            arb_t arb_rhs;
            arb_init(arb_rhs);
            if (arb_set_str(arb_rhs, rhs, prec))
            {
                printf("演算時の代入失敗( lhs(Matrix) / rhs(char*) )\n");
            }
            // 1/rhs
            arb_inv(arb_rhs, arb_rhs, prec);
            // lhs/rhs
            arb_mat_scalar_mul_arb(res.mat, lhs.mat, arb_rhs, prec);
            // clear
            arb_clear(arb_rhs);
            return res;
        }
        // 実数（char*）/行列
        friend const Matrix operator/(const char* lhs, const Matrix rhs)
        {
            Matrix res;
            arb_t arb_lhs;
            arb_init(arb_lhs);
            if (arb_set_str(arb_lhs, lhs, prec))
            {
                printf("演算時の代入失敗( lhs(*char) / rhs(Matrix) )\n");
            }
            if (arb_mat_inv(res.mat, rhs.mat, prec))
            {
                arb_mat_scalar_mul_arb(res.mat, rhs.mat, arb_lhs, prec);
            }
            else
            {
                printf("厳密な逆行列を求めることが出来ません。\n");
            }
            arb_clear(arb_lhs);
            return res;
        }

        // 代入
        // 行列=行列
        Matrix operator=(const Matrix obj)
        {
            arb_mat_set(this->mat,obj.mat);
            return *this;
        }
        // 行列=整数（0代入）
        Matrix operator=(const int obj)
        {
            arb_mat_one(this->mat);
            arb_mat_scalar_mul_si(this->mat, this->mat, obj, prec);
            return *this;
        }
        // 行列=整数
        Matrix operator=(const slong obj)
        {
            arb_mat_one(this->mat);
            arb_mat_scalar_mul_si(this->mat,this->mat,obj,prec);
            return *this;
        }
        // 行列=実数(arb_t)
        Matrix operator=(const arb_t obj)
        {
            arb_mat_one(this->mat);
            arb_mat_scalar_mul_arb(this->mat, this->mat, obj, prec);
            return *this;
        }
        // 行列=実数(char*)
        Matrix operator=(const char* obj)
        {
            arb_t arb_obj;
            arb_init(arb_obj);
            if (arb_set_str(arb_obj, obj, prec))
            {
                printf("定義時の代入失敗\n");
            }
            arb_mat_one(this->mat);
            arb_mat_scalar_mul_arb(this->mat, this->mat, arb_obj, prec);
            arb_clear(arb_obj);
            return *this;
        }

        // 複合代入
        Matrix operator+=(const Matrix obj)
        {
            *this = *this + obj;
            return *this;
        }
        Matrix operator+=(const int obj)
        {
            *this = *this + obj;
            return *this;
        }
        Matrix operator+=(const slong obj)
        {
            *this = *this + obj;
            return *this;
        }
        Matrix operator+=(const arb_t obj)
        {
            *this = *this + obj;
            return *this;
        }
        Matrix operator+=(const char* obj)
        {
            *this = *this + obj;
            return *this;
        }
        Matrix operator-=(const Matrix obj)
        {
            *this = *this - obj;
            return *this;
        }
        Matrix operator-=(const int obj)
        {
            *this = *this - obj;
            return *this;
        }
        Matrix operator-=(const slong obj)
        {
            *this = *this - obj;
            return *this;
        }
        Matrix operator-=(const arb_t obj)
        {
            *this = *this - obj;
            return *this;
        }
        Matrix operator-=(const char* obj)
        {
            *this = *this - obj;
            return *this;
        }
        Matrix operator*=(const Matrix obj)
        {
            *this = *this * obj;
            return *this;
        }
        Matrix operator*=(const int obj)
        {
            *this = *this * obj;
            return *this;
        }
        Matrix operator*=(const slong obj)
        {
            *this = *this * obj;
            return *this;
        }
        Matrix operator*=(const arb_t obj)
        {
            *this = *this * obj;
            return *this;
        }
        Matrix operator*=(const char* obj)
        {
            *this = *this * obj;
            return *this;
        }
        Matrix operator/=(const Matrix obj)
        {
            *this = *this / obj;
            return *this;
        }
        Matrix operator/=(const int obj)
        {
            *this = *this / obj;
            return *this;
        }
        Matrix operator/=(const slong obj)
        {
            *this = *this / obj;
            return *this;
        }
        Matrix operator/=(const arb_t obj)
        {
            *this = *this / obj;
            return *this;
        }
        Matrix operator/=(const char* obj)
        {
            *this = *this / obj;
            return *this;
        }

        // 累乗 正の整数のみ
        // A^exp
        Matrix pow(ulong exp)
        {
            Matrix res;
            arb_mat_pow_ui(res.mat,this->mat,exp,prec);
            return res;
        }

        // exp(a+ε)=exp(a)*exp(ε)
        Matrix exp(void)
        {
            Matrix res;
            arb_mat_exp(res.mat,this->mat,prec);
            return res;
        }

        // 三角関数(sin,cos)
        // sin(x+ε) = sin(x)*cos(ε) + cos(x)*sin(ε)
        // cos(x+ε) = cos(x)*cos(ε) - sin(x)*sin(ε)
        // tan(x+ε) = sin(x+ε)/cos(x+ε)

        // dualnumber用
        Matrix eps_sin(void)
        {
            Matrix res;
            arb_t  fact,neg,pm;
            arb_init(fact);
            arb_init(neg);
            arb_init(pm);
            arb_set_si(neg,-1);

            // sin A = sum_i=0^\infty \frac{(-1)^i}{(2i+1)!} A^{2i+1}
            // A^{2i+1}はA=εのときi>=1で全て0になる
            for (ulong i = 0; i <= 1; i++) {
                arb_pow_ui(pm,neg,i,prec);
                arb_set_si(fact,factrial(2*i+1));
                arb_div(fact,pm,fact,prec);
                res += fact * this->pow(2 * i + 1);
            }
            arb_clear(fact);
            arb_clear(neg);
            arb_clear(pm);

            return res;
        }

        // dualnumber用
        Matrix eps_cos(void)
        {
            Matrix res;
            arb_t fact, neg, pm;
            arb_init(fact);
            arb_init(neg);
            arb_init(pm);
            arb_set_si(neg, -1);

            // cos A = sum_i=0^\infty \frac{(-1)^i}{(2i)!} A^{2i}
            // A^{2i+1}はA=εのときi>=1で全て0になる
            for (ulong i = 0; i <= 1; i++)
            {
                arb_pow_ui(pm, neg, i, prec);
                arb_set_si(fact, factrial(2 * i));
                arb_div(fact, pm, fact, prec);
                res += fact * this->pow(2 * i);
            }
            arb_clear(fact);
            arb_clear(neg);
            arb_clear(pm);

            return res;
        }

        // sin(x+ε) = sin(x)*cos(ε) + cos(x)*sin(ε)
        Matrix sin(void)
        {
            Matrix res,m_dn;
            arb_ptr mat_0_0,mat_0_1,mat_1_1;
            arb_t  arb_sinx,arb_cosx,dn;
            arb_init(arb_sinx);
            arb_init(arb_cosx);
            arb_init(dn);
            // [0][0]と[1][1]
            mat_0_0 = arb_mat_entry(this->mat, 0, 0);
            mat_1_1 = arb_mat_entry(this->mat, 1, 1);
            mat_0_1 = arb_mat_entry(this->mat, 0, 1);
            if(arb_is_zero(mat_0_0)) {
                res = this->eps_sin();
            } else {
                arb_sin(arb_sinx, mat_0_0, prec);
                arb_cos(arb_cosx, mat_0_0, prec);
                arb_set(dn, mat_0_1);
                m_dn.DualNumber();
                m_dn *= dn;
                // sin(x+ε) = sin(x)*cos(ε) + cos(x)*sin(ε)
                res = arb_sinx * m_dn.eps_cos() + arb_cosx * m_dn.eps_sin();
            }
            arb_clear(arb_sinx);
            arb_clear(arb_cosx);
            arb_clear(dn);
            return res;
        }

        // cos(x+ε) = cos(x)*cos(ε) - sin(x)*sin(ε)
        Matrix cos(void)
        {
            Matrix res, m_dn;
            arb_ptr mat_0_0, mat_0_1, mat_1_1;
            arb_t arb_sinx, arb_cosx, dn;
            arb_init(arb_sinx);
            arb_init(arb_cosx);
            arb_init(dn);
            // [0][0]と[1][1]
            mat_0_0 = arb_mat_entry(this->mat, 0, 0);
            mat_1_1 = arb_mat_entry(this->mat, 1, 1);
            mat_0_1 = arb_mat_entry(this->mat, 0, 1);
            if (arb_is_zero(mat_0_0))
            {
                res = this->eps_cos();
            } else {
                arb_sin(arb_sinx, mat_0_0, prec);
                arb_cos(arb_cosx, mat_0_0, prec);
                arb_set(dn, mat_0_1);
                m_dn.DualNumber();
                m_dn *= dn;
                // cos(x+ε) = cos(x)*cos(ε) - sin(x)*sin(ε)
                res = arb_cosx * m_dn.eps_cos() - arb_sinx * m_dn.eps_sin();
            }
            arb_clear(arb_sinx);
            arb_clear(arb_cosx);
            arb_clear(dn);
            return res;
        }

        // tan(x+ε) = sin(x+ε)/cos(x+ε)
        Matrix tan(void)
        {
            Matrix res, m_dn;
            arb_ptr mat_0_0, mat_0_1, mat_1_1;
            arb_t arb_sinx, arb_cosx, dn;
            arb_init(arb_sinx);
            arb_init(arb_cosx);
            arb_init(dn);
            mat_0_0 = arb_mat_entry(this->mat, 0, 0);
            mat_1_1 = arb_mat_entry(this->mat, 1, 1);
            mat_0_1 = arb_mat_entry(this->mat, 0, 1);
            if (arb_is_zero(mat_0_0))
            {
                res = this->eps_sin()/this->eps_cos();
            } else {
                Matrix sinxe,cosxe;
                arb_sin(arb_sinx, mat_0_0, prec);
                arb_cos(arb_cosx, mat_0_0, prec);
                arb_set(dn, mat_0_1);
                m_dn.DualNumber();
                m_dn *= dn;
                // sin(x+ε) = sin(x)*cos(ε) + cos(x)*sin(ε)
                sinxe = arb_sinx * m_dn.eps_cos() + arb_cosx * m_dn.eps_sin();
                // cos(x+ε) = cos(x)*cos(ε) - sin(x)*sin(ε)
                cosxe = arb_cosx * m_dn.eps_cos() - arb_sinx * m_dn.eps_sin();
                // tan(x+ε) =  sin(x+ε) / cos(x+ε)
                res = sinxe/cosxe;
            }
            arb_clear(arb_sinx);
            arb_clear(arb_cosx);
            arb_clear(dn);
            return res;
        }

        // 対数関数(自然対数)
        // x+ε=x*(1+ε/x)
        // log(x*(1+ε/x))=log(x) + log(1+ε/x)
        // log(x)はdouble型の用意された関数を使って計算してからMatrix{{log(x),0},{0,log(x)}}
        // log(1+ε/x)は
        // log(1+X) := sum_k=1^inf ((-1)^(k-1) * (x^k))/k
        // k>=2の項はε^2=0により0になる
        // log(1+ε/x) = (1/x)*ε
        // まとめると
        // log(x+ε) = log(x) + (1/x)*ε
        Matrix log(void)
        {
            Matrix res;
            arb_t rn,dn,zero,tmp;
            arb_init(rn);
            arb_init(dn);
            arb_init(zero);
            arb_init(tmp);
            arb_zero(zero);
            arb_ptr mat_0_0, mat_0_1, mat_1_1;
            mat_0_0 = arb_mat_entry(this->mat, 0, 0);
            mat_1_1 = arb_mat_entry(this->mat, 1, 1);
            mat_0_1 = arb_mat_entry(this->mat, 0, 1);
            arb_set(rn, mat_0_0);
            arb_set(dn, mat_0_1);

            // rn <= 0
            if(arb_le(rn,zero)) {
                printf("log(x) x>0 を満たしていない。\n");
            }

            arb_log(tmp,rn,prec);
            res = tmp;

            if(arb_is_nonzero(dn))
            {
                Matrix m_dn;
                arb_t neg,pm;
                arb_init(neg);
                arb_init(pm);
                arb_one(neg);
                arb_mul_si(neg,neg,-1,prec);
                arb_div(dn,dn,rn,prec);
                m_dn.DualNumber();
                m_dn *= dn;
                // log(1+ε/x) の 1+ の部分はここで相殺
                // εはi<=2で0になる
                // sun_i=1^\infty pow(-1,i-1)*frac{A^i}{i}
                for(slong i=1; i <= 1; i++) {
                    arb_pow_ui(pm,neg,i-1,prec);
                    arb_div_si(pm,pm,i,prec);
                    res += pm * m_dn.pow(i);
                }
            }
            arb_clear(rn);
            arb_clear(dn);
            arb_clear(zero);
            return res;
        }

        // sqrt(x)=exp(0.5*log(x)) ただし x>0 に注意
        Matrix sqrt()
        {
            Matrix res;
            arb_ptr mat_0_0;
            mat_0_0 = arb_mat_entry(this->mat, 0, 0);
            arb_t x,zero;
            arb_init(x);
            arb_init(zero);
            arb_zero(zero);
            arb_set(x,mat_0_0);
            // x <= 0
            if (arb_le(x, zero))
            {
                printf("log(x) x>0 を満たしていない。\n");
            }

            res = this->log() / 2;
            res = res.exp();
            return res;
        }

        // DualNumber
        void DualNumber()
        {
            arb_ptr mat_0_1;
            mat_0_1 = arb_mat_entry(mat, 0, 1);
            arb_one(mat_0_1);
        }
        // εの係数を取得、微分値f'(x)
        arb_ptr Get_DN()
        {
            return arb_mat_entry(this->mat, 0,1);
        }
        //f(x)を取得
        arb_ptr Get_RN()
        {
            return arb_mat_entry(this->mat, 0, 0);
        }

        // 行列の表示
        void show_mat()
        {
            arb_mat_printd(mat, digit);
        }
};

Matrix pow(Matrix obj,ulong n)
{
    Matrix res;
    res = obj.pow(n);
    return res;
}

Matrix exp(Matrix obj)
{
    Matrix res;
    res = obj.exp();
    return res;
}

Matrix sin(Matrix obj)
{
    Matrix res;
    res = obj.sin();
    return res;
}

Matrix cos(Matrix obj)
{
    Matrix res;
    res = obj.cos();
    return res;
}

Matrix tan(Matrix obj)
{
    Matrix res;
    res = obj.tan();
    return res;
}

Matrix log(Matrix obj)
{
    Matrix res;
    res = obj.log();
    return res;
}

Matrix sqrt(Matrix obj)
{
    Matrix res;
    res = obj.sqrt();
    return res;
}

Matrix DualNumber(void)
{
    Matrix res;
    res.DualNumber();
    return res;
}

void show_mat(Matrix obj)
{
    obj.show_mat();
}

void show_arb(arb_ptr obj)
{
    arb_t fx;
    arb_init(fx);
    arb_set(fx,obj);
    arb_printd(fx, digit); flint_printf("\n");
    arb_clear(fx);
}