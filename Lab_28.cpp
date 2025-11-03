
#include <iostream>
#include <fstream>
#include <iomanip>
#include <list>
#include "Goat.h"
using namespace std;

const int SZ_NAMES = 200, SZ_COLORS = 25;

int select_goat(list<Goat> trip);
void delete_goat(list<Goat> &trip);
void add_goat(list<Goat> &trip, string [], string []);
void display_trip(list<Goat> trip);
int main_menu();

void sortGoats(list<Goat> &trip) {
    trip.sort([](const Goat &a, const Goat &b) {
        return a.get_age() < b.get_age();
    });
    cout << "Goats sorted by age (youngest to oldest).\n";
}

//2. reverse
void reverseGoats(list<Goat> &trip) { //going to be using this structure alot

trip.reverse();
    cout << "Goats reversed.\n";
}

//3, count by age
void countByAge(const list<Goat> &trip, int age) {
    int cap;
    cout << "Enter age cap: ";
    cin >> cap;

    int count = 0;
for (auto it = trip.begin(); it != trip.end(); it++) {
    if (it->get_age() > cap) {
        count++;
    }
}

    cout << "Number of goats older than " << cap << ": " << count << endl;

}

//4. find by color
void findByColor(list<Goat> trip) {
    string color;
    cout << "Enter color to search: ";
    cin >> color;
    
    auto it = find_if(trip.begin(), trip.end(), [color](const Goat &g) {
        return g.get_color() == color;
    });
    if (it != trip.end()) {
        cout << "Found " << it -> get_name() << " of color " << color << endl;
    } else {
        cout << "No goats found of color " << color << endl;
    }
}

//5. find oldest goat

void findOldestGoat(const list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats in the group.\n";
        return;
    }

    auto oldest = max_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b) {
        return a.get_age() < b.get_age();
    });

    cout << "Oldest goat: " << oldest->get_name() 
         << " (age " << oldest->get_age() 
         << ", " << oldest->get_color() << ")\n";
}

//6. find youngest goat - using structure from oldest goat 
void findYoungestGoat(const list<Goat> &trip) {
    if (trip.empty()) {
        cout << "No goats in the group.\n";
        return;
    }

    auto youngest = min_element(trip.begin(), trip.end(), [](const Goat &a, const Goat &b) {
        return a.get_age() < b.get_age();
    });

    cout << "Youngest goat: " << youngest->get_name() 
         << " (age " << youngest->get_age() 
         << ", " << youngest->get_color() << ")\n";
}

//7. remove by color

void removeByColor(list<Goat> &trip) {
    string color;
    
    cout << "Enter color to remove: ";
    cin >> color;

    int original = trip.size();
    trip.remove_if((const Goat &g)[color]) {
        return g.get_color() == color;
    }
    
    int removed = original - trip.size();

    cout << "Remove : " << removed << " goats that are " << color << endl;
}



int main() {
    srand(time(0));
    bool again;

    // read & populate arrays for names and colors
    ifstream fin("names.txt");
    string names[SZ_NAMES];
    int i = 0;
    while (fin >> names[i++]);
    fin.close();
    ifstream fin1("colors.txt");
    string colors[SZ_COLORS];
    i = 0;
    while (fin1 >> colors[i++]);
    fin1.close();

    // create & populate a trip of Goats using std::list of random size 8-15
    int tripSize = rand() % 8 + 8;
    list<Goat> trip;
    int age;
    string name, color;
    for (int i = 0; i < tripSize; i++) {
        age = rand() % MAX_AGE;  // defined in Goat.h
        name = names[rand() % SZ_NAMES];
        color = colors[rand() % SZ_COLORS];
        Goat tmp(name, age, color);
        trip.push_back(tmp);
    }
    
    // Goat Manager 3001 Engine
    int sel = main_menu();
    while (sel != 4) {
        switch (sel) {
            case 1:
                cout << "Adding a goat.\n";
                add_goat(trip, names, colors);
                break;
            case 2:    
                cout << "Removing a goat.\n";
                delete_goat(trip);
                break;
            case 3:    
                cout << "Displaying goat data.\n";
                display_trip(trip);
                break;
            case 5:
                cout << "Sorting goats by age.\n";
                sortGoats(trip);
                cout << "Goats sorted by age.\n";
                break;
            case 6:
                cout << "Reversing goat order.\n";
                reverseGoats(trip);
                cout << "Goats reversed.\n";
                break;
            case 7:
                cout << "Counting goats by age.\n";
                countByAge(trip, age);
                break;
            case 8:
                cout << "Finding goats by color.\n";
                findByColor(trip);
                break;
            case 9:
                cout << "Finding oldest goat.\n";
                findOldestGoat(trip);
                break;
            case 10:
                cout << "Finding youngest goat.\n";
                findYoungestGoat(trip);
                break;
            case 11:
                cout << "Removing goats by color.\n";
                removeByColor(trip);
                break;
            default:
                cout << "Invalid selection.\n";
                break;
        }
        sel = main_menu();
    }
    

    return 0;
}

int main_menu() {
    cout << "*** GOAT MANAGER 3001 ***\n";
    cout << "[1] Add a goat\n";
    cout << "[2] Delete a goat\n";
    cout << "[3] List goats\n";
    cout << "[4] Quit\n";
    cout << "[5] Sort goats by age\n";
    cout << "[6] Reverse goat order\n";
    cout << "[7] Count goats older than a certain age\n";
    cout << "[8] Find goats by color\n";
    cout << "[9] Find oldest goat\n";
    cout << "[10] Find youngest goat\n";
    cout << "[11] Remove goats by color\n";
    cout << "Choice --> ";
    int choice;
    cin >> choice;
    while (choice < 1 || choice > 20) {  //**COME BACK TO THIS WHEN DONE**//
        cout << "Invalid, again --> ";
        cin >> choice;
    }
    return choice;
}

void delete_goat(list<Goat> &trip) {
    cout << "DELETE A GOAT\n";
    int index = select_goat(trip);
    auto it = trip.begin();
    advance(it, index-1);
    trip.erase(it);
    cout << "Goat deleted. New trip size: " << trip.size() << endl;
}

void add_goat(list<Goat> &trip, string nms[], string cls[]) {
    cout << "ADD A GOAT\n";
    int age = rand() % MAX_AGE;
    string nm = nms[rand() % SZ_NAMES];
    string cl = cls[rand() % SZ_COLORS];
    Goat tmp(nm, age, cl);
    trip.push_back(tmp);
    cout << "Goat added. New trip size: " << trip.size() << endl;
}

void display_trip(list<Goat> trp) {
    int i = 1;
    for (auto gt: trp)
        cout << "\t" 
             << "[" << i++ << "] "
             << gt.get_name() 
             << " (" << gt.get_age() 
             << ", " << gt.get_color() << ")\n";
}

int select_goat(list<Goat> trp) {
    int input;
    cout << "Make a selection:\n";
    display_trip(trp);
    cout << "Choice --> ";
    cin >> input;
    while (input < 1 or input > trp.size()) {
        cout << "Invalid choice, again --> ";
        cin >> input;
    }
    return input;
}






//8. age all goats
