.486
.model flat

.data
freq db 10 dup(0)
size_ dword 0
dst db 1000 dup(0)

.code


@can_be_palindrome@8 proc
	; ecx is sequence
	; edx is seq size

	push ebx;
	push esi;

	mov size_, edx;
	mov esi, edx;
	add esi, ecx;  // esi points to the end of src
;	mov edx, freq;

	loop_start:
		cmp ecx, esi;
		jge loop_end;

		xor eax, eax;
		mov al, [ecx];
		xor ebx, ebx;
		mov bl, freq[eax];
		inc bl;
		mov freq[eax], bl;

		inc ecx;
		jmp loop_start;

	loop_end:
		mov ecx, 0;     left index
		mov esi, size_
		dec esi ;       right index
		mov ebx, 0;     ebx is current freq's index

	before:
		cmp esi, ecx;
		jl pre_end;

		xor eax, eax;
		mov al, freq[ebx];
		cmp al, 2;
		jl next_dig

		;// add current digit to dst ///
		mov dst[ecx], bl;
		mov dst[esi], bl;
		;///////////////////////////////

		dec esi;
		inc ecx;

		cmp ebx, 10;
		jge pre_end;

		xor eax, eax;
		mov al, freq[ebx];
		sub al, 2;
		mov freq[ebx], al;

		jmp before;

	next_dig:
		inc ebx;
		jmp before;

	pre_end:
		mov ebx, 0;      // ebx is current freq's index

		xor eax, eax;  // eax is sum of remained freqs

	sstart:
		mov al, freq[ebx];
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
		
		mov eax, size_;
		xor edx, edx;

		push ecx;
		mov ecx, 2
		div ecx;
		pop ecx;

		mov ebx, esi;
		mov dst[eax], bl;

		jmp done;

	mark_digit:
		mov esi, ebx;
		jmp after_mark;


	impossible:
		mov eax, 0;
		jmp very_end;

	done:
		mov eax, offset dst;
		jmp very_end;

	very_end:
		pop esi;
		pop ebx;

	ret
@can_be_palindrome@8 endp


;----------------------------------------------
END
;----------------------------------------------
