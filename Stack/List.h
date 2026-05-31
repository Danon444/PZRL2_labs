#pragma once

#include <stdexcept>
#include <stdlib.h>

using ValueType = double;

class List 
{
protected:
	class Node
	{
	public:
		Node* _next;
		Node* _prev;
		ValueType _data;
		Node(const ValueType& value, Node* prev = nullptr, Node* next = nullptr);
	};
	Node* _head = nullptr;
	Node* _end = nullptr;
	size_t _size = 0;
public:
	List() = default;
	explicit List(const ValueType& value);
	List(const ValueType& value, size_t count);
	List(const ValueType* array, size_t size);
	List(const List& other);
	List& operator=(const List& other);
	List(List&& other) noexcept;
	List& operator=(List&& other) noexcept;
	
	void push(const ValueType& value);
	void pop();
	const ValueType& top() const;
	bool isEmpty() const;
 	size_t size() const;
	~List();
};
