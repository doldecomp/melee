/**
 * @file bytecode.h
 * @brief SysDolphin Bytecode Virtual Machine
 * @details Implements a simple stack-based interpreter for executing bytecode scripts.
 * Often used for evaluating mathematical expressions or subaction event parameters.
 */
#ifndef SYSDOLPHIN_BASELIB_BYTECODE_H
#define SYSDOLPHIN_BASELIB_BYTECODE_H

#include <Runtime/platform.h>

/**
 * @brief Evaluates a bytecode expression and returns a float result.
 * @param bytecode Pointer to the bytecode instruction stream.
 * @param args Array of float arguments passed to the script.
 * @param nb_args Number of arguments in the args array.
 * @return The final evaluated float value.
 */
float HSD_ByteCodeEval(u8* bytecode, const f32* args, s32 nb_args);

#endif
