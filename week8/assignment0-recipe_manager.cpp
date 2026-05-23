#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

// This assignment was very confusing as just a heads up. Reminder, take this tag down
struct Recipe {
    string name;
    vector<string> ingredients;
    vector<string> steps;
};

// --- Function Prototypes ---
void displayMenu();
void addRecipe(vector<Recipe>& collection);
void displayAllRecipes(const vector<Recipe>& collection);
void searchRecipes(const vector<Recipe>& collection);
void removeRecipe(vector<Recipe>& collection);
void showStatistics(const vector<Recipe>& collection);
void editRecipe(vector<Recipe>& collection);
void saveRecipes(const vector<Recipe>& collection);
void loadRecipes(vector<Recipe>& collection);
void sortRecipes(vector<Recipe>& collection);
string trim(const string& str);

int main() {
    vector<Recipe> recipeCollection;
    loadRecipes(recipeCollection); // Load existing recipes on start
    
    int choice;
    do {
        displayMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number between 1 and 7.\n\n";
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer

        switch (choice) {
            case 1: addRecipe(recipeCollection); break;
            case 2: displayAllRecipes(recipeCollection); break;
            case 3: searchRecipes(recipeCollection); break;
            case 4: removeRecipe(recipeCollection); break;
            case 5: showStatistics(recipeCollection); break;
            case 6: editRecipe(recipeCollection); break;
            case 7: cout << "\nSaving and exiting...\n"; break;
            default: cout << "Invalid choice. Please select 1-7.\n\n";
        }
    } while (choice != 7);

    saveRecipes(recipeCollection);
    return 0;
}

void displayMenu() {
    cout << "DYNAMIC RECIPE MANAGER\n";
    cout << "---------------------\n";
    cout << "1. Add Recipe\n";
    cout << "2. Display All Recipes\n";
    cout << "3. Search Recipes\n";
    cout << "4. Remove Recipe\n";
    cout << "5. Show Statistics\n";
    cout << "6. Edit Recipe\n";
    cout << "7. Exit\n";
    cout << "Enter choice: ";
}

void addRecipe(vector<Recipe>& collection) {
    Recipe newRecipe;
    cout << "Enter recipe name: ";
    getline(cin, newRecipe.name);

    int ingCount;
    cout << "How many ingredients? ";
    while (!(cin >> ingCount) || ingCount <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number. Please enter a positive integer: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < ingCount; ++i) {
        cout << "Enter ingredient " << i + 1 << ": ";
        string ingredient;
        getline(cin, ingredient);
        newRecipe.ingredients.push_back(ingredient);
    }

    int stepCount;
    cout << "How many steps? ";
    while (!(cin >> stepCount) || stepCount <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number. Please enter a positive integer: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int i = 0; i < stepCount; ++i) {
        cout << "Enter step " << i + 1 << ": ";
        string step;
        getline(cin, step);
        newRecipe.steps.push_back(step);
    }

    collection.push_back(newRecipe);
    sortRecipes(collection); // Keep alphabetical order
    cout << "Recipe added successfully!\n\n";
}

void displayAllRecipes(const vector<Recipe>& collection) {
    if (collection.empty()) {
        cout << "\nNo recipes in the collection.\n\n";
        return;
    }
    cout << "\nALL RECIPES\n";
    cout << "-----------\n";
    for (size_t i = 0; i < collection.size(); ++i) {
        cout << i + 1 << ". " << collection.at(i).name << "\n";
        cout << "   Ingredients:\n";
        for (const string& ing : collection.at(i).ingredients) {
            cout << "   - " << ing << "\n";
        }
        cout << "   Steps:\n";
        for (size_t j = 0; j < collection.at(i).steps.size(); ++j) {
            cout << "   " << j + 1 << ". " << collection.at(i).steps.at(j) << "\n";
        }
        cout << "\n";
    }
}

void searchRecipes(const vector<Recipe>& collection) {
    if (collection.empty()) {
        cout << "\nNo recipes to search.\n\n";
        return;
    }
    cout << "\nEnter search term (name or ingredient): ";
    string keyword;
    getline(cin, keyword);
    
    // Convert to lowercase for case-insensitive comparison
    string keywordLower = keyword;
    transform(keywordLower.begin(), keywordLower.end(), keywordLower.begin(), ::tolower);

    cout << "\nSEARCH RESULTS\n";
    cout << "--------------\n";
    bool found = false;

    for (const Recipe& r : collection) {
        string nameLower = r.name;
        transform(nameLower.begin(), nameLower.end(), nameLower.begin(), ::tolower);
        
        bool match = nameLower.find(keywordLower) != string::npos;
        
        if (!match) {
            for (const string& ing : r.ingredients) {
                string ingLower = ing;
                transform(ingLower.begin(), ingLower.end(), ingLower.begin(), ::tolower);
                if (ingLower.find(keywordLower) != string::npos) {
                    match = true;
                    break;
                }
            }
        }

        if (match) {
            cout << "- " << r.name << "\n";
            found = true;
        }
    }
    if (!found) cout << "No matching recipes found.\n";
    cout << "\n";
}

void removeRecipe(vector<Recipe>& collection) {
    if (collection.empty()) {
        cout << "\nNo recipes to remove.\n\n";
        return;
    }
    cout << "\nREMOVABLE RECIPES\n";
    for (size_t i = 0; i < collection.size(); ++i) {
        cout << i + 1 << ". " << collection.at(i).name << "\n";
    }
    cout << "Enter number of recipe to remove (or 0 to cancel): ";
    size_t index;
    while (!(cin >> index) || index > collection.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid number. Please select a valid number from the list: ";
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    if (index > 0) {
        collection.erase(collection.begin() + (index - 1));
        cout << "Recipe removed successfully!\n\n";
    }
}

void showStatistics(const vector<Recipe>& collection) {
    int total = collection.size();
    if (total == 0) {
        cout << "\nCOLLECTION STATISTICS\n";
        cout << "--------------------\n";
        cout << "Total recipes: 0\n\n";
        return;
    }

    double totalIngredients = 0;
    double totalSteps = 0;

    for (const Recipe& r : collection) {
        totalIngredients += r.ingredients.size();
        totalSteps += r.steps.size();
    }

    cout << "\nCOLLECTION STATISTICS\n";
    cout << "--------------------\n";
    cout << "Total recipes: " << total << "\n";
    cout << fixed << setprecision(1);
    cout << "Average ingredients per recipe: " << totalIngredients / total << "\n";
    cout << "Average steps per recipe: " << totalSteps / total << "\n\n";
}

void editRecipe(vector<Recipe>& collection) {
    if (collection.empty()) {
        cout << "\nNo recipes to edit.\n\n";
        return;
    }
    cout << "\nSELECT RECIPUT RECIPE INDEX TO EDIT\n";
    for (size_t i = 0; i < collection.size(); ++i) {
        cout << i + 1 << ". " << collection.at(i).name << "\n";
    }
    cout << "Enter choice: ";
    size_t index;
    if (!(cin >> index) || index < 1 || index > collection.size()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid index.\n\n";
        return;
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    Recipe& r = collection.at(index - 1);
    cout << "Editing: " << r.name << "\n";
    cout << "Enter new name (or press Enter to keep current): ";
    string newName;
    getline(cin, newName);
    if (!newName.empty()) r.name = newName;

    int choice;
    cout << "1. Edit Ingredients\n2. Edit Steps\n3. Done\nEnter choice: ";
    if (cin >> choice && (choice == 1 || choice == 2)) {
        cin.ignore();
        if (choice == 1) {
            r.ingredients.clear();
            int count;
            cout << "How many ingredients? ";
            cin >> count; cin.ignore();
            for (int i = 0; i < count; ++i) {
                cout << "Enter ingredient " << i + 1 << ": ";
                string ing; getline(cin, ing);
                r.ingredients.push_back(ing);
            }
        } else {
            r.steps.clear();
            int count;
            cout << "How many steps? ";
            cin >> count; cin.ignore();
            for (int i = 0; i < count; ++i) {
                cout << "Enter step " << i + 1 << ": ";
                string step; getline(cin, step);
                r.steps.push_back(step);
            }
        }
    }
    sortRecipes(collection);
    cout << "Recipe updated successfully!\n\n";
}

void sortRecipes(vector<Recipe>& collection) {
    sort(collection.begin(), collection.end(), [](const Recipe& a, const Recipe& b) {
        return a.name < b.name;
    });
}

// Utility to save to recipes.txt if you will
void saveRecipes(const vector<Recipe>& collection) {
    ofstream outFile("recipes.txt");
    if (!outFile.is_open()) return;

    for (const Recipe& r : collection) {
        outFile << r.name << "\n";
        outFile << r.ingredients.size() << "\n";
        for (const string& ing : r.ingredients) {
            outFile << ing << "\n";
        }
        outFile << r.steps.size() << "\n";
        for (const string& step : r.steps) {
            outFile << step << "\n";
        }
    }
    outFile.close();
}

// Utility to load from "recipes.txt"
