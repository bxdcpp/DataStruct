#ifndef __HJJ_C11_H
#define __HJJ_C11_H
// test_variadic_templates.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <bitset>

#define SIZE 100



//----------------------------------------------------
#include <iostream>
#include <cstdio>  //snprintf()
#include <cstdlib> //RAND_MAX
#include <cstring> //strlen(), memcpy()
#include <string> 
using std::cin;
using std::cout;
using std::string;

//以下 MyString 是為了測試 containers with moveable elements 效果.  
class MyString {
public:
    static size_t DCtor;  	//累計 default-ctor 的呼叫次數 
    static size_t Ctor;  	//累計 ctor      的呼叫次數 
    static size_t CCtor;  	//累計 copy-ctor 的呼叫次數 
    static size_t CAsgn;  	//累計 copy-asgn 的呼叫次數 
    static size_t MCtor;  	//累計 move-ctor 的呼叫次數 
    static size_t MAsgn;  	//累計 move-asgn 的呼叫次數 		    
    static size_t Dtor;	//累計 dtor 的呼叫次數 
private:
    char* _data;
    size_t _len;
    void _init_data(const char* s) {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }
public:
    //default ctor
    MyString() : _data(NULL), _len(0) { ++DCtor; }

    //ctor
    MyString(const char* p) : _len(strlen(p)) {
        ++Ctor;
        _init_data(p);
    }

    // copy ctor
    MyString(const MyString& str) : _len(str._len) {
        ++CCtor;
        _init_data(str._data); 	//COPY
    }

    //move ctor, with "noexcept"
    MyString(MyString&& str) noexcept : _data(str._data), _len(str._len) {
        ++MCtor;
        str._len = 0;
        str._data = NULL;  	//避免 delete (in dtor) 
    }

    //copy assignment
    MyString& operator=(const MyString& str) {
        ++CAsgn;
        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _init_data(str._data); 	//COPY! 
        }
        else {
            // Self Assignment, Nothing to do.   
        }
        return *this;
    }

    //move assignment
    MyString& operator=(MyString&& str) noexcept {
        ++MAsgn;
        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _data = str._data;	//MOVE!
            str._len = 0;
            str._data = NULL; 	//避免 deleted in dtor 
        }
        return *this;
    }

    //dtor
    virtual ~MyString() {
        ++Dtor;
        if (_data) {
            delete _data;
        }
    }

    bool
        operator<(const MyString& rhs) const	//為了讓 set 比較大小  
    {
        return std::string(this->_data) < std::string(rhs._data); 	//借用事實：string 已能比較大小. 
    }
    bool
        operator==(const MyString& rhs) const	//為了讓 set 判斷相等. 
    {
        return std::string(this->_data) == std::string(rhs._data); 	//借用事實：string 已能判斷相等. 
    }

    char* get() const { return _data; }
};
size_t MyString::DCtor = 0;
size_t MyString::Ctor = 0;
size_t MyString::CCtor = 0;
size_t MyString::CAsgn = 0;
size_t MyString::MCtor = 0;
size_t MyString::MAsgn = 0;
size_t MyString::Dtor = 0;

namespace std 	//必須放在 std 內 
{
    template<>
    struct hash<MyString> 	//這是為了 unordered containers 
    {
        size_t
            operator()(const MyString& s) const noexcept
        {
            return hash<string>()(string(s.get()));
        }
        //借用現有的 hash<string> (in ...\include\c++\bits\basic_string.h)
    };
}
//-----------------
//以下 MyStrNoMove 是為了測試 containers with no-moveable elements 效果.  
class MyStrNoMove {
public:
    static size_t DCtor;  	//累計 default-ctor 的呼叫次數 
    static size_t Ctor;  	//累計 ctor      的呼叫次數 
    static size_t CCtor;  	//累計 copy-ctor 的呼叫次數 
    static size_t CAsgn;  	//累計 copy-asgn 的呼叫次數 
    static size_t MCtor;  	//累計 move-ctor 的呼叫次數 
    static size_t MAsgn;  	//累計 move-asgn 的呼叫次數 		    
    static size_t Dtor;	    //累計 dtor 的呼叫次數 
private:
    char* _data;
    size_t _len;
    void _init_data(const char* s) {
        _data = new char[_len + 1];
        memcpy(_data, s, _len);
        _data[_len] = '\0';
    }
public:
    //default ctor
    MyStrNoMove() : _data(NULL), _len(0) { ++DCtor; _init_data("jjhou"); }

    //ctor
    MyStrNoMove(const char* p) : _len(strlen(p)) {
        ++Ctor;  _init_data(p);
    }

    // copy ctor
    MyStrNoMove(const MyStrNoMove& str) : _len(str._len) {
        ++CCtor;
        _init_data(str._data); 	//COPY
    }

    //copy assignment
    MyStrNoMove& operator=(const MyStrNoMove& str) {
        ++CAsgn;

        if (this != &str) {
            if (_data) delete _data;
            _len = str._len;
            _init_data(str._data); 	//COPY! 
        }
        else {
            // Self Assignment, Nothing to do.   
        }
        return *this;
    }

    //dtor
    virtual ~MyStrNoMove() {
        ++Dtor;
        if (_data) {
            delete _data;
        }
    }

    bool
        operator<(const MyStrNoMove& rhs) const		//為了讓 set 比較大小 
    {
        return string(this->_data) < string(rhs._data);  //借用事實：string 已能比較大小. 
    }

    bool
        operator==(const MyStrNoMove& rhs) const	//為了讓 set 判斷相等. 
    {
        return string(this->_data) == string(rhs._data);  //借用事實：string 已能判斷相等. 
    }

    char* get() const { return _data; }
};
size_t MyStrNoMove::DCtor = 0;
size_t MyStrNoMove::Ctor = 0;
size_t MyStrNoMove::CCtor = 0;
size_t MyStrNoMove::CAsgn = 0;
size_t MyStrNoMove::MCtor = 0;
size_t MyStrNoMove::MAsgn = 0;
size_t MyStrNoMove::Dtor = 0;

namespace std 	//必須放在 std 內 
{
    template<>
    struct hash<MyStrNoMove> 	//這是為了 unordered containers 
    {
        size_t
            operator()(const MyStrNoMove& s) const noexcept
        {
            return hash<string>()(string(s.get()));
        }
        //借用現有的 hash<string> (in ...\4.9.2\include\c++\bits\basic_string.h)
    };
}

//----------------------------------------------------

#include <typeinfo>  //typeid()
template<typename T>
void output_static_data(const T& myStr)
{
    cout << typeid(myStr).name() << " -- " << std::endl;
    cout << " CCtor=" << T::CCtor
        << " MCtor=" << T::MCtor
        << " CAsgn=" << T::CAsgn
        << " MAsgn=" << T::MAsgn
        << " Dtor=" << T::Dtor
        << " Ctor=" << T::Ctor
        << " DCtor=" << T::DCtor
        << std::endl;
}


void print()
{

}

template<typename T, typename... Types>
void print(const T& firstArg, const Types&... args)
{
    sizeof...(args);
    std::cout << firstArg << std::endl;
    print(args...);
}

void myprintf(const char* s)
{
    while (*s)
    {
        if (*s == '%' && *(++s) != '%')
            throw "invalid format string: missing arguments";
        std::cout << *s++;
    }
}

template<typename T, typename... Args>
void myprintf(const char* s, T value, Args... args)
{
    while (*s)
    {
        if (*s == '%' && *(++s) != '%')
        {
            std::cout << value;
            myprintf(++s, args...); // call even when *s == 0 to detect extra arguments
            return;
        }
        std::cout << *s++;
    }
    throw "extra arguments provided to printf";
}




#include<vector>
#include<list>
#include<deque>

template<typename T>
using Vec = std::vector<T, std::allocator<T>>;


template<typename T>
using Lst = std::list < T, std::allocator<T>>;


template<typename T>
using Deq = std::deque < T, std::allocator<T>>;

template<typename T, template<class> class Container>
class XCls
{
public:
    XCls() {
        for (int i = 0; i < SIZE; i++) {
            c.insert(c.end(), T());


            output_static_data(T());
            Container<T> c1(c);
            Container<T> c2(std::move(c));
            
            c1.swap(c2);
        }
    }
    ~XCls() {};

private:
    Container<T> c;

};


namespace hjj001 {

    template<typename... Values>
    class tuple;

    template<> 
    class tuple<> {};

    template<typename Head,typename... Tail>
    class tuple<Head, Tail...> :private tuple<Tail...>
    {
        typedef tuple<Tail...> inherited;
    public:
        tuple() {};
        tuple(Head v, Tail... vtail):m_head(v),inherited(vtail...){}

        typename Head head() { return m_head; }
        inherited& tail() { return *this; }
    protected:
        Head m_head;
    };

    void test_tuple() {
        std::cout << "---------test_variadic templates------------------" << std::endl;
        tuple<int, float, std::string> t(41, 6.3, "nice");
        std::cout << "head:" << t.head()<<"\n"
            //<< "tail" << t.tail()
            << "tail().head():" << t.tail().head()<<"\n"
            << "&tail:" << &(t.tail()) << std::endl;

    }


}


namespace hjj002 {

    class P 
    {
    public:
        P(int a, int b)
        {
            std::cout << "p(int,int),a=" << a << ",b=" << b << std::endl;
        }
        P(std::initializer_list<int> initList)
        {
            std::cout << "p(initializer_list<int>, values=";
            for (auto i : initList)
                cout << i << ' ';
            cout << std::endl;
        }
    };

    //-----------------------------------initializer_list----------------------------
    void myCout(std::initializer_list<int> vals) {
        for (auto p = vals.begin(); p != vals.end(); p++)
            std::cout << *p << "\n";
    }


    void test_initializer_list()
    {
        P p( 77,5 );//P(int,int) a=77, b =5
        P q{ 77,5 };//P(std::initializer_list<int>), values = 77 5
        P r{ 77,55,42 };//P(std::initializer_list<int>), values = 77 55 42
        P s = { 77,5 };//P(std::initializer_list<int>), values = 77 5
    }

    void test_initializer_lists()
    {
		int i;//i has undefined value
		int j{};//j is initialized by 0
		int* p;//p has undefine value
		//cout << i << " " << j << " " << p << ' ' << std::endl;

		int x1(5.3);
		int x2 = 5.3;
		//!int x3{ 5.0 };//从 "double" 到 "int" 进行收缩转换无效
		//!int x4 = { 5.3 };//从 "double" 到 "int" 进行收缩转换无效

		char c1{ 7 };
		//!char c2{ 99999 };//从 "int" 到 "char" 进行收缩转换无效
		cout << x1 << " " << x2 << " " /*<< x3 << ' '<< x4 */<< c1 << " " /* << c2*/ << std::endl;

        std::vector<int> v1{ 1,2,3,4,5 };
        //!std::vector<int> v2{ 1,2.3,4,5.6 };//从 "double" 到 "int" 进行收缩转换无效


      /*  for (auto& elem : v2) {
            cout << elem << " ";
        }
        cout << std::endl;*/
    }
    
#define keyword
//#define keyword explicit
    struct Complex
    {
        int real, imag;
        keyword Complex(int re,int im=0):real(re),imag(im)
        {}
        Complex operator+(const Complex& x)
        {
            return Complex((real + x.real), imag + x.imag);
        }
    };

    void test_explicit()
    {

        Complex c1(12, 5);
        //if keyword is explicit 
        //error c2679 二元“ + ”: 没有找到接受“int”类型的右操作数的运算符(或没有可接受的转换)
        Complex c2 = c1 + 5;
    }
}


namespace hjj003 {

    class Zoo
    {
    public:
        Zoo(int i1, int i2) :d1(i1), d2(i2) {};
        Zoo(const Zoo&) = delete;
        Zoo(Zoo&&) = default;
        Zoo& operator=(const Zoo&) = default;
        Zoo& operator=(const Zoo&&) = delete;
        virtual ~Zoo() {};
        void address() { std::cout << "Beijing..." << std::endl; }
        virtual void printSelf() { std::cout << "Zoo" << std::endl; }
        virtual void test() = 0;

    
    private:
        int d1, d2;

    };

    class City :public Zoo
    {
    public:
        City(int x, int y) :Zoo(x, y) {}
        //override函数 名称前可以写virtual或者不写 overrid 关键字可以写也可以不写，良好的编程习惯要写
        //1
        //void printSelf() override { std::cout << "city" << std::endl; };
        //2
        //void printSelf()  { std::cout << "city" << std::endl; };
        //3
        //virtual void printSelf() { std::cout << "city" << std::endl; };
        //4
        void printSelf() { std::cout << "city" << std::endl; };

        virtual void test() override { std::cout << "test..." << std::endl; }
        //void test() override { std::cout << "test..." << std::endl; }
        //同名覆盖
        void address() { std::cout << "Shanghai..." << std::endl; }
    };

    void test_11_inherited()
    {
        City c(10, 5);
        c.printSelf();
        c.address();
    }

    struct Base1 final
    {
    };

    //error C3246“hjj003::Derived1”: 无法从"hjj003::Base1"继承，因为它已被声明为"final"
 /*   struct Derived1:Base1
    {
    };*/


}


void hjj_c11_test()
{

    std::cout << __cplusplus << std::endl;
    std::cout << __FUNCTION__ << "start_test............." << std::endl;
    print(7.5, "helllo", std::bitset<16>(377), 42);

    int* pi = new int;
    myprintf("%d %s %p %f\n", 15, "This is Ace", pi, 3.1415926);
 

    XCls<MyString, Vec>c1;

    hjj001::test_tuple();
    hjj002::test_initializer_list();
    hjj003::test_11_inherited();
}




#endif /*__PROTECT_TEST_H*/