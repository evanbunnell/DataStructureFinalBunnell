/***************************************************************
* Name        : Character
* Author      : Evan Bunnell
* Created     : 5/4/2023
***************************************************************/
#include "character.h"
#include <algorithm>

/**************************************************************
* Name: Character
* Description: Default no-arg constructor
* Input parameters: none
***************************************************************/
Character::Character() {
    name = "No Name";
    Class = "No Class";
    role = "No Role";
}

/***************************************************************
* Class Functions
***************************************************************/
string Character::getName() {
    return name;
}

void Character::setName(string input){
    name = input;
}

string Character::getClass() {
    return Class;
}

void Character::setClass(string input){
    Class = input;
}

string Character::getRole() {
    return role;
}

void Character::setRole(string input){
    role = input;
}

/**************************************************************
* Name: build
* Description: Builds a full object for the Character class
* Input: string, string, string, string, double
* Output: n/a
***************************************************************/
void Character::build(string newName, string newClass, string newRole) {
    name = newName;
    Class = newClass;
    role = newRole;
    priority = setPrio();
}
/**************************************************************
* Name: print
* Description: Prints object information on display
* Input: n/a
* Output: Object attributes via cout
***************************************************************/
void Character::print() {
    Class[0] = toupper(Class[0]);
    role[0] = toupper(role[0]);
    if (name.length() > 5) {
        cout << "Name: " << name << "\tClass: " << Class << "\tRole: " << role;
        if (priority >= 4) {
            cout << " [Backup]" << endl;
        }
        else cout << endl;
        cout << "Priority: " << priority << endl;   //FOR TESTING ONLY
    }
    else {
        cout << "Name: " << name << "\t\tClass: " << Class << "\tRole: " << role;
            if (priority >= 4) {
                cout << " [Backup]" << endl;
            }
            else cout << endl;
        cout << "Priority: " << priority << endl;   //FOR TESTING ONLY
    }
}
/**************************************************************
* Name: setPrio
* Description: Sets attribute priority based on role attribute
*              value
* Input: n/a
* Output: n/a
***************************************************************/
int Character::setPrio() {
    if (getRole() == "tank") {
        return 1;
    }
    if (getRole() == "healer") {
        return 2;
    }
    if (getRole() == "dps") {
        return 3;
    }
    return 0;
}
