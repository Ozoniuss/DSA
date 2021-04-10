#include "SetIterator.h"
#include "Set.h"
#include <exception>

//SetIterator::SetIterator(const Set& m) : set(m)
//{
	//current = m.headPos;
//}


void SetIterator::first() {
	current = set.headPos;
}


void SetIterator::next() {
	if (!valid())
		throw std::exception("Invalid iterator!");
	current = set.nextPos[current];
}


TElem SetIterator::getCurrent()
{
	if (!valid())
		throw std::exception("Invalid iterator!");
	return set.elems[current];
}

bool SetIterator::valid() const {
	return current != -1;
}

//Th(1) for all iterator functions

