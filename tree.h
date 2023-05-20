/* tree.h
   Joseph Baruch 
 */
#ifndef TREE_H // file guard
#define TREE_H

#include <iostream>
#include <string>
#include "list.h"

using namespace std;

// contstant array size
const int MAX_LINE = 128; 

class tree{
    private:
        // BSTreeNode that constains all required series information
        struct BSTreeNode{
            list actorList; // instance of linked list
            char line[MAX_LINE];
            char seriesName[MAX_LINE];
            char seriesCategory[MAX_LINE/2];
            char seriesURL[MAX_LINE];
            string actorsName[MAX_LINE];
            int  yStart, yEnd;
            BSTreeNode * leftPtr; // left pointer
            BSTreeNode * rightPtr; // right pointer
        };
    public:
        typedef BSTreeNode * TreePtr; // declaration of TreePtr variable type
        TreePtr rootPtr; // declare rootPtr ( initialized in tree() )
        tree(); // constructor
        // ---------------------- Adds series to tree ( called in ReadTVFile ) ---------------------------
        void AddSeries( TreePtr& t, char name[], char cate[], char url[], list h, int start, int end );

        void printActorsOf(TreePtr& t, string name ); // print all actor names of a given show 
        void printShowsOf(TreePtr& t, string act ); // print all shows of a given actor
        void printShowsInDecade( TreePtr& t, int start, int end ); // print all shows primered in a given decade 
        void printSeriesName( TreePtr& t ); // print all show names 
};

#endif // end file guard