
#include <iostream>
#include <vector>
#include <fstream>
#include <string>   
#include <algorithm>
#include <limits>
#include "Headers/OutfitPicker.h"
using namespace std;

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

void addClothing(vector<ClothingItem>& outfits) {
    ClothingItem newItem;
    string isLongInput;
    cout << "Enter clothing type: ";
    getline(cin, newItem.type);  // No need to ignore here

    cout << "Is it long-sleeved or long-pants? (Yes/No): ";
    getline(cin, isLongInput);
    newItem.isLong = (isLongInput == "Yes" || isLongInput == "yes");

    cout << "Enter clothing material: ";
    getline(cin, newItem.material);

    cout << "Enter clothing color: ";
    getline(cin, newItem.color);

    cout << "Enter clothing pattern: ";
    getline(cin, newItem.pattern);

    outfits.push_back(newItem);
}

void printClothingDatabase(const vector<ClothingItem>& outfits) {
    cout << "\n" << "Current clothing database:\n";
    for (const auto& item : outfits) {
        cout << "Type: " << item.type 
             << ", Is Long: " << (item.isLong ? "true" : "false")
             << ", Material: " << item.material 
             << ", Color: " << item.color 
             << ", Pattern: " << item.pattern << endl;
    }
}

void removeClothing(vector<ClothingItem>& outfits) {
    ClothingItem itemToRemove;
    string isLongInput;
    printClothingDatabase(outfits);

    cout << "Enter the type of clothing to remove: ";
    getline(cin, itemToRemove.type);

    cout << "Is the item long-sleeved or long-pants? (Yes/No): ";
    getline(cin, isLongInput);
    itemToRemove.isLong = (isLongInput == "Yes" || isLongInput == "yes");

    cout << "Enter the clothing material: ";
    getline(cin, itemToRemove.material);

    cout << "Enter the clothing color: ";
    getline(cin, itemToRemove.color);

    cout << "Enter the clothing pattern: ";
    getline(cin, itemToRemove.pattern);

    outfits.erase(remove_if(outfits.begin(), outfits.end(),
                    [&itemToRemove](const ClothingItem& item) {
                        return item.type == itemToRemove.type &&
                               item.isLong == itemToRemove.isLong &&
                               item.material == itemToRemove.material &&
                               item.color == itemToRemove.color &&
                               item.pattern == itemToRemove.pattern;        
                    })
                , outfits.end());
}


int main() {
// 1. Load clothing database from file
    vector<ClothingItem> outfits = loadClothingDatabase("Other Files/outfits.csv");
/* Print loaded outfits for verification
    for (const auto& item : outfits) {
        cout << "Type: " << item.type 
             << ", Is Long: " << (item.isLong ? "true" : "false")
             << ", Material: " << item.material 
             << ", Color: " << item.color 
             << ", Pattern: " << item.pattern << endl;
    }
*/
// 2. Load worn outfits from file
// 3. Prompt user for:
//    a. Add clothes

    string action;

    cout << "\n Welcome to the Outfit Picker!" << endl;
    printClothingDatabase(outfits);

    //a. Add clothes
    cout << "\n Do you have any clothes to add? (Yes/No): ";
    cin >> action;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (action != "No" && action != "no") {
        addClothing(outfits);
        cout << "\n Do you want to add more clothes? (Yes/No): ";  //ensures user can add multiple items
        cin >> action;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    printClothingDatabase(outfits);

    //b. Remove clothes
    cout << "\n" << "\n Do you have any clothes to remove? (Yes/No): ";
    cin >> action;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    while (action != "No" && action != "no") {
        removeClothing(outfits);
        cout << "\n Do you want to remove more clothes? (Yes/No): ";  //ensures user can remove multiple items
        cin >> action;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
//    b. Laundry done?
//    c. Pick outfit
// 4. Save updated data to files

    return 0;
}