// OutfitPicker.h
#ifndef OUTFITPICKER_H
#define OUTFITPICKER_H
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

struct Wardrobe {
    vector<ClothingItem> jackets;
    vector<ClothingItem> tops;
    vector<ClothingItem> bottoms;
    vector<ClothingItem> shoes;
};

void addClothing(Wardrobe& outfits);
void printClothing(const vector<ClothingItem>& outfits);
void printWardrobe(const Wardrobe& outfits);
void removeClothing(Wardrobe& outfits);
void updateVectors(Wardrobe& src, Wardrobe& dest, const vector<ClothingItem>& stay);
void pushDatabase(const Wardrobe& src, const string& filename);
void toLower(string& input);
void updateWardrobes(Wardrobe& src, Wardrobe& dest, const Wardrobe& stay);
void pickOutfit(Wardrobe& outfits, Wardrobe& dirty, bool jacket);
vector<ClothingItem>& getType(Wardrobe& outfits, ClothingItem Item);
Wardrobe loadDatabase(const string& filename);
ClothingItem getUsersClothing();


#endif