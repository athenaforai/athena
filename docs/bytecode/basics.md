# Basics
## Athena Bytecode
Each node of execution graph is being translated into
a bytecode before execution. An Athena Bytecode is 
a sequence of 4 byte integer numbers. 

**Warning! Athena Bytecode is not interchangeable! It is 
different for every framework version.**

Bytecode instructions look like
> **opcode** [operand1, operand2, ...]

Each operation has its own unique opcode. There are 4 reserved
opcodes:
1. **0x00 (DEL) \<cell\>**. Frees one memory cell. \<cell\> is
a 4-byte pointer to a memory cell. 
2. **0x01 (PUSH) \<register\>**. Push register value to stack.
\<register\> is a 4-byte number of register.
3. **0x02 (POP) \<register\>**. Pops value to register from
top of stack. \<register\> is a 4-byte number of register.
4. **0x03 (JMP) \<offset\>**. Jump **offset** words. \<offset\>
us a signed 4-byte integer.

## Athena VM

 
