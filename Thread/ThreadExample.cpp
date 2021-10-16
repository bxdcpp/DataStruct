#include <iostream>
#include <iterator>
#include <functional>
#include <algorithm>
#include <vector>
#include <stack>
#include <time.h>
#include <thread>

using namespace std;


namespace bxd001 {
	struct A
	{
		void operator()() const
		{
			std::cout << 1;
		}
	};

	void f(int& n) { ++n; cout << "n:" << n<<endl; }

	void f2(std::unique_ptr<int> p) {
		std::cout << *p << std::endl;
	}



	void test_crete_thread()
	{
		A a;
		thread t1(a);
		//thread t(A());//most vexing parse,A()被视为函数申明
		//解决most vexing parse的方法
		thread t2{ A() };
		thread t3( (A()) );
		thread t4{ [] {std::cout << 1<<std::endl; } };

		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}

	void test_ref_parameter()
	{
		//std::thread会无视参数的引用类型，因此需要使用std::ref来生成一个引用包裹
		//对象以传入引用类型
		int i = 1;
		std::thread t(f,std::ref(i));
		t.join();
		//std::cout <<"current:"<< i;
	}

	class B
	{

	public:
		void f(int i) { std::cout << i<<std::endl; };
	

	};

	void test_class_func_parameter()
	{
		B b;
		std::thread t(&B::f, &b, 22);
		t.join();

	}

	void test_moveOnly()
	{
		auto p = std::make_unique<int>(42);
		std::thread t(f2, std::move(p));
		t.join();
	}


}

namespace bxd002 {

	void f() {};
	void g() {};

	void test_move()
	{
		std::thread t1(f);
		std::thread t2 = std::move(t1); //t1所有权给t2,t2关联执行f线程
		t1 = std::thread(g);//t1 重新关联一个线程g
		std::thread t3;
		t3 = std::move(t2);//t3关联t2的线程，t2无关联
		t1 = std::move(t3);//t1已经关联了g线程，调用std::terminate终止程序
	}
}
#include <list>
#include <mutex>

namespace bxd003
{
	std::list<int> v;
	std::mutex m;


	struct Box {
		explicit Box(int num) : num_things{ num } {}

		int num_things;
		std::mutex m;
	};

	void transfer(Box& from, Box& to, int num)
	{
		//std::lock(from.m, to.m);

		// 仍未实际取锁
		std::unique_lock<std::mutex> lock1(from.m, std::defer_lock);
		std::unique_lock<std::mutex> lock2(to.m, std::defer_lock);
	

		// 锁两个 unique_lock 而不死锁
		std::lock(lock1, lock2);


		from.num_things -= num;
		to.num_things += num;

		// 'from.m' 与 'to.m' 互斥解锁于 'unique_lock' 析构函数
		cout << "from.m:" << from.num_things<<std::endl;
		cout << "to.m:" << to.num_things << std::endl;


		/*from.m.unlock();
		to.m.unlock();*/
	}

	void  test_unique_lock()
	{
		Box acc1(100);
		Box acc2(50);

		std::thread t1(transfer, std::ref(acc1), std::ref(acc2), 10);
		std::thread t2(transfer, std::ref(acc2), std::ref(acc1), 5);

	

		t1.join();
		t2.join();

	}



	void f(int n)
	{
		std::lock_guard<std::mutex>lo(m);
		v.emplace_back(n);
	}

	int getData() {

		return 5;
	}

	bool process(int data) { return false; }

	void f3(int n)
	{
		std::unique_lock<std::mutex>lo(m);
		auto data = getData();
		lo.unlock();//费时操作没比较持有锁，先解锁
		auto res = process(data);
		lo.lock();//为了写入数据再次加锁
		//writeResult(data, res);
	}
}

namespace bxd004 
{
	class A {
	public:
		explicit A(int x) :i(x) {}
		int i;
		std::mutex m;
	};


	void f(A& from, A& to, int n)
	{
		std::lock(from.m, to.m);//同时lock
		//下面按固定顺序加锁,看似不会死锁
		//如果没有std::lock(from.m, to.m)同时加锁
		//就会出现函数f2中的的死锁情况
		std::lock_guard<std::mutex>lock1(from.m, std::adopt_lock);
		std::lock_guard<std::mutex>lock2(to.m, std::adopt_lock);
		from.i -= n;
		to.i += n;
		cout << "from.m:" << from.i << std::endl;
		cout << "to.m:" << to.i << std::endl;
	}

	void f2(A& from, A& to, int n) {
	

		//执行f2(from,to, n)
		//执行f2(to,from,n)
		//此时加锁的顺序就反过来了
		//这样就会存在不同线程中互相加锁产生死锁
		from.m.lock(), to.m.lock();

		from.i -= n;
		to.i += n;
		cout << "from.m:" << from.i << std::endl;
		cout << "to.m:" << to.i << std::endl;

		from.m.unlock(), to.m.unlock();
	
	}

	void  test_lock_dead()
	{
		A x(100);
		A y(50);

		std::thread t1(f, std::ref(x), std::ref(y), 5);
		std::thread t2(f, std::ref(y), std::ref(x), 10);

		t1.join();
		t2.join();

	}
}

namespace bxd005
{
	std::mutex m;
	void f1()
	{
		for (int i = 0; i < 100; i++)
		{
			std::cout << "A";
		}
	}
	void f2()
	{
		for (int i = 0; i < 100; i++)
		{
			std::cout << "B";
		}
	}
	void f3()
	{
		for (int i = 0; i < 100; i++)
		{
			std::cout << "C";
		}
	}

	void test_order_print()
	{
		std::thread t1(f1);
		std::thread t2(f2);
		std::thread t3(f1);

		t1.join();
		t2.join();
		t3.join();
	}
}

namespace bxd006
{
	std::once_flag flag;
	
	void f() 
	{
		std::call_once(flag, [] {std::cout << "call_once"<<std::endl; });
		std::cout << "call_two" << std::endl;
	}

	void test_call_once()
	{
		std::thread t1(f);
		std::thread t2(f);
		std::thread t3(f);

		t1.join();
		t2.join();
		t3.join();
	}


	std::once_flag flag1, flag2;

	void simple_do_once()
	{
		std::call_once(flag1, []() { std::cout << "Simple example: called once\n"; });
	}

	void may_throw_function(bool do_throw)
	{
		if (do_throw) {
			std::cout << "throw: call_once will retry\n"; // 这会出现多于一次
			throw std::exception();
		}
		std::cout << "Didn't throw, call_once will not attempt again\n"; // 保证一次
	}

	void do_once(bool do_throw)
	{
		try {
			std::call_once(flag2, may_throw_function, do_throw);
		}
		catch (...) {
		}
	}

	void  test_call_once2()
	{
		std::thread st1(simple_do_once);
		std::thread st2(simple_do_once);
		std::thread st3(simple_do_once);
		std::thread st4(simple_do_once);
		st1.join();
		st2.join();
		st3.join();
		st4.join();

		std::thread t1(do_once, true);
		std::thread t2(do_once, true);
		std::thread t3(do_once, false);
		std::thread t4(do_once, true);
		t1.join();
		t2.join();
		t3.join();
		t4.join();
	}
}

#include <condition_variable>
namespace bxd007 
{
	std::mutex m;
	std::condition_variable cv;
	std::string data;

	bool processed = false;
	bool ready = false;

	void f()
	{
		std::unique_lock<std::mutex> lock1(m);
		cv.wait(lock1, [] {return ready; });
		//当收到其他线程notify_one时wait会被唤醒
		data += "after processing";
		processed = true;
		lock1.unlock();
		cv.notify_one();

	}

	void test_condition_variable()
	{
		std::thread t(f);
		data = "data,";
		{
			std::lock_guard<std::mutex>lock(m);
			data += "ready ";
			ready = true;
			cv.notify_one();//唤醒cv.wait,重新检查ready == true;

		}

		{
			std::unique_lock<std::mutex>lock(m);
			cv.wait(lock, [] {return processed; });
		}
		std::cout << data; //data, ready after processing
		t.join();
	}
}

namespace bxd008
{

	std::mutex mu;
	std::condition_variable cond_var;
	int num = 0;

	void func(char ch)
	{
		int n = ch - 'A';
		for (int i = 0; i < 10; i++)
		{
			std::unique_lock<std::mutex> mylock(mu);
			cond_var.wait(mylock, [n] {return n == num; });
			cout << ch;
			num = (num + 1) % 3;
			//mylock.unlock();
			cond_var.notify_all();
		}
	}

	void  test_order_print()
	{
		vector<thread> pool;
		pool.push_back(thread(func, 'A'));
		pool.push_back(thread(func, 'B'));
		pool.push_back(thread(func, 'C'));
		for (auto iter = pool.begin(); iter != pool.end(); iter++)
		{
			iter->join();
		}
	}
}


#include <chrono>
#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <thread>
#include <utility>

namespace bxd009
{
	using namespace std;

	class scoped_thread {
	public:
		template <typename... Arg>
		scoped_thread(Arg&&... arg)
			: thread_(std::forward<Arg>(arg)...)
		{}
		scoped_thread(
			scoped_thread&& other) noexcept
			: thread_(
				std::move(other.thread_))
		{}
		scoped_thread(
			const scoped_thread&) = delete;
		~scoped_thread()
		{
			if (thread_.joinable()) {
				thread_.join();
			}
		}

	private:
		thread thread_;
	};

	void work(condition_variable& cv,
		int& result)
	{
		// 假装我们计算了很久
		this_thread::sleep_for(2s);
		result = 42;
		cv.notify_one();
	}

	void test_myScoped_thread()
	{
		condition_variable cv;
		mutex cv_mut;
		int result;

		scoped_thread th{ work, ref(cv),
						 ref(result) };
		// 干一些其他事
		cout << "I am waiting now\n";
		unique_lock<std::mutex> lock{ cv_mut };
		cv.wait(lock);
		cout << "Answer: " << result
			<< '\n';
	}
	
}


int main()
{
#if 0
	{
		using namespace  bxd001;
		//test_crete_thread();
		test_ref_parameter();
		test_class_func_parameter();
		test_moveOnly();

	}
#endif 

	/*using namespace bxd002;
	{
		test_move();
	}*/  
	
#if 1
	//● std::thread::hardware_concurrency()：返回支持的并发线程数。
	//● std::this_thread::get_id()： 获取线程id。 
	//● std::this_thread::yield()：让出处理器，重新调度各执行线程。
	//● std::this_thread::sleep_for：使当前线程的执行停止指定的时间段。
	//● std::this_thread::sleep_until：使当前线程的执行停止直到指定的时间点。
	std::cout << "返回支持的并发线程数:" << std::thread::hardware_concurrency() << std::endl;
	std::cout << "获取线程id:" << std::this_thread::get_id() << std::endl;


#endif
	/*{
		using namespace bxd003;
		test_unique_lock();
	}*/

	//bxd004::test_lock_dead();
	bxd005::test_order_print();
	/*bxd006::test_call_once();
	bxd006::test_call_once2();*/
	//bxd007::test_condition_variable();
	//bxd008::test_order_print();
	return 0;
}
