# Custom C++ STL-like Map Implementation (Binary Search Tree)

A template-based associative container implemented as a **Binary Search Tree (BST)**. This project demonstrates advanced C++ concepts, including manual memory management, pointer manipulation, and custom bidirectional iterators.

## Technical Overview

The `CustomMap` stores key-value pairs in a tree structure where each node consists of a key, a value, and pointers to its left child, right child, and parent. This allows for efficient searching, insertion, and ordered iteration.

### Key Features

- **Binary Search Tree Logic**: Implements core BST algorithms including `transplant` and `eraseNode` for robust element removal.
- **Associative Access**: Supports `operator[]` for both accessing and inserting elements, similar to `std::map`.
- **Memory Management**: 
    - **Rule of Three**: Fully implemented Copy Constructor, Assignment Operator, and Destructor to handle deep copies of the tree structure.
    - **Clean-up**: Recursive tree destruction to prevent memory leaks.
- **Bidirectional Iterator**: 
    - Custom `Iterator` class that performs an **In-order traversal**.
    - Uses a `ValueProxy` to provide `it->first` (Key) and `it->second` (Value) access.
    - Fully compatible with range-based `for` loops and standard algorithms.
- **Utility Methods**: `size()`, `empty()`, `clear()`, and `insert()`.
- **Formatted Output**: Overloaded `operator<<` for elegant printing of the entire map content.

## Code Structure

- `CustomMap.h`: Template class definition and internal `Node` structure.
- `CustomMap.hpp`: Implementation of template methods (Logic separation).
- `main.cpp`: Test suite demonstrating insertion, removal, and iteration.

## Implementation Details

The iterator logic handles the complex task of finding the "successor" node in a tree:
1. If a right child exists, go to the leftmost node of the right subtree.
2. Otherwise, move up to the parent until you come from a left child.



## How to Build

1. Open the project in **Visual Studio**.
2. Ensure `CustomMap.h`, `CustomMap.hpp`, and `main.cpp` are in the same directory.
3. Compile and run using the **Local Windows Debugger** (F5).

## Author
**Dmitrii Livatov** 
