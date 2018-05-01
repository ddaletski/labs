#include <iostream>
#include <string>


int main() {

	int numerator;
	unsigned int denominator;

	std::cout << "numerator: ";
	std::cin >> numerator;
	std::cout << "denominator: ";
	std::cin >> denominator;

	std::cout << "before: " << numerator << "/" << denominator << std::endl;

	__asm {
		mov eax, numerator;
		mov ecx, denominator;
		mov edx, 0;

		cmp eax, 0;
		jl is_negative;  // if numerator < 0 => negate it

		body:
			cmp eax, ecx;  // if eax < ecx, swap them
			jl swap_a_c;
		after_swap:
			mov edx, 0;
			div ecx;  // divide eax by ecx

			cmp edx, 0;  // if remainder is 0 - abs(gcd) is in ecx
			je end;

			mov eax, edx;  // else - move remainder in eax to repeat operation
			mov edx, 0;

			jmp body;


		swap_a_c:
			mov edx, eax;
			mov eax, ecx;
			mov ecx, edx;
			jmp after_swap;


		is_negative:
			neg eax;
			jmp body;


		end:
			mov eax, numerator;
			cdq;
			idiv ecx;
			mov numerator, eax;

			mov eax, denominator;
			cdq;
			div ecx;
			mov denominator, eax;
	}


	std::cout << "after: " << numerator << "/" << denominator << std::endl;

	system("pause");
	return 0;
}
