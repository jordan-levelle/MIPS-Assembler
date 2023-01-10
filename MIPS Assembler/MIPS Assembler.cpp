// Jordan C. Levelle
// Computer Architecture

// File created 02/12/21


#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <memory>
#include "malloc.h"
#include "header.h"

using namespace std;

#define MSK_OPCO 0xFC000000 // Masks to use for bitwise and operations
#define MSK_REG1 0x03E00000 // to extract bits
#define MSK_REG2 0x001F0000
#define MSK_REG3 0x0000F800
#define MSK_SHMT 0x000007C0
#define MSK_FUNC 0x0000003F
#define MSK_IONS 0x0000FFFF

// Instruction set given 



unsigned int intru[11] = {
0x032BA020,
0x8CE90014,
0x12A90003,
0x022DA822,
0xADB30020,
0x02697824,
0xAE8FFFF4,
0x018C6020,
0x02A4A825,
0x158FFFF7,
0x8ECDFFF0 };

// storing instructions into the proper format
struct rType {
    unsigned int opCode;
    unsigned int reg1;
    unsigned int reg2;
    unsigned int reg3;
    unsigned int shmt;
    unsigned int function;
};

// storing instructions into the proper format
struct iType {
    unsigned int opCode;
    unsigned int reg1;
    unsigned int reg2;
    signed short cnst;

};

int main()
{

    Intro Hello; // Object Hello
    Hello.printIntro(); // Prints simple welcome statement 
    for (int j = 0; j < 11; j++) // for loop to print out Instruction set
        cout << hex << "0x" << intru[j] << endl;
        cout << "\nInstructions: " << endl;

    struct rType* r = (struct rType*)malloc(sizeof(struct rType)); // Allocate memory space for the formats
    struct iType* i = (struct iType*)malloc(sizeof(struct iType)); // Allocate memory

    int address = 0x9A040; // program counter
    int opCode = 0;

    //Iterate over instructions
    //for (int j = 0; j < 11; j++) {
    
    while (intru[j] < 11){
        if (!(opCode = ((intru[j] & MSK_OPCO) >> 26))) { // Bitwise and 6 bits. Shift to least significant.
                                                         // unsigned int is opCode
            r->opCode = 0;
            r->reg1 = (*intru & MSK_REG1) >> 21; // shift to least significant bit
            r->reg2 = (*intru & MSK_REG2) >> 16;
            r->reg3 = (*intru & MSK_REG3) >> 11;
            r->shmt = (*intru & MSK_SHMT) >> 6;
            r->function = (*intru & MSK_FUNC);

            // Print Instructions for R Format
            if (r->function == 32) {
                cout << hex << " " << address << " add $" << dec << r->reg3 << ", $" << r->reg1 << ", $" << r->reg2 << endl;
            }
            else if (r->function == 34) {
                cout << hex << " " << address << " sub $" << dec << r->reg3 << ", $" << r->reg1 << ", $" << r->reg2 << endl;
            }
            else if (r->function == 36) {
                cout << hex << " " << address << " and $" << dec << r->reg3 << ", $" << r->reg1 << ", $" << r->reg2 << endl;
            }
            else if (r->function == 37) {
                cout << hex << " " << address << " or $" << dec << r->reg3 << ", $" << r->reg1 << ", $" << r->reg2 << endl;
            }
            else if (r->function == 42) {
                cout << hex << " " << address << " slt $" << dec << r->reg3 << ", $" << r->reg1 << ", $" << r->reg2 << endl;
            }
          
        }

        else {
            i->opCode = opCode;
            i->reg1 = (*intru & MSK_REG1) >> 21;
            i->reg2 = (*intru & MSK_REG2) >> 16;
            i->cnst = (signed short)(*intru & MSK_IONS);

            // Print Instruction for I Format
            if (opCode == 35) {
                cout << hex << " " << address << dec << " lw  $" << i->reg2 << ", $";
                cout << i->cnst << ", ($" << i->reg1 << ")" << endl;
            }
            else if (opCode == 43) {
                cout << hex << " " << address << dec << " sw, $" << i->reg2 << ", $";
                cout << i->cnst << ", ($" << i->reg1 << ")" << endl;;
            }
            else if (opCode == 4)
            {
                int target1 = (i->cnst << 2) + 4 + address;
                cout << hex << " " << address << " beq $" << dec << i->reg1 << ", $" << i->reg2;
                cout << ", address " << hex << target1 << endl;
            }
            else if (opCode == 5)
            {
                int target2 = (i->cnst << 2) + 4 + address;
                cout << hex << " " << address << " bne $" << dec << i->reg1 << ", $" << i->reg2;
                cout << ", address " << hex << target2 << endl;
            }
            j++;
        }
        address += 4; 
    }
   
    return 0;
}
