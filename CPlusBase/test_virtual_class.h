// TestVirtual.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//

#include <iostream>


namespace bxd001
{
    //ֻ�г�Ա����
    class Base1
    {
    public:
        int base1_1;
        int base1_2;
    };
}

namespace bxd002
{
    //�г�Ա�����ͳ�Ա����û���麯��
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
    //1���麯������
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
    //������麯������
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
    //���̳��ұ��������麯���ļ̳�����ڴ沼��
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
    //���������麯��(���Ͻ�)�����ڻ����麯�����ǵĵ��̳�����ڴ沼��
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

        // ��д���ຯ��
        void base1_fun1() override {}
    };
}

namespace bxd007
{
    //�����˻���û�е��麯���ĵ��̳е�����󲼾�
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
    //��̳��Ҵ����麯������ͬʱ�ִ�����������麯��������󲼾�
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

    // ��̳�
    class Derive1 : public Base1, public Base2
    {
    public:
        int derive1_1;
        int derive1_2;

        // �����麯������
        virtual void base1_fun1() {}
        virtual void base2_fun2() {}

        // ��������麯��
        virtual void derive1_fun1() {}
        virtual void derive1_fun2() {}
    };
}


namespace bxd009
{
    //�����1��ֱ�ӻ���û���麯��(��)
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

    // ��̳�
    class Derive1 : public Base1, public Base2
    {
    public:
        int derive1_1;
        int derive1_2;

        // ��������麯��
        virtual void derive1_fun1() {}
        virtual void derive1_fun2() {}
    };

    void test_mem()
    {

    }
}


namespace bxd010
{
    //if �������඼û���麯����
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

    // ��̳�
    class Derive1 : public Base1, public Base2
    {
    public:
        int derive1_1;
        int derive1_2;

        // ��������麯��
        virtual void derive1_fun1() {}
        virtual void derive1_fun2() {}
    };
}


namespace bxd011
{
    //�������������: �麯����ֱ�����, û��, ��!
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

    // ��̳�
    class Derive1 : public Base1, public Base2, public Base3
    {
    public:
        int derive1_1;
        int derive1_2;

        // ��������麯��
        virtual void derive1_fun1() {}
        virtual void derive1_fun2() {}
    };

    void test_memory_layout()
    {

        {
            //Ҫ��֪��C++������ڴ沼��, �����ж��ַ�ʽ, ����:
            //�����Ա������ƫ��, ͨ��offsetof�����õ�
            //ͨ���������鿴, ���糣�õ�VS
            using namespace bxd001;

            std::cout << "Base1 size:" << sizeof(Base1) << std::endl;
            std::cout << "base1_1:" << offsetof(Base1, base1_1) << std::endl;
            std::cout << "base1_2:" << offsetof(Base1, base1_2) << std::endl;
        }

        {
            //����:
            //1.�麯����
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



