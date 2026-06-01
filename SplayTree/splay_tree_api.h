#pragma once
#include <cstddef>
#include <utility>

/**
 * @brief Класс SplayTree — самобалансирующееся дерево поиска (splay tree).
 * 
 * @tparam Key Тип ключа (должен поддерживать сравнение).
 * @tparam Value Тип значения.
 */
template<typename Key, typename Value>
class SplayTree 
{
private:
	struct Node
	{
		std::pair<Key, Value> keyValuePair;
		Node* parent = nullptr;
		Node* left = nullptr;
		Node* right = nullptr;
		Node(Key key, Value value, Node *parent = nullptr, Node *left = nullptr, Node *right = nullptr) : keyValuePair(key, value), parent(parent), left(left), right(right) {}
	};
	Node* _root;
	size_t _size;
	void rotateLeft(Node* a)
	{
		Node* b = a->right;
		if (!b) 
			return;
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
	void rotateRight(Node* a)
	{
		Node* b = a->left;
		if (!b) 
			return;
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
	void splay(Node* node)
	{
		while (node && node->parent)
		{
			Node* parent = node->parent;
			Node* grandp = parent->parent;
			if (!grandp)
			{
				if (node == parent->left)
					rotateRight(parent);
				else
					rotateLeft(parent);
			}
			else if (node == parent->left && parent == grandp->left)
			{
				rotateRight(grandp);
				rotateRight(parent);
			}
			else if (node == parent->right && parent == grandp->right)
			{
				rotateLeft(grandp);
				rotateLeft(parent);
			}
			else if (node == parent->left && parent == grandp->right)
			{
				rotateRight(parent);
				rotateLeft(grandp);
			}
			else
			{
				rotateLeft(parent);
				rotateRight(grandp);
			}
		}
	}
	Node* findNode(const Key& key) 
	{
		Node* current = _root;
		Node* last = nullptr;
		while (current) 
		{
			last = current;
			if (key < current->keyValuePair.first) 
				current = current->left;
			else if (key > current->keyValuePair.first) 
				current = current->right;
			else 
			{
				splay(current);
				return current;
			}
		}
		if (last)
		       	splay(last);
		return nullptr;
	}
	Node* findNodeConst(const Key& key) const 
	{
		Node* current = _root;
		while (current)
		{
			if (key < current->keyValuePair.first)
			       	current = current->left;
			else if (key > current->keyValuePair.first) 
				current = current->right;
			else 
				return current;
		}
		return nullptr;
	}
	void clear(Node* node)
       	{
		if (!node)
			return;
		clear(node->left);
		clear(node->right);
		delete node;
	}
	bool validateBST(Node* node, const Node* minNode, const Node* maxNode) const 
	{
		if (!node) 
			return true;
		if (minNode && !(minNode->keyValuePair.first < node->keyValuePair.first))
		       	return false;
		if (maxNode && !(maxNode->keyValuePair.first > node->keyValuePair.first))
		       	return false;
		return validateBST(node->left, minNode, node) && validateBST(node->right, node, maxNode);
	}

public:
    /**
     * @brief Конструктор по умолчанию. Создаёт пустое дерево.
     */
    SplayTree() : _root(nullptr), _size(0) {}

    /**
     * @brief Деструктор. Очищает все ресурсы, связанные с деревом.
     */
    ~SplayTree()
    {
	    clear(_root);
    }

    /**
     * @brief Вставляет пару (key, value) в дерево.
     * Если ключ уже существует, его значение обновляется.
     * После вставки/обновления соответствующий узел становится корнем (splay).
     * 
     * @param key Ключ для вставки.
     * @param value Значение для вставки.
     */
    void insert(const Key& key, const Value& value)
    {
	    if (!_root)
	    {
		    _root = new Node(key, value);
		    _size++;
		    return;
	    }
	    Node* current = _root;
	    Node* parent = nullptr;
	    while (current)
	    {
		    parent = current;
		    if (key < current->keyValuePair.first)
			    current = current->left;
		    else if (key > current->keyValuePair.first)
			    current = current->right;
		    else
		    {
			    current->keyValuePair.second = value;
			    splay(current);
			    return;
		    }
	    }
	    Node* newNode = new Node(key, value);
	    newNode->parent = parent;
	    if (key < parent->keyValuePair.first)
		    parent->left = newNode;
	    else
		    parent->right = newNode;
	    _size++;
	    splay(newNode);
    }

    /**
     * @brief Удаляет узел с заданным ключом из дерева.
     * 
     * @param key Ключ для удаления.
     * @return true если элемент был найден и удалён, false если такого ключа нет.
     */
    bool remove(const Key& key)
    {
	    Node* node = findNode(key);
	    if (!node)
		    return false;
	    splay(node);
	    Node* leftSubtree = node->left;
	    Node* rightSubtree = node->right;
	    if (leftSubtree)
		    leftSubtree->parent = nullptr;
	    if (rightSubtree)
		    rightSubtree->parent = nullptr;
	    delete node;
	    _size--;
	    if (!leftSubtree)
	    {
		    _root = rightSubtree;
	    }
	    else 
	    {
		    _root = leftSubtree;
		    Node* maxNode = leftSubtree;
		    while (maxNode->right)
		    {
			    maxNode = maxNode->right;
		    }
		    splay(maxNode);
		    _root->right = rightSubtree;
		    if (rightSubtree)
		    {
			    rightSubtree->parent = _root;
		    }
	    }
	    return true;
    }
    /**
     * @brief Ищет элемент по ключу.
     * Если найден, возвращает указатель на значение (Value*), иначе nullptr.
     * После поиска найденный (или последний просмотренный) узел становится корнем (splay).
     * 
     * @param key Ключ для поиска.
     * @return Value* Указатель на значение или nullptr.
     */
    Value* search(const Key& key)
    {
	    Node* node = findNode(key);
	    if (node)
		    return &node->keyValuePair.second;
	    else
		    return nullptr;
    }
    /**
     * @brief Константная версия поиска.
     * Не изменяет структуру дерева.
     * 
     * @param key Ключ для поиска.
     * @return const Value* Указатель на значение или nullptr.
     */
    const Value* search(const Key& key) const
    {
	    Node* node = findNodeConst(key);
	    if (node)  
		    return &node->keyValuePair.second;
	    else
		    return nullptr;
    }

    /**
     * @brief Проверяет, что дерево удовлетворяет свойству бинарного дерева поиска (BST).
     * 
     * @return true если дерево корректно, false иначе.
     */
    bool isValidBST() const
    {
	    return validateBST(_root, nullptr, nullptr);
    }

    /**
     * @brief Возвращает количество элементов в дереве.
     * 
     * @return size_t Количество элементов.
     */
    size_t size() const
    {
	    return _size;
    }

    /**
     * @brief Проверяет, пусто ли дерево.
     * 
     * @return true если дерево пустое, false иначе.
     */
    bool empty() const
    {
	    if (_size == 0)
		    return true;
	    else
		    return false;
    }
};
