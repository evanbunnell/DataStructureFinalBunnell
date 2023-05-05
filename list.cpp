/***************************************************************
* Name        : Class Name
* Author      : Evan Bunnell
* Created     : 4/24/2019
***************************************************************/
#include "list.h"
#include <iostream>
#include <iomanip>
#include <cstddef>
using namespace std;

const int MAX_TANK = 2;
const int MAX_HEAL = 2;
const int MAX_DPS = 2;

List::List() {
    tank = 0;
    healer = 0;
    dps = 0;
}

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

        if (curr->character.getRole() == "tank") {
            --tank;
        }
        if (curr->character.getRole() == "healer") {
            --healer;
        }
        if (curr->character.getRole() == "dps") {
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

void List::peak() {
    cout << "Peak element is :" << &front->character << endl;
}

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

void List::sort() {
    int i;

    Node *curr, *pre;
    curr = front;

    cout << "Tanks: " << tank << endl << "Healers: " << healer << endl << "DPS: " << dps << endl;

    rePrio();

    if (tank > MAX_TANK) {
        for (i = 0; i < MAX_TANK; i++) {
            pre = curr;
            curr = curr->next;
        }
        while (curr and curr->character.getRole() == "tank") {
            curr->character.priority += 3;

            emplace(curr->character);

            pre->next = curr->next;

            pre = curr;
            curr = curr->next;
        }
    }

    curr = front;
    if (healer > MAX_HEAL) {
        if (tank > MAX_TANK) {
            for (i = 0; i < MAX_TANK + MAX_HEAL; i++) {
                pre = curr;
                curr = curr->next;
            }
        }
        else {
            for (i = 0; i < tank + MAX_HEAL; i++) {
            pre = curr;
            curr = curr->next;
            }
        }
        while (curr and curr->character.getRole() == "healer") {
            curr->character.priority += 3;

            emplace(curr->character);

            pre->next = curr->next;

            pre = curr;
            curr = curr->next;
        }
    }

    curr = front;
    if (dps > MAX_DPS) {
        if (tank > MAX_TANK && healer > MAX_HEAL) {
            for (i = 0; i < MAX_TANK + MAX_HEAL + MAX_DPS; i++) {
                pre = curr;
                curr = curr->next;
            }
        }
        else if (tank > MAX_TANK){
            for (i = 0; i < MAX_TANK + healer + MAX_DPS; i++) {
            pre = curr;
            curr = curr->next;
            }
        }
        else if (healer > MAX_HEAL){
            for (i = 0; i < tank + MAX_HEAL + MAX_DPS; i++) {
            pre = curr;
            curr = curr->next;
            }
        }
        else {
            for (i = 0; i < tank + healer + MAX_DPS; i++) {
                pre = curr;
                curr = curr->next;
            }
        }
        while (curr and curr->character.getRole() == "dps") {
            curr->character.priority += 3;

            emplace(curr->character);

            pre->next = curr->next;

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
