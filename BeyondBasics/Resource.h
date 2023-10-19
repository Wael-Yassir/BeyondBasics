#pragma once

#include <string>

class Resource
{
private:
	std::string _name;

public:
	Resource(std::string name);
	Resource(Resource const& r);					// Copy constructor
	Resource& operator=(Resource const& r);			// Copy assignment operator

	// && is a reference to an instance that is about to disappear.
	Resource(Resource&& r);							// Move constructor
	Resource& operator=(Resource&& r);				// Move assignment operator
	
	~Resource(void);
	std::string GetName() const { return _name; }
};


/*
  Move semantic helps speed up the program. When you don't need to go over all the trouble to copy because
  we won't need the original object anymore as for temporary object for example.

  string s = s1 + s2 => as part of doing this, we need to add s1 and s2, store them
  to a temp object, then copy the value from the temp object to another object 
  and make s reference the new object location, but in face we don't need temp anymore

  Move semantics will help making s reference temp object and by this we don't need to
  copy any data from the temp to a new object to make s reference it.
*/