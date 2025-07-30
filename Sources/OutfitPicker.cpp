// OutfitPicker.cpp
#include "../Headers/OutfitPicker.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>

using namespace std;


inline bool operator==(const ClothingItem& a, const ClothingItem& b) {
    return a.type == b.type &&
           a.isLong == b.isLong &&
           a.material == b.material &&
           a.color == b.color &&
           a.pattern == b.pattern;
}

/* Load from files:
    Open file using ifstream
    Loop through each line
    Parse line into ClothingItem struct
    Add it to vector
*/
Wardrobe loadDatabase(const string& filename) {   
    Wardrobe clothingDatabase;
    ifstream file(filename);
    string line;
    vector<ClothingItem> jackets;
    vector<ClothingItem> tops;
    vector<ClothingItem> bottoms;
    vector<ClothingItem> shoes;

    while (getline(file, line)) {
        ClothingItem item;
        // Line is formatted as: type,isLong,material,color,pattern
        size_t pos = 0;
        pos = line.find(',');
        item.type = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        item.isLong = (line.substr(0, pos) == "true");
        line.erase(0, pos + 1);

        pos = line.find(',');
        item.material = line.substr(0, pos);
        line.erase(0, pos + 1);

        pos = line.find(',');
        item.color = line.substr(0, pos);
        line.erase(0, pos + 1);

        item.pattern = line; // Remaining part is pattern

        if (item.type == "top") tops.push_back(item);
        else if (item.type == "bottom") bottoms.push_back(item);
        else if (item.type == "shoes") shoes.push_back(item);
        else if (item.type == "jacket") jackets.push_back(item);
    }

    clothingDatabase.shoes = shoes;
    clothingDatabase.bottoms = bottoms;
    clothingDatabase.tops = tops;
    clothingDatabase.jackets = jackets;

    file.close();
    return clothingDatabase;
}

void toLower(string& input) {
    for (int i = 0; i < input.length(); i++) {
        if (!isalpha(input[i])) {
            cerr << "Error: Only onter letters";
        }
        input[i] = tolower(input[i]);
    }
}

ClothingItem getUsersClothing() {
    ClothingItem Item;
    string isLongInput;
    string converted;
    cout << "Enter clothing type: (Jacket/Top/Bottom/Shoes)";
    getline(cin, converted);  // No need to ignore here
    toLower(converted);
    Item.type = converted;


    cout << "Is it long-sleeved or long-pants? (Yes/No): ";
    getline(cin, isLongInput);
    toLower(isLongInput);
    Item.isLong = (isLongInput == "yes");

    cout << "Enter clothing material: ";
    getline(cin, converted);
    toLower(converted);
    Item.material = converted;

    cout << "Enter clothing color: ";
    getline(cin, converted);
    toLower(converted);
    Item.color = converted;

    cout << "Enter clothing pattern: ";
    getline(cin, converted);
    toLower(converted);
    Item.pattern = converted;

    return Item;
}

vector<ClothingItem>& getType(Wardrobe& outfits, ClothingItem Item) {
    if (Item.type == "jacket") return outfits.jackets;
    else if (Item.type == "top") return outfits.tops;
    else if (Item.type == "bottom") return outfits.bottoms;
    else if (Item.type == "shoes") return outfits.shoes;
    
    throw runtime_error("Unknown clothing type: " + Item.type);
}

/*Prompts user for all aspects of the clothing item they wish to add
 * Adds to vector containing all items in wardrobe
*/
void addClothing(Wardrobe& outfits) {
    ClothingItem newItem = getUsersClothing();
    getType(outfits, newItem).push_back(newItem);
}

/*Prints the contents of the clothing database vector in a visually appealing way
 * allows easy browsing from user
*/
void printClothing(const vector<ClothingItem>& clothes) {
    for (const auto& item : clothes) {
        cout << "       Type: " << item.type 
             << ", Is Long: " << (item.isLong ? "Yes" : "No")
             << ", Material: " << item.material 
             << ", Color: " << item.color 
             << ", Pattern: " << item.pattern << endl;
    }
}

/* Prints contents of entire wardrobe for user
*/
void printWardrobe(const Wardrobe& outfits) {
    cout << "\nJackets: \n";
    printClothing(outfits.jackets);

    cout<< "\nTops: \n";
    printClothing(outfits.tops);

    cout << "\nBottoms: \n";
    printClothing(outfits.bottoms);

    cout << "\nShoes: \n";
    printClothing(outfits.shoes);
}

/* Allows user to remove any clothing from database vector by prompting for all aspects of items
*/
void removeClothing(Wardrobe& outfits) {
    ClothingItem itemToRemove = getUsersClothing();
    vector<ClothingItem>& type = getType(outfits, itemToRemove);
    type.erase(remove_if(type.begin(), type.end(),
                  [&itemToRemove](const ClothingItem& item) {
                      return item == itemToRemove;}), type.end());
}


void updateVectors(vector<ClothingItem>& src, vector<ClothingItem>& dest, const vector<ClothingItem>& stay) {
    for (int i = 0; i < src.size(); i++) {
        if (find(stay.begin(), stay.end(), src[i]) == stay.end()) {
            dest.push_back(src[i]);
        } 
    }
    src = stay;
}

void updateWardrobes(Wardrobe& src, Wardrobe& dest, const vector<ClothingItem>& stay) {
    updateVectors(src.shoes, dest.shoes, stay);
    updateVectors(src.bottoms, dest.bottoms, stay);
    updateVectors(src.tops, dest.tops, stay);
    updateVectors(src.jackets, dest.jackets, stay);
}

void pushDatabase(const Wardrobe& src, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing.";
        return;
    }

    auto writeVector = [&](const vector<ClothingItem>& items) {
        for (const auto& item : items) {
            file << item.type << ","
                    << (item.isLong ? "true" : "false") << ","
                    << item.material << ","
                    << item.color << ","
                    << item.pattern << "n";
        }
    };

    writeVector(src.jackets);
    writeVector(src.tops);
    writeVector(src.bottoms);
    writeVector(src.shoes);

    file.close();
}

//future plans after basic functionality:
    //- connect to a weather API to suggest outfits based on the weather
    //- allow user to set preferences for outfits (e.g., formal, casual, etc.)
    //- allow user to input work field and suggest outfits based on that
    //- turn program into website or app for easier access
    //- allow user to snap picture of new clothing item and add it to the database

