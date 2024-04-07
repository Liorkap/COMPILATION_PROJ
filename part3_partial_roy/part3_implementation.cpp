#include "part3_header.hpp"

/**
 * @brief Merge operation, used for backpatching
 * @param A List of unpatched GOTO commands
 * @param B List of unpatched GOTO commands
 * @return The joined list of unpatched GOTO commands
 */
vector<int> merge(vector<int>& A, vector<int>& B) {
	A.insert(A.end(), B.begin(), B.end());
	return A;
}

/**
 * @brief Adds an empty block symbol table to the deepest function symbol table. Called when entering a new block
 */
void SymbolTable::AddBlockScope() {
	map<string, Symbol> scope;
	this->symbolTable.push_back(scope);
}

/**
 * @brief Adds a symbol to the deepest scope
 * @param identifier The name to add
 * @param type Then type of the name to add
 * @param memOffset the address in memory where the value of the name resides 
 */
void SymbolTable::AddSymbol(string identifier, Type type, int memOffset) {
	Symbol newSym;
	newSym.type = type;
	newSym.memOffset = memOffset;
	this->symbolTable.back().insert(make_pair(identifier, newSym));
}

/**
 * @brief Removes the deepest block symbol table. Called when leaving a block
 */
void SymbolTable::RemoveBlockScope() {
	this->symbolTable.pop_back();
}

/**
 * @brief The identifier exists in the most recent (deepest) scope
 * @param identifier The name of the symbol to search
 * @return True if the identifier exists in the most recent scope and false otherwise
 */
bool SymbolTable::IsExist(string identifier) {
	if (!this->symbolTable.size()) return false;
	else return (this->symbolTable.back().find(identifier) != symbolTable.back().end());
}

/**
 * @brief Searches a record for a name in the scope of a function (in the seepest function symbol table)
 * @return A pointer to the record if it's found and nullptr if it's not found
 */
Symbol* SymbolTable::GetRecord(string identifier) {
	for (auto it = this->symbolTable.rbegin(); it != this->symbolTable.rend(); it++) {
		auto symbolTableEntry = it->find(identifier);
        if (symbolTableEntry != it->end()) {
			return &(symbolTableEntry->second);
		}
	}
	return nullptr;
}



/**
 * @brief Prints the symbol table. For debugging
 */
void SymbolTable::Print() {
	cout << "Depth --> ";
	for (auto scope = this->symbolTable.rbegin(); scope != this->symbolTable.rend(); scope++) {
		cout << "Scope: ";
		for (auto sym = scope->begin(); sym != scope->end(); sym++) {
        	cout << "name: " << sym->first << " type: " << sym->second.type << " ";
    	}
	}
}

/**
 * @brief Construct a new Buffer object and initializes the stack registers I1 and F0
 */
Buffer::Buffer() {

}

/**
 * @brief Lines tracker
 * @return The number of the next empty line of code in the buffer
 */
int Buffer::nextquad() {
	return code.size() + 1;
}

/**
 * @brief Emit operation. Adds a new Riski command to the buffer 
 * @param str The command to add 
 */
void Buffer::emit(const string& str) {
	code.push_back(str);
}

/**
 * @brief Backpatch operation
 * @param A A list to backpatch
 * @param quadAddr The address to be patched
 */
void Buffer::backpatch(vector<int> A, int quadAddr) {
	for (int i = 0; i < A.size(); i++) {
		// code addresses starting from 1.
		// arrays/vectors starting from 0.
		// so A[i] - 1 is the correct offset.
		code[A[i] - 1] += to_string(quadAddr) + " ";
	}
}

/**
 * @brief Prints the current data in the buffer. Actually it will be called once at the end of the compilation process
 * @return The Riski code
 */
string Buffer::print() {
	string codeToPrint;
	for (int i = 0; i < code.size(); ++i)
		codeToPrint += code[i] + "\n";
	return codeToPrint;
}
