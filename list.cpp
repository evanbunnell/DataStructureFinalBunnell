/***************************************************************
* Name        : List
* Author      : Evan Bunnell
* Created     : 5/4/2023
***************************************************************/
#include "list.h"
#include <iostream>
#include <iomanip>
#include <cstddef>
using namespace std;

const int MAX_TANK = 2;
const int MAX_HEAL = 2;
const int MAX_DPS = 2;

/**************************************************************
* Name: Character
* Description: Default no-arg constructor
* Input parameters: none
***************************************************************/
List::List() {
    tank = 0;
    healer = 0;
    dps = 0;
}
/***************************************************************
* Class Functions
***************************************************************/
/**************************************************************
* Name: insert
* Description: Handles initial placement of object in the queue
* and increments appropriate role variable
* Input: Character
* Output: n/a
***************************************************************/
void List::insert(Character character) {
    //iterate counters up
    if (character.getRole() == "tank") {
        ++tank;
    }
    if (character.getRole() == "healer") {
        ++healer;
    }
    if (character.getRole() == "dps") {
        ++dps;
    }

    emplace(character);
}
/**************************************************************
* Name: emplace
* Description: Emplaces object into queue
* Input: Character
* Output: n/a
***************************************************************/
void List::emplace(Character character) {
    Node *temp, *curr, *pre = NULL;

    temp = new Node;
    temp->character = character;

    if (front == NULL or character.priority < front->character.priority) {
        temp->next = front;
        front = temp;
    }

    else {
        curr = front;

        while (curr and character.priority >= curr->character.priority) {
            pre = curr;
            curr = curr->next;
        }

        temp->next = pre->next;
        pre->next = temp;
    }
}
/**************************************************************
* Name: search
* Description: Searches for object in queue by name
* Input: String
* Output: Boolean
***************************************************************/
bool List::search(string name) {
    if (front == NULL) {
        return 0;
    }
    else {
        Node *curr;
        curr = front;

        for (int i = 0; i < size(); i++) {
            if (curr->character.getName() == name) {
                return 1;
            }
            curr = curr->next;
        }
        return 0;
    }
}
/**************************************************************
* Name: Delete
* Description: Deletes object from queue after search() confirms
* existence
* Input: String
* Output: n/a
***************************************************************/
void List::Delete(string name) {
    if (front == NULL) {
        return;
    }

    else {
        Node *curr, *pre;
        curr = front;

        while (curr->character.getName() != name) {
            pre = curr;
            curr = curr->next;
        }

        if (curr->character.priority == 1 || curr->character.priority == 4) {
            --tank;
        }
        if (curr->character.priority == 2 || curr->character.priority == 5) {
            --healer;
        }
        if (curr->character.priority == 3 || curr->character.priority == 6) {
            --dps;
        }

        cout << "\nDeleted character: " << curr->character.getName() << endl;


        if (curr == front) {
            front = curr->next;
        }
        else pre->next = curr->next;
        free (curr);
    }
}
/**************************************************************
* Name: display
* Description: Cycles through queue and calls Character print()
* function per object, numbers list
* Input: n/a
* Output: Numbered list of all objects
***************************************************************/
void List::display() {
    if (front == NULL){
        cout << "\nRoster is empty." << endl;
        return;
    }

    Node *curr = front;

    cout << "\nCurrently signed up: " << endl;

    int counter = 1;

    while (curr) {
        cout << setfill('0') << setw(2) << counter << ". ";
        ++counter;
        curr->character.print();
        curr = curr->next;
    }

    cout << endl;

    return;
}
/**************************************************************
* Name: size
* Description: Function for determining size of queue
* Input: n/a
* Output: Int
***************************************************************/
int List::size() {
    int size = 0;
    if (front == NULL)
        cout << "Roster is empty." << endl;

    Node *curr = front;

    while (curr) {
        ++size;
        curr = curr->next;
    }

    return size;
}
/**************************************************************
* Name: sort
* Description: Sorts list and changes priority based on MAX
* variables
* Input: n/a
* Output: n/a
***************************************************************/

void List::sort() {
    int tCount = 0, hCount = 0, dCount = 0;

    Node *curr, *pre;
    curr = front;

    //cout << "Tanks: " << tank << endl << "Healers: " << healer << endl << "DPS: " << dps << endl;     //FOR TESTING PURPOSES ONLY

    if (tank > MAX_TANK) {
        while (curr and curr->character.priority <= 1) {
            if (curr->character.priority == 1) ++tCount;
            if (tCount > MAX_TANK) {
                curr->character.priority += 3;

                emplace(curr->character);

                pre->next = curr->next;
            }
        pre = curr;
        curr = curr->next;
        }
    }
    else rePrio();

    if (healer > MAX_HEAL) {
        while (curr and curr->character.priority <= 2) {
            if (curr->character.priority == 2) ++hCount;
            if (hCount > MAX_HEAL) {
                curr->character.priority += 3;

                emplace(curr->character);

                pre->next = curr->next;
            }
        pre = curr;
        curr = curr->next;
        }
    }

    if (dps > MAX_DPS) {
        while (curr and curr->character.priority <= 3) {
            if (curr->character.priority == 3) ++dCount;
            if (dCount > MAX_DPS) {
                curr->character.priority += 3;

                emplace(curr->character);

                pre->next = curr->next;
            }
        pre = curr;
        curr = curr->next;
        }
    }
}

/**************************************************************
* Name: rePrio()
* Description: Iterates through queue, searches for priority
* of 4 or higher (denoting extra players), and re-prioritizes
* them to a starting priority, 1, 2, or 3.
* Input: n/a
* Output: n/a
***************************************************************/

void List::rePrio() {
    Node *curr, *pre;

    curr = front;

    while (curr and curr->character.priority <= 3) {
        pre = curr;
        curr = curr->next;
    }
    while (curr and curr->character.priority >= 4) {
        if (tank <= MAX_TANK && tank > 0 && curr->character.priority == 4) {
            curr->character.priority -= 3;

            emplace(curr->character);

            pre->next = curr->next;
        }
        if (healer <= MAX_HEAL && healer > 0 && curr->character.priority == 5) {
            curr->character.priority -= 3;

            emplace(curr->character);

            pre->next = curr->next;
        }
        if (dps <= MAX_DPS && dps > 0 && curr->character.priority == 6) {
            curr->character.priority -= 3;

            emplace(curr->character);

            pre->next = curr->next;
        }
        pre = curr;
        curr = curr->next;
    }
}
