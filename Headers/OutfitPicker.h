#ifndef OUTFITPICKER_H
#define OUTFITPICKER_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct ClothingItem {
    string type;     // e.g., "top", "bottom", "shoes", "jacket"
    bool isLong;     // true if long-sleeved or long-pants, false otherwise
    string material; // e.g., "cotton", "wool", "synthetic"
    string color;
    string pattern;  // e.g., "solid", "striped", "plaid"
};

struct Wardrobe {
    vector<ClothingItem> jackets;
    vector<ClothingItem> tops;
    vector<ClothingItem> bottoms;
    vector<ClothingItem> shoes;
};

// Comparison operator
/* operator==
 * Compares two ClothingItem objects for equality.
 *
 * Parameters:
 *   a - first ClothingItem.
 *   b - second ClothingItem.
 *
 * Returns:
 *   true if all fields match; false otherwise.
 */
inline bool operator==(const ClothingItem& a, const ClothingItem& b) {
    return a.type == b.type &&
           a.isLong == b.isLong &&
           a.material == b.material &&
           a.color == b.color &&
           a.pattern == b.pattern;
}
// Utility functions
void toLower(string& input);
void checkBool(string& input);
void checkType(string& input);
//void checkInt(string& input);
vector<ClothingItem>& getType(Wardrobe& outfits, ClothingItem Item);

// Core functionality
Wardrobe loadDatabase(const string& filename);
ClothingItem getUsersClothing();
void addClothing(Wardrobe& outfits);
void printClothing(const vector<ClothingItem>& clothes);
void printWardrobe(const Wardrobe& outfits);
void removeClothing(Wardrobe& outfits);
void updateVectors(vector<ClothingItem>& src, vector<ClothingItem>& dest, const vector<ClothingItem>& stay);
void updateWardrobes(Wardrobe& src, Wardrobe& dest, const Wardrobe& stay);
void pushDatabase(const Wardrobe& src, const string& filename);
void pickOutfit(Wardrobe& outfits, Wardrobe& dirty, bool jacket);

#endif
