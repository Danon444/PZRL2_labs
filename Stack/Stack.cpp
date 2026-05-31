#include "Stack.h"
#include "StackImplementation.h"

#include <iostream>
#include <string>

Stack::Stack(StackContainer container) : _containerType(container) 
{
	switch(_containerType)
	{
		case StackContainer::Vector:
		{
			_pimpl = new VectorImplementation();
			break;
		}
		case StackContainer::List:
		{
			_pimpl = new ListImplementation();
			break;
		}
		default:
		{
			_pimpl = new VectorImplementation();
			break;
		}
	}
}
Stack::Stack(const ValueType* valueArray, const size_t arraySize, StackContainer container) : _containerType(container)
{
	switch(_containerType)
        {
                case StackContainer::Vector:
		{
                     	_pimpl = new VectorImplementation();
                        break;
		}
                case StackContainer::List:
		{
			_pimpl = new ListImplementation();
                        break;
		}
		default:
		{
			_pimpl = new VectorImplementation();
		        break;
		}
        }
	for (size_t i = 0; i < arraySize; ++i)
	{
		_pimpl->push(valueArray[i]);
	}
}
Stack::Stack(const Stack& copyStack)
{
	*this = copyStack;
}
Stack& Stack::operator=(const Stack& copyStack)
{
	if (this == &copyStack)
	{
		return *this;
	}
	_containerType = copyStack._containerType;
	delete _pimpl;
	_pimpl = nullptr;

	if (!copyStack._pimpl)
	{
		return *this;
	}
	switch(_containerType)
	{
		case StackContainer::Vector:
                {
                        _pimpl = new VectorImplementation(*dynamic_cast<VectorImplementation*>(copyStack._pimpl));
                        break;
                }
                case StackContainer::List:
                {
                        _pimpl = new ListImplementation(*dynamic_cast<ListImplementation*>(copyStack._pimpl));
                        break;
                }
                default:
                {
                        _pimpl = new VectorImplementation(*dynamic_cast<VectorImplementation*>(copyStack._pimpl));
                        break;
                }
	}
	return *this;
}

Stack::Stack(Stack&& moveStack) noexcept : _containerType(moveStack._containerType)
{
	std::swap(_pimpl, moveStack._pimpl);
}
Stack& Stack::operator=(Stack&& moveStack) noexcept
{
	if (this == &moveStack)
        {
                return *this;
        }
	_containerType = moveStack._containerType;
	std::swap(_pimpl, moveStack._pimpl);
	return *this;
}
Stack::~Stack()
{
	delete _pimpl;
}

void Stack::push(const ValueType& value)
{
	_pimpl->push(value);
}
void Stack::pop()
{
	if (!_pimpl) 
	{
        	throw std::runtime_error("Stack is empty");
	}
	_pimpl->pop();
}
const ValueType& Stack::top() const
{
	if (!_pimpl)
	{
		throw std::runtime_error("Stack is empty");
	}
	return _pimpl->top();
}
bool Stack::isEmpty() const
{
	if (!_pimpl)
        {
                return true;
        }
	return _pimpl->isEmpty();
}
size_t Stack::size() const
{
	if (!_pimpl)
	{
		return 0;
	}
	return _pimpl->size();
}
