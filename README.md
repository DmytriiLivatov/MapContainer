# Custom C++ STL-like Container Implementation

This repository contains a custom implementation of a template-based container in C++, designed to mimic the behavior of standard STL containers (like `std::vector` or `std::list`). This project was developed as part of a university laboratory assignment on version control systems and advanced C++ programming.

## Features

The container provides the following functionality:
- **Dynamic Memory Management**: Implements the "Rule of Three" (Destructor, Copy Constructor, and Copy Assignment Operator) to ensure deep copying and prevent memory leaks.
- **Template-based**: Supports any data type via C++ templates.
- **Size Management**: Methods to check the current size and clear the container.
- **Element Access**: Overloaded `operator[]` for intuitive element access.
- **Modifiers**: Methods to add (`push_back`) and remove (`pop_back` / `erase`) elements.
- **Stream Output**: Overloaded `operator<<` for easy printing using `std::cout`.

## Advanced Feature: Iterators
Following the "Task for the Curious," this container includes a custom **Iterator** implementation. 
- Inherits from `std::iterator` (or follows the iterator traits pattern).
- Supports standard navigation (`operator++`, `operator*`, `operator!=`).
- Compatible with range-based `for` loops.

## Project Structure

- `main.cpp`: Demonstration of the container's capabilities.
- `MyContainer.h`: Core logic and template implementation.
- `.gitignore`: Configured to exclude build artifacts and IDE-specific files (Visual Studio).

## How to Run

1. Clone the repository:
   ```bash
   git clone [https://github.com/DmitriiLivatov/ConsoleApplication3.git](https://github.com/DmitriiLivatov/ConsoleApplication3.git)
