/* link.h
   Joseph Baurch*/

#ifndef LINK_H
#define LINK_H

#include <iostream> 

using namespace std;

class list{
    private:
        struct Node{ 
            string actN;
            Node * next;
        };
        typedef struct Node * nodePtr;
        nodePtr head; // creates head nodePtr
    public:
        list(); // sets head = NULL
        void addNode(string a); // add node to list
        void print(); // print list
        bool find( string a ); // sees if list contains string
};

#endif