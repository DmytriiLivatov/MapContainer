#ifndef CUSTOM_MAP_H
#define CUSTOM_MAP_H

#include <cstddef>
#include <iostream>
#include <iterator>
#include <utility>


template <typename Key, typename Value>
class CustomMap 
{

    struct Node
    {
        Key key;
        Value value;
        Node* left;
        Node* right;
        Node* parent;

        Node(const Key& k, const Value& v, Node* p = nullptr);
    };

    Node* root = nullptr;
    size_t m_size = 0;
    void  destroyTree(Node* node);
    Node* findNode(const Key& key) const;
    void  transplant(Node* u, Node* v);
    void  eraseNode(Node* node);
    Node* insertInternal(const Key& key, Value value);

public:

    struct ValueProxy 
    {
        const Key& first;
        Value& second;

        explicit ValueProxy(Node* n);
        ValueProxy* operator->();
    };

    class Iterator {
        Node* current;
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = std::pair<const Key, Value>;
        using difference_type = std::ptrdiff_t;
        using pointer = ValueProxy;
        using reference = ValueProxy;

        explicit Iterator(Node* node);

        reference operator* () const;
        pointer operator->() const;

        Iterator& operator++();
        Iterator operator++(int);

        bool operator==(const Iterator& o) const;
        bool operator!=(const Iterator& o) const;
    };


    CustomMap();
    ~CustomMap();
    CustomMap(const CustomMap& other);
    CustomMap& operator=(const CustomMap& other);

    void insert(const Key& key, const Value& value);
    void erase(const Key& key);
    Value& operator[](const Key& key);

    Iterator begin() const;
    Iterator end() const;

    size_t size() const;
    bool empty() const;
    void clear();

    friend std::ostream& operator<<(std::ostream& os, const CustomMap& map)
    {
        os << "{ ";
        for (auto it = map.begin(); it != map.end(); ++it)
            os << "[" << it->first << " : " << it->second << "] ";
        return os << "}";
    }
};

#include "CustomMap.hpp"

#endif // CUSTOM_MAP_H