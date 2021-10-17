#include <random>
#include <iostream>
#include <memory>
#include <functional>

using namespace std;


namespace bxd001 {


	void f(int n1, int n2, int n3, const int& n4, int n5)
	{
		std::cout << n1 << ' ' << n2 << ' ' << n3 << ' ' << n4 << ' ' << n5 << '\n';
	}

	int g(int n1)
	{
		return n1;
	}

	struct Foo {
		void print_sum(int n1, int n2)
		{
			std::cout << n1 + n2 << '\n';
		}
		int data = 10;
	};

	void test_bind()
	{
		cout << "starting test bind()...." << endl;
		using namespace std::placeholders;  // 对于 _1, _2, _3...

		// 演示参数重排序和按引用传递
		int n = 7;
		// （ _1 与 _2 来自 std::placeholders ，并表示将来会传递给 f1 的参数）
		// std::ref 转ref std::cref 转const ref
		auto f1 = std::bind(f, _2, 42, _1, std::cref(n), n);
		n = 10;
		f1(1, 2, 1001); // 1 为 _1 所绑定， 2 为 _2 所绑定，不使用 1001
						// 进行到 f(2, 42, 1, n, 7) 的调用

		// 嵌套 bind 子表达式共享占位符
		auto f2 = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);
		f2(10, 11, 12); // 进行到 f(12, g(12), 12, 4, 5); 的调用

		//std::bind 返回类型
		using bind_type = std::_Binder<std::_Unforced, void(__cdecl&)(int, int, int, int const&, int), std::_Ph<3> const&, std::_Binder<std::_Unforced, int(__cdecl&)(int), std::_Ph<3> const&>, std::_Ph<3> const&, int, int>;
		bind_type fx  = std::bind(f, _3, std::bind(g, _3), _3, 4, 5);

		//auto s = 8.00;
		//decltype(n)

		//std::cout << decltype(n) << endl;

		// 常见使用情况：以分布绑定 RNG
		std::default_random_engine e;//创建随机数引擎
		std::uniform_int_distribution<> d(0, 10);//创建取值范围
		//d(e) 会返回一个随机数
		std::function<int()> rnd = std::bind(d, e); // e 的一个副本存储于 rnd
		for (int n = 0; n < 10; ++n)
			std::cout << rnd() << ' ';
		std::cout << '\n';

		// 绑定指向成员函数指针
		Foo foo;
		auto f3 = std::bind(&Foo::print_sum, &foo, 95, _1);
		f3(5);

		// 绑定指向数据成员指针
		auto f4 = std::bind(&Foo::data, _1);
		std::cout << f4(foo) << '\n';

		// 智能指针亦能用于调用被引用对象的成员
		std::cout << f4(std::make_shared<Foo>(foo)) << '\n'
			<< f4(std::make_unique<Foo>(foo)) << '\n';


	}
}

namespace bxd002{

	struct Foo {
		/*explicit*/ Foo(int num) : num_(num) {}
		void print_add(int i) const { std::cout << num_ + i << '\n'; }
		int num_;
	};

	void print_num(int i)
	{
		std::cout << i << '\n';
	}

	struct PrintNum {
		void operator()(int i) const
		{
			std::cout << i << '\n';
		}
	};

	void test_function()
	{
		cout << "starting test std::function..." << endl;
		// 存储自由函数
		std::function<void(int)> f_display = print_num;
		f_display(-9);

		// 存储 lambda
		std::function<void()> f_display_42 = []() { print_num(42); };
		f_display_42();

		// 存储到 std::bind 调用的结果
		std::function<void()> f_display_31337 = std::bind(print_num, 31337);
		f_display_31337();

		// 存储到成员函数的调用
		std::function<void(const Foo&, int)> f_add_display = &Foo::print_add;
		const Foo foo(314159);
		f_add_display(foo, 1);
		f_add_display(314159, 1);//隐式转换 如果Foo 构造函数前加explicit 此句编译不过

		// 存储到数据成员访问器的调用
		std::function<int(Foo const&)> f_num = &Foo::num_;
		std::cout << "num_: " << f_num(foo) << '\n';

		// 存储到成员函数及对象的调用cdxv 5s43
		using std::placeholders::_1;
		std::function<void(int)> f_add_display2 = std::bind(&Foo::print_add, foo, _1);
		f_add_display2(2);

		// 存储到成员函数和对象指针的调用
		std::function<void(int)> f_add_display3 = std::bind(&Foo::print_add, &foo, _1);
		f_add_display3(3);

		// 存储到函数对象的调用
		std::function<void(int)> f_display_obj = PrintNum();
		f_display_obj(18);

		auto factorial = [](int n) {
			// 存储 lambda 对象以模拟“递归 lambda ”，注意额外开销
			std::function<int(int)> fac = [&](int n) { return (n < 2) ? 1 : n * fac(n - 1); };
			// note that "auto fac = [&](int n){...};" does not work in recursive calls
			return fac(n);
		};
		for (int i{ 5 }; i != 8; ++i) { std::cout << i << "! = " << factorial(i) << ";  "; }
	}
}

#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <functional>

namespace bxd003 {

	void test_all_of() {

		cout << "starting test all_of none_of any_of..." << endl;
		std::vector<int> v(10, 2);

		//部分求和，{2 4 6 8 10 12 14 16 18 20 }
		std::partial_sum(v.cbegin(), v.cend(), v.begin());
		std::cout << "Among the numbers: ";
		std::copy(v.cbegin(), v.cend(), std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';

		if (std::all_of(v.cbegin(), v.cend(), [](int i) { return i % 2 == 0; })) {
			std::cout << "All numbers are even\n";
		}
		// std::modulus 求模
		if (std::none_of(v.cbegin(), v.cend(), std::bind(std::modulus<int>(),
			std::placeholders::_1, 2))) {
			std::cout << "None of them are odd\n";
		}
		struct DivisibleBy
		{
			const int d;
			DivisibleBy(int n) : d(n) {}
			bool operator()(int n) const { return n % d == 0; }
		};

		if (std::any_of(v.cbegin(), v.cend(), DivisibleBy(7))) {
			std::cout << "At least one number is divisible by 7\n";
		}
	}
}

namespace bxd004 {

	void test_find() {

		cout << "test find_if find_if_not" << endl;
		std::vector<int> v{ 1, 2, 3, 4 };
		int n1 = 3;
		int n2 = 5;
		auto is_even = [](int i) { return i % 2 == 0; };

		auto result1 = std::find(begin(v), end(v), n1);
		auto result2 = std::find(begin(v), end(v), n2);
		auto result3 = std::find_if(begin(v), end(v), is_even);
		auto result4 = std::find_if_not(begin(v), end(v), is_even);

		(result1 != std::end(v))
			? std::cout << "v contains " << n1 << '\n'
			: std::cout << "v does not contain " << n1 << '\n';

		(result2 != std::end(v))
			? std::cout << "v contains " << n2 << '\n'
			: std::cout << "v does not contain " << n2 << '\n';

		(result3 != std::end(v))
			? std::cout << "v contains an even number: " << *result3 << '\n'
			: std::cout << "v does not contain even numbers\n";

		(result4 != std::end(v))
			? std::cout << "v contains an odd number: " << *result4 << '\n'
			: std::cout << "v does not contain odd numbers\n";
	}

	void test_copy() {

		cout << "starting test copy..." << endl;
		std::vector<int> from_vector(10);
		//	以 value 开始，按顺序递增填充的值的范围
		std::iota(from_vector.begin(), from_vector.end(), 0);

		std::vector<int> to_vector;
		std::copy(from_vector.begin(), from_vector.end(),
			std::back_inserter(to_vector));
		// 或可选地，
		//  std::vector<int> to_vector(from_vector.size());
		//  std::copy(from_vector.begin(), from_vector.end(), to_vector.begin());
		// 任一方式都等价于
		//  std::vector<int> to_vector = from_vector;

		std::cout << "to_vector contains: ";

		std::copy(to_vector.begin(), to_vector.end(),
			std::ostream_iterator<int>(std::cout, " "));
		std::cout << '\n';

		std::cout << "odd numbers in to_vector are: ";

		std::copy_if(to_vector.begin(), to_vector.end(),
			std::ostream_iterator<int>(std::cout, " "),
			[](int x) { return (x % 2) == 1; });
		std::cout << '\n';
	}

	void test_for_each() {
		
		cout << "starting test for_each..." << endl;
		std::vector<int> v(10);
		std::iota(v.begin(), v.end(), 1);

		std::for_each(v.cbegin(), v.cend(), [&](const int& v) {cout << v << " "; });
		cout << endl;
	}

	void test_count() {

		cout << "starting test count...." << endl;
		std::vector<int> v{ 1, 2, 3, 4, 4, 3, 7, 8, 9, 10 };

		// 确定 std::vector 中有多少个整数匹配目标值。
		int target1 = 3;
		int target2 = 5;
		int num_items1 = std::count(v.begin(), v.end(), target1);
		int num_items2 = std::count(v.begin(), v.end(), target2);
		std::cout << "number: " << target1 << " count: " << num_items1 << '\n';
		std::cout << "number: " << target2 << " count: " << num_items2 << '\n';

		// 用 lambda 表达式计量能被 3 整除的元素数。
		int num_items3 = std::count_if(v.begin(), v.end(), [](int i) {return i % 3 == 0; });
		std::cout << "number divisible by three: " << num_items3 << '\n';

	}

	void test_find_end()
	{
		//指向范围 [first, last) 中 [s_first, s_last) 最后一次出现的起始的迭代器
		cout << "starting test find_end...." << endl;

		std::vector<int> v{ 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4 };
		std::vector<int>::iterator result;

		std::vector<int> t1{ 1, 2, 3 };
		//std::vector<int> t1{ 4, 1, 2 };

		result = std::find_end(v.begin(), v.end(), t1.begin(), t1.end());
		if (result == v.end()) {
			std::cout << "subsequence not found\n";
		}
		else {
			std::cout << "last subsequence is at: "
				<< std::distance(v.begin(), result) << "\n";
		}

		std::vector<int> t2{ 4, 5, 6 };
		result = std::find_end(v.begin(), v.end(), t2.begin(), t2.end());
		if (result == v.end()) {
			std::cout << "subsequence not found\n";
		}
		else {
			std::cout << "last subsequence is at: "
				<< std::distance(v.begin(), result) << "\n";
		}
	}

	void test_find_first_of() {
		//指向范围 [first, last) 中等于来自范围 [s_first; s_last) 中一个元素的首个元素。若找不到这种元素，则返回 last 。
		cout << "starting test find_end..." << endl;
		std::vector<int> v{ 0, 2, 3, 25, 5 };
		const auto t = { 3, 19, 10, 2 };

		auto result = std::find_first_of(v.begin(), v.end(), t.begin(), t.end());

		if (result == v.end()) {
			std::cout << "no elements of v were equal to 3, 19, 10 or 2\n";
		}
		else {
			std::cout << "found a match at "
				<< std::distance(v.begin(), result) << "\n";//found a match at 1
		}
	}

	void test_adjacent_find() {
		//在范围 [first, last) 中搜索二个相继的相等元素。
		cout << "starting test adjacent_find..." << endl;
		std::vector<int> v1{ 0, 1, 2, 3, 40, 40, 41, 41, 5 };

		auto i1 = std::adjacent_find(v1.begin(), v1.end());

		if (i1 == v1.end()) {
			std::cout << "no matching adjacent elements\n";
		}
		else {
			std::cout << "the first adjacent pair of equal elements at: "
				<< std::distance(v1.begin(), i1) << '\n';
		}

		auto i2 = std::adjacent_find(v1.begin(), v1.end(), std::greater<int>());
		if (i2 == v1.end()) {
			std::cout << "The entire vector is sorted in ascending order\n";
		}
		else {
			std::cout << "The last element in the non-decreasing subsequence is at: "
				<< std::distance(v1.begin(), i2) << '\n';
		}
	}

	template<typename Container>
	bool in_quote(const Container& cont, const std::string& s)
	{
		return std::search(cont.begin(), cont.end(), s.begin(), s.end()) != cont.end();
	}

	void  test_search()
	{
		std::string str = "why waste time learning, when ignorance is instantaneous?";
		// str.find() 也能使用
		std::cout << std::boolalpha << in_quote(str, "learning") << '\n'
			<< in_quote(str, "lemming") << '\n';

		std::vector<char> vec(str.begin(), str.end());
		std::cout << std::boolalpha << in_quote(vec, "learning") << '\n'
			<< in_quote(vec, "lemming") << '\n';


		std::vector<int> v{ 1,4,5,6,9 };
		if (std::search(v.begin(), v.end(), 5) != v.end())
			std::cout << "find 5 in vec" << endl;


		// C++17 重载演示：
		/*std::string in = "Lorem ipsum dolor sit amet, consectetur adipiscing elit,"
			" sed do eiusmod tempor incididunt ut labore et dolore magna aliqua";
		std::string needle = "pisci";
		auto it = std::search(in.begin(), in.end(),
			std::boyer_moore_searcher(
				needle.begin(), needle.end()));
		if (it != in.end())
			std::cout << "The string " << needle << " found at offset "
			<< it - in.begin() << '\n';
		else
			std::cout << "The string " << needle << " not found\n";*/
	}


	std::string mirror_ends(const std::string& in)
	{
		return std::string(in.begin(),
			std::mismatch(in.begin(), in.end(), in.rbegin()).first);
	}

	//std::mismatch 寻找两个范围出现不同的首个位置
	void test_mismatch() {
		std::cout << mirror_ends("abXYZba") << '\n'
			<< mirror_ends("abca") << '\n'
			<< mirror_ends("aba") << '\n'
			<< mirror_ends("cns") <<'\n'
			<< mirror_ends("abceeabcdsdcbaffcba") << endl;
			

	}

	void test_search_n()
	{
		string s = "abcdssssffggsa";
		//	在范围中搜索一定量的某个元素的连续副本
		auto it = std::search_n(s.begin(), s.end(), 4, 's');
		if (it != s.end()) {
			cout << "find s ." << *it;
		}
	}
	

}

namespace bxd005 {

	//test_
}

int main()
{
	cout << "不修改序列的操作" << endl;
	bxd001::test_bind();
	//bxd002::test_function();
	//bxd003::test_all_of();
	/*bxd004::test_find();

	bxd004::test_for_each();
	bxd004::test_count();*/

	//bxd004::test_find_end();
	//bxd004::test_adjacent_find();
	bxd004::test_mismatch();
	bxd004::test_search();
	//bxd004::test_search_n();
	cout << "修改序列的操作" << endl;
	//bxd004::test_copy();


	cout << "hello world!" << endl;
}