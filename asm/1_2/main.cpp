#include <iostream>
#include <string>

__int16 randint16(bool last=false) {
	__int16 result = 0;

	int end = last ? 15 : 16;

	for (int i = 0; i < end; ++i) {
		result <<= 1;
		result += rand() % 2;
	}

	return result;
}

std::string i16_to_str(__int16 val) {
	std::string result;

	for (int i = 0; i < 16; ++i, val >>= 1) {
		result.push_back('0' + (val & 1));
	}

	std::reverse(result.begin(), result.end());
	return result;
}


char to_hex(__int8 val) {
	if (val < 10) {
		return '0' + val;
	} else {
		return 'A' + val - 10;
	}
}

std::string i16_to_hex(__int16 val) {
	std::string result;

	for (int i = 0; i < 4; ++i, val >>= 4) {
		result.push_back(to_hex(val & 15));
	}

	std::reverse(result.begin(), result.end());
	return result;
}


__int64 compose(__int16 little, __int16 mid, __int16 big) {
	__int64 result = 0;

	std::memcpy((char*)(&result), &little, 2);
	std::memcpy((char*)(&result)+2, &mid, 2);
	std::memcpy((char*)(&result)+4, &big, 2);

	return result;
}


int main() {
	__int16 A1 = randint16();
	__int16 A2 = randint16();
	__int16 A3 = randint16(true);

	__int64 A = compose(A1, A2, A3);

	__int16 B1 = randint16();
	__int16 B2 = randint16();
	__int16 B3 = randint16(true);

	__int64 B = compose(B1, B2, B3);

	std::cout << "A: " << A << "\nB: " << B << std::endl;

	__int16 C1, C2, C3;
	__asm {
		mov eax, 0;
		mov ebx, 0;

		mov ax, A1;
		mov bx, B1;
		add eax, ebx;
		mov C1, ax;

		shr eax, 16;
		mov ecx, eax; // store overflow in ecx

		/////////////

		mov eax, 0;
		mov ebx, 0;

		mov ax, A2;
		mov bx, B2;
		add eax, ebx;
		add eax, ecx; // add overflow of previous 16 bytes to current sum
		mov C2, ax;

		shr eax, 16;
		mov ecx, eax;

		/////////////

		mov eax, 0;
		mov ebx, 0;

		mov ax, A3;
		mov bx, B3;
		add eax, ebx;
		add eax, ecx;
		mov C3, ax;
	}

	__int64 C = compose(C1, C2, C3);
	std::cout << "C: " << C << std::endl;

	std::cout << "--------------- binary ----------------\n";
	std::cout << "A: " << i16_to_str(A3) << " " << i16_to_str(A2) << " " << i16_to_str(A1) << std::endl;
	std::cout << "B: " << i16_to_str(B3) <<  " " << i16_to_str(B2) << " " << i16_to_str(B1) << std::endl;
	std::cout << "C: " << i16_to_str(C3) <<  " " << i16_to_str(C2) << " " << i16_to_str(C1) << std::endl;

	std::cout << "--------------- hex ----------------\n";
	std::cout << "A: " << i16_to_hex(A3) << " " << i16_to_hex(A2) << " " << i16_to_hex(A1) << std::endl;
	std::cout << "B: " << i16_to_hex(B3) <<  " " << i16_to_hex(B2) << " " << i16_to_hex(B1) << std::endl;
	std::cout << "C: " << i16_to_hex(C3) <<  " " << i16_to_hex(C2) << " " << i16_to_hex(C1) << std::endl;


	system("pause");
	return 0;
}