/* tree.cpp 
   Joseph Baruch
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include "tree.h"

using namespace std;

//  ------ constructor -----
tree::tree(){  
    rootPtr = NULL; // intialize the rootPtr = NULL
}

// ----- Add Series information (within BSTreeNode) to tree -------
void tree::AddSeries( TreePtr& t, char name[], char cate[], 
                      char url[], list h, int start, int end ){
    if( t == NULL ){ // if at the end of tree, place node
        // allocate new TreePtr
        TreePtr newPtr = new BSTreeNode;
        // initialize  all information for series in new TreePtr
        for(int i = 0; i < MAX_LINE; i++ ){
            newPtr->seriesName[i] = name[i];
            newPtr->seriesCategory[i] = cate[i];
            newPtr->seriesURL[i] = url[i];
        }
        newPtr->actorList = h;
        newPtr->yStart = start;
        newPtr->yEnd = end;

        // set left and right pointers = NULL
        newPtr->leftPtr = NULL;
        newPtr->rightPtr = NULL;

        t = newPtr; // place
    // if current position in tree's start year is less than start
    }else if( t->yStart <= start ){ 
        // go left in tree
        AddSeries( t->leftPtr, name, cate, url, h, start, end );
    // if current position in tree's start year is greater than start        
    }else{
        AddSeries( t->rightPtr, name, cate, url, h, start, end );
    }
}

//  --------- print all Series Names ----------
void tree::printSeriesName( TreePtr& t ){ 
    // printing using in-order traversal (recursion)
    if( t != NULL ) {   
        printSeriesName( t->leftPtr );
        cout << "-" << t->seriesName << endl;
        printSeriesName( t->rightPtr ); 
    }
}

// ------- print actors of a specific show ---------
void tree::printActorsOf( TreePtr& t, string a ){ 
    // printing using in-order traversal (recursion)
    if( t != NULL ) {   
        printActorsOf( t->leftPtr, a );
        // if current series name matches given series name
        if( t->seriesName == a ){ 
            // print list of actor names
            t->actorList.print();
        }
        printActorsOf( t->rightPtr, a ); 
    }
}

//  ------ print all shows of a given actor -----
void tree::printShowsOf(TreePtr& t, string act ){ 
    // printing using in-order traversal (recursion)   
    if( t != NULL ) {   
        printShowsOf( t->leftPtr, act );
        // if actor is found for series in list
        if( t->actorList.find( act ) ){ 
            cout << t->seriesName << endl;
        }
        printShowsOf( t->rightPtr, act ); 
    }
}

// ----- print all shows that premiered within a given decade ---
void tree::printShowsInDecade( TreePtr& t, int start, int end ){
    // printing using in-order traversal (recursion)    
    if( t != NULL ) {   
        printShowsInDecade( t->leftPtr, start, end );
        // if start is within given decade
        if( start <= t->yStart && end >= t->yStart ){
            cout << "-" << t->seriesName << endl;
        }
        printShowsInDecade( t->rightPtr, start, end ); 
    }
}

