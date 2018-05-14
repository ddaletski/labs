#include <iostream>
#include <vector>


std::vector<char> palindrome(const std::vector<char>& digits) {
	std::vector<char> result(digits.size());
	char freq_[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	char* freq = freq_;

	const char* src = digits.data();
	char* dst = result.data();

	int size_ = digits.size();

	bool has_odd_freq = false;

	__asm {
		mov ecx, src;
		mov edx, freq;

		mov esi, size_;
		add esi, ecx;  // esi points to the end of src

		loop_start:
			cmp ecx, esi;
			jge loop_end;

			xor eax, eax;
			mov al, [ecx];
			add eax, freq;

			mov ebx, [eax];
			inc ebx;
			mov [eax], ebx;

			inc ecx;
			jmp loop_start;

		loop_end:
			mov ecx, dst;
	}

	for (int i = 0; i < 10; ++i) {
		std::cout << i << ": " << int(freq[i]) << std::endl;
	}

	return result;
}


int main() {
	palindrome({ 1, 2, 3, 4, 1, 2 });
	system("pause");
	return 0;
}