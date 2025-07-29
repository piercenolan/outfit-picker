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

vector<ClothingItem> loadClothingDatabase(const string& filename);
ClothingItem getUsersClothing();
void addClothing(vector<ClothingItem>& outfits);
void printClothing(const vector<ClothingItem>& outfits);
void removeClothing(vector<ClothingItem>& outfits);
void updateDatabase(vector<ClothingItem>& src, vector<ClothingItem>& dest, const vector<ClothingItem>& stay);


#endif