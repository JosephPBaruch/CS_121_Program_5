/* main.cpp
   Joseph Baruch 
   CS 121
   Professor Bolden
   Read TV Series File into a Binary Search Tree
   Due: Wednesday, April 26, 2023
 */
 
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <string.h>
#include <stdlib.h>
#include "tree.cpp"
#include "list.h"
#include "list.cpp"
 
using namespace std;

// tree class instances declaration
tree t; 

// function prototypes
int ReadTVFile(); 
void GetSeriesName( char line[], char seriesName[] ); 
void GetYears( char line[], int & yStart, int & yEnd );

int main(){
    int nSeries = 0;
    nSeries = ReadTVFile();

    cout << "\nSeries Titles: " << endl;
    t.printSeriesName( t.rootPtr );
    cout << endl;
   

    // NCIS, McHale’s Navy, The Prisoner, The Office, F Troop, Mary Tyler Moore
    char title[] = {"Mary Tyler Moore"}; 
    cout << "\nAll actors of " << title << ":" << endl;
    t.printActorsOf( t.rootPtr, title ); 
    cout << endl;

    // Bill Daily, Dana Elcar, Andy Griffith, Tress MacNeille, Chris Potter, Dick Sargent 
    char actor[] = {"Dick Sargent"}; 
    cout << "\nAll shows that star " << actor << ":" << endl;
    t.printShowsOf( t.rootPtr, actor ); 
    cout << endl;

    // (2005, 2015), (1990, 2000)
    int printStart = 1990; 
    int printEnd = 2000; 
    cout << "\nShows Priemered between " << printStart << " and " << printEnd << ":" << endl;
    t.printShowsInDecade( t.rootPtr, printStart, printEnd ); 
    cout << endl;

   return EXIT_SUCCESS;
}

int IndexOf( char s[], char c ){ // finds the index (in the array) of a char 
    int i = 0;
    // while current position in array isnt '\0' or c
    while( s[i] != '\0' && s[i] != c )
       i++; // increment current position to evaluate in loop
    return i;
}

int ReadTVFile(){ // Reads in the TV Series File and calls AddSeries()
    ifstream fIn( "tvDB.txt", ios::in ); // opens file
    if( !fIn ){ //checks to see if file is open
        cout << "Unable to open \"tvDB\" data file" << endl;
        exit( -1 ); // end program if file isn't open
    }
    // ------ Variable Declarations ----------
    const int MAX_LINE = 128;
    char line[MAX_LINE];
    char seriesName[MAX_LINE];
    char seriesCategory[MAX_LINE/2];
    char seriesURL[MAX_LINE];
    char actorName[MAX_LINE/2];
    int  yStart, yEnd;
    int nSeries = 0;

    while( fIn.getline( line, MAX_LINE ) ){ // while file isnt fully read
        if( strlen(line) == 0 ) // if length of string ins't empty
            continue;
        GetSeriesName( line, seriesName ); // get series name 
        GetYears( line, yStart, yEnd ); // get series years
        fIn.getline( seriesCategory, MAX_LINE/2 ); // getline for series category
        fIn.getline( seriesURL, MAX_LINE ); // getline for series URL
        fIn.getline( line, MAX_LINE/2 ); // getline for actors 

        list * h = new list; // declare a new pointer to a list instance

        while( strlen(line) > 0 ){ // while line is greater than 0
            strcpy( actorName, line ); // copy string for actor name
            h->addNode( actorName ); // add actor to front of list
            fIn.getline( line, MAX_LINE/2 ); // new getline if more than one actor
        }
        nSeries++; // increment the number of series counter
        // -------- Add current series to the tree ------------
        t.AddSeries( t.rootPtr, seriesName, seriesCategory, seriesURL, *h, yStart, yEnd );
    }
    fIn.close(); // close the file
    return nSeries;
}

void RemoveBlanksFromString( char s[] ){ // removes blanks from string in GetSubString()
    int sLen = strlen( s ); 
    for( int i = sLen ; i >= 0 ; i-- ){ // works back to front in array
        if( isalpha(s[i]) )
            break;
       if( s[i] == ' ' ) // if array index is empty 
           s[i] = '\0'; // set as '\0'
    }
}

void GetSubString( char s[], int start, int end, char res[] ){ // gets Substring to be set to result array
    int i;
    int iRes = 0;    //  index of result string initialization
    for( i = start ; i < start+end ; i++ ){
       res[iRes++] = s[i]; // copies from s[] into res[] at appropriate positions
    }
    res[iRes] = '\0';
    RemoveBlanksFromString( res ); // remove the blanks from resulting string
}

void GetSeriesName( char line[], char seriesName[] ){ // get series name
    int yearStart;
    yearStart = IndexOf( line, '(' ); // find index of '(' (end of series name)
    // gets series name by stopping when the current position in '('
    GetSubString( line, 0, yearStart-1, seriesName ); 
}

void GetYears( char line[], int & yStart, int & yEnd ){ // get yStart and yEnd
    char tmpString[8];
    char yearString[16];
    int yearStart, yearEnd;
    
    yearStart = IndexOf( line, '(' ); // yStart starts right after '('
    yearEnd = IndexOf( line, ')' ); // yEnd ends right before ')'

    // --------------- Get both years together -------------------
    GetSubString( line, yearStart+1, yearEnd-yearStart-1, yearString );

    // --------- Seperate out yStart -----------
    GetSubString( yearString, 0, 4, tmpString );
    yStart = atoi( tmpString ); // set yStart as an integer value

    // ------------------- Separate out yEnd --------------------
    GetSubString( yearString, 7, 4, tmpString );  // 7? not ’-’!
    yEnd = atoi( tmpString ); // set yEnd as an integer value
}