#include <iostream>
#include <string>
#include "CustomMap.h"

int main()
{
    setlocale(LC_ALL, "");

    CustomMap<std::string, int> myMap;

    myMap.insert("Kyiv", 100);
    myMap.insert("Lviv", 80);
    myMap["Odesa"] = 90;
    myMap["Dnipro"] = 85;
    std::cout << "Size after adding: " << myMap.size() << std::endl;
    std::cout << "Size after adding: " << myMap.size() << std::endl;

    std::cout << "Score for Lviv: " << myMap["Lviv"] << std::endl;

    std::cout << "All elements: \n" << myMap << std::endl;

    std::cout << " Iterating with iterator:" << std::endl;

    for (auto it = myMap.begin(); it != myMap.end(); ++it)
    {

        std::cout << it->first << " -> " << it->second << std::endl;
    }

    std::cout << " Removing 'Kyiv'..." << std::endl;
   
    myMap.erase("Kyiv");
    std::cout << "Contents after removal: " << myMap << std::endl;
    myMap.clear();
    std::cout << "Size after clear(): " << myMap.size() << std::endl;

    return 0;
}