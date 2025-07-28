// OutfitPicker.h

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct ClothingItem {
    string type; // e.g., "top", "bottom", "shoes", "jacket"
    bool isLong; //true if long-sleeved or long-pants, false if short-sleeved or shorts
    string material; // e.g., "cotton", "wool", "synthetic
    string color;
    string pattern; // e.g., "solid", "striped", "plaid"

};