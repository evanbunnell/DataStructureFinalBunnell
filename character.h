#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
using namespace std;


class Character {
public:
    Character();
    int priority;
    string getName();
    void setName(string newName);
    string getClass();
    void setClass(string input);
    string getRole();
    void setRole(string input);
    void build(string newName, string newClass, string newRole);
    void print();
    int setPrio();
private:
    string name;
    string Class;
    string role;
};

#endif // CHARACTER_H
