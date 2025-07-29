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
vector<ClothingItem> loadClothingDatabase(const string& filename) {
    vector<ClothingItem> clothingDatabase;
    ifstream file(filename);
    string line;

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

        clothingDatabase.push_back(item);
    }

    file.close();
    return clothingDatabase;
}

ClothingItem getUsersClothing() {
    ClothingItem Item;
    string isLongInput;
    cout << "Enter clothing type: ";
    getline(cin, Item.type);  // No need to ignore here

    cout << "Is it long-sleeved or long-pants? (Yes/No): ";
    getline(cin, isLongInput);
    Item.isLong = (isLongInput == "Yes" || isLongInput == "yes");

    cout << "Enter clothing material: ";
    getline(cin, Item.material);

    cout << "Enter clothing color: ";
    getline(cin, Item.color);

    cout << "Enter clothing pattern: ";
    getline(cin, Item.pattern);

    return Item;
}
/*Prompts user for all aspects of the clothing item they wish to add
 * Adds to vector containing all items in wardrobe
*/
void addClothing(vector<ClothingItem>& outfits) {
    ClothingItem newItem = getUsersClothing();
    outfits.push_back(newItem);
}

/*Prints the contents of the clothing database vector in a visually appealing way
 * allows easy browsing from user
*/
void printClothing(const vector<ClothingItem>& outfits) {
    for (const auto& item : outfits) {
        cout << "Type: " << item.type 
             << ", Is Long: " << (item.isLong ? "true" : "false")
             << ", Material: " << item.material 
             << ", Color: " << item.color 
             << ", Pattern: " << item.pattern << endl;
    }
}

/* Allows user to remove any clothing from database vector by prompting for all aspects of items
*/
void removeClothing(vector<ClothingItem>& outfits) {
    ClothingItem itemToRemove = getUsersClothing();
    outfits.erase(remove_if(outfits.begin(), outfits.end(),
                  [&itemToRemove](const ClothingItem& item) {
                      return item == itemToRemove;}), outfits.end());
}


void updateDatabase(vector<ClothingItem>& src, vector<ClothingItem>& dest, const vector<ClothingItem>& stay) {
    for (int i = 0; i < src.size(); i++) {
        if (find(stay.begin(), stay.end(), src[i]) == stay.end()) {
            dest.push_back(src[i]);
        } 
    }
    src = stay;
}


//future plans after basic functionality:
    //- connect to a weather API to suggest outfits based on the weather
    //- allow user to set preferences for outfits (e.g., formal, casual, etc.)
    //- allow user to input work field and suggest outfits based on that
    //- turn program into website or app for easier access
    //- allow user to snap picture of new clothing item and add it to the database

