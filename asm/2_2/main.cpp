#include <iostream>
#include <vector>


std::pair<bool, std::vector<char>> palindrome(const std::vector<char>& digits) {
	std::vector<char> result(digits.size());
	char freq_[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	char* freq = freq_;

	const char* src = digits.data();
	char* dst = result.data();

	int size_ = digits.size();

	bool possible = false;

	__asm {
		push eax;
		push ebx;
		push ecx;
		push edx;
		push esi;


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
			mov esi, size_;  // esi is dst size
			dec esi;

			mov ecx, dst;    // ecx is dst front
			mov edx, freq;   // edx is freq start
			mov ebx, 0;      // ebx is current freq's index

		before:
			cmp esi, 0;
			jle end;

			xor eax, eax;
			mov al, [edx+ebx];
			cmp eax, 2;
			jl next_dig

			// add current digit to dst ///
			mov [ecx], bl;
			mov [ecx + esi], bl;
			///////////////////////////////

			dec esi;
			dec esi;
			inc ecx;

			cmp ebx, 10;
			jge end;

			xor eax, eax;
			mov al, [edx + ebx];
			sub al, 2;
			mov[edx + ebx], al;

			jmp before;

		next_dig:
			inc ebx;
			jmp before;

		end:
			mov ecx, dst;    // ecx is dst front
			mov edx, freq;   // edx is freq start
			mov ebx, 0;      // ebx is current freq's index

			xor eax, eax;  // eax is sum of remained freqs

		sstart:
			mov al, [edx + ebx];
			add ah, al;

			cmp al, 1;
			je mark_digit;
		after_mark:

			inc ebx;

			cmp ebx, 10;
			jge eend;

			jmp sstart;

		eend:
			cmp ah, 1;
			jl done;
			jg impossible;
			
		possible:
			mov eax, size_;
			xor edx, edx;

			push ecx;
			mov ecx, 2
			div ecx;
			pop ecx;

			mov ebx, esi;
			mov[ecx + eax], bl;

			jmp done;

		mark_digit:
			mov esi, ebx;
			jmp after_mark;


		impossible:
			mov possible, 0;
			jmp very_end;

		done:
			mov possible, 1;
			jmp very_end;

		very_end:
			pop esi;
			pop edx;
			pop ecx;
			pop ebx;
			pop eax;

	}

	return std::make_pair(possible, result);
}


void checkSequence(const std::vector<char>& seq) {
	std::cout << "Input sequence: ";
	for (int i = 0; i < seq.size(); ++i) {
		std::cout << int(seq[i]) << " ";
	}
	std::cout << std::endl;

	std::pair<bool, std::vector<char>> result = palindrome(seq);

	if (result.first) {
		std::cout << "Possible: ";
		for (int i = 0; i < result.second.size(); ++i) {
			std::cout << int(result.second[i]) << " ";
		}
	} else {
		std::cout << "Impossible";
	}
	std::cout << std::endl << std::endl;
}


int main() {
	std::vector<char> seq;

	seq = { 2, 1, 3, 3, 0, 0, 0, 1, 2 };
	checkSequence(seq);

	seq = { 2, 1, 3, 3, 0, 0, 0, 0, 0, 1, 2 };
	checkSequence(seq);

	seq = { 2, 1, 3, 9, 0, 0, 0, 1, 2 };
	checkSequence(seq);

	seq = { 2, 1, 7, 3, 0, 0, 1, 2 };
	checkSequence(seq);

	system("pause");
	return 0;
}