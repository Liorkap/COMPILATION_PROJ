#ifndef _PART3_HEADER
#define _PART3_HEADER

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stack>

#define LEXICAL_ERROR 1
#define SYNTAX_ERROR 2
#define SEMANTIC_ERROR 3
#define OPERATIONAL_ERROR 9 

using namespace std;

typedef enum { int_type = 4, float_type = 8, void_type = 0} Type;


// Define the relevant symbol/token fields
typedef struct {
	// id name if it has one
	string str;
	// token's type
	Type type;

	// address in our growing stack memory, possible range is 0-1023
	int memAddr;
	
	// token's width, how many bytes it takes in memory
	int width;

	// the quad address in the final riski code, starting from 1.
	int quadAddr;

	// Number of allocated register for this symbol/token
	int regNum;

	// maintain Lists for further backpatching
	vector<int> nextList;
	vector<int> trueList;
	vector<int> falseList;

} yystype;

// for symbolTable entry, only type and memAddr are relevant I guess.
class Symbol {
public:
	Type type; // type of the symbol(INT FLOAT VOID)
	int memAddr; // address in the stack memory
};

// The main buffer holding the riski code
class Buffer {
	vector<string> code;
public:
	// default constructor
	Buffer() {};

	// Return the next empty line in the buffer
	int nextquad();

	// Emit operation
	void emit(const string& str);

	// Backpatch operation
	void backpatch(vector<int> A, int quadAddr);

	// print the current data in the buffer
	// actually it will be called once at the end of the compilation process
	string print();

	//default destructor
	~Buffer() { };
};

// Global variables
static Buffer* buffer;
static stack< map<string, Symbol> > symbolTables; // each stack entry is a symbolTable according to current BLK depth

/* some functionTable has to be implemented aswell*/

static int currReturnType; // hold the return type from the function - INT,FLOAT,VOID
static int currentScopeRegsNum = 0; // Number of registers in use in the current function
static int currMemOffset = 0; // a stack pointer, pointing to the curernt empty slot in the memory.
static int lastMemOffset = 0; // used for calculating bytes offset for new data, currMemOffset - lastMemOffset.


// merge operation, used for backpatching.
vector<int> merge(vector<int>& A, vector<int>& B); 

#define YYSTYPE yystype

#endif
