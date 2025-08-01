/* Nolan Pierce - Outfit Picker Implementation
 *
 * Overview:
 *   Implements all wardrobe and outfit management functions for the Outfit Picker program.
 *   Handles reading and writing clothing data, adding/removing items, tracking laundry,
 *   and generating random outfit suggestions.
 *
 * Features:
 *   - Load wardrobe data from CSV files.
 *   - Add and remove clothing items.
 *   - Track clean and dirty clothes.
 *   - Save updated wardrobe data.
 *   - Suggest outfits randomly, with optional jacket.
 *
 * Future Goals:
 *   - Integrate weather-based outfit suggestions.
 *   - Add user style preference filtering.
 *   - Convert to web or mobile interface.
 */
#include "../Headers/OutfitPicker.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <random>

using namespace std;

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

/* toLower
 * Converts all characters in a string to lowercase.
 *
 * Parameters:
 *   input - reference to the string to modify.
 *
 * Details:
 *   - Changes the string in-place.
 */
void toLower(string& input) {
    for (int i = 0; i < input.length(); i++) {
        /* TODO: Ensure user only enters correct input (only letters for sentences, only numbers for quantities)
        if (!isalpha(input[i])) {
            cerr << "Error: Only onter letters";
        }
        */
        input[i] = tolower(input[i]);
    }
}

/* checkBool
 * Checks that user input is "yes" or "no"
 * 
 * Parameters:
 *   input  - reference to the string to check/modify.
 * 
 * Details:
 *   - Changes the string in-place.
 *   - Loops until user enters correct input 
 */
void checkBool(string& input) {
    while (input != "yes" && input != "no") {
        cerr << "Error: Incorrect Input! Please enter either 'Yes' or 'No': ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');        
        toLower(input);
    }
}

void checkType(string& input) {
    while (input != "yes" && input != "no") {
        cerr << "Error: Incorrect Input! Please enter either 'Yes' or 'No': ";
        cin >> input;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');        
        toLower(input);
    }    
}
/* loadDatabase
 * Loads wardrobe data from a CSV file into a Wardrobe object.
 *
 * Parameters:
 *   filename - path to the CSV file.
 *
 * Returns:
 *   Wardrobe populated with clothing items from the file.
 */
Wardrobe loadDatabase(const string& filename) {   
    //Var Initialization
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
        
        //Add ClothingItem to corresponding vector
        if (item.type == "top") tops.push_back(item);
        else if (item.type == "bottom") bottoms.push_back(item);
        else if (item.type == "shoes") shoes.push_back(item);
        else if (item.type == "jacket") jackets.push_back(item);
    }

    //Update overall wardrobe to include corresponding vectors for each type
    clothingDatabase.shoes = shoes;
    clothingDatabase.bottoms = bottoms;
    clothingDatabase.tops = tops;
    clothingDatabase.jackets = jackets;

    file.close();
    return clothingDatabase;
}

/* getUsersClothing
 * Prompts the user for details about a clothing item.
 *
 * Returns:
 *   ClothingItem filled with user-provided data.
 */
ClothingItem getUsersClothing() {
    //Var initialization
    ClothingItem Item;
    string isLongInput;
    string converted;
    cout << "Enter clothing type: (Jacket/Top/Bottom/Shoes)";
    getline(cin, converted);
    toLower(converted);     //ensures formatting in vectors/.csv's are uniform
    Item.type = converted;


    cout << "Is it long-sleeved or long-pants? (Yes/No): ";
    getline(cin, isLongInput);
    toLower(isLongInput);
    Item.isLong = (isLongInput == "yes");       //ensures a boolean value for IsLong

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

/* getType
 * Returns the vector in a Wardrobe corresponding to a clothing item’s type.
 *
 * Parameters:
 *   outfits - wardrobe to search.
 *   Item    - clothing item whose type determines the returned vector.
 *
 * Returns:
 *   Reference to the correct vector in outfits.
 *
 * Throws:
 *   runtime_error if the clothing type is unknown.
 */
vector<ClothingItem>& getType(Wardrobe& outfits, ClothingItem Item) {
    if (Item.type == "jacket") return outfits.jackets;
    else if (Item.type == "top") return outfits.tops;
    else if (Item.type == "bottom") return outfits.bottoms;
    else if (Item.type == "shoes") return outfits.shoes;
    
    throw runtime_error("Unknown clothing type: " + Item.type);
}

/* addClothing
 * Prompts user for a clothing item and adds it to the wardrobe.
 *
 * Parameters:
 *   outfits - wardrobe to update.
 */
void addClothing(Wardrobe& outfits) {
    ClothingItem newItem = getUsersClothing();
    getType(outfits, newItem).push_back(newItem);
}

/* printClothing
 * Displays a list of clothing items in a readable format.
 *
 * Parameters:
 *   clothes - vector of ClothingItem objects to display.
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

/* printWardrobe
 * Displays all clothing items in a wardrobe.
 *
 * Parameters:
 *   outfits - wardrobe to display.
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

/* removeClothing
 * Prompts user for a clothing item and removes it from the wardrobe.
 *
 * Parameters:
 *   outfits - wardrobe to update.
 */
void removeClothing(Wardrobe& outfits) {
    ClothingItem itemToRemove = getUsersClothing();
    vector<ClothingItem>& type = getType(outfits, itemToRemove);
    type.erase(remove_if(type.begin(), type.end(),
                  [&itemToRemove](const ClothingItem& item) {
                      return item == itemToRemove;}), type.end());
}

/* updateVectors
 * Moves items from one vector to another, excluding those that should stay.
 *
 * Parameters:
 *   src  - source vector.
 *   dest - destination vector.
 *   stay - items to remain in source.
 */
void updateVectors(vector<ClothingItem>& src, vector<ClothingItem>& dest, const vector<ClothingItem>& stay) {
    for (int i = 0; i < src.size(); i++) {
        //Add elements from src to dest, unless they are in 'stay'
        if (find(stay.begin(), stay.end(), src[i]) == stay.end()) {
            dest.push_back(src[i]);
        } 
    }
    //As long as src wasn't an empty vector (i.e. dirtyLaundry.csv was empty),
    //src vector becomes the stay vector, ensuring items meant to stay, remain
    if (!src.empty()) src = stay;
}

/* updateWardrobes
 * Moves items between two wardrobes, excluding items that should stay.
 *
 * Parameters:
 *   src  - source wardrobe.
 *   dest - destination wardrobe.
 *   stay - items to remain in source.
 */
void updateWardrobes(Wardrobe& src, Wardrobe& dest, const Wardrobe& stay) {
    updateVectors(src.shoes, dest.shoes, stay.shoes);
    updateVectors(src.bottoms, dest.bottoms, stay.bottoms);
    updateVectors(src.tops, dest.tops, stay.tops);
    updateVectors(src.jackets, dest.jackets, stay.jackets);
}

/* pushDatabase
 * Saves wardrobe data to a CSV file.
 *
 * Parameters:
 *   src      - wardrobe to save.
 *   filename - path to CSV file.
 */
void pushDatabase(const Wardrobe& src, const string& filename) {
    ofstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file for writing.";
        return;
    }

    //Lambda to write all ClothingItems of a certain type into file
    auto writeVector = [&](const vector<ClothingItem>& items) {
        for (const auto& item : items) {
            file << item.type << ","
                    << (item.isLong ? "true" : "false") << ","
                    << item.material << ","
                    << item.color << ","
                    << item.pattern << "\n";
        }
    };
    //Write all 4 vectors from wardrobe into the file
    writeVector(src.jackets);
    writeVector(src.tops);
    writeVector(src.bottoms);
    writeVector(src.shoes);

    file.close();
}

/* pickOutfit
 * Generates and displays a random outfit from the wardrobe.
 *
 * Parameters:
 *   outfits - wardrobe to pick from.
 *   dirty   - wardrobe to move worn clothes into.
 *   jacket  - whether to include a jacket in the outfit.
 */
void pickOutfit(Wardrobe& outfits, Wardrobe& dirty, bool jacket) {
    Wardrobe picked;

    //Lambda to randomly pick a clothing item from vector parameter
    //      removes chosen item from the outfits database
    auto pickNremove = [&](vector<ClothingItem>& from) -> ClothingItem {
        if (from.empty()) throw runtime_error("You have no items of this clothing type to choose from.");
        int index = rand() % from.size();
        ClothingItem chosen = from[index];
        from.erase(from.begin() + index);
        return chosen;
    };
    
    //manually choose shoes, as shoes don't need washed after 1 wear
    int index = rand() % outfits.shoes.size();
    ClothingItem chosenShoe = outfits.shoes[index];
    picked.shoes.push_back(chosenShoe);
    picked.bottoms.push_back(pickNremove(outfits.bottoms));
    picked.tops.push_back(pickNremove(outfits.tops));
    if (jacket) picked.jackets.push_back(pickNremove(outfits.jackets)); //only choose jacket if user said so

    // Move to dirty wardrobe
    dirty.bottoms.insert(dirty.bottoms.end(), picked.bottoms.begin(), picked.bottoms.end());
    dirty.tops.insert(dirty.tops.end(), picked.tops.begin(), picked.tops.end());
    dirty.jackets.insert(dirty.jackets.end(), picked.jackets.begin(), picked.jackets.end());

    cout << "\n\nToday's Outfit: ";
    printWardrobe(picked);
}