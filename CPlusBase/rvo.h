#ifndef __RVO_H
#define __RVO_H


#include <iostream>

using namespace std;

// Can copy and move
class A {
public:
	A() { cout << "Create A\n"; }
	~A() { cout << "Destroy A\n"; }
	A(const A&) { cout << "Copy A\n"; }
	A(A&&) { cout << "Move A\n"; }
};

A getA_unnamed()
{
	return A();
}

void test_unnamed()
{
	std::cout << __FUNCTION__ << std::endl;
	auto a = getA_unnamed();
}



A getA_named()
{
	A a;
	return a;
}

void test_named()
{
	std::cout << __FUNCTION__ << std::endl;
	auto a = getA_named();
}


#include <stdlib.h>

A getA_duang()
{
	A a1;
	A a2;
	if (rand() > 42) {
		return a1;
	}
	else {
		return a2;
	}
}

void test_duang()
{
	std::cout << __FUNCTION__ << std::endl;
	auto a = getA_duang();
}

//请问有何方法可以测试编译器是否为一个类提供了右值引用的版本的成员函数
class Obj {
public:
	void foo()&&;
	void foo() const&;

};

template <typename T, typename = void_t<>>
struct has_rvalue_ref_foo : false_type {};

template <typename T>
struct has_rvalue_ref_foo<
	T, void_t<decltype(static_cast<void (T::*)()&&>(&T::foo))>>
	: true_type {};

#endif /*__PROTECT_TEST_H*/