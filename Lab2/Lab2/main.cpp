// main.cpp : Defines the entry point for the console application.
// by: Josh Buck

#include <stdio.h>
#include <iostream>

// Requirements
// 1) copy 12 bytes from the BSS section to the stack
// 2) copy 13 bytes from the heap to the data section
// 3) copy 14 bytes from the stack to the heap
// 4) copy 15 bytes from the data section to the BSS
// 5) copy 4 bytes from the text section to the data section

// Create some uninitialized BSS variables
int BSSone, BSStwo, BSSthree;
bool BSSlucky_13, BSSlucky_14, BSSlucky15;

int main(int argc, char* argv[])
{
	// 1) copy 12 bytes from the BSS section to the stack
	// --------------------------------------------------
	{
		// Integers are [probably] 4 bytes
		if (sizeof(int) != 4) {
			printf("Integers need to be 4 bytes each for this to work!\n");
			return -1;
		}
		// Create some stack variables
		int stack_int1 = BSSone, stack_int2 = BSStwo, stack_int3 = BSSthree;
		printf("1) successfully coppied 12 bytes from BSS to stack\n");
	}

	// 2) copy 13 bytes from the heap to the data section
	// --------------------------------------------------
	{
	// create a static data section
	static bool data_section[13] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; // false

	// Booleans are [probably] 1 byte
	if (sizeof(bool) != 1) {
		printf("Booleans need to be 1 byte each for this to work!\n");
		return -1;
	}
	// Create the heap
	bool *bool_heap1 = new bool[26]();
	std::fill(bool_heap1, bool_heap1 + 13, true);
	std::copy(bool_heap1, bool_heap1 + 13, data_section);
	if (data_section[0] && // if data section is true than success
		data_section[1] &&
		data_section[2] &&
		data_section[3] &&
		data_section[4] &&
		data_section[5] &&
		data_section[6] &&
		data_section[7] &&
		data_section[8] &&
		data_section[9] &&
		data_section[10] &&
		data_section[11] &&
		data_section[12]) {
		printf("2) successfully coppied 13 bytes from heap to data\n");
	}

	// Delete heap
	delete[] bool_heap1; bool_heap1 = NULL;
}

	// 3) copy 14 bytes from the stack to the heap
	// --------------------------------------------------
	{
		bool bool_stack1[13] = { 1,1,1,1,1,1,1,1,1,1,1,1,1 }; // true values on stack
		bool *bool_heap1 = new bool[28]();
		std::fill(bool_heap1, bool_heap1 + 14, false); // false values on heap
		std::copy(&bool_stack1, &bool_stack1 + 14, bool_heap1); // copy stack(true) to heap(false)
		if (bool_heap1[0] && // if heap is now true than success
			bool_heap1[1] &&
			bool_heap1[2] &&
			bool_heap1[3] &&
			bool_heap1[4] &&
			bool_heap1[5] &&
			bool_heap1[6] &&
			bool_heap1[7] &&
			bool_heap1[8] &&
			bool_heap1[9] &&
			bool_heap1[10] &&
			bool_heap1[11] &&
			bool_heap1[12] &&
			bool_heap1[13]) {
			printf("3) successfully coppied 14 bytes from stack to heap\n");
		}

		// Delete heap
		delete[] bool_heap1; bool_heap1 = NULL;
	}

	// 4) copy 15 bytes from the data section to the BSS
	// --------------------------------------------------
	{
		// Create 15 bytes worth of stuff in the data section
		static int FOUR_DATA_BYTES = 42;
		static bool ONE_DATA_BYTE = true;

		// copy 15 bytes
		BSSone = FOUR_DATA_BYTES; // 4 copied
		BSStwo = FOUR_DATA_BYTES; // 4 copied
		BSSthree = FOUR_DATA_BYTES; // 4 copied
		BSSlucky_13 = ONE_DATA_BYTE; // 1 copied
		BSSlucky_14 = ONE_DATA_BYTE; // 1 copied
		BSSlucky15 = ONE_DATA_BYTE; // 1 copied

		printf("4) successfully coppied 15 bytes from data section to BSS\n");
	}

	// 5) copy 4 bytes from the text section to the data section
	// --------------------------------------------------
	{
		// Text section
		#define text_int 4

		static int data_section = 0;
		data_section = text_int; // copy from text section to data section
		if (data_section == text_int && sizeof(text_int) == 4) {
			printf("5) successfully coppied 4 bytes from text section to data section\n");
		}
	}

	printf("Press any key and enter to close...\n");
	char c;
	std::cin >> c;
	return 0;
}