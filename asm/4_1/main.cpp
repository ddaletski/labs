#include <iostream>
#include <iostream>
#include <string>
#include <vector>



extern "C" {
	char* __fastcall can_be_palindrome(const char* seq, int n);
	char* __cdecl can_be_palindrome2(const char* seq, int n);
	char* __stdcall can_be_palindrome3(const char* seq, int n);
}


void checkSequence(const std::vector<char>& seq) {
	std::cout << "Input sequence: ";
	for (int i = 0; i < seq.size(); ++i) {
		std::cout << int(seq[i]) << " ";
	}

	if (!seq.size()) {
		std::cout << "empty sequence" << std::endl << std::endl;
		return;
	}

	char* result = 0;

	std::cout << "\ncdecl   : ";
	result = can_be_palindrome2(seq.data(), seq.size());
	if (result == 0) {
		std::cout << "impossible" << std::endl;
	}
	else {
		std::cout << "possible: ";
		for (int i = 0; i < seq.size(); ++i) {
			std::cout << int(result[i]);
		}
	}

	std::cout << "\nfastcall: ";
	result = can_be_palindrome(seq.data(), seq.size());
	if (result == 0) {
		std::cout << "impossible" << std::endl;
	}
	else {
		std::cout << "possible: ";
		for (int i = 0; i < seq.size(); ++i) {
			std::cout << int(result[i]);
		}
	}


	std::cout << "\nstdcall : ";
	result = can_be_palindrome3(seq.data(), seq.size());
	if (result == 0) {
		std::cout << "impossible" << std::endl;
	}
	else {
		std::cout << "possible: ";
		for (int i = 0; i < seq.size(); ++i) {
			std::cout << int(result[i]);
		}
	}


	std::cout << std::endl << std::endl;
}



int main(int argc, char* argv[]) {
	std::vector<char> seq;

	seq = { 2, 1, 3, 3, 0, 0, 0, 1, 2 };
	checkSequence(seq);

	seq = { 2, 1, 3, 3, 0, 0, 0, 0, 1, 2 };
	checkSequence(seq);


	seq = {1, 1, 1, 3, 3, 3};
	checkSequence(seq);

	seq = {1};
	checkSequence(seq);

	system("pause");
	return 0;
}
