#include "BST.h"
#include <iostream>
#include <limits>

BinarySearchTree::Node::Node(Key key, Value value, Node *parent, Node *left, Node *right) : keyValuePair(key, value), parent(parent), left(left), right(right) {}

BinarySearchTree::Node::Node(const Node &other) : keyValuePair(other.keyValuePair)
{
	if (other.left)
	{
		left = new Node(*other.left);
		left->parent = this;
	}
	if (other.right)
	{
		right = new Node(*other.right);
		right->parent = this;
	}
}
bool BinarySearchTree::Node::operator==(const Node &other) const
{
	if (other.keyValuePair == keyValuePair)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BinarySearchTree::Node::output_node_tree() const
{
	if (left)
	{
		left->output_node_tree();
	}
	if (this->keyValuePair.first == std::numeric_limits<Key>::max())
	{	
		return;
	}
	std::cout << "Key: " << keyValuePair.first << ":" << "Value: " << keyValuePair.second << std::endl;
	if (right)
	{
		right->output_node_tree();
	}
}

void BinarySearchTree::Node::insert(const Key &key, const Value &value)
{
	if (key < keyValuePair.first)
	{
		if (left)
		{
			left->insert(key, value);
		}
		else
		{
			left = new Node(key, value, this);
		}
	}
	else
	{
		if (right)
		{
			right->insert(key, value);
		}
		else
		{
			right = new Node(key, value, this);
		}
	}
}

void BinarySearchTree::Node::erase(const Key &key)
{
	if (key < keyValuePair.first)
	{
		if (left)
		{
			left->erase(key);
		}
	}
	else if (key > keyValuePair.first)
	{
		if (right)
		{
			right->erase(key);
		}
	}
	else
	{
		if (!left && !right)
		{
			if (parent)
			{
				if (parent->left == this)
				{
					parent->left = nullptr;
				}
				else
				{
					parent->right = nullptr;
				}
			}
			delete this;
		}
		else if (!right)
		{
			left->parent = parent;
			if (parent)
			{
				if (parent->left == this)
				{
					parent->left = left;
				}
				else
				{
					parent->right = left;
				}
			}
			delete this;
		}
		else if (!left)
		{
			right->parent = parent;
			if (parent)
			{
				if (parent->left == this)
				{
					parent->left = right;
				}		
				else
				{
					parent->right = right;
				}
			}
			delete this;
		}
		else
		{
			Node *minNode = right;
			while (minNode->left)
			{
				minNode = minNode->left;
			}
			keyValuePair = minNode->keyValuePair;
			minNode->erase(minNode->keyValuePair.first);
		}
	}
}
void BinarySearchTree::freeSubtree(BinarySearchTree::Node* node) 
{ 
	if (!node)
	       	return;
	freeSubtree(node->left); 
	freeSubtree(node->right); 
	delete node;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other) : _size(other._size)
{
	if (other._root)
	{
		_root = new Node(*other._root);
	}
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree &other)
{
	if (this == &other)
	{
		return *this;
	}

	freeSubtree(_root);
	
	_root = nullptr;

	if (other._root)
	{
		_root = new Node(*other._root);
	}
	_size = other._size;
	return *this;
}

BinarySearchTree::BinarySearchTree(BinarySearchTree &&other) noexcept
{
	_root = other._root;
	_size = other._size;
	other._root = nullptr;
	other._size = 0;
}

BinarySearchTree& BinarySearchTree::operator=(BinarySearchTree &&other) noexcept
{
	if (this == &other)
	{
		return *this;
	}

	freeSubtree(_root);
	_root = other._root;
	_size = other._size;
	other._root = nullptr;
	other._size = 0;

	return *this;
}

BinarySearchTree::~BinarySearchTree()
{
	freeSubtree(_root);
}

BinarySearchTree::Iterator::Iterator(Node* node) : _node(node) {}

std::pair<Key, Value>& BinarySearchTree::Iterator::operator*()
{
	if (!_node)
		throw std::runtime_error("Null iterator!");
	return _node->keyValuePair;
}

const std::pair<Key, Value>& BinarySearchTree::Iterator::operator*() const
{
	if (!_node)
		throw std::runtime_error("Null inerator!");
	return _node->keyValuePair;
}

std::pair<Key, Value>* BinarySearchTree::Iterator::operator->()
{
	if (!_node)
		throw std::runtime_error("Null iterator!");
	return &_node->keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::Iterator::operator->() const
{
	if (!_node)
		throw std::runtime_error("Null iterator!");
	return &_node->keyValuePair;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++()
{
	if (!_node)
		throw std::runtime_error("Null iterator!");
	if (_node->right)
	{
		_node = _node->right;
		while (_node->left)
		{
			_node=_node->left;
		}
		return *this;
	}
	Node* _parent = _node->parent;
	while (_parent)
	{
		if (_node == _parent->left)
		{
			_node = _parent;
			return *this;
		}
		_node = _parent;
		_parent = _parent->parent;
	}
	throw std::runtime_error("Iterator in end");
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++(int)
{
	Iterator temp = *this;
	++(*this);
	return temp;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--()
{
	if (!_node)
		throw std::runtime_error("Null iterator!");
	if (_node->left)
	{
		_node = _node->left;
		while (_node->right)
		{
			_node=_node->right;
		}
		return *this;
	}
	Node* _parent = _node->parent;
	while (_parent)
	{
		if (_node == _parent->right)
		{
			_node = _parent;
			return *this;
		}
		_node = _parent;
		_parent = _parent->parent;
	}
	throw std::runtime_error("Iterator in end");
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int)
{
	Iterator temp = *this;
	--(*this);
	return temp;
}

bool BinarySearchTree::Iterator::operator==(const Iterator &other) const
{
	if (_node == other._node)
		return true;
	else
		return false;
}

bool BinarySearchTree::Iterator::operator!=(const Iterator &other) const
{
	if (_node != other._node)
		return true;
	else
		return false;
}

BinarySearchTree::ConstIterator::ConstIterator(const Node *node) : _node(node) {}

const std::pair<Key, Value>& BinarySearchTree::ConstIterator::operator*() const
{
	if (!_node)
		throw std::runtime_error("Null inerator!");
	return _node->keyValuePair;
}

const std::pair<Key, Value>* BinarySearchTree::ConstIterator::operator->() const
{
	if (!_node)
		throw std::runtime_error("Null iterator!");
	return &_node->keyValuePair;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++()
{
	if (!_node)
		throw std::runtime_error("Null iterator!");
	if (_node->right)
	{
		_node = _node->right;
		while (_node->left)
		{
			_node=_node->left;
		}
		return *this;
	}
	Node* _parent = _node->parent;
	while (_parent)
	{
		if (_node == _parent->left)
		{
			_node = _parent;
			return *this;
		}
		_node = _parent;
		_parent = _parent->parent;
	}
	throw std::runtime_error("Iterator in end");
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++(int)
{
	ConstIterator temp = *this;
	++(*this);
	return temp;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--()
{
	if (!_node)
		throw std::runtime_error("Null iterator!");
	if (_node->left)
	{
		_node = _node->left;
		while (_node->right)
		{
			_node=_node->right;
		}
		return *this;
	}
	Node* _parent = _node->parent;
	while (_parent)
	{
		if (_node == _parent->right)
		{
			_node = _parent;
			return *this;
		}
		_node = _parent;
		_parent = _parent->parent;
	}
	throw std::runtime_error("Iterator in end");
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int)
{
	ConstIterator temp = *this;
	--(*this);
	return temp;
}

bool BinarySearchTree::ConstIterator::operator==(const ConstIterator &other) const
{
	if (_node == other._node)
		return true;
	else
		return false;
}

bool BinarySearchTree::ConstIterator::operator!=(const ConstIterator &other) const
{
	if (_node != other._node)
		return true;
	else
		return false;
}

void BinarySearchTree::insert(const Key &key, const Value &value)
{
	if (!_root)
	{
		_root = new Node(key, value);
		_root->right = new Node(std::numeric_limits<Key>::max(), value, _root);
	}
	else
	{
		_root->insert(key, value);
	}
	++_size;
}

void BinarySearchTree::erase(const Key &key)
{
	if (!_root)
		return;
	Iterator temp(_root);
	while ((temp = find(key)) != end())
	{
		temp._node->erase(key);
		--_size;
	}
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const
{
	const Node* current = _root;
	while (current)
	{
		if (current->keyValuePair.first < key)
		{
			current = current->right;
		}
		else if (current->keyValuePair.first > key)
		{
			current = current->left;
		}
		else
		{
			return ConstIterator(current);
		}
	}
	return cend();
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key &key)
{
	Node* current = _root;
	while (current)
	{
		if (current->keyValuePair.first < key)
		{
			current = current->right;
		}
		else if (current->keyValuePair.first > key)
		{
			current = current->left;
		}
		else
		{
			return Iterator(current);
		}
	}
	return end();
}

std::pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key)
{
	Iterator first = find(key);
	if (first == end())
	{
		return {end(),end()};
	}
	Iterator second = first;
	while (second != end() && (*second).first == key)
	{
		++second;
	}
	return {first, second};
}

std::pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key &key) const
{
	ConstIterator first = find(key);
	if (first == cend())
	{
		return {cend(),cend()};
	}
	ConstIterator second = first;
	while (second != cend() && (*second).first == key)
	{
		++second;
	}
	return {first, second};
}

BinarySearchTree::ConstIterator BinarySearchTree::min() const
{
	return cbegin();
}

BinarySearchTree::ConstIterator BinarySearchTree::max() const
{
	return --cend();
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const
{
	std::pair<ConstIterator, ConstIterator> temp = equalRange(key);
	if (temp.first == cend())
	{
		return cend();
	}
	ConstIterator m = temp.first;
	for (auto i = temp.first; i != temp.second; ++i)
	{
		if (m->second > i->second)
		{
			m = i;
		}
	}
	return m;
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const
{
	std::pair<ConstIterator, ConstIterator> temp = equalRange(key);
	if (temp.first == cend())
	{
		return cend();
	}
	ConstIterator m = temp.first;
	for (auto i = temp.first; i != temp.second; ++i)
	{
		if (m->second < i->second)
		{
			m = i;
		}
	}
	return m;
}

BinarySearchTree::Iterator BinarySearchTree::begin()
{
	Node *temp = _root;
	while (temp->left)
	{
		temp = temp->left;
	}
	return Iterator(temp);
}

BinarySearchTree::Iterator BinarySearchTree::end()
{
	Node *temp = _root;
	while (temp->right)
	{
		temp = temp->right;
	}
	return Iterator(temp);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const
{
	Node *temp = _root;
	while (temp->left)
	{
		temp = temp->left;
	}
	return ConstIterator(temp);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const
{
	Node *temp = _root;
	while (temp->right)
	{
		temp = temp->right;
	}
	return ConstIterator(temp);
}

size_t BinarySearchTree::size() const
{
	return _size;
}

void BinarySearchTree::output_tree()
{
	if (_root)
	{
		_root->output_node_tree();
	}
}
