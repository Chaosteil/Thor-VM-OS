/*
 * Thor - VM
 *
 * Entry Point
 *
 * Author: Balys Dapkunas, Dominykas Djacenka
 */

/* ============================================================================
 * I N C L U D E S
 * ============================================================================*/

#include <iostream>
#include "processor.h"
#include "memory.h"
#include "interface.h"

using namespace Thor::VM;

/* ============================================================================
 * E N T R Y   P O I N T
 * ============================================================================*/

int main(int argc, const char *argv[]){
	Memory mem(16*1024*1024, "\0\0\0\0+DAX00000010-RR0AX", 24);
	Processor *proc = new Processor(mem);
	Interface interface(*proc);

	while(42){
		interface.refreshUI();
		getch();
		proc->cycle();
	}
	
	return 0;
}
