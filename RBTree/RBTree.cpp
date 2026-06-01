#include "RBTree.h"
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <limits>
using namespace std;

static const bool RED   = false;
static const bool BLACK = true;

BinarySearchTree::Node::Node(Key key, Value value, Node *parent, Node *left, Node *right)
{
        keyValuePair.first=key;
        keyValuePair.second=value;
        this->parent = parent;
        this->left = left;
        this->right = right;
}

BinarySearchTree::Node::Node(const Node &other)
{
        keyValuePair=other.keyValuePair;
        color = other.color;
        parent = nullptr;
        if (other.left)
	{
                left = new Node(*other.left);
                left->parent = this;
        }
        else
	{
                left = nullptr;
        }
        if (other.right)
	{
                right = new Node(*other.right);
                right->parent = this;
        }
        else
	{
                right = nullptr;
        }
}

bool BinarySearchTree::Node::operator==(const Node &other) const
{
        return keyValuePair == other.keyValuePair;
}

void BinarySearchTree::Node::output_node_tree() const
{
        if (left)
	{
                left->output_node_tree();
        }
        if (keyValuePair.first != std::numeric_limits<Key>::max())
	{
                std::cout << keyValuePair.first << " : " << keyValuePair.second << std::endl;
        }
        if (right)
	{
                right->output_node_tree();
        }
}

void BinarySearchTree::Node::insert(const Key &, const Value &){}
void BinarySearchTree::Node::erase(const Key &){}

void BinarySearchTree::clear(Node* node)
{
        if (node == nullptr)
	{
                return;
        }
        clear(node->left);
        clear(node->right);
        delete node;
}

BinarySearchTree::~BinarySearchTree()
{
        clear(_root);
        _root = nullptr;
        _size = 0;
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &other)
{
        _size = other._size;
        if (other._root)
	{
                _root = new Node(*other._root);
        }
        else
	{
                _root = nullptr;
        }
}

BinarySearchTree& BinarySearchTree::operator=(const BinarySearchTree& other)
{
        if (this != &other)
	{
                BinarySearchTree temp(other);
                swap(_root, temp._root);
                swap(_size, temp._size);
        }
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
        if (this != &other)
	{
                clear(_root);
                _root = other._root;
                _size = other._size;
                other._root = nullptr;
                other._size = 0;
        }
        return *this;
}

BinarySearchTree::Iterator::Iterator(Node *node)
{
        _node=node;
}

pair<Key, Value>& BinarySearchTree::Iterator::operator*()
{
        if (!_node)
	{
                throw runtime_error("Null ptr");
        }
        return _node->keyValuePair;
}

const pair<Key, Value>& BinarySearchTree::Iterator::operator*() const
{
        if (!_node)
	{
                throw runtime_error("Null ptr");
        }
        return _node->keyValuePair;
}

pair<Key, Value>* BinarySearchTree::Iterator::operator->()
{
        if (!_node)
	{
                throw runtime_error("Null ptr");
        }
        return &_node->keyValuePair;
}

const pair<Key, Value>* BinarySearchTree::Iterator::operator->() const
{
        if (!_node)
	{
                throw runtime_error("Null ptr");
        }
        return &_node->keyValuePair;
}

bool BinarySearchTree::Iterator::operator==(const Iterator &other) const
{
        return _node==other._node;
}

bool BinarySearchTree::Iterator::operator!=(const Iterator &other) const
{
        return _node!=other._node;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator++()
{
        if (!_node)
	{
                throw runtime_error("Null ptr");
        }
        if (_node->keyValuePair.first == std::numeric_limits<Key>::max() && !_node->right)
	{
                throw runtime_error("Итератор уже в конце");
        }
        if (_node->right)
	{
                _node=_node->right;
                while(_node->left)
		{
                        _node = _node->left;
                }
        }
        else
	{
                Node* p = _node->parent;
                while(p && _node==p->right)
		{
                        _node = p;
                        p=p->parent;
                }
                _node=p;
        }
        return *this;
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
	{
                throw runtime_error("Итератор уже в конце");
        }
        if (_node->left)
	{
                _node=_node->left;
                while(_node->right)
		{
                        _node = _node->right;
                }
        }
        else
	{
                Node* p = _node->parent;
                while(p && _node==p->left)
		{
                        _node = p;
                        p=p->parent;
                }
                _node=p;
        }
        return *this;
}

BinarySearchTree::Iterator BinarySearchTree::Iterator::operator--(int)
{
        Iterator temp = *this;
        --(*this);
        return temp;
}

BinarySearchTree::ConstIterator::ConstIterator(const Node *node)
{
        _node=node;
}

const pair<Key, Value>& BinarySearchTree::ConstIterator::operator*() const
{
        if (!_node)
	{
                throw runtime_error("Null ptr");
        }
        return _node->keyValuePair;
}

const pair<Key, Value>* BinarySearchTree::ConstIterator::operator->() const
{
        if (!_node)
	{
                throw runtime_error("Null ptr");
        }
        return &_node->keyValuePair;
}

bool BinarySearchTree::ConstIterator::operator==(const ConstIterator &other) const
{
        return _node==other._node;
}

bool BinarySearchTree::ConstIterator::operator!=(const ConstIterator &other) const
{
        return _node!=other._node;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator++()
{
        if (!_node)
	{
                throw runtime_error("Null ptr");
        }
        if (_node->keyValuePair.first == std::numeric_limits<Key>::max() && !_node->right)
	{
                throw runtime_error("Итератор уже в конце");
        }
        if (_node->right)
	{
                _node=_node->right;
                while(_node->left)
		{
                        _node = _node->left;
                }
        }
        else
	{
                const Node* p = _node->parent;
                while(p && _node==p->right)
		{
                        _node = p;
                        p=p->parent;
                }
                _node=p;
        }
        return *this;
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
	{
                throw runtime_error("Null ptr");
        }
        if (_node->left)
	{
                _node=_node->left;
                while(_node->right)
		{
                        _node = _node->right;
                }
        }
        else
	{
                const Node* p = _node->parent;
                while(p && _node==p->left){
                        _node = p;
                        p=p->parent;
                }
                _node=p;
        }
        return *this;
}

BinarySearchTree::ConstIterator BinarySearchTree::ConstIterator::operator--(int)
{
        ConstIterator temp = *this;
        --(*this);
        return temp;
}

pair<BinarySearchTree::Iterator, BinarySearchTree::Iterator> BinarySearchTree::equalRange(const Key &key)
{
        Iterator first = find(key);
        if (first == end())
	{
                return {end(), end()};
        }
        Iterator last = first;
        while (last != end() && last->first == key)
	{
                ++last;
        }
        return {first, last};
}

pair<BinarySearchTree::ConstIterator, BinarySearchTree::ConstIterator> BinarySearchTree::equalRange(const Key &key) const
{
        ConstIterator first = find(key);
        if (first == cend())
	{
                return {cend(), cend()};
        }
        ConstIterator last = first;
        while (last != cend() && last->first == key)
	{
                ++last;
        }
        return {first, last};
}

BinarySearchTree::Iterator BinarySearchTree::end()
{
        if (!_root)
	{
                return Iterator(nullptr);
        }
        Node* current = _root;
        while (current->right)
	{
                current = current->right;
        }
        return Iterator(current);
}

BinarySearchTree::ConstIterator BinarySearchTree::cend() const
{
        if (!_root)
	{
                return ConstIterator(nullptr);
        }
        Node* current = _root;
        while (current->right)
	{
                current = current->right;
        }
        return ConstIterator(current);
}

BinarySearchTree::Iterator BinarySearchTree::begin()
{
        if (_root == nullptr)
	{
                return end();
        }
        Node* current = _root;
        while (current->left)
        {
                current = current->left;
        }
        return Iterator(current);
}

BinarySearchTree::ConstIterator BinarySearchTree::cbegin() const
{
        if (_root == nullptr)
	{
                return cend();
        }
        Node* current = _root;
        while (current->left)
        {
                current = current->left;
        }
        return ConstIterator(current);
}

BinarySearchTree::Iterator BinarySearchTree::find(const Key &key)
{
        Node* current = _root;
        Node* match = nullptr;
        while (current)
	{
                if (key < current->keyValuePair.first)
		{
                        current = current->left;
                }
                else if (key > current->keyValuePair.first)
		{
                        current = current->right;
                }
                else
		{
                        match = current;
                        current = current->left;
                }
        }
        if (match)
	{
                return Iterator(match);
        }
        return end();
}

BinarySearchTree::ConstIterator BinarySearchTree::find(const Key &key) const
{
        Node* current = _root;
        Node* match = nullptr;
        while (current)
	{
                if (key < current->keyValuePair.first)
		{
                        current = current->left;
                }
                else if (key > current->keyValuePair.first)
		{
                        current = current->right;
                }
                else
		{
                        match = current;
                        current = current->left;
                }
        }
        if (match)
	{
                return ConstIterator(match);
        }
        return cend();
}

BinarySearchTree::ConstIterator BinarySearchTree::min() const
{
        return cbegin();
}

BinarySearchTree::ConstIterator BinarySearchTree::min(const Key &key) const
{
        ConstIterator temp1 = find(key);
        if (temp1 == cend())
	{
                return cend();
        }
        ConstIterator temp2 = temp1;
        ++temp1;
        while (temp1 != cend() && temp1->first == key)
	{
                if (temp1->second < temp2->second){
                        temp2 = temp1;
                }
                ++temp1;
        }
        return temp2;
}

BinarySearchTree::ConstIterator BinarySearchTree::max() const
{
        if (!_root)
	{
                return cend();
        }
        return --cend();
}

BinarySearchTree::ConstIterator BinarySearchTree::max(const Key &key) const
{
        ConstIterator temp1 = find(key);
        if (temp1 == cend())
	{
                return cend();
        }
        ConstIterator temp2 = temp1;
        ++temp1;
        while (temp1 != cend() && temp1->first == key)
	{
                if (temp1->second > temp2->second)
		{
                        temp2 = temp1;
                }
                ++temp1;
        }
        return temp2;
}

BinarySearchTree::Node* BinarySearchTree::detachSentinel()
{
        if (!_root)
	{
                return nullptr;
        }
        Node* cur = _root;
        while (cur->right)
	{
                cur = cur->right;
        }
        if (cur->keyValuePair.first != std::numeric_limits<Key>::max())
	{
                return nullptr;
        }
        Node* sent = cur;
        if (sent->parent)
	{
                sent->parent->right = nullptr;
                sent->parent = nullptr;
        }
        else
	{
                _root = nullptr;
        }
        return sent;
}

void BinarySearchTree::attachSentinel(Node* sent)
{
        if (!sent)
	{
                return;
        }
        sent->color = BLACK;
        sent->left = nullptr;
        sent->right = nullptr;
        if (!_root)
	{
                _root = sent;
                sent->parent = nullptr;
                return;
        }
        Node* cur = _root;
        while (cur->right)
	{
                cur = cur->right;
        }
        cur->right = sent;
        sent->parent = cur;
}

void BinarySearchTree::rotateLeft(Node* a)
{
        Node* b = a->right;
        a->right = b->left;
        if (b->left)
	{
                b->left->parent = a;
        }
        b->parent = a->parent;
        if (!a->parent)
	{
                _root = b;
        }
        else if (a == a->parent->left)
	{
                a->parent->left = b;
        }
        else
	{
                a->parent->right = b;
        }
        b->left = a;
        a->parent = b;
}

void BinarySearchTree::rotateRight(Node* a)
{
        Node* b = a->left;
        a->left = b->right;
        if (b->right)
	{
                b->right->parent = a;
        }
        b->parent = a->parent;
        if (!a->parent)
	{
                _root = b;
        }
        else if (a == a->parent->right)
	{
                a->parent->right = b;
        }
        else
	{
                a->parent->left = b;
        }
        b->right = a;
        a->parent = b;
}

void BinarySearchTree::insertFixup(Node* node)
{
        while (node->parent && node->parent->color == RED)
	{
                Node* grandparent = node->parent->parent;
                if (!grandparent)
		{
                        break;
                }
                if (node->parent == grandparent->left)
		{
                        Node* uncle = grandparent->right;
                        if (uncle && uncle->color == RED)
			{
                                node->parent->color = BLACK;
                                uncle->color = BLACK;
                                grandparent->color = RED;
                                node = grandparent;
                        }
                        else
			{
                                if (node == node->parent->right)
				{
                                        node = node->parent;
                                        rotateLeft(node);
                                }
                                node->parent->color = BLACK;
                                node->parent->parent->color = RED;
                                rotateRight(node->parent->parent);
                        }
                }
                else
		{
                        Node* uncle = grandparent->left;
                        if (uncle && uncle->color == RED)
			{
                                node->parent->color = BLACK;
                                uncle->color = BLACK;
                                grandparent->color = RED;
                                node = grandparent;
                        }
                        else
			{
                                if (node == node->parent->left)
				{
                                        node = node->parent;
                                        rotateRight(node);
                                }
                                node->parent->color = BLACK;
                                node->parent->parent->color = RED;
                                rotateLeft(node->parent->parent);
                        }
                }
        }
        if (_root)
	{
                _root->color = BLACK;
        }
}

void BinarySearchTree::insert(const Key &key, const Value &value)
{
        if (key == std::numeric_limits<Key>::max())
	{
                throw std::invalid_argument("Ключ уперся вправо");
        }
        Node* sent = detachSentinel();

        Node* newNode = new Node(key, value);
        newNode->color = RED;

        Node* trailing = nullptr;
        Node* current = _root;
        while (current)
	{
                trailing = current;
                if (key < current->keyValuePair.first)
		{
                        current = current->left;
                }
                else
		{
                        current = current->right;
                }
        }
        newNode->parent = trailing;
        if (!trailing)
	{
                _root = newNode;
        }
        else if (key < trailing->keyValuePair.first)
	{
                trailing->left = newNode;
        }
        else
	{
                trailing->right = newNode;
        }

        insertFixup(newNode);

        if (!sent)
	{
                sent = new Node(std::numeric_limits<Key>::max(), Value());
        }
        attachSentinel(sent);

        ++_size;
}

void BinarySearchTree::transplant(Node* target, Node* source)
{
        if (!target->parent)
	{
                _root = source;
        }
        else if (target == target->parent->left)
	{
                target->parent->left = source;
        }
        else
	{
                target->parent->right = source;
        }
        if (source)
	{
                source->parent = target->parent;
        }
}

BinarySearchTree::Node* BinarySearchTree::minNode(Node* node) const
{
        while (node && node->left)
	{
                node = node->left;
        }
        return node;
}

void BinarySearchTree::eraseFixup(Node* node, Node* nodeParent)
{
        while (node != _root && (node == nullptr || node->color == BLACK))
	{
                if (nodeParent == nullptr)
		{
                        break;
                }
                if (node == nodeParent->left)
		{
                        Node* sibling = nodeParent->right;
                        if (sibling && sibling->color == RED)
			{
                                sibling->color = BLACK;
                                nodeParent->color = RED;
                                rotateLeft(nodeParent);
                                sibling = nodeParent->right;
                        }
                        bool leftBlack = (!sibling || !sibling->left  || sibling->left->color  == BLACK);
                        bool rightBlack = (!sibling || !sibling->right || sibling->right->color == BLACK);
                        if (leftBlack && rightBlack)
			{
                                if (sibling)
				{
                                        sibling->color = RED;
                                }
                                node = nodeParent;
                                nodeParent = node ? node->parent : nullptr;
                        }
                        else
			{
                                if (rightBlack)
				{
                                        if (sibling && sibling->left)
					{
                                                sibling->left->color = BLACK;
                                        }
                                        if (sibling)
					{
                                                sibling->color = RED;
                                                rotateRight(sibling);
                                        }
                                        sibling = nodeParent->right;
                                }
                                if (sibling)
				{
                                        sibling->color = nodeParent->color;
                                }
                                nodeParent->color = BLACK;
                                if (sibling && sibling->right)
				{
                                        sibling->right->color = BLACK;
                                }
                                rotateLeft(nodeParent);
                                node = _root;
                                break;
                        }
                }
                else
		{
                        Node* sibling = nodeParent->left;
                        if (sibling && sibling->color == RED)
			{
                                sibling->color = BLACK;
                                nodeParent->color = RED;
                                rotateRight(nodeParent);
                                sibling = nodeParent->left;
                        }
                        bool rightBlack = (!sibling || !sibling->right || sibling->right->color == BLACK);
                        bool leftBlack = (!sibling || !sibling->left  || sibling->left->color  == BLACK);
                        if (rightBlack && leftBlack)
			{
                                if (sibling)
				{
                                        sibling->color = RED;
                                }
                                node = nodeParent;
                                nodeParent = node ? node->parent : nullptr;
                        }
                        else
			{
                                if (leftBlack)
				{
                                        if (sibling && sibling->right)
					{
                                                sibling->right->color = BLACK;
                                        }
                                        if (sibling)
					{
                                                sibling->color = RED;
                                                rotateLeft(sibling);
                                        }
                                        sibling = nodeParent->left;
                                }
                                if (sibling)
				{
                                        sibling->color = nodeParent->color;
                                }
                                nodeParent->color = BLACK;
                                if (sibling && sibling->left)
				{
                                        sibling->left->color = BLACK;
                                }
                                rotateRight(nodeParent);
                                node = _root;
                                break;
                        }
                }
        }
        if (node)
	{
                node->color = BLACK;
        }
}

void BinarySearchTree::erase(const Key &key)
{
        if (!_root)
	{
                return;
        }
        if (key == std::numeric_limits<Key>::max())
	{
                return;
        }
        Node* sent = detachSentinel();

        while (_root)
	{
                Node* toErase = _root;
                while (toErase)
		{
                        if (key < toErase->keyValuePair.first)
			{
                                toErase = toErase->left;
                        }
                        else if (key > toErase->keyValuePair.first)
			{
                                toErase = toErase->right;
                        }
                        else
			{
                                break;
                        }
                }
                if (!toErase)
		{
                        break;
                }

                Node* replacement = toErase;
                bool originalColor = replacement->color;
                Node* fixNode = nullptr;
                Node* fixParent = nullptr;

                if (!toErase->left)
		{
                        fixNode = toErase->right;
                        fixParent = toErase->parent;
                        transplant(toErase, toErase->right);
                }
                else if (!toErase->right)
		{
                        fixNode = toErase->left;
                        fixParent = toErase->parent;
                        transplant(toErase, toErase->left);
                }
                else
		{
                        replacement = minNode(toErase->right);
                        originalColor = replacement->color;
                        fixNode = replacement->right;
                        if (replacement->parent == toErase)
			{
                                fixParent = replacement;
                        }
                        else
			{
                                fixParent = replacement->parent;
                                transplant(replacement, replacement->right);
                                replacement->right = toErase->right;
                                replacement->right->parent = replacement;
                        }
                        transplant(toErase, replacement);
                        replacement->left = toErase->left;
                        replacement->left->parent = replacement;
                        replacement->color = toErase->color;
                }

                delete toErase;
                --_size;

                if (originalColor == BLACK && _root)
		{
                        eraseFixup(fixNode, fixParent);
                }
        }

        if (_root)
	{
                attachSentinel(sent);
        }
        else
	{
                delete sent;
        }
}

size_t BinarySearchTree::size() const
{
        return _size;
}

void BinarySearchTree::output_tree() 
{
        if (!_root)
	{
                return;
        }
        _root->output_node_tree();
}

size_t BinarySearchTree::heightImpl(Node* node) const
{
        if (!node)
	{
                return 0;
        }
        if (node->keyValuePair.first == std::numeric_limits<Key>::max())
	{
                return 0;
        }
        size_t leftHeight = heightImpl(node->left);
        size_t rightHeight = heightImpl(node->right);
        return 1 + std::max(leftHeight, rightHeight);
}

size_t BinarySearchTree::max_height() const
{
        return heightImpl(_root);
}
