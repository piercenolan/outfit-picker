/* Nolan Pierce - Custom Outfit Organizer

This project contains code for a command-line outfit organizer program.

It allows the user to add and remove clothes that may be in their wardrobe.

It tracks which clothes the user has, which ones have been worn recently, and 
which are dirty and need washed before wearing again.

Starting functionality includes random clothing pairings from the wardrobe.

Future Goals:
- allow user to provide input on their style
    - updating algorithm to choose outfits they enjoy
- Allow user to input career field, impacting outfit recommendations
- Connect to a weather API to give real-time outfits based on weather
- Convert to web or mobile interface
*/
#include <iostream>
#include <vector>
#include <fstream>
#include <string>   
#include <algorithm>
#include <limits>
#include "Headers/OutfitPicker.h"
using namespace std;


/* Function handles prompting the user if they wish to add any clothe
*/
void promptAdditions(vector<ClothingItem>& outfits) {
    string action;
    cout << "\n Do you have any clothes to add? (Yes/No): ";
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (action == "No" || action == "no") { return; }
    while (action != "No" && action != "no") {
        addClothing(outfits);
        cout << "\n Do you want to add more clothes? (Yes/No): ";  //ensures user can add multiple items
        cin >> action;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "\n" << "Current clothing database:\n";
    printClothing(outfits);
}

void promptRemovals(vector<ClothingItem>& outfits) {
    string action;
    cout << "\n" << "\n Do you have any clothes to remove? (Yes/No): ";
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (action == "No" || action == "no") { return; }

    while (action != "No" && action != "no") {
        removeClothing(outfits);
        cout << "\n Do you want to remove more clothes? (Yes/No): ";  //ensures user can remove multiple items
        cin >> action;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cout << "\n" << "Current clothing database:\n";
    printClothing(outfits);
}

void promptLaundry(vector<ClothingItem>& outfits) {
    string action;
    cout << " \nHave you done laundry? (Yes/No)";
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (action == "No" || action == "no") {
        return;
    }

    cout << " \n Did you wash all dirty clothes? (Yes/No)";
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<ClothingItem> unwashedClothes;
    if (action == "No" || action == "no") {
        int numDirty = 0;
        cout << "\n How many clothes did you leave dirty? (#)";
        cin >> numDirty;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
        for (int i = 1; i <= numDirty; i++) {
            cout << "\nPlease describe item " << i << " that you didn't wash \n";
            ClothingItem dirty = getUsersClothing();
            unwashedClothes.push_back(dirty);
        }
        cout << "\nHere are the clothes that are still dirty: \n";
        printClothing(unwashedClothes);
    }  
    vector<ClothingItem> dirtyLaundry = loadClothingDatabase("Other Files/dirtyLaundry.csv");
    updateDatabase(dirtyLaundry, outfits, unwashedClothes);
    cout << "Good job! I have updated the outfit database to now include the clean clothes!";
}

int main() {
    // 1. Load clothing database from file
    vector<ClothingItem> outfits = loadClothingDatabase("Other Files/outfits.csv");

    //2. Welcome and print current database
    cout << "\n Welcome to the Outfit Picker!" << endl;
    cout << "\n" << "Current clothing database:\n";
    printClothing(outfits);

    // 3. Prompt user for:
    //  a. Add clothes?
    promptAdditions(outfits);

    //  b. Remove clothes?
    promptRemovals(outfits);
    
    //  c. Laundry done?
    promptLaundry(outfits);

    //  d. Pick outfit
    // 4. Save updated data to files

    //print or show current clothing database

    //ask user if they need to add or remove any clothing items 

    //ask user if they did laundry
    //will return worn outfits to main database

    //ask user if they want to pick an outfit

    //On yes: will return a matching top, bottom, shoes, and jacket (if applicable) to user
    //moves outfit to worn outfits database (except shoes, which stay in main database)

    return 0;
}