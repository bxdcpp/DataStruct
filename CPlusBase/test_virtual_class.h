// TestVirtual.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>


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

    void test_memory_layout()
    {

        {
            //要想知道C++对象的内存布局, 可以有多种方式, 比如:
            //输出成员变量的偏移, 通过offsetof宏来得到
            //通过调试器查看, 比如常用的VS
            using namespace bxd001;

            std::cout << "Base1 size:" << sizeof(Base1) << std::endl;
            std::cout << "base1_1:" << offsetof(Base1, base1_1) << std::endl;
            std::cout << "base1_2:" << offsetof(Base1, base1_2) << std::endl;
        }

        {
            //结论:
            //1.虚函数表
            using namespace bxd002;
            Base1 b1;
            std::cout << "Base1 size:" << sizeof(Base1) << std::endl;
            std::cout << "base1_1:" << offsetof(Base1, base1_1) << std::endl;
            std::cout << "base1_2:" << offsetof(Base1, base1_2) << std::endl;

        }


        {
            using namespace bxd003;
        }


        {
            using namespace bxd004;
        }

        {
            using namespace bxd005;
        }



        std::cout << "Hello World!\n";
    }
}



