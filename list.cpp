/* list.cpp
    Joseph Baruch
 */

#include <iostream>
#include "list.h"

using namespace std;

list::list(){
    head = NULL; // sets head = null
}

// adds node to the front of the linked list
void list::addNode( string a ){
    nodePtr t = new Node;
    t->actN = a;
    t->next = NULL;

    if( head == NULL ){
        head = t;
    }else{
        t->next = head;
        head = t;
    }
}

// prints linked list
void list::print(){
    nodePtr p = head;
    while( p != NULL ){
        cout << p->actN << endl; 
        p = p->next;
    }
}

// returns true if string a is in list
bool list::find( string a ){
    nodePtr p = head; // aux pointer
    while( p != NULL ){ 
        if( p->actN == a){
            return true;
        }
        p = p->next;
    }
    // return false if a not found
    return false; 
}