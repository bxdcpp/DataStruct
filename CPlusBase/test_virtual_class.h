// TestVirtual.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#ifndef __TEST_VIRTUAL_CLASS_H
#define __TEST_VIRTUAL_CLASS_H






#include <iostream>

//bxd001-bxd011虚函数内存布局测试
namespace bxd001
{
    //只有成员变量
    class Base1
    {
    public:
        int base1_1;
        int base1_2;
    };
}

namespace bxd002
{
    //有成员变量和成员函数没有虚函数
    class Base1
    {
    public:
        int base1_1;
        int base1_2;

        void foo() {}
    };
}


namespace bxd003
{
    //1个虚函数的类
    class Base1
    {
    public:
        int base1_1;
        int base1_2;

        virtual void base1_fun1() {}
    };
}

namespace bxd004
{
    //多个个虚函数的类
    class Base1
    {
    public:
        int base1_1;
        int base1_2;

        virtual void base1_fun1() {}
        virtual void base1_fun2() {}
        virtual void base1_fun3() {}
    };
}


namespace bxd005 {
    //单继承且本身不存在虚函数的继承类的内存布局
    class Base1
    {
    public:
        int base1_1;
        int base1_2;

        virtual void base1_fun1() {}
        virtual void base1_fun2() {}
    };

    class Derive1 : public Base1
    {
    public:
        int derive1_1;
        int derive1_2;
    };

}



namespace bxd006
{
    //本身不存在虚函数(不严谨)但存在基类虚函数覆盖的单继承类的内存布局
    class Base1
    {
    public:
        int base1_1;
        int base1_2;

        virtual void base1_fun1() {}
        virtual void base1_fun2() {}
    };

    class Derive1 : public Base1
    {
    public:
        int derive1_1;
        int derive1_2;

        // 重写基类函数
        void base1_fun1() override {}
    };
}

namespace bxd007
{
    //定义了基类没有的虚函数的单继承的类对象布局
    class Base1
    {
    public:
        int base1_1;
        int base1_2;

        virtual void base1_fun1() {}
        virtual void base1_fun2() {}
    };

    class Derive1 : public Base1
    {
    public:
        int derive1_1;
        int derive1_2;

        virtual void derive1_fun1() {}
    };
}


namespace bxd008
{
    //多继承且存在虚函数覆盖同时又存在自身定义的虚函数的类对象布局
    class Base1
    {
    public:
        int base1_1;
        int base1_2;

        virtual void base1_fun1() {}
        virtual void base1_fun2() {}
    };

    class Base2
    {
    public:
        int base2_1;
        int base2_2;

        virtual void base2_fun1() {}
        virtual void base2_fun2() {}
    };

    // 多继承
    class Derive1 : public Base1, public Base2
    {
    public:
        int derive1_1;
        int derive1_2;

        // 基类虚函数覆盖
        virtual void base1_fun1() {}
        virtual void base2_fun2() {}

        // 自身定义的虚函数
        virtual void derive1_fun1() {}
        virtual void derive1_fun2() {}
    };
}


namespace bxd009
{
    //如果第1个直接基类没有虚函数(表)
    class Base1
    {
    public:
        int base1_1;
        int base1_2;
    };

    class Base2
    {
    public:
        int base2_1;
        int base2_2;

        virtual void base2_fun1() {}
        virtual void base2_fun2() {}
    };

    // 多继承
    class Derive1 : public Base1, public Base2
    {
    public:
        int derive1_1;
        int derive1_2;

        // 自身定义的虚函数
        virtual void derive1_fun1() {}
        virtual void derive1_fun2() {}
    };

    void test_mem()
    {

    }
}


namespace bxd010
{
    //if 两个基类都没有虚函数表
    class Base1
    {
    public:
        int base1_1;
        int base1_2;
    };

    class Base2
    {
    public:
        int base2_1;
        int base2_2;
    };

    // 多继承
    class Derive1 : public Base1, public Base2
    {
    public:
        int derive1_1;
        int derive1_2;

        // 自身定义的虚函数
        virtual void derive1_fun1() {}
        virtual void derive1_fun2() {}
    };
}


namespace bxd011
{
    //如果有三个基类: 虚函数表分别是有, 没有, 有!
    class Base1
    {
    public:
        int base1_1;
        int base1_2;

        virtual void base1_fun1() {}
        virtual void base1_fun2() {}
    };

    class Base2
    {
    public:
        int base2_1;
        int base2_2;
    };

    class Base3
    {
    public:
        int base3_1;
        int base3_2;

        virtual void base3_fun1() {}
        virtual void base3_fun2() {}
    };

    // 多继承
    class Derive1 : public Base1, public Base2, public Base3
    {
    public:
        int derive1_1;
        int derive1_2;

        // 自身定义的虚函数
        virtual void derive1_fun1() {}
        virtual void derive1_fun2() {}
    };

   
}

void test_memory_layout(int caseNumber)
{
    switch (caseNumber)
    {
    case 1:
    {
          //要想知道C++对象的内存布局, 可以有多种方式, 比如:
          //输出成员变量的偏移, 通过offsetof宏来得到
          //通过调试器查看, 比如常用的VS
          using namespace bxd001;

          std::cout << "Base1 size:" << sizeof(Base1) << std::endl;
          std::cout << "base1_1:" << offsetof(Base1, base1_1) << std::endl;
          std::cout << "base1_2:" << offsetof(Base1, base1_2) << std::endl;
    }
	break;
	case 2:
	{
		//结论:
		//1.虚函数表
		using namespace bxd002;
		Base1 b1;
		std::cout << "Base1 size:" << sizeof(Base1) << std::endl;
		std::cout << "base1_1:" << offsetof(Base1, base1_1) << std::endl;
		std::cout << "base1_2:" << offsetof(Base1, base1_2) << std::endl;

	}
	break;
	case 8:

	{
		using namespace bxd008;
		Derive1 d1;
		Derive1* pd1 = &d1;
		pd1->derive1_fun1();
	}
	break;
	case 3:

	{
		using namespace bxd003;
        Base1 b1;
        std::cout << "Base1 size:" << sizeof(Base1) << std::endl;
        std::cout << "base1_1:" << offsetof(Base1, base1_1) << std::endl;
        std::cout << "base1_2:" << offsetof(Base1, base1_2) << std::endl;

	}
	break;

	case 4:
	{
		using namespace bxd004;
	}
	break;
	case 5:
	{
		using namespace bxd005;
	}
	break;

	default:
		break;
	}
    std::cout << "Hello World!\n";
}


//类成员大小测试
namespace bxd012 {

    //# pragma pack(16)
    struct A {
        char a;
        double b;
        short c;
    };

    struct B {
        char a;
        short c;
        double b;
    };

    class C {
    private:
        char a;
        double b;
        short c;
    };

    class D {
    private:
        char a;
        short c;
        double b;
    };

    void test_size()
    {
        std::cout << "test_size........................"  << std::endl;
        std::cout << "A struct size:" << sizeof(A) << std::endl;
        std::cout << "B struct size:" << sizeof(B) << std::endl;
        std::cout << "C claas size:" << sizeof(C) << std::endl;
        std::cout << "D class size:" << sizeof(D) << std::endl;
    }
}

/***砖石类二义性问题https://www.cnblogs.com/duwenxing/p/7492247.html
* 
* 假设我们已经有了两个类Father1和Father2，他们都是类GrandFather的子类。
*现在又有一个新类Son，这个新类通过多继承机制对类Father1和Father2都进行了继承，
*此时类GrandFather、Father1、Father2和Son的继承关系是一个菱形，
*仿佛一个钻石，因此这种继承关系在C++中通常被称为钻石继承（或菱形继承）。
* 
* 
* 
* 
* 
* 
* 在C++中通常利用虚基类和虚继承来解决钻石继承中的“数据不一致”问题
* 1.什么是虚继承和虚基类

• 虚继承：在继承定义中包含了virtual关键字的继承关系

• 虚基类：在虚继承体系中通过关键字virtual继承而来的基类

2.为什么使用虚基类和虚继承

• 使用虚基类和虚继承可以让一个指定的基类在继承体系中将其成员数据实例共享给从该基类直接或间接派生出的其它类，
*即使从不同路径继承来的同名数据成员在内存中只有一个拷贝，同一个函数名也只有一个映射(只实例化一次)
* 
* 
* 
* 
* 
* 
* */
namespace bxd013 {

    using namespace std;
    class GrandFather { //第一层基类GrandFather
    public:
        GrandFather() = default;
        GrandFather(int v) :value(v) {
            cout << "调用了GrandFather类的构造函数" << endl;
        }
        int value;
    };

    class Father1 :public GrandFather { //第二层基类Father1
    public:
        Father1() = default;
        Father1(int v) :GrandFather(v) {
            cout << "调用Father1类的构造函数" << endl;
        }
        void set_value(int value) { //设置value的值
            this->value = value;
        }
    };

    class Father2 :public GrandFather { //第二层基类Father2
    public:
        Father2() = default;
        Father2(int v) :GrandFather(v) {
            cout << "调用Father2类的构造函数" << endl;
        }
        int get_value() { //获取value的值
            return this->value;
        }
    };

    class Son :public Father1, public Father2 { //第三次层类Son
    public:
        Son() = default;
        Son(int v) :Father1(v), Father2(v) {
            cout << "调用Son类的构造函数" << endl;
        }
    };

     void test_inherit() {
         //Father1 中有set_value
         //Father2 中有get_value
        Son s(10);
        s.set_value(20);
        cout << s.get_value() << endl;//10
        //S在内存中会有Father1和Father2 2个类对象
        //Father1和Father2中会有各自的GrandFather类对象
        cout << "Father1类创建的子对象的value值：" << s.Father1::value << endl;
        cout << "Father2类创建的子对象的value值：" << s.Father2::value << endl;
    }
}

namespace bxd014 {

    using namespace std;
    class GrandFather { //第一层基类GrandFather
    public:
        GrandFather() = default;
        GrandFather(int v) :value(v) {
            cout << "调用了GrandFather类的构造函数" << endl;
        }
        int value;
    };

    class Father1 : virtual public GrandFather { //第二层基类Father1,虚继承基类GrandFather
    public:
        Father1() = default;
        Father1(int v) :GrandFather(v) {
            cout << "调用Father1类的构造函数" << endl;
        }
        void set_value(int value) { //设置value的值
            this->value = value;
        }
    };

    class Father2 : virtual public GrandFather { //第二层基类Father2，虚继承基类GrandFather
    public:
        Father2() = default;
        Father2(int v) :GrandFather(v) {
            cout << "调用Father2类的构造函数" << endl;
        }
        int get_value() { //获取value的值
            return this->value;
        }
    };

    class Son :virtual public Father1, virtual public Father2 { //第三次子类Son
    public:
        Son() = default;
        Son(int v) :Father1(v), Father2(v), GrandFather(v) {
            cout << "调用Son类的构造函数" << endl;
        }
    };

    void test_inherit() {
        //Warining, 不能间接虚继承 Father1和Father2必须虚继承Grandfather
        Son s(10);
        s.set_value(20);
        cout << s.get_value() << endl;
    }


    class One {
    public:
        int one;
        One(int o) :one(o) {
            cout << "调用类One的构造函数" << endl;
        }
    };

    class Two {
    public:
        int two;
        Two(int t) :two(t) {
            cout << "调用类Two的构造函数" << endl;
        }
    };

    class Three {
    public:
        int three;
        Three(int t) :three(t) {
            cout << "调用类Three的构造函数" << endl;
        }
    };

    class Four {
    public:
        Four() {
            cout << "调用类Four的构造函数" << endl;
        }
    };

    class Five {
    public:
        int five;
        Five(int f) :five(f) {
            cout << "调用类Five的构造函数" << endl;
        }
    };

    class Six :public One, virtual Two, virtual Three, public Five {
    public:
        Six(int value) :One(value), Two(value), Three(value), Five(value) { //在派生类的构造函数的成员初始化列表中必须列出对虚基类构造函数的调用
            cout << "调用类Six的构造函数" << endl;
        }
    private:
        Four four;
    };

    void test_inherit2() {
        /*
           3.构造函数的调用顺序

            • 首先按照虚基类的声明顺序调用虚基类的构造函数

            • 然后按照非虚基类的声明顺序调用非虚基类的构造函数

            • 之后调用派生类中成员对象的构造函数

            • 最后调用派生类自己的构造函数
        */
        Six six(10);
    }

    class Waiter
    {
    public:
        void work() { std::cout << "Service" << std::endl; }
    };
    class Singer
    {
    public:
        void work() { std::cout << "Sing" << std::endl; }
    };
    class SingerWaiter :public Waiter, public Singer
    {};
    int test_inherits3()
    {
        SingerWaiter singerWaiter;
       // singerWaiter.work();
        return 0;
    }


}

#endif // !__TEST_VIRTUAL_CLASS_H



