#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define MEM_SIZE   256
#define NUM_REGS   16

#define OPCODE_ADD  0x0
#define OPCODE_LW   0x2
#define OPCODE_SW   0x3
#define OPCODE_BEQ  0x4
#define OPCODE_J    0xE

#define REG_T0  0
#define REG_T3  3
#define REG_S0  4
#define REG_GP  11
#define REG_SP  12

typedef struct {
    uint32_t pc;
    uint32_t psw;
    uint32_t regs[NUM_REGS];
} CPU;

typedef struct {
    uint32_t data_memory[MEM_SIZE];
    uint32_t program_memory[MEM_SIZE];
} Memory;

/*
 * Tipo R: [ opcode 4 ][ ø 4 ][ $rd 4 ][ $rs 4 ][ $rt 4 ][ funct 12 ]
 * Tipo I: [ opcode 4 ][ $rd 4 ][ $rs 4 ][ inmediato 20 ]
 * Tipo J: [ opcode 4 ][ direccion 28 ]
 */
#define GET_OPCODE(i)  (((i) >> 28) & 0xF)
#define GET_R_RD(i)    (((i) >> 20) & 0xF)
#define GET_R_RS(i)    (((i) >> 16) & 0xF)
#define GET_R_RT(i)    (((i) >> 12) & 0xF)
#define GET_I_RD(i)    (((i) >> 24) & 0xF)
#define GET_I_RS(i)    (((i) >> 20) & 0xF)
#define GET_I_IMM(i)   ((int32_t)((i) & 0x000FFFFF))
#define GET_JADDR(i)   ((i) & 0x0FFFFFFF)

void add(CPU *cpu, uint32_t inst)
{
    int rd = GET_R_RD(inst);
    int rs = GET_R_RS(inst);
    int rt = GET_R_RT(inst);
    cpu->regs[rd] = cpu->regs[rs] + cpu->regs[rt];
}

void lw(CPU *cpu, Memory *mem, uint32_t inst)
{
    int rd  = GET_I_RD(inst);
    int rs  = GET_I_RS(inst);
    int imm = GET_I_IMM(inst);
    uint32_t addr = (cpu->regs[rs] + imm) % MEM_SIZE;
    cpu->regs[rd] = mem->data_memory[addr];
}

void sw(CPU *cpu, Memory *mem, uint32_t inst)
{

}

void beq(CPU *cpu, uint32_t inst)
{
    /* completar */
}

void j(CPU *cpu, uint32_t inst)
{
    /* completar */
}

int main(void)
{
    CPU    cpu;
    Memory mem;
    memset(&cpu, 0, sizeof(cpu));
    memset(&mem, 0, sizeof(mem));

    cpu.regs[REG_T0] = 10;
    cpu.regs[REG_T3] = 20;

    return 0;
}
