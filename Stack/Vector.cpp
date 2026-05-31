#include <iostream>
#include "Vector.h"

Vector::Vector(const ValueType* rawArray, const size_t size, float coef) : _size(size), _capacity(size), _multiplicativeCoef(coef) 
{
	if (_size > 0) 
	{
        _data = new ValueType[_capacity];
        	for (size_t i = 0; i < _size; ++i) 
		{
			_data[i] = rawArray[i];
        	}
	}
       	else 
	{
		_data = nullptr;
	}
}
Vector::Vector(const Vector& other)
{
	*this = other;
}
Vector& Vector::operator=(const Vector& other)
{
	if (this == &other)
	{
		return *this;
	}
	delete[] _data;
	_size = other._size;
        _capacity = other._size;
        _multiplicativeCoef = other._multiplicativeCoef;
	if (other._size > 0)
	{
		_data = new ValueType[_capacity];
		for (size_t i = 0; i < _size; ++i)
		{
			_data[i] = other._data[i];
		}
	}
	else
	{
		_data = nullptr;
	}
	return *this;
}

Vector::Vector(Vector&& other) noexcept
{
	*this = std::move(other);
}
Vector& Vector::operator=(Vector&& other) noexcept
{
	if (this == &other)
	{
		return *this;
	}
	delete[] _data;

	_size = other._size;
        _capacity = other._capacity;
        _multiplicativeCoef = other._multiplicativeCoef;
	_data = other._data;
        other._size = 0;
        other._capacity = 0;
        other._data = nullptr;
	return *this;
}

Vector::~Vector()
{
	delete[] _data;
}

void Vector::reserve(size_t capacity)
{
	if (capacity > _capacity)
	{
		/*if (capacity == 0)
		{
			ValueType* newData = nullptr;
		}
		else
		{
			ValueType* newData = new ValueType[capacity];
		}*/
		ValueType* newData = new ValueType[capacity];
		for (size_t i = 0; i < _size; ++i)
		{
			newData[i] = _data[i];
		}
		delete[] _data;
		_data = newData;
		_capacity = capacity;
	}
}
void Vector::shrinkToFit()
{
	if (_capacity > _size)
	{
		ValueType* newData = new ValueType[_size];
		for (size_t i = 0; i < _size; ++i)
                {
                        newData[i] = _data[i];
                }
                delete[] _data;
                _data = newData;
		_capacity = _size;
	}
}

void Vector::pushBack(const ValueType& value)
{
	if (_size == _capacity)
	{
		if (_capacity == 0)
		{
			reserve(_multiplicativeCoef);
		}
		else
		{
			reserve(_capacity * _multiplicativeCoef);
		}
	}
	_data[_size] = value;
	++_size;
}
void Vector::pushFront(const ValueType& value)
{
	if (_size == _capacity)
        {
                if (_capacity == 0)
                {
                        reserve(_multiplicativeCoef);
                }
                else
                {
                        reserve(_capacity * _multiplicativeCoef);
                }
        }
	for (size_t i = _size; i > 0; --i)
	{
		_data[i] = _data[i - 1];
	}
	_data[0] = value;
	++_size;
}

void Vector::insert(const ValueType& value, size_t pos)
{
	if (_size == _capacity)
        {
                if (_capacity == 0)
                {
                        reserve(_multiplicativeCoef);
                }
                else
                {
                        reserve(_capacity * _multiplicativeCoef);
                }
	}
	ValueType* newData = new ValueType[_capacity];
	newData[pos] = value;
	for (size_t i = 0; i < pos; ++i)
        {
                newData[i] = _data[i];
        }
	for (size_t i = pos; i < _size; ++i)
        {
                newData[i+1] = _data[i];
        }
	delete[] _data;
        _data = newData;
        ++_size;
}

void Vector::insert(const ValueType* values, size_t size, size_t pos)
{
	while (_size + size > _capacity)
        {
                if (_capacity == 0)
                {
                        reserve(_multiplicativeCoef);
                }
                else
                {
                        reserve(_capacity * _multiplicativeCoef);
                }
        }
	ValueType* newData = new ValueType[_capacity];
	for (size_t i = 0; i < pos; ++i)
        {
                newData[i] = _data[i];
        }
	size_t temp = 0;
	for (size_t i = pos; i < pos + size; ++i)
        {
                newData[i] = values[temp++];
        }
	for (size_t i = pos; i < _size; ++i)
        {
                newData[i + size] = _data[i];
        }
	delete[] _data;
        _data = newData;
        _size += size;
}

void Vector::insert(const Vector& vector, size_t pos)
{
	if (vector._data == nullptr){ return; }
	if (_capacity == 0)
        {
        	reserve(_multiplicativeCoef);
       	}
	while (_size + vector._size > _capacity)
        {
                reserve(_capacity * _multiplicativeCoef);
        }
	ValueType* newData = new ValueType[_capacity];
        for (size_t i = 0; i < pos; ++i)
        {
                newData[i] = _data[i];
        }
        size_t temp = 0;
        for (size_t i = pos; i < pos + vector._size; ++i)
        {
                newData[i] = vector._data[temp++];
        }
        for (size_t i = pos; i < _size; ++i)
        {
                newData[i + vector._size] = _data[i];
        }
        delete[] _data;
        _data = newData;
        _size += vector._size;
}

void Vector::popBack()
{
	if(_size == 0)
	{
		throw std::out_of_range("Массив уже пустой!");
	}
	if (_size > 0)
	{
		--_size;
	}
}
void Vector::popFront()
{
	if (_size == 0)
        {
                throw std::out_of_range("Массив уже пустой!");
        }
	if (_size > 0)
	{
		for (size_t i = 1; i < _size; ++i)
		{
			_data[i-1] = _data[i];
		}	
		--_size;
	}
}

void Vector::erase(size_t pos, size_t count)
{
	if (_size == 0)
        {
                throw std::out_of_range("Массив уже пустой!");
        }
	if (pos < _size && count > 0)
	{
		if (pos + count >= _size)
		{
			_size = pos;
		}
		else
		{
			for (size_t i = pos; i < _size - count; ++i)
			{
				_data[i] = _data[i + count];
			}
			_size -= count;
		}
	}
}

void Vector::eraseBetween(size_t beginPos, size_t endPos)
{
	if (beginPos < endPos && _size > beginPos)
	{
		size_t count = endPos - beginPos;
		erase(beginPos, count);
	}
}

size_t Vector::size() const
{
	return _size;
}
size_t Vector::capacity() const
{
	return _capacity;
}
double Vector::loadFactor() const
{
	if (_size == 0)
	{
		return 0.0;
	}
	return 1.0 * _capacity / _size;
}

ValueType& Vector::operator[](size_t idx)
{
	if (idx >= _size)
	{
		throw std::out_of_range("Out of range");
	}
	return _data[idx];
}
const ValueType& Vector::operator[](size_t idx) const
{	
	if (idx >= _size)
        {
                throw std::out_of_range("Out of range");
        }
	return _data[idx];
}

long long Vector::find(const ValueType& value) const
{
	for (size_t i = 0; i < _size; ++i)
	{
		if (_data[i] == value)
		{
			return (long long)i;
		}
	}
	return (long long)-1;
}
Vector::Iterator::Iterator(ValueType* ptr) : _ptr(ptr) {}
ValueType& Vector::Iterator::operator*()
{
	return *_ptr;
}
const ValueType& Vector::Iterator::operator*() const
{
	return *_ptr;
}
ValueType* Vector::Iterator::operator->()
{
	return _ptr;
}
const ValueType* Vector::Iterator::operator->() const
{
	return _ptr;
}
Vector::Iterator Vector::Iterator::operator++()
{
	++_ptr;
	return *this;
}
Vector::Iterator Vector::Iterator::operator++(int)
{
	_ptr++;
	return *this;
}
bool Vector::Iterator::operator==(const Iterator& other) const
{
	if (_ptr == other._ptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool Vector::Iterator::operator!=(const Iterator& other) const
{
	if (_ptr != other._ptr)
        {
                return true;
        }
        else
        {
                return false;
        }
}

Vector::Iterator Vector::begin()
{
	return Iterator(_data);
}
Vector::Iterator Vector::end()
{
        return Iterator(_data + _size);
}
