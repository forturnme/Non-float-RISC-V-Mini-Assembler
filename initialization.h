#include "hash_table.h"
#include <string.h>

#define lw "100011"
#define sw "101011"
#define add "100000"
#define sub "100010"
#define addi "001000"
#define ior "100101"
#define iand "100100"
#define ori "001101"
#define andi "001100"
#define slt "101010"
#define slti "001010"
#define sll "000000"
#define srl "000010"
#define beq "000100"
#define bne "000101"
#define j "000010"
#define jr "000000000000000001000"
#define jal "000011"
#define lui "001111"
//added
#define addu "100001"
#define subu "100011"
#define ixor "100110"
#define nor "100111"
#define sltu "101011"
#define sra "000011"
#define sllv "000100"
#define srlv "000110"
#define srav "000111"
#define addiu "001001"
#define xori "001110"
#define sltiu "001011"
#define nop "000000"
//
#define $v0 "00010"
#define $v1 "00011"	
#define $a0 "00100"	
#define $a1 "00101"
#define $a2 "00110"
#define $a3 "00111"
#define $t0 "01000"
#define $t1 "01001"
#define $t2 "01010"
#define $t3 "01011"
#define $t4 "01100"
#define $t5 "01101"
#define $t6 "01110"
#define $t7 "01111"	
#define $s0 "10000"
#define $s1 "10001"
#define $s2 "10010"
#define $s3 "10011"
#define $s4 "10100"
#define $s5 "10101"
#define $s6 "10110"
#define $s7 "10111"
#define $t8 "11000"
#define $t9 "11001"
#define $gp "11100"
#define $sp "11101"
#define $fp "11110"
#define $ra "11111"
#define $i0 "11010"
#define $i1 "11011"
#define $at "00001"
#define $zero "00000"
#define la "-1"

/*
 * Description: Initialize
 */

void init_opcodes_table(hash_table_t *code_table);

void init_register_table(hash_table_t *register_table);

/*
 * Initializes our hash table with the opcodes. It simply calls the hash_insert method
 * for each intruction
 */
void init_opcodes_table(hash_table_t *code_table) 
{
	hash_insert(code_table, "lw", strlen("lw"), lw); 
	hash_insert(code_table, "LW", strlen("LW"), lw); 
	
	hash_insert(code_table, "sw", strlen("sw"), sw);
	hash_insert(code_table, "SW", strlen("SW"), sw);

	hash_insert(code_table, "add", strlen("add"), add);
	hash_insert(code_table, "ADD", strlen("ADD"), add);
	
	hash_insert(code_table, "sub", strlen("sub"), sub);
	hash_insert(code_table, "SUB", strlen("SUB"), sub);

	hash_insert(code_table, "addi", strlen("addi"), addi);
	hash_insert(code_table, "ADDI", strlen("ADDI"), addi);

	hash_insert(code_table, "or", strlen("or"), ior);
	hash_insert(code_table, "OR", strlen("OR"), ior);
	
	hash_insert(code_table, "and", strlen("and"), iand);
	hash_insert(code_table, "AND", strlen("AND"), iand);
	
	hash_insert(code_table, "ori", strlen("ori"), ori);
	hash_insert(code_table, "ORI", strlen("ORI"), ori);
	
	hash_insert(code_table, "andi", strlen("andi"), andi);
	hash_insert(code_table, "ANDI", strlen("ANDI"), andi);
	
	hash_insert(code_table, "slt", strlen("slt"), slt);
	hash_insert(code_table, "SLT", strlen("SLT"), slt);
	
	hash_insert(code_table, "slti", strlen("slti"), slti);
	hash_insert(code_table, "SLTI", strlen("SLTI"), slti);
	
	hash_insert(code_table, "sll", strlen("sll"), sll);
	hash_insert(code_table, "SLL", strlen("SLL"), sll);
	
	hash_insert(code_table, "srl", strlen("srl"), srl);
	hash_insert(code_table, "SRL", strlen("SRL"), srl);
	
	hash_insert(code_table, "beq", strlen("beq"), beq);
	hash_insert(code_table, "BEQ", strlen("BEQ"), beq);
	
	hash_insert(code_table, "j", strlen("j"), j);
	hash_insert(code_table, "J", strlen("J"), j);
	hash_insert(code_table, "JMP", strlen("JMP"), j);
	hash_insert(code_table, "jmp", strlen("jmp"), j);
	
	hash_insert(code_table, "jr", strlen("jr"), jr);
	hash_insert(code_table, "JR", strlen("JR"), jr);
	hash_insert(code_table, "jrn", strlen("jrn"), jr);
	hash_insert(code_table, "JRN", strlen("JRN"), jr);
	
	hash_insert(code_table, "jal", strlen("jal"), jal);
	hash_insert(code_table, "JAL", strlen("JAL"), jal);

	hash_insert(code_table, "lui", strlen("lui"), lui);
	hash_insert(code_table, "LUI", strlen("LUI"), lui);
	
	hash_insert(code_table, "bne", strlen("bne"), bne);
	hash_insert(code_table, "BNE", strlen("BNE"), bne);

	hash_insert(code_table, "la", strlen("la"), bne);
	hash_insert(code_table, "LA", strlen("LA"), bne);

	hash_insert(code_table, "addu", strlen("addu"), addu);
	hash_insert(code_table, "ADDU", strlen("ADDU"), addu);

	hash_insert(code_table, "subu", strlen("subu"), subu);
	hash_insert(code_table, "SUBU", strlen("SUBU"), subu);

	hash_insert(code_table, "xor", strlen("xor"), ixor);
	hash_insert(code_table, "XOR", strlen("XOR"), ixor);

	hash_insert(code_table, "nor", strlen("nor"), nor);
	hash_insert(code_table, "NOR", strlen("NOR"), nor);

	hash_insert(code_table, "sltu", strlen("sltu"), sltu);
	hash_insert(code_table, "SLTU", strlen("SLTU"), sltu);

	hash_insert(code_table, "sra", strlen("sra"), sra);
	hash_insert(code_table, "SRA", strlen("SRA"), sra);

	hash_insert(code_table, "sllv", strlen("sllv"), sllv);
	hash_insert(code_table, "SLLV", strlen("SLLV"), sllv);

	hash_insert(code_table, "srlv", strlen("srlv"), srlv);
	hash_insert(code_table, "SRLV", strlen("SRLV"), srlv);

	hash_insert(code_table, "srav", strlen("srav"), srav);
	hash_insert(code_table, "SRAV", strlen("SRAV"), srav);

	hash_insert(code_table, "xori", strlen("xori"), xori);
	hash_insert(code_table, "XORI", strlen("XORI"), xori);

	hash_insert(code_table, "sltiu", strlen("sltiu"), sltiu);
	hash_insert(code_table, "SLTIU", strlen("SLTIU"), sltiu);

	hash_insert(code_table, "nop", strlen("nop"), nop);
	hash_insert(code_table, "NOP", strlen("NOP"), nop);

	hash_insert(code_table, "addiu", strlen("addiu"), addiu);
	hash_insert(code_table, "ADDIU", strlen("ADDIU"), addiu);
}

/*
 * Initializes the register table. Calls the hash_insert method
 * several times.
 */
void init_register_table(hash_table_t *register_table) 
{
	hash_insert(register_table, "$v0", strlen("$v0"), $v0);
	hash_insert(register_table, "$V0", strlen("$V0"), $v0);
	hash_insert(register_table, "$2", strlen("$2"), $v0);

	hash_insert(register_table, "$v1", strlen("$v1"), $v1);
	hash_insert(register_table, "$V1", strlen("$V1"), $v1);
	hash_insert(register_table, "$3", strlen("$3"), $v1);

	hash_insert(register_table, "$a0", strlen("$a0"), $a0);
	hash_insert(register_table, "$A0", strlen("$A0"), $a0);
	hash_insert(register_table, "$4", strlen("$4"), $a0);

	hash_insert(register_table, "$a1", strlen("$a1"), $a1);
	hash_insert(register_table, "$A1", strlen("$A1"), $a1);
	hash_insert(register_table, "$5", strlen("$5"), $a1);

	hash_insert(register_table, "$a2", strlen("$a2"), $a2);
	hash_insert(register_table, "$A2", strlen("$A2"), $a2);
	hash_insert(register_table, "$6", strlen("$6"), $a2);

	hash_insert(register_table, "$a3", strlen("$a3"), $a3);
	hash_insert(register_table, "$A3", strlen("$A3"), $a3);
	hash_insert(register_table, "$7", strlen("$7"), $a3);

	hash_insert(register_table, "$t0", strlen("$t0"), $t0);
	hash_insert(register_table, "$T0", strlen("$T0"), $t0);
	hash_insert(register_table, "$8", strlen("$8"), $t0);

	hash_insert(register_table, "$t1", strlen("$t1"), $t1);
	hash_insert(register_table, "$T1", strlen("$T1"), $t1);
	hash_insert(register_table, "$9", strlen("$9"), $t1);

	hash_insert(register_table, "$t2", strlen("$t2"), $t2);
	hash_insert(register_table, "$T2", strlen("$T2"), $t2);
	hash_insert(register_table, "$10", strlen("$10"), $t2);

	hash_insert(register_table, "$t3", strlen("$t3"), $t3);
	hash_insert(register_table, "$T3", strlen("$T3"), $t3);
	hash_insert(register_table, "$11", strlen("$11"), $t3);

	hash_insert(register_table, "$t4", strlen("$t4"), $t4);
	hash_insert(register_table, "$T4", strlen("$T4"), $t4);
	hash_insert(register_table, "$12", strlen("$12"), $t4);

	hash_insert(register_table, "$t5", strlen("$t5"), $t5);
	hash_insert(register_table, "$T5", strlen("$T5"), $t5);
	hash_insert(register_table, "$13", strlen("$13"), $t5);

	hash_insert(register_table, "$t6", strlen("$t6"), $t6);
	hash_insert(register_table, "$T6", strlen("$T6"), $t6);
	hash_insert(register_table, "$14", strlen("$14"), $t6);

	hash_insert(register_table, "$t7", strlen("$t7"), $t7);
	hash_insert(register_table, "$T7", strlen("$T7"), $t7);
	hash_insert(register_table, "$15", strlen("$15"), $t7);

	hash_insert(register_table, "$t8", strlen("$t8"), $t8);
	hash_insert(register_table, "$T8", strlen("$T8"), $t8);
	hash_insert(register_table, "$24", strlen("$24"), $t8);

	hash_insert(register_table, "$t9", strlen("$t9"), $t9);
	hash_insert(register_table, "$T9", strlen("$T9"), $t9);
	hash_insert(register_table, "$25", strlen("$25"), $t9);

	hash_insert(register_table, "$s0", strlen("$s0"), $s0);
	hash_insert(register_table, "$S0", strlen("$S0"), $s0);
	hash_insert(register_table, "$16", strlen("$16"), $s0);

	hash_insert(register_table, "$s1", strlen("$s1"), $s1);
	hash_insert(register_table, "$S1", strlen("$S1"), $s1);
	hash_insert(register_table, "$17", strlen("$17"), $s1);

	hash_insert(register_table, "$s2", strlen("$s2"), $s2);
	hash_insert(register_table, "$S2", strlen("$S2"), $s2);
	hash_insert(register_table, "$18", strlen("$18"), $s2);

	hash_insert(register_table, "$s3", strlen("$s3"), $s3);
	hash_insert(register_table, "$S3", strlen("$S3"), $s3);
	hash_insert(register_table, "$19", strlen("$19"), $s3);

	hash_insert(register_table, "$s4", strlen("$s4"), $s4);
	hash_insert(register_table, "$S4", strlen("$S4"), $s4);
	hash_insert(register_table, "$20", strlen("$20"), $s4);

	hash_insert(register_table, "$s5", strlen("$s5"), $s5);
	hash_insert(register_table, "$S5", strlen("$S5"), $s5);
	hash_insert(register_table, "$21", strlen("$21"), $s5);

	hash_insert(register_table, "$s6", strlen("$s6"), $s6);
	hash_insert(register_table, "$S6", strlen("$S6"), $s6);
	hash_insert(register_table, "$22", strlen("$22"), $s6);

	hash_insert(register_table, "$s7", strlen("$s7"), $s7);
	hash_insert(register_table, "$S7", strlen("$S7"), $s7);
	hash_insert(register_table, "$23", strlen("$23"), $s7);

	hash_insert(register_table, "$gp", strlen("$gp"), $gp);
	hash_insert(register_table, "$GP", strlen("$GP"), $gp);
	hash_insert(register_table, "$28", strlen("$28"), $gp);
	hash_insert(register_table, "$s9", strlen("$s9"), $gp);
	hash_insert(register_table, "$S9", strlen("$S9"), $gp);
	
	hash_insert(register_table, "$sp", strlen("$sp"), $sp);
	hash_insert(register_table, "$SP", strlen("$SP"), $sp);
	hash_insert(register_table, "$29", strlen("$29"), $sp);

	hash_insert(register_table, "$fp", strlen("$fp"), $fp);
	hash_insert(register_table, "$FP", strlen("$FP"), $fp);
	hash_insert(register_table, "$30", strlen("$30"), $fp);
	hash_insert(register_table, "$s8", strlen("$s8"), $fp);
	hash_insert(register_table, "$S8", strlen("$S8"), $fp);

	hash_insert(register_table, "$ra", strlen("$ra"), $ra);
	hash_insert(register_table, "$RA", strlen("$RA"), $ra);
	hash_insert(register_table, "$31", strlen("$31"), $ra);

	hash_insert(register_table, "$i0", strlen("$i0"), $i0);
	hash_insert(register_table, "$I0", strlen("$I0"), $i0);
	hash_insert(register_table, "$26", strlen("$26"), $i0);
	hash_insert(register_table, "$k0", strlen("$k0"), $i0);
	hash_insert(register_table, "$K0", strlen("$K0"), $i0);
	
	hash_insert(register_table, "$i1", strlen("$i1"), $i1);
	hash_insert(register_table, "$I1", strlen("$I1"), $i1);
	hash_insert(register_table, "$27", strlen("$27"), $i1);
	hash_insert(register_table, "$k1", strlen("$k1"), $i1);
	hash_insert(register_table, "$K1", strlen("$K1"), $i1);

	hash_insert(register_table, "$at", strlen("$at"), $at);
	hash_insert(register_table, "$AT", strlen("$AT"), $at);
	hash_insert(register_table, "$1", strlen("$1"), $at);

	hash_insert(register_table, "$zero", strlen("$zero"), $zero);
	hash_insert(register_table, "$Zero", strlen("$Zero"), $zero);
	hash_insert(register_table, "$ZERO", strlen("$ZERO"), $zero);
	hash_insert(register_table, "$0", strlen("$0"), $zero);
}
