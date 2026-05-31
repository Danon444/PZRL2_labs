#include "HashTable.h"
#include <stdexcept>

HashTable::HashTable(size_t size) noexcept : _capacity(size), _filled(0), table(size) {}

HashTable::~HashTable() {}

size_t HashTable::hash_function(const KeyType &key) const
{
	size_t hash = 0;
	size_t size = key.size();
	for (size_t i = 0; i < size; ++i)
	{
		hash = hash * 53 + int(key[i]);
	}
	return hash % _capacity;
}

void HashTable::insert(const KeyType &key, const ValueType &value)
{
	size_t bucket = hash_function(key);
	for (auto& elem : table[bucket])
	{
		if (elem.first == key)
		{
			elem.second = value;
			return;
		}
	}
	if (table[bucket].empty())
	{
		++_filled;
	}
	table[bucket].push_back({key, value});
	if (getLoadFactor() > 0.75)
	{
		auto oldTable = table;
		_capacity *= 2;
		table.clear();
		table.resize(_capacity);
		_filled = 0;
		for (auto& bucket : oldTable)
		{
			for (auto& elem : bucket)
			{
				insert(elem.first, elem.second);
			}
		}
	}
}

bool HashTable::find(const KeyType &key, ValueType &value) const
{
	size_t bucket = hash_function(key);
	for (const auto& elem : table[bucket])
	{
		if (elem.first == key)
		{
			value = elem.second;		//присваивать или проверить
			return true;
		}
	}
	return false;
}

void HashTable::remove(const KeyType &key)
{
	size_t bucket = hash_function(key);
	for (auto it = table[bucket].begin(); it != table[bucket].end(); ++it)
	{
		if (it->first == key)
		{
			table[bucket].erase(it);
			if (table[bucket].empty())
			{
				--_filled;
			}
			return;
		}
	}
}

ValueType& HashTable::operator[](const KeyType &key)
{
	size_t bucket = hash_function(key);
	for (auto& elem : table[bucket])
	{
		if (elem.first == key)
		{
			return elem.second;
		}
	}
	throw std::runtime_error("Элемент не найден!");
}

double HashTable::getLoadFactor()
{
	return _filled / _capacity;
}
