/**************************************************************
* Name        : Project Name
* Author      : Evan Bunnell
* Created     : 00/00/0000
* Course      : CIS 152 - Data Structures
* Version     : 1.0
* OS          : Windows 10
* Copyright   : This is my own original work based on
*               specifications issued by our instructor
* Description : This program overall description here
*               Input:  list and describe
*               Output: list and describe
* Academic Honesty: I attest that this is my original work.
* I have not used unauthorized source code, either modified or
* unmodified. I have not given other fellow student(s) access to
* my program.
***************************************************************/
#include <algorithm>
#include <iostream>
#include "character.h"
#include "list.h"
using namespace std;

void menu();
void insertMenu();
void deleteMenu();
void displayRoster();

Character character;
List list;

int main() {
    // prepopulating the list for testing/demonstration
    character.build("Kards", "Rogue", "dps");
    list.insert(character);
    character.build("Melody", "Priest", "healer");
    list.insert(character);
    character.build("Kronkh", "Warrior", "tank");
    list.insert(character);
    character.build("Fergy", "Paladin", "tank");
    list.insert(character);
    character.build("Hohenheim", "Paladin", "healer");
    list.insert(character);
    character.build("Boomboom", "Mage", "dps");
    list.insert(character);


    menu();

    return 0;
}

void menu() {
    int input;

    cout << "What would you like to do?\n"
         << "1. Add character to roster.\n"
         << "2. Delete character from roster.\n"
         << "3. Display roster.\n"
         << "0. Quit.\n";

    cin >> input;

    while (input != 0) {
        if (input > 3 || input < 0) {
            cout << "Invalid input.\n";
            menu();
            cin >> input;
        }
        if (input == 1) {
            insertMenu();
        }
        else if (input == 2) {
            deleteMenu();
        }
        else displayRoster();
    }
    exit(0);
}

void insertMenu() {
    string name, Class, role;
    char confirm;

    cout << "\nPlease enter the name of the character:\n";
    cin >> name;
    while (name.length() > 12) {
        cout << "Sorry, character names must be no longer than 12 characters.\n"
        "Please re-enter the name:\n";
        cin >> name;
    }
    cout << "\nPlease enter the character's in-game class:\n(Warrior, Paladin, Priest, Mage, or Rogue)\n";
    cin >> Class;
    transform(Class.begin(), Class.end(), Class.begin(), [](unsigned char c) {return tolower(c);});
    while (Class != "warrior" && Class != "paladin" && Class != "priest" && Class != "rogue" && Class != "mage") {
        cout << "Sorry, the character's class must be either Warrior, Paladin, Priest, Mage, or Rogue.\n"
                "Please re-renter the class:\n";
        cin >> Class;
        transform(Class.begin(), Class.end(), Class.begin(), [](unsigned char c) {return tolower(c);});
    }
    if (Class == "rogue" || Class == "mage") {
        role = "dps";
    }
    else {
        cout << "\nAre you a tank, healer, or dps (damage per second)?\n";
        cin >> role;
        transform(role.begin(), role.end(), role.begin(), [](unsigned char c) {return tolower(c);});
        if (Class == "warrior") {
            while (role != "tank" && role != "dps") {
                cout << "Warriors can only be tanks or dps.\n"
                        "Please re-enter your role.\n";
                cin >> role;
                transform(role.begin(), role.end(), role.begin(), [](unsigned char c) {return tolower(c);});
            }
        }
        else if (Class == "paladin") {
            while (role != "tank" && role != "dps" && role != "healer") {
                cout << "The available roles are: Tank, Healer, or DPS.\n"
                        "Please re-enter your role.\n";
                cin >> role;
                transform(role.begin(), role.end(), role.begin(), [](unsigned char c) {return tolower(c);});
            }
        }
        else if (Class == "priest") {
            while (role != "dps" && role != "healer") {
                cout << "Priests can only be healer or dps.\n"
                        "Please re-enter your role.\n";
                cin >> role;
                transform(role.begin(), role.end(), role.begin(), [](unsigned char c) {return tolower(c);});
            }
        }
    }
    cout << "\nYou have entered:\nName: " << name << "\nClass: " << Class << "\nRole: " << role << "\n\nIs this correct? (y/n)" << endl;
    cin >> confirm;
    confirm = tolower(confirm);
    while (confirm != 'y') {
        if (confirm == 'n') {
            insertMenu();
        }
        else {
            cout << "You have entered:\nName: " << name << "\nClass: " << Class << "\nRole: " << role << "\n\nIs this correct? (y/n)" << endl;
            cin >> confirm;
            confirm = tolower(confirm);
        }
    }
    character.build(name, Class, role);
    list.insert(character);

    cout << endl;
    menu();
}

void deleteMenu() {
    string name;

    cout << "\nWhat is the name of the character you would like to remove from the roster?\n";
    cin >> name;

    if (list.search(name)) {
        list.Delete(name);
    }
    else {
        cout << "Character " << name << " not found.\n";
        deleteMenu();
    }

    cout << endl;
    menu();
}

void displayRoster() {
    list.sort();
    list.display();

    cout << endl;
    menu();
}
