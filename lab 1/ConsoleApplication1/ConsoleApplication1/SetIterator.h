#pragma once
#include "Set.h"

class SetIterator
{
	//DO NOT CHANGE THIS PART
	friend class Set;
private:
	//DO NOT CHANGE THIS PART
	const Set& set;
	SetIterator(const Set& s);

	//TODO - Representation
	int current_element = 0;
	//iterate from the first element of the array

public:
	void first();
	void next();
	TElem getCurrent();
	bool valid() const;
};


