// TestVirtual.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
//https://blog.csdn.net/weixin_43734095/article/details/104465307


#ifndef __TEST_OPERATOR_OVERLOAD_H
#define __TEST_OPERATOR_OVERLOAD_H


#include <iostream>


namespace bxd015 {
    using namespace std;
    class Complex {
    public:
		Complex() = default;
		Complex(double r, double i);
		Complex(const Complex & c);
		Complex(const Complex && c);
		Complex& operator= (const Complex & c);

         ~Complex();
    public:
        const Complex operator+(Complex& c);
        const Complex operator-(Complex& c);
        Complex&  operator+=(Complex& c);
        inline ostream& operator << (ostream& os);//能运行不符合常理
    public:
       friend ostream& operator << (ostream& os,const Complex& c);
       friend istream& operator>>(istream& in, Complex& c);
       friend Complex operator+(const Complex& c1, const Complex& c2);
       friend Complex operator-(const Complex& c1, const Complex& c2);
       friend Complex operator*(const Complex& c1, const Complex& c2);
       friend Complex operator/(const Complex& c1, const Complex& c2);


    private:
        double real =0, imag = 0;
    };


    Complex::Complex(double r, double i)
        :real(r),imag(i)  {
        std::cout << "construction " << endl;
    }
    Complex::Complex(const Complex& c) {
 
            this->imag = c.imag;
            this->real = c.real;
            std::cout << "Copy construction " << endl;
    }
    Complex::Complex(const Complex&& c) {
        imag = c.imag;
        real = c.real;
        std::cout << "Move construction " << endl;

    }
    inline Complex& Complex::operator=(const Complex& c)
    {
        std::cout << "= construction " << endl;
        if (this != &c)
        {

            this->real = c.real;
            this->imag = c.imag;
        }
       
        // TODO: 在此处插入 return 语句
        return *this;
    }
    Complex::~Complex(){
        std::cout << "disconstruction " << endl;
    }

    inline const Complex Complex::operator+(Complex& c)
    {
        cout << "operator+" << endl;
        return Complex(real+ c.real,imag+c.imag);

    }

    inline const Complex Complex::operator-(Complex& c)
    {
        cout << "operator-" << endl;
        return Complex(real-c.real,imag-c.imag);
    }

    inline  Complex& Complex::operator+=(Complex& c)
    {
        cout << "ooperator+=" << endl;
        real += c.real;
        imag += c.imag;
        return *this;
    }

    inline ostream& Complex::operator<<(ostream& os)
    {
        // TODO: 在此处插入 return 语句
        os << real << "+" << imag << "i"<<endl; //以"a+bi"的形式输出
        return os;
    }

    ostream& operator << (ostream& os, const Complex& c)
    {
        cout << "friend <<" << endl;
        os << c. real << "+" << c.imag << "i" << endl; //以"a+bi"的形式输出
        return os;
    }

    istream& operator>>(istream& in, Complex& c)
    {
        // TODO: 在此处插入 return 语句

        in >> c.real >> c.imag;
        return in;
    }

    Complex operator+(const Complex& c1, const Complex& c2)
    {
        return Complex(c1.real+c2.real,c2.imag+c1.imag);
    }

    Complex operator-(const Complex& c1, const Complex& c2)
    {
        return Complex(c1.real - c2.real, c1.imag - c2.imag);
    }

    Complex operator*(const Complex& c1, const Complex& c2)
    {
        Complex C(0,0);
        C.real = c1.real * c2.real - c1.imag * c2.imag;
        C.imag = c1.imag * c2.real + c1.real * c2.imag;
        return C;
    }

    Complex operator/(const Complex& c1, const Complex& c2)
    {
        double square = c1.real * c1.real + c1.imag * c1.imag;
        double real = (c1.real * c2.real + c1.imag * c2.imag)/square;
        double imag = (c1.imag * c2.real - c1.real * c2.imag)/square;
        return Complex(real,imag);
    }


    void test_Complex()
    {
        Complex A(5,9);
        Complex B(A);
      ;
       /* Complex C(std::move(A));
         A << (B << (C << cout));

        Complex D = A + B;

        const Complex E = D - B;

        cout << E << B << A << endl;*/

        Complex F(8, 9);
        F += A+=B;
        cout << F<<endl;

        // operator / 构造,拷贝构造
        B = F / A;//
        cout << B << endl;
        
        Complex G = F / A;//返回值优化，一次构造
        cout << G << endl;
        int a = 7; int b = 8;
        int c = 9;
        a += c += b;

    }

}

namespace bxd016 {
    using namespace std;

    class complex {
    public:
        complex(double real = 0.0, double imag = 0.0) : m_real(real), m_imag(imag) { };
    public:
        friend complex operator+(const complex& A, const complex& B);
        friend complex operator-(const complex& A, const complex& B);
        friend complex operator*(const complex& A, const complex& B);
        friend complex operator/(const complex& A, const complex& B);
        friend istream& operator>>(istream& in, complex& A);
        friend ostream& operator<<(ostream& out, complex& A);
    private:
        double m_real;  //实部
        double m_imag;  //虚部
    };

    //重载加法运算符
    complex operator+(const complex& A, const complex& B) {
        complex C;
        C.m_real = A.m_real + B.m_real;
        C.m_imag = A.m_imag + B.m_imag;
        return C;
    }

    //重载减法运算符
    complex operator-(const complex& A, const complex& B) {
        complex C;
        C.m_real = A.m_real - B.m_real;
        C.m_imag = A.m_imag - B.m_imag;
        return C;
    }

    //重载乘法运算符
    complex operator*(const complex& A, const complex& B) {
        complex C;
        C.m_real = A.m_real * B.m_real - A.m_imag * B.m_imag;
        C.m_imag = A.m_imag * B.m_real + A.m_real * B.m_imag;
        return C;
    }

    //重载除法运算符
    complex operator/(const complex& A, const complex& B) {
        complex C;
        double square = A.m_real * A.m_real + A.m_imag * A.m_imag;
        C.m_real = (A.m_real * B.m_real + A.m_imag * B.m_imag) / square;
        C.m_imag = (A.m_imag * B.m_real - A.m_real * B.m_imag) / square;
        return C;
    }

    //重载输入运算符
    istream& operator>>(istream& in, complex& A) {
        in >> A.m_real >> A.m_imag;
        return in;
    }

    //重载输出运算符
    ostream& operator<<(ostream& out, complex& A) {
        out << A.m_real << " + " << A.m_imag << " i ";;
        return out;
    }

    int test_complex() {
        /*2.4 3.6
4.8 1.7
c1 + c2 = 7.2 + 5.3 i
c1 - c2 = -2.4 + 1.9 i
c1 * c2 = 5.4 + 21.36 i
c1 / c2 = 0.942308 + 0.705128 i
*/
        complex c1, c2, c3;
        cin >> c1 >> c2;

        c3 = c1 + c2;
        cout << "c1 + c2 = " << c3 << endl;

        c3 = c1 - c2;
        cout << "c1 - c2 = " << c3 << endl;

        c3 = c1 * c2;
        cout << "c1 * c2 = " << c3 << endl;

        c3 = c1 / c2;
        cout << "c1 / c2 = " << c3 << endl;

        return 0;
    }



}

#endif // !__TEST_VIRTUAL_CLASS_H



