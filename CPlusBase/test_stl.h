#ifndef __TEST_STL_H
#define __TEST_STL_H

#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <array>
#include <queue>
#include <stack>
#include <algorithm>
#include <utility>


namespace stl001
{
	using namespace std;
	void test_use_array()
	{
		std::array<int, 13> array{ 99,10,77,234,34,7,4,1,76,876,44,88,10 };

		//********************遍历方式************************************/
		{
			for (auto it : array){
				cout << it << " ";
			}

			std::for_each(array.begin(), array.end(), [=](int v) {std::cout << v << " "; });

			for (auto& it = array.begin(); it != array.end(); it++){
				cout << *it << " ";
			}
			
			for (auto& it = array.cbegin(); it != array.cend(); it++){
				cout << *it << " ";
			}

			for (auto& it = array.rbegin(); it != array.rend(); it++){
				cout << *it << " ";
			}

			for (auto& it = array.crbegin(); it != array.crend(); it++){
				cout << *it << " ";
			}

			int myarray[13]{ 0 };
			memcpy(myarray, array.data(), sizeof(int) * 13);

			cout << "at:" << array.at(1) << std::endl;
			cout << "back:" << array.back() << std::endl;
			cout << "front:" << array.front() << std::endl;
			cout << "max_size:" << array.max_size() << std::endl;
			cout << "size:" << array.size() << std::endl;
			cout << "get:" << std::get<0>(array) << " " << std::get<1>(array) << std::endl;

			std::array<int, 3>a1{ 1,4,5 }, a2{ 4,7,9 };

			auto it1 = a1.begin();
			auto it2 = a2.begin();
			int& ref1 = a1[1];
			int& ref2 = a2[1];

			std::cout << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
			a1.swap(a2);
			std::cout << *it1 << ' ' << *it2 << ' ' << ref1 << ' ' << ref2 << '\n';
			array.fill(0);
			std::array<int, 10> a3{ 1,2,3 };
			cout << "max_size:" << a3.max_size() << std::endl;//10
			cout << "size:" << a3.size() << std::endl;//10

		}


	}

}

#endif // !__TEST_VIRTUAL_CLASS_H



