#ifndef _PART3_HEADER
#define _PART3_HEADER

/** #include directives */
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <stack>
#include <list>
#include <tuple>
#include <cstdio>
#include <fstream>

/** #define directives */
#define LEXICAL_ERROR 1
#define SYNTAX_ERROR 2
#define SEMANTIC_ERROR 3
#define OPERATIONAL_ERROR 9 
#define OTHER_FILE -1

/** Using statements */
using namespace std;

/** Enums */
/** Type system of C-- and each type's size in bytes */
typedef enum { int_type = 4, float_type = 8, void_type = 0 } Type;

/**
 * @brief The type of each symbol and token. Each symbol and token assign values only to the relevant fieslds
 */
typedef struct {
	string value;	/**< The value associated with the token */
	Type type;		/**< Type */	
	int memOffset; 	/**< Address in our growing stack memory. Possible range is 0-1023 */
	int quadAddr;	/**< The quad address in the final riski code, starting from 1 */
	int regNum;		/**< Number of allocated registers for this symbol or token */

	/** Lists for further backpatching */
	vector<int> nextList;	/**< Next list */
	vector<int> trueList;	/**< True list */
	vector<int> falseList;	/**< False list */

	/** Lists for variables declaraion */
	vector<string> variablesList; 	/**< List of names of declared variables of the same type */
	
	/** Lists for parameters */
	vector<string> paramsList;		/**< List of names of parameters of a function */
	vector<Type> paramsTypeList; 	/**< List of type of the parameters of a function */
	
	/** Lists for arguments */
	vector<int> argsRegList; 		/**< List of register numbers that holds the results of the expressions that are passed to a function */
	vector<Type> argsTypeList;

} yystype;

/**
 * @brief Represents a symbol
 */
class Symbol {
public:
	Type type;
	int memOffset;
};

/**
 * @brief Represents the symbol table of our compiler 
 */
class SymbolTable {
private:
 	vector<map<string, Symbol>> symbolTable; /**< List of scopes symbol tables. The deeper the scope, the further it is in the list */

public:
	/**
	 * @brief Adds an empty block symbol table to the deepest function symbol table. Called when entering a new block
	 */
	void AddBlockScope();

	/**
	 * @brief Adds a symbol to the deepest scope
	 * @param identifier The name to add
	 * @param type Then type of the name to add
	 * @param memOffset the address in memory where the value of the name resides 
	 */
	void AddSymbol(string identifier, Type type, int memOffset);

	/**
	 * @brief Removes the deepest block symbol table. Called when leaving a block
	 */
	void RemoveBlockScope();

	/**
	 * @brief The identifier exists in the most recent (deepest) scope
	 * @param identifier The name of the symbol to search
	 * @return True if the identifier exists in the most recent scope and false otherwise
	 */
	bool IsExist(string identifier);

	/**
	 * @brief Searches a record for a name in the scope of a function (in the deepest function symbol table)
	 * @param identifier The symbol name to search
	 * @return A pointer to the most recent declaration of the identifier 
	 */
	Symbol* GetRecord(string identifier);

	/**
	 * @brief Prints the symbol table. For debugging
	 */
	void Print();
};

/**
 * @brief Represents a function found in the C-- program
 */
class Function {
public:
	int definitionLine; 			/**< The number of the first line of the definition in the Risky file */
	Type returnType; 				/**< The return type of the function (int, float, void). Part of the signature */
	vector<Type> paramsTypeList; 	/**< A list of the types of the parameters. Part of the signature */
	vector<int> calls;				/**< A list of line numbers in the Riski file where the function is called and need to be backpatched */
	bool isDefined;					/**< True if the function is a definition. Helps to validate that a function is defined once */ 
};

/**
 * @brief The main buffer that holds the Riski code
 */
class Buffer {
	vector<string> code;	/**< List of code lines */
public:
	/**
	 * @brief Construct a new Buffer object. Default constructor
	 */
	Buffer();

	/**
	 * @brief Lines tracker
	 * @return The number of the next empty line of code in the buffer
	 */
	int nextquad();

	/**
	 * @brief Emit operation. Adds a new Riski command to the buffer 
	 * @param str The command to add 
	 */
	void emit(const string& str);

	/**
	 * @brief Backpatch operation
	 * @param A A list to backpatch
	 * @param quadAddr The address to be patched
	 */
	void backpatch(vector<int> A, int quadAddr);

	/**
	 * @brief Prints the current data in the buffer. Actually it will be called once at the end of the compilation process
	 * @return The Riski code
	 */
	string print();

	/**
	 * @brief Destroy the Buffer object. Default destructor
	 */
	~Buffer() { };
};

/**
 * @brief Represents the register of the machine and the allocation of them along the program
 * 
 */

/** Globals - manages the compilation process */
static Buffer buffer;						/** A buffer to hold the code */
/** Stack and data management variables (current means the function or the block that is currently compiling) */
static SymbolTable symbolTable; 			/** Symbol table for non-function names in the C-- program. Key - identifier, value - all the symbols with that name */
static map<string, Function> functionTable;	/** Symbol table for function names in the C-- program. Key - identifier, value - the function symbol with that name  */
static int currentReturnType; 				/** Holds the return type from the current function (int, float, void) */						
static string currentFuncName;				/** The name of the function that its definition has just compiled */
static int currentMemOffset = 4;			/** The memory offset from the frame pointer (I1) for allocating local variables and registers and adrguments in function calls */
static int nextFreeIntReg = 2;				/** The number of the next int free register in a function scope */
static int nextFreeFloatReg = 1;			/** The number of the next float free register in a function scope */
static bool hasDefCreatedScope = false;		/** Flag. If a function definition creates the main block of a function then the blk symbol need not to it himself */

/** Special saved registers:
 * I0 - Holds the return address. Has to be saved in the stack since if we call another function this value will be overriden.
 * I1 - Frame pointer. Points to the return address and all alocations and accesses are done relative to it. 
 */

/**
 * @brief Merge operation, used for backpatching
 * @param A List of unpatched GOTO commands
 * @param B List of unpatched GOTO commands
 * @return The joined list of unpatched GOTO commands
 */
vector<int> merge(vector<int>& A, vector<int>& B); 

/**
 * @brief Searches a given name in the symbol table, in the possible scopes
 * 
 * @return A pointer to a record in the symbol table
 */
Symbol* findInSymbolTable(string identifier);

/**
 * @brief Adds a new symbol to the symbol table
 */
void addToSymbolTable(string identifier, Type type, int memAddr);

/** Setting the semantic value of each symbol and token to be of type struct yystep */
#define YYSTYPE yystype

#endif
