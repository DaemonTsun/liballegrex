
#pragma once

#include "file_stream.hpp"
#include "instruction.hpp"

int format_instruction(file_stream *stream, const instruction *inst);
int format_instruction(FILE *stream, const instruction *inst);
int format_instruction(char *str, const instruction *inst);

int format_instruction_argument(file_stream *stream, instruction_argument arg);
int format_instruction_argument(FILE *stream, instruction_argument arg);
int format_instruction_argument(char *str, instruction_argument arg);
