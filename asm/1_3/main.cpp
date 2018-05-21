#include <iostream>
#include <vector>


std::vector<int> factorize(int x) {
	std::vector<int> factors;

	int factor = 2;
	while (x > 1) {
		if (x % factor == 0) {
			factors.push_back(factor);
			x /= factor;
		} else {
			++factor;
		}
	}

	return factors;
}


std::vector<int> factorize_asm(int x) {
	std::vector<int> factors;
	factors.resize(log2(x) + 1);
	int* fdata = factors.data();
	int actual_size;

	__asm {
		mov eax, x;			// current divident
		mov ebx, 2;			// current factor
		mov ecx, fdata;		// memory array

	loop_start:
		cmp eax, 1;
		jle end;

		mov esi, eax; // store eax
		xor edx, edx;
		div ebx;
		cmp edx, 0;
		jne next_divisor;

		mov [ecx], ebx;
		add ecx, 4;
		jmp loop_start;


	next_divisor:
		mov eax, esi; // restore eax
		inc ebx;
		jmp loop_start;

	end:
		sub ecx, fdata;
		mov eax, ecx;
		xor edx, edx;
		mov ebx, 4;
		div ebx;
		mov actual_size, eax;
	}

	factors.resize(actual_size);

	return factors;
}


void print_factors(const std::vector<int>& factors) {
	std::cout << "prime factorization: ";

	if (factors.empty()) {
		std::cout << 1 << std::endl;
		return;
	}

	std::cout << factors[0];
	for (int i = 1; i < factors.size(); ++i) {
		std::cout << "*" << factors[i];
	}

	std::cout << std::endl;
}


int main() {
	auto factors = factorize(2*2*2*3*5*7*11*19);
	print_factors(factors);

	auto asm_factors = factorize_asm(2 * 2 * 2 * 3 * 5 * 7 * 11 * 19 * 2);
	print_factors(asm_factors);

	system("pause");
	return 0;
}