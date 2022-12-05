#if !defined(INCL__8085H)
#define INCL__8085H

#include <print.h>
#include <stdbool.h>

// max memory = 0xffff = 65536 bytes
#define MAX_MEM_8085H 65536

// set re/set properties
#define set 1
#define reset 0

// start functions
#define start() int main() {
#define hlt() ; return 0; }

// Flags
bool FLAG_SIGN = reset;
bool FLAG_ZERO = reset;
bool FLAG_PARITY = reset;
bool FLAG_CARRY = reset;
bool FLAG_AUXCARRY = reset;

/// Registers in 8085
char A = reset, B = reset, C = reset, D = reset, E = reset, H = reset, L = reset;

/// Registers in 8085
#define a A
#define b B
#define c C
#define d D
#define e E
#define h H
#define l L

// Memory
char mem[MAX_MEM_8085H] = {0};

// to be used before start to set memory value
#define set_mem(pos, val) mem[pos] = (char)val;

// to print memory [which has values]
#define print_mem() { int i; bool f = reset; for(i = 0; i < MAX_MEM_8085H; i++)\
{ if(mem[i]) { if(f && i%5==0) { print() } else if (f) { print_wn(","); } \
f = set; printf("0x%x = 0x%x", i, mem[i]);} } if(f) { print(); } }

#define print__base_reg(regN, reg) print_wn(regN, "=", "0x"); printf("%x", a); print();
#define printA() print__base_reg("A", A);
#define printB() print__base_reg("B", B);
#define printC() print__base_reg("C", C);
#define printD() print__base_reg("D", D);
#define printE() print__base_reg("E", E);
#define printH() print__base_reg("H", H);
#define printL() print__base_reg("L", L);


// operations

// same thing in c (mov, mvi)
#define mov(x, y) x = y;
#define mvi(x, val) mov(x, val);

// same thing in c (add, adi)
#define add(y) a += y;
#define adi(y) add(y)

#define lda(addr) a = mem[addr];
#define sta(addr) mem[addr] = a;

#define cmp(val) if(A==val)\
{ FLAG_ZERO = set; FLAG_CARRY = reset; } else if(a > val) { FLAG_ZERO = reset; FLAG_CARRY = reset; }\
else { FLAG_CARRY = set; FLAG_ZERO = reset; }

// jump to label `lb`
#define jmp(lb) goto lb;

// jump to label `lb` if carry flag is reset
#define jnc(lb) if(!FLAG_CARRY) { jmp(lb) }
// jump to label `lb` if carry flag is set
#define jc(lb) if(FLAG_CARRY) { jmp(lb) }

// jump to label `lb` if sign flag is reset
#define jm(lb) if(!FLAG_SIGN) { jmp(lb) }
// jump to label `lb` if sign flag is set
#define jp(lb) if(FLAG_SIGN) { jmp(lb) }

// jump to label `lb` if zero flag is reset
#define jnz(lb) if(!FLAG_ZERO) { jmp(lb) }
// jump to label `lb` if zero flag is set
#define jz(lb) if(FLAG_ZERO) { jmp(lb) }

// jump to label `lb` if parity flag is reset
#define jpo(lb) if(!FLAG_PARITY) { jmp(lb) }
// jump to label `lb` if parity flag is set
#define jpe(lb) if(FLAG_PARITY) { jmp(lb) }

#endif // INCL__8085H
