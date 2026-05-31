#include "List.h"
#include <utility>

List::Node::Node(const ValueType& value,Node* prev, Node* next) : _data(value), _next(next), _prev(prev) {}

List::List(const ValueType& value) 
{
	push(value);
}
List::List(const ValueType& value, size_t count)
{
	for (size_t i = 0; i < count; ++i)
	{
		push(value);
	}
}
List::List(const ValueType* array, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		push(array[i]);
	}
}
List::List(const List& other) : _head(nullptr), _end(nullptr), _size(0)
{
	*this = other;
}
List& List::operator=(const List& other)
{
	if (this == &other)
	{
		return *this;
	}
	Node* current = _head;
	while (current != nullptr)
	{
		Node* next = current->_next;
		delete current;
		current = next;
	}
	current = other._head;
	_head = nullptr;
	_end = nullptr;
	_size = 0;
	while (current != nullptr)
	{
		push(current->_data);
		current = current -> _next;
	}
	return *this;
}
List::List(List&& other) noexcept
{
	*this = std::move(other);
}
List& List::operator=(List&& other) noexcept
{
	if (this == &other)
        {
                return *this;
        }
	Node* current = _head;
	while (current != nullptr)
        {
                Node* next = current->_next;
                delete current;
                current = next;
        }
	_head = other._head;
	_end = other._end;
	_size = other._size;
	other._head = nullptr;
	other._end = nullptr;
	other._size = 0;
        return *this;
}
List::~List()
{
    Node* current = _head;
    while (current != nullptr)
    {
        Node* next = current->_next;
        delete current;
        current = next;
    }
    _head = nullptr;
    _end = nullptr;
    _size = 0;
}

void List::push(const ValueType& value)
{
	Node* newNode = new Node(value, _end, nullptr);
	if (_head == nullptr)
	{
		_head = newNode;
	}
	else
	{
		_end->_next = newNode;
	}
	_end = newNode;
	++_size;
}
void List::pop()
{
	if (_head == nullptr)
	{
		return;
	}
	if (_head == _end)
	{
		delete _head;
		_head = nullptr;
		_size = 0;
	}
	else
	{
		Node* newEnd = _end->_prev;
        	newEnd->_next = nullptr;
		delete _end;
		_end = newEnd;
		--_size;
	}
}
const ValueType& List::top() const
{
	if(_head == nullptr)
	{
		throw std::out_of_range("List is empty");
	}
	return _end->_data;
}
bool List::isEmpty() const
{
	if (_head == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
size_t List::size() const
{
	return _size;
}
