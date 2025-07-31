# OutfitPicker

A **C++ command-line wardrobe organizer** that helps you manage your clothing inventory, track dirty laundry, and suggest daily outfits.  
Built as a personal project to demonstrate **C++ programming**, **file I/O**, and **object-oriented design**.

---

## Features

- **Add and remove clothing items** to your wardrobe.
- **Track dirty laundry** after wearing clothes.
- **Simulate doing laundry** and update the wardrobe automatically.
- **Random outfit suggestions** based on available clean clothes.
- **Persistent data storage** in CSV files.

---

## Project Structure
OutfitPicker/  
│  
├── main.cpp # Main program entry point  
├── Sources/  
│ └── OutfitPicker.cpp # Core wardrobe and outfit logic  
├── Headers/  
│ └── OutfitPicker.h # Wardrobe data structures & function declarations  
├── Other Files/  
│ ├── outfits.csv # Current wardrobe inventory  
│ ├── dirtyLaundry.csv # Items currently dirty  
├── .vscode/ # VSCode debug/build settings  
│ ├── launch.json  
│ └── tasks.json  
└── README.md # Project documentation  

---

## How it Works

1. **Load wardrobe** from 'outfits.csv' and 'dirtyLaundry.csv'.
2. **Prompt the user** to:
    - Add or remove clothes.
    - Record laundry events.
    - Request an outfit suggestion.
3. **Generate a random outfit** and mark worn clothes as dirty.
4. **Save updated wardrobe data** back to CSV for next session.

---

## Installation & Usage 

### **1. Clone the repository**
```bash
git clone https://github.com/yourusername/OutfitPicker.git
cd OutfitPicker
```
### **2. Compile the Program**
Using g++:
```g++ -g -o OutfitPicker main.cpp Sources/OutfitPicker.cpp```

### **3. Run the Program**
./OutfitPicker
(Use ./OutfitPicker.exe on Windows)

---

## Future Goals
- Improve outfit suggestion algorithm based on user preferences.
- Integrate with weather API for weather-appropriate outfit suggestions.
- Add career-based outfit recommendations.
- Convert to a GUI or mobile app.
