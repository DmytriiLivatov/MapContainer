#ifndef CUSTOM_MAP_HPP
#define CUSTOM_MAP_HPP

//////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Value>
CustomMap<Key, Value>::Node::Node(const Key& k, const Value& v, Node* p)
: key(k), value(v), left(nullptr), right(nullptr), parent(p) {}

//////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Value>
CustomMap<Key, Value>::ValueProxy::ValueProxy(Node* n)
: first(n->key), second(n->value) {
}

template <typename Key, typename Value>
typename CustomMap<Key, Value>::ValueProxy*
CustomMap<Key, Value>::ValueProxy::operator->() { return this; }

//////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Value>
CustomMap<Key, Value>::Iterator::Iterator(Node* node) 
: current(node) {}

template <typename Key, typename Value>
typename CustomMap<Key, Value>::ValueProxy
CustomMap<Key, Value>::Iterator::operator*() const
{
    return ValueProxy(current);
}

template <typename Key, typename Value>
typename CustomMap<Key, Value>::ValueProxy
CustomMap<Key, Value>::Iterator::operator->() const
{
    return ValueProxy(current);
}

template <typename Key, typename Value>
typename CustomMap<Key, Value>::Iterator&
CustomMap<Key, Value>::Iterator::operator++() 
{
    if (!current)
        return *this;

    if (current->right) 
    {
        current = current->right;
        while (current->left) current = current->left;
    }
    else {
        Node* p = current->parent;
        while (p && current == p->right)
        {
            current = p;
            p = p->parent;
        }
        current = p;
    }
    return *this;
}

template <typename Key, typename Value>
typename CustomMap<Key, Value>::Iterator
CustomMap<Key, Value>::Iterator::operator++(int)
{
    Iterator tmp = *this;
    ++(*this);
    return tmp;
}

template <typename Key, typename Value>
bool CustomMap<Key, Value>::Iterator::operator==(const Iterator& o) const
{
    return current == o.current;
}

template <typename Key, typename Value>
bool CustomMap<Key, Value>::Iterator::operator!=(const Iterator& o) const 
{
    return current != o.current;
}

//////////////////////////////////////////////////////////////////////////////////////////

template <typename Key, typename Value>
void CustomMap<Key, Value>::destroyTree(Node* node)
{
    if (!node) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

template <typename Key, typename Value>
typename CustomMap<Key, Value>::Node*
CustomMap<Key, Value>::findNode(const Key& key) const 
{
    Node* curr = root;
    while (curr) 
    {
        if (key < curr->key) curr = curr->left;
        else if (curr->key < key) curr = curr->right;
        else           
            return curr;
    }
    return nullptr;
}

template <typename Key, typename Value>
void CustomMap<Key, Value>::transplant(Node* u, Node* v)
{
    if (!u->parent)   
        root = v;
  
    else if
        (u == u->parent->left) u->parent->left = v;
  
    else  
        u->parent->right = v;
   
    if (v) 
        v->parent = u->parent;
}

template <typename Key, typename Value>
void CustomMap<Key, Value>::eraseNode(Node* node)
{
    if (!node)
        return;

    if (!node->left)
    {
        transplant(node, node->right);
    }
    else if (!node->right)
    {
        transplant(node, node->left);
    }
    else 
    {
        Node* succ = node->right;
        while (succ->left) succ = succ->left;

        if (succ->parent != node)
        {
            transplant(succ, succ->right);
            succ->right = node->right;
            succ->right->parent = succ;
        }
        transplant(node, succ);
        succ->left = node->left;
        succ->left->parent = succ;
    }

    delete node;
    --m_size;
}

template <typename Key, typename Value>
typename CustomMap<Key, Value>::Node*
CustomMap<Key, Value>::insertInternal(const Key& key, Value value) 
{
    if (!root)
    {
        root = new Node(key, std::move(value));
        m_size = 1;
        return root;
    }

    Node* curr = root;
    Node* parent = nullptr;

    while (curr) 
    {
        parent = curr;
        if (key < curr->key) curr = curr->left;
        else if (curr->key < key) curr = curr->right;
        else {
            curr->value = std::move(value);
            return curr;
        }
    }

    Node* n = new Node(key, std::move(value), parent);
   
    if (key < parent->key)
        parent->left = n;
  
    else                   
        parent->right = n;
 
    ++m_size;
    return n;
}

//////////////////////////////////////////////////////////////////////////////////////////
template <typename Key, typename Value>
CustomMap<Key, Value>::CustomMap(): root(nullptr), m_size(0) {}

template <typename Key, typename Value>
CustomMap<Key, Value>::~CustomMap() { clear(); }

template <typename Key, typename Value>
CustomMap<Key, Value>::CustomMap(const CustomMap& other): root(nullptr), m_size(0)
{
    for (auto it = other.begin(); it != other.end(); ++it)
        insertInternal(it->first, it->second);
}

template <typename Key, typename Value>
CustomMap<Key, Value>&
CustomMap<Key, Value>::operator=(const CustomMap& other)
{
    if (this != &other) 
    {
        clear();
        for (auto it = other.begin(); it != other.end(); ++it)
            insertInternal(it->first, it->second);
    }
    return *this;
}

template <typename Key, typename Value>
void CustomMap<Key, Value>::insert(const Key& key, const Value& value)
{
    insertInternal(key, value);
}

template <typename Key, typename Value>
void CustomMap<Key, Value>::erase(const Key& key)
{
    eraseNode(findNode(key));
}

template <typename Key, typename Value>
Value& CustomMap<Key, Value>::operator[](const Key& key)
{
    Node* node = findNode(key);
    if (!node) node = insertInternal(key, Value());
    return node->value;
}

template <typename Key, typename Value>
typename CustomMap<Key, Value>::Iterator
CustomMap<Key, Value>::begin() const 
{
    Node* curr = root;
   
    if (!curr)
        return Iterator(nullptr);
    
    while (curr->left) 
        curr = curr->left;
  
    return Iterator(curr);
}

template <typename Key, typename Value>
typename CustomMap<Key, Value>::Iterator
CustomMap<Key, Value>::end() const 
{
    return Iterator(nullptr);
}

template <typename Key, typename Value>
size_t CustomMap<Key, Value>::size() const { return m_size; }

template <typename Key, typename Value>
bool CustomMap<Key, Value>::empty() const { return m_size == 0; }

template <typename Key, typename Value>
void CustomMap<Key, Value>::clear()
{
    destroyTree(root);
    root = nullptr;
    m_size = 0;
}

#endif // CUSTOM_MAP_HPP