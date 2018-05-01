#include <iostream>


int f1(int x) {
	return (pow(double(x), 5) + 2 * (x*x - 4) + x) / pow(double(x), 3);
}

int f2(int x) {
	return (2 * x - 1) * (2 * x + 1) * (x + 3) / (2 * x);
}


int f3(int x) {
	return (4 * x - 1) * (4 * x + 1) / 4;
}


int f1_asm(int x) {
	int result;

	__asm {
		mov eax, x;
		mov ebx, x;

		mul ebx;
		mov ecx, eax;  // ecx = x^2
		mul ebx;
		mul ebx;
		mul ebx; // eax = x^5
		push eax;
		mov eax, ecx;
		mul ebx;
		mov ebx, eax; // ebx = x^3
		pop eax;

		sub ecx, 4;
		add eax, ecx;
		add eax, ecx;
		add eax, x;

		div ebx;
		mov result, eax;
	}

	return result;
}


int f2_asm(int x) {
	int result;

	__asm {
		mov eax, x;
		add eax, eax;

		mov ebx, eax;
		push eax;

		add eax, 1;
		sub ebx, 1;
		mov ecx, x;
		add ecx, 3;

		mul ebx;
		mul ecx;
		pop ecx;
		div ecx;

		mov result, eax;
	}

	return result;
}


int f3_asm(int x) {
	int result;

	__asm {
		mov eax, x;
		mov ebx, 4;
		mul ebx;

		mov ecx, eax;
		sub eax, 1;
		add ecx, 1;

		mul ecx;
		div ebx;

		mov result, eax;
	}

	return (4 * x - 1) * (4 * x + 1) / 4;
}


int main() {

	std::cout << "---f1---" << std::endl;
	for (int i = 1; i <= 10; ++i) {
		std::cout << f1(i) << " " << f1_asm(i) << std::endl;
	}

	std::cout << "---f2---" << std::endl;
	for (int i = 1; i <= 10; ++i) {
		std::cout << f2(i) << " " << f2_asm(i) << std::endl;
	}

	std::cout << "---f2---" << std::endl;
	for (int i = 1; i <= 10; ++i) {
		std::cout << f3(i) << " " << f3_asm(i) << std::endl;
	}
	return 0;
}