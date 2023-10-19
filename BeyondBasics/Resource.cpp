
#include "Resource.h"
#include<iostream>

using std::cout;
using std::endl; 
using std::string;

Resource::Resource(std::string name) : _name(name)
{
	cout << "Constructing " << _name << endl;
}

Resource::Resource(Resource const& r) : _name(r._name)
{
	cout << "Copy constructing " << _name << endl;
}

// use when the compiler knows that we are constructing an object
// from something that is about to go away. (like when resize a vector)
Resource::Resource(Resource&& r) : _name(std::move(r._name))
{
	cout << "Move constructing " << _name << endl;
}

Resource& Resource::operator=(Resource const& r)
{
	// If this class managed Resource lifetime, clean up existing one before
	// setting new values. No need here because string takes care of it.

	_name = r.GetName();
	cout << "Copy assigning " << _name << endl;
	return *this;
}

// test for self assginment.
Resource& Resource::operator=(Resource&& r)
{
	if (this != &r)
	{
		_name = std::move(r._name);
		r._name.clear();

		cout << "move assignment " << _name << endl;
	}

	return *this;
}

Resource::~Resource()
{
	cout << "Destructing " << _name << endl;
}

