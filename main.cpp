/* Nolan Pierce - Custom Outfit Organizer
 *
 * Overview:
 *   Command-line tool for managing a personal wardrobe and generating outfit suggestions.
 *
 * Features:
 *   - Add or remove clothing items from the wardrobe.
 *   - Track which items are clean, recently worn, or dirty.
 *   - Randomly suggest outfits from available clothes.
 *   - Persist wardrobe data between runs using CSV files.
 *
 * Future Goals:
 *   - Allow user style preferences to influence outfit selection.
 *   - Support career-based outfit recommendations.
 *   - Integrate with a weather API for weather-appropriate suggestions.
 *   - Convert to a web or mobile interface.
 */
#include <iostream>
#include <vector>
#include <fstream>
#include <string>   
#include <algorithm>
#include <limits>
#include "Headers/OutfitPicker.h"


/* promptAdditions
 * Prompts the user to add any new clothing items to their wardrobe.
 *
 * Parameters:
 *   outfits - reference to the Wardrobe object containing all available clothes.
 *
 * Details:
 *   - Asks the user if they have new clothes to add.
 *   - Allows multiple additions until the user responds "No".
 *   - Converts all input to lowercase for case-insensitive matching.
 *   - Prints the updated wardrobe when finished.
 */
void promptAdditions(Wardrobe& outfits) {
    string action;      //re-usable variable to store user input
    cout << "\n Do you have any clothes to add? (Yes/No): ";
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');        //throws away any additional input including newline 
    toLower(action);
    if (action == "no")  return;        //Abort function to improve runtime
    while (action != "no") {        //ensures user can add multiple items
        addClothing(outfits);
        cout << "\n Do you want to add more clothes? (Yes/No): ";  
        cin >> action;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        toLower(action);
    }
    cout << "\n" << "Current Wardrobe:\n";
    printWardrobe(outfits);
}

/* promptRemovals
 * Prompts the user to remove clothing items from their wardrobe.
 *
 * Parameters:
 *   outfits - reference to the Wardrobe object containing all available clothes.
 *
 * Details:
 *   - Asks the user if they have clothes to remove.
 *   - Allows multiple removals until the user responds "No".
 *   - Converts all input to lowercase for case-insensitive matching.
 *   - Prints the updated wardrobe when finished.
 */
void promptRemovals(Wardrobe& outfits) {
    string action;
    cout << "\n Do you have any clothes to remove? (Yes/No): ";
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    toLower(action);
    if (action == "no") return;         //Abort function to improve runtime
    while (action != "no") {        //ensures user can remove multiple items
        removeClothing(outfits);
        cout << "\n Do you want to remove more clothes? (Yes/No): ";  
        cin >> action;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        toLower(action);
    }
    cout << "\nCurrent Wardrobe:\n";
    printWardrobe(outfits);
}

/* promptLaundry
 * Prompts the user about doing laundry and updates wardrobe availability.
 *
 * Parameters:
 *   outfits      - reference to the Wardrobe object containing clean clothes.
 *   dirtyLaundry - reference to the Wardrobe object containing dirty clothes.
 *
 * Details:
 *   - If laundry is done, asks whether all dirty clothes were washed.
 *   - If not all clothes were washed, the user specifies which remain dirty.
 *   - Updates wardrobe and dirty laundry lists accordingly.
 *   - Persists changes for future outfit selections.
 */
void promptLaundry(Wardrobe& outfits, Wardrobe& dirtyLaundry) {
    Wardrobe unwashed;
    string action;
    cout << " \nHave you done laundry? (Yes/No)";
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    toLower(action);

    if (action == "no") return;     //Abort function to improve runtime

    cout << " \n Did you wash all dirty clothes? (Yes/No)";
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    toLower(action);
    //User may not wash all dirty items each time they do laundry
    //this allows user to keep some items dirty if they didn't get washed
    if (action == "no") {
        int numDirty = 0;
        cout << "\n How many clothes did you leave dirty? (#)";
        cin >> numDirty;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        //User describes each item they left dirty to ensure it doesn't become available to pick from
        for (int i = 1; i <= numDirty; i++) {
            cout << "\nPlease describe item " << i << " that you didn't wash \n";
            ClothingItem dirty = getUsersClothing();
            getType(unwashed, dirty).push_back(dirty);
        }
        cout << "\nHere are the clothes that are still dirty: \n";      //allows user to ensure correctness of their answers
        printWardrobe(unwashed);
    }  
    updateWardrobes(dirtyLaundry, outfits, unwashed);       //Saves changes so outfit picked can include washed items
    cout << "Good job! I have updated the outfit database to now include the clean clothes!";
}

/* promptOutfit
 * Prompts the user for an outfit suggestion and updates clothing availability.
 *
 * Parameters:
 *   outfits - reference to the Wardrobe object containing clean clothes.
 *   dirty   - reference to the Wardrobe object containing dirty clothes.
 *
 * Details:
 *   - Asks whether the user wants an outfit suggestion.
 *   - If yes, asks whether to include a jacket.
 *   - Picks a random outfit (and jacket if desired).
 *   - Moves selected clothes to dirty laundry.
 */
void promptOutfit(Wardrobe& outfits, Wardrobe& dirty) {
    string action;

    cout << "\nDo you want an outfit suggestion?";
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    toLower(action);
    if (action == "no") return;     //Aborts function to improve runtime

    cout << "   Do you need a jacket? (Yes/No): ";      //FUTURE PLANS: check weather API to suggest jacket or not
    cin >> action;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    toLower(action);
    bool jacket;
    action == "yes" ? jacket = true : jacket = false;

    pickOutfit(outfits, dirty, jacket);
}



int main() {
    // 1. Load clothing database from file
    Wardrobe outfits = loadDatabase("Other Files/outfits.csv");
    Wardrobe dirty = loadDatabase("Other Files/dirtyLaundry.csv");

    //2. Welcome and print current database
    cout << "\n Welcome to the Outfit Picker!" << endl;
    cout << "\nCurrent clothing database:\n";
    printWardrobe(outfits);

    // 3. Prompt user for:
    //  a. Add clothes?
    promptAdditions(outfits);

    //  b. Remove clothes?
    promptRemovals(outfits);
    
    //  c. Laundry done?
    promptLaundry(outfits, dirty);

    //  d. Pick outfit?
    promptOutfit(outfits, dirty);

    // 4. Save updated data to files
    pushDatabase(outfits, "Other Files/outfits.csv");
    pushDatabase(dirty, "Other Files/dirtyLaundry.csv");

    cout << "\nAll databases updated. Have a great day!";
    return 0;
}