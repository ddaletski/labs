#include <iostream>
#include <string>


bool checkAnagramme(const std::string& s1, const std::string& s2) {
	const char* src1 = s1.c_str();
	int size_1 = s1.size();

	const char* src2 = s2.c_str();
	int size_2 = s2.size();

	char freq1_[256] = { 0 };
	char freq2_[256] = { 0 };

	char* freq1 = freq1_;
	char* freq2 = freq2_;

	bool result = false;


	__asm {
		push esi;
		push edx;

		mov ecx, src1;
		mov edx, freq1;

		mov esi, size_1;
		add esi, ecx;  // esi points to the end of src

	loop_start:
		cmp ecx, esi;
		jge loop_end;

		xor eax, eax;
		mov al, [ecx];
		add eax, freq1;

		mov ebx, [eax];
		inc ebx;
		mov[eax], ebx;

		inc ecx;
		jmp loop_start;

	loop_end:
		mov ecx, src2;
		mov edx, freq2;

		mov esi, size_2;
		add esi, ecx;  // esi points to the end of src

	loop_start_2:
		cmp ecx, esi;
		jge loop_end_2;

		xor eax, eax;
		mov al, [ecx];
		add eax, freq2;

		mov ebx, [eax];
		inc ebx;
		mov[eax], ebx;

		inc ecx;
		jmp loop_start_2;
	loop_end_2:

		mov eax, freq1;
		mov ebx, freq2;

		mov ecx, 0;
		mov edx, 0;
		mov edi, 0;

	lp:
		mov cl, [eax+edi];
		mov dl, [ebx+edi];
		cmp cl, dl;

		jne very_end;

		inc edi;
		cmp edi, 255;
		je true_result;

		jmp lp;


	true_result:
		mov result, 1;

	very_end:
		pop edx;
		pop esi;
	}

	std::cout << "\nfreq1:\n";
	for (int i = 0; i < 256; ++i) {
		if(freq1_[i])
			std::cout << (unsigned char)(i) << ": " << int(freq1_[i]) << std::endl;
	}

	std::cout << "\nfreq2:\n";
	for (int i = 0; i < 256; ++i) {
		if(freq2_[i])
			std::cout << (unsigned char)(i) << ": " << int(freq2_[i]) << std::endl;
	}

	std::cout << std::endl;

	return result;
}


int main(int argc, char* argv[]) {
	std::string s1, s2;

	std::cout << "str1: ";
	std::cin >> s1;
	std::cout << "str2: ";
	std::cin >> s2;

	bool isAnagramme = checkAnagramme(s1, s2);

	std::cout << "are annagrammes: " << isAnagramme << std::endl;

	system("pause");
	return 0;
}
