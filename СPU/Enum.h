//
// Created by bulat on 21.02.2021.
//
//TODO:
// - создать регистры DONE
// - создать доп команды для регистров DONE

enum COMMANDS {
    CMD_UNDF = -1,
    CMD_PUSH = 10,
    CMD_POP  = 11,
    CMD_ADD  = 12,
    CMD_SUB  = 13,
    CMD_DIV  = 14,
    CMD_MUL  = 15,
    CMD_JMP  = 20,
    CMD_JMP_NEQ = 21,
    CMD_JMP_EQ = 22,
    CMD_JMP_M = 23,
    CMD_JMP_L = 24,
    CMD_JMP_MEQ = 25,
    CMD_JMP_LEQ = 26,
    CMD_CALL = 30,
    CMD_RET = 96,
    CMD_OUT  = 97,
    CMD_END  = 98,
    CMD_HLT  = 99,
    CMD_PUSH_R = 110,
    CMD_POP_R = 111
};

enum REGISTERS{
    CMD_RAX = 0,
    CMD_RBX = 1,
    CMD_RCX = 2,
    CMD_RDX = 3
};