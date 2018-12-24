#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "InstrUtils.h"
#include "Utils.h"

int main()
{
	Instruction *head;

	head = ReadInstructionList(stdin);
	if (!head) {
		WARNING("No instructions\n");
		exit(EXIT_FAILURE);
	}
	/* YOUR CODE GOES HERE */
	if (head) {
		// counter for number of optimizations, used to determine if propogation is needed in infinite loop
		short counter_optimize = 0;
		Instruction* curr_pos = head;
		// Loop through doubly LL until all possible peephole optimizations are complete
		while(1){
			counter_optimize = 0;
			curr_pos = head;
			// If LL is of size 1 or 2, return
			if(head->next == NULL || head->next->next == NULL){
				break;
			}
			// Loop through LL and check for a sequence of optimizeable instructions
			while(curr_pos->next->next != NULL){
				// found sequence of optimizeable instructions
				if(curr_pos->opcode == LOADI ){
					if(curr_pos->next->opcode == LOADI) {
						// optimizeable set of nodes found
						if(curr_pos->next->next->opcode == ADD){
							counter_optimize = 1;
							int temp;
							temp = curr_pos->field2 + curr_pos->next->field2;
							curr_pos->field2 = temp;
							curr_pos->field1 = curr_pos->next->next->field1;
							// delete LOADI
							curr_pos->next = curr_pos->next->next->next;
							curr_pos->next->next->prev = curr_pos;

						}else if(curr_pos->next->next->opcode == MUL){
							counter_optimize = 1;
							int temp;
							temp = curr_pos->field2 * curr_pos->next->field2;
							curr_pos->field2 = temp;
							curr_pos->field1 = curr_pos->next->next->field1;
							// delete LOADI
							curr_pos->next = curr_pos->next->next->next;
							curr_pos->next->next->prev = curr_pos;


						}else if(curr_pos->next->next->opcode == SUB){
							counter_optimize = 1;
							int temp;
							if(curr_pos->next->next->field2 == curr_pos->field1){
								temp = curr_pos->field2 - curr_pos->next->field2;
							}else if(curr_pos->next->next->field2 == curr_pos->field1){
								temp = curr_pos->next->field2 - curr_pos->field2;
							}
							curr_pos->field2 = temp;
							curr_pos->field1 = curr_pos->next->next->field1;
							// delete LOADI
							curr_pos->next = curr_pos->next->next->next;
							curr_pos->next->next->prev = curr_pos;

							
						}else{
							curr_pos = curr_pos->next;
						}
					}else{
						curr_pos = curr_pos->next;
					}
				}else{
					curr_pos = curr_pos->next;
				}
			}
				
			if(counter_optimize == 0){
				break;
			}
		}
		PrintInstructionList(stdout, head);
		DestroyInstructionList(head);
	}
	return EXIT_SUCCESS;
}

