
#include<chrono>
#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
#include <algorithm>
#include <exception>

#include "Resource.h"

using std::vector;
using std::list;
using std::cout;

using std::chrono::system_clock;
using std::chrono::steady_clock;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::milliseconds;

using std::exception;
using std::out_of_range;

template <typename Func>
long long TimeFunc(Func f)
{
	auto begin = steady_clock::now();
	f();
	auto end = steady_clock::now();

	return duration_cast<milliseconds>(end - begin).count();
}

int main()
{
	vector<int> numbers{ 1, 2, 3 };
	numbers.push_back(4);
	numbers[0] = 0;
	int num = numbers[2];

	for (int i : numbers)
	{
		cout << i << std::endl;
	}

	Resource r{ "local" };

	{   // create local scope
		cout << "--------------------------------------" << std::endl;
		vector<Resource> resources;
		resources.push_back(r);
		cout << "--------------------------------------" << std::endl;
		resources.push_back(Resource{ "first" });
		cout << "--------------------------------------" << std::endl;
		resources.push_back(Resource{ "second" });
		cout << "--------------------------------------" << std::endl;
	}

	// lambda: the compiler generate a class and instance of this class using when you put as parameters.
	/*
		auto lmbda = [](lambda args) |-> returnType: optional| |mutable: optional| { lambda login };
		- []:
			  * Capture close, where you can pass variable by value or references from the calling
				scope. If you want to pass everything, you can use =, or & sign: [=], [&]
			  * mutable: by default parameters in [] are const if passed by value, unless mutable is used.
		- If the lambda is not stored on a variable, you can pass the args by value
		  but if it is stored to call later, better to pass them by value because this will
		  eliminate the risk of having parameters out of scope used in the lambda.
		-
	*/
	auto isOdd = [/*Put variables from calling scope if needed*/](int num) { return num % 2 != 0; };

	bool is3Odd = isOdd(3);
	vector<int> numVector{ 2, 3, 4, -1, 1 };
	int oddCount = std::count_if(std::begin(numVector), std::end(numVector), isOdd);

	// Capturing by value and reference explicity [x, y, &message]
	int x = 3;
	int y = 7;
	std::string message = "Elements between ";
	message += std::to_string(x) + " and " + std::to_string(y) + " inclusive: ";

	std::for_each(std::begin(numbers), std::end(numbers),
		[x, y, &message](int n)
		{
			if (n >= x && n <= y)
				message += " " + std::to_string(n);
		});

	//////////////////////////////
	x = y = 0;

	// x by value, rest by ref
	std::for_each(std::begin(numbers), std::end(numbers),
		[&, x](int n) mutable
		{
			x += n;
			y += n;
		});

	// looping with iterator
	for (auto it = std::begin(numbers); it != std::end(numbers); it++)
	{
		cout << *it << std::endl;
	}

	// will return a new iterator pointing to the new end after taking out all 3's and rearrange the vector
	auto endNumbers = std::remove_if(std::begin(numbers), end(numbers), [](int n) { return n == 3; });
	numbers.erase(endNumbers, std::end(numbers));

	// using exception
	vector<int> integers{ 1, 2, 3, 4 };

	// catching exception by reference will avoid slicing, meaning all  
	// the child exception data will be still there to access 
	try
	{
		int j = integers.at(99);
	}
	catch (const std::out_of_range& e)
	{
		cout << e.what() << std::endl;
	}
	catch (const std::exception& e)
	{
		cout << e.what() << std::endl;
	}

	return 0;
} 
