#ifndef FRACTION_H_INCLUDED
#define FRACTION_H_INCLUDED

// issue:
// 各運算子不具優先順序

class Frac {
private:
    int num;  // 分子
    int den;  // 分母

public:
    Frac();
    Frac(const Frac &x);
    Frac(int a, int b);
    void set(int a, int b);

    Frac& operator=(const Frac &x);
    Frac& operator=(double x);

    Frac operator*(Frac &x);
    Frac operator/(Frac &x);
    Frac operator+(Frac &x);
    Frac operator-(Frac &x);

    Frac& operator*=(Frac &x);
    Frac& operator/=(Frac &x);
    Frac& operator+=(Frac &x);
    Frac& operator-=(Frac &x);

    bool operator==(Frac &x);
    bool operator!=(Frac &x);

    void display();

private:
    void reduction();

    int gcd  (int a, int b);
    int gcd_r(int a, int b);
    int lcm  (int a, int b);
    int lcm_r(int a, int b);
};

Frac::Frac() {
    num = den = int();
}

Frac::Frac(const Frac &x) {
    num = x.num;
    den = x.den;
}

Frac::Frac(int a, int b) {
    set(a, b);
}

void Frac::set(int a, int b) {
    if ( b==0 )
       { cout << "error" << endl;
         return;
       }

    num = a;
    den = b;

    reduction();
}

Frac& Frac::operator=(const Frac &x) {
    num = x.num;
    den = x.den;
    return *this;
}

Frac& Frac::operator=(double x) {
    den = 1;

    for ( ; true ; )
        { int    xi = (int)   x;
          double xd = (double)xi;

          if ( xd==x )
             { num = xi;
               break;
             }
          x   *= 10;
          den *= 10;
        }

    reduction();
    return *this;
}

Frac Frac::operator*(Frac &x) {
    Frac ans(num*x.num, den*x.den);
    return ans;
}

Frac Frac::operator/(Frac &x) {
    if ( x.num==0 )
       { cout << "error" << endl;
         return Frac();
       }

    Frac ans(num*x.den, den*x.num);
    return ans;
}

Frac Frac::operator+(Frac &x) {
    int t = lcm(den, x.den);

    Frac ans(num*t/den + x.num*t/x.den, t);
    return ans;
}

Frac Frac::operator-(Frac &x) {
    int t = lcm(den, x.den);

    Frac ans(num*t/den - x.num*t/x.den, t);
    return ans;
}

Frac& Frac::operator*=(Frac &x) {
    *this = *this * x;
    return *this;
}

Frac& Frac::operator/=(Frac &x) {
    *this = *this / x;
    return *this;
}

Frac& Frac::operator+=(Frac &x) {
    *this = *this + x;
    return *this;
}

Frac& Frac::operator-=(Frac &x) {
    *this = *this - x;
    return *this;
}

bool Frac::operator==(Frac &x) {
    if ( num==x.num )
    if ( den==x.den )
        return true;

    return false;
}

bool Frac::operator!=(Frac &x) {
    return !( *this==x );
}

void Frac::display() {
          cout << num;
    if ( den!=1 ) cout << "/" << den;
}

void Frac::reduction() {
    if ( den<0 )
       { num *= -1;
         den *= -1;
       }

    int t = gcd(num, den);
    if ( t!=0 )
       { num /= t;
         den /= t;
       }
}

int Frac::gcd(int a, int b) {
    if ( a<0 )  a *= -1;
    if ( b<0 )  b *= -1;
    return gcd_r(a, b);
}

int Frac::gcd_r(int a, int b) {
    if ( a==0 )
       { return b;
       }
    return gcd_r(b%a, a);
}

int Frac::lcm(int a, int b) {
    if ( a<0 )  a *= -1;
    if ( b<0 )  b *= -1;
    return lcm_r(a, b);
}

int Frac::lcm_r(int a, int b) {
    return a * b / gcd(a, b);
}

#endif // FRACTION_H_INCLUDED
