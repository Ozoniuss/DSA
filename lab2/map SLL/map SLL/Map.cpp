#include "Map.h"
#include "MapIterator.h"
#include <iostream>

Map::Map()
{
	head = nullptr;
	tail = nullptr;
	length = 0;
}

Map::~Map() 
{
	while (head != nullptr)
	{
		Node* current_node = head->next;
		delete head;
		head = current_node;
	}
	tail = nullptr;

}

void Map::filter(Condition cond)
{
	if (length == 0)
		return;
	if (length == 1 && cond(std::get<1>(head->key_value) == false))
		remove(std::get<0>(head->key_value));
	if (length >= 2)
	{
		Node* current_element = head->next;
		Node* previous_node = head;
		while (current_element != nullptr)
		{
			if (cond(std::get<1>(current_element->key_value)) == false)
			{
				current_element = current_element->next;
				previous_node->next = current_element;
				length--;
			}
			else
			{
				previous_node = current_element;
				current_element = current_element->next;
			}
		}
		if (cond(std::get<0>(head->key_value)) == false)
		{
			TKey k = std::get<0>(head->key_value);
			remove(k);
		}
	}
}
//theta(n) in all cases

TValue Map::add(TKey c, TValue v)
{
	Node* new_node = new Node;
	new_node->key_value = std::make_pair(c, v);
	new_node->next = nullptr;
	if (length == 0)
	{
		head = tail = new_node;
		length++;
		return NULL_TVALUE;
	}
	Node* current_node = this->head;
	while (current_node != nullptr && std::get<0>(current_node->key_value) != c)
	{
		current_node = current_node->next;
	}
	if (current_node != nullptr)
	{
		TValue value = std::get<1>(current_node->key_value);
		current_node->key_value.second = v;
		delete new_node;
		return value;
	}
	if (current_node == nullptr)
	{
		//this->tail->next = new_node;
		//this->tail = new_node;
		new_node->next = this->head;
		this->head = new_node;
		length++;
		return NULL_TVALUE;
	}
	
}
//BC = TH(1), WC = TH(n), AC = O(n)

TValue Map::search(TKey c) const
{
	if (length == 0)
		return NULL_TVALUE;

	Node* current_node = this->head;
	while (current_node != nullptr)
	{
		if (std::get<0>(current_node->key_value) == c)
			return std::get<1>(current_node->key_value);

		current_node = current_node->next;
	}
	return NULL_TVALUE;
}
//BC = theta(1), WC = theta(n), AC = O(n)

TValue Map::remove(TKey c)
{
	if (length == 0)
		return NULL_TVALUE;

	//if (search(c) == NULL_TVALUE)
		//return NULL_TVALUE;

	if (length == 1 && std::get<0>(this->head->key_value) == c)
	{
		length = 0;
		TValue value = std::get<1>(this->head->key_value);
		delete this->head;
		this->head = this->tail = nullptr;
		return value;
	}


	Node* current_node = this->head;
	Node* previous_node = nullptr;
	while (current_node != nullptr && std::get<0>(current_node->key_value) != c)
	{
		previous_node = current_node;
		current_node = current_node->next;
	}
	if (current_node != nullptr && previous_node == nullptr)
	{
		TValue value = std::get<1>(current_node->key_value);
		//Node* auxiliary;
		//auxiliary = this->head;
		//delete this->head;
		this->head = this->head->next;
		length--;
		return value;
	}
	else if (current_node != nullptr)
	{
		TValue value = std::get<1>(current_node->key_value);
		previous_node->next = current_node->next;
		current_node->next = nullptr;
		delete current_node;
		length--;
		return value;
	}
	return NULL_TVALUE;
}
//BC = th(1), WC = th(n), AC = O(n)

int Map::size() const
{
	return length;
}
//theta(1) all cases

bool Map::isEmpty() const
{
	if (length == 0)
		return true;
	return false;
}
//theta(1) all cases

MapIterator Map::iterator() const
{
	return MapIterator(*this);
}
//theta(1)all cases


