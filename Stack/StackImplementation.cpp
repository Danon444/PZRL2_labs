#include "StackImplementation.h"

void VectorImplementation::push(const ValueType& value)
{
	container.pushBack(value);
}
void VectorImplementation::pop()
{
	container.popBack();
}
const ValueType& VectorImplementation::top() const
{
	return container[container.size()-1];
}
bool VectorImplementation::isEmpty() const
{
	if (container.size() == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}
size_t VectorImplementation::size() const
{
	return container.size();
}

void ListImplementation::push(const ValueType& value)
{
        container.push(value);
}
void ListImplementation::pop()
{
        container.pop();
}
const ValueType& ListImplementation::top() const
{
        return container.top();
}
bool ListImplementation::isEmpty() const
{
        if (container.size() == 0)
        {
                return true;
        }
        else
        {
                return false;
        }
}
size_t ListImplementation::size() const
{
        return container.size();
}
