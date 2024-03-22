#include "part3_header.hpp"

// implement merge operation
vector<int> merge(vector<int>& A, vector<int>& B) {
	A.insert(A.end(), B.begin(), B.end());
	return A;
}

int Buffer::nextquad() {
	return code.size() + 1;
}

void Buffer::emit(const string& str) {
	code.push_back(str);
}

void Buffer::backpatch(vector<int> A, int quadAddr) {
	for (int i = 0; i < A.size(); i++) {
		// code addresses starting from 1.
		// arrays/vectors starting from 0.
		// so A[i] - 1 is the correct offset.
		code[A[i] - 1] += to_string(quadAddr) + " ";
	}
}

string Buffer::print() {
	for (int i = 0; i < code.size(); ++i)
		cout << code[i] + "\n";
}
