#include <iostream>
#include <string>
#include "colours.h"
#include "kmp.h"

using namespace std;

/** constructor */
kmpSearcher::kmpSearcher(const string &pattern)
{
    ptrn = pattern;
    ptrnLen = ptrn.length();    
    lookup = new int[ptrnLen+1];
}

/** destructor */
kmpSearcher::~kmpSearcher()
{
    delete[] lookup;
}


/**
 *  builds the lookup array for searching. 
 *  stores the width of the widest border for each 
 *  prefix of the pattern.
 */

void kmpSearcher::ptrnPreprocess()
{
    int i = 0, j = -1;
    lookup[i] = j;
    
    while (i < ptrnLen) {
        
        while (j>=0 && ptrn[i]!=ptrn[j])
            j = lookup[j];
        
        i++;
        j++;
        lookup[i] = j;
    }
}


/**
 *  finds the first occurence of pattern in line.
 */

int kmpSearcher::kmpSearch(const string &line)
{
    int i = 0, j = 0;
    lineLen = line.length();
     
    while (i < lineLen) {

        while (j>0 && line[i]!=ptrn[j])
            j = lookup[j];
        
        i++;   // tracks char in line string
        j++;   // tracks char in pattern string

        // match found
        if (ptrn[j-1]==line[i-1] && j==ptrnLen)
            return i - ptrnLen;
    }

    return -1;
}


/**
 *  finds and highlights all occurences of
 *  pattern in line.
 */

void kmpSearcher::searchLine(const string &line)
{
    ptrnPreprocess();

    int start = 0;
    int posn = kmpSearch(line);
    bool found = false;

    while (posn!=-1) {
        
        cout << line.substr(start, posn);
        cout << CYAN << ptrn << RESET;

        start += posn + ptrnLen;
        posn = kmpSearch(line.substr(start));
        
        found = true;
    }
    
    if (found)
        cout << line.substr(start) << endl;
}

int main(int argc, char *argv[])
{
    if (argc==3) {

        string pattern(argv[1]);
        string text(argv[2]);

        cout << "pattern = " << pattern << endl;
        cout << "text = " << text << endl;
        
        kmpSearcher kmp(pattern);
//        kmp.ptrnPreprocess();
        kmp.searchLine(text);
    } else {
        cerr << "usage: ";
        cerr << argv[0] << " " << "<pattern> <text>";    
    }
}

