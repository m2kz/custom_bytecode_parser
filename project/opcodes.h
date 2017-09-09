//
// Created by michal on 09.09.17.
//

#ifndef PROJECT_OPCODES_H
#define PROJECT_OPCODES_H

struct Opcode {
    std::string bit_sequence;
    std::string param_list;
};

static const Opcode mov{"000", "RR"};
static const Opcode add{"010001", "RRR"};
static const Opcode sub{"010010", "RRR"};
static const Opcode divide{"010011", "RRR"};
static const Opcode mod{"010100", "RRR"};
static const Opcode mul{"010101", "RRR"};
static const Opcode compare{"01100", "RRR"};
static const Opcode hlt{"10110", ""};

#endif //PROJECT_OPCODES_H
