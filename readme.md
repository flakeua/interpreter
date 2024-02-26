## Interpreter for a madeup programming language

For some tests to run you have to put input.txt into the cmake-build-debug directory.
To disable tests and enable the interpreter make isTesting bool in main() function false and choose interpreter run profile in clion.

Languages basic ideas are based on brainfuck and turing machine. This also proves that it is turing complete, since all brainfuck commands have their counterparts in here.

When launching the interpreter -s flag can be used to specify byte array(memory you work with) size.
Also when launching the interpreter you can add name of file to run it, or leave it blank to run interactive mode.

There are three different programs that test basic functionality of the interpreter in here(basic_program.prog, cyclesAndConditions.prog, input.prog).

Main commands:

- left {n} - move to the left by n, without n moves by 1
- right {n} - move to the right by n, without n moves by 1
- plus {n} - add n to current value, without n adds 1
- minus {n} - subtract n from current value, without n subtracts 1
- print {n} - prints ascii characters from numbers in next n blocks, pointer stays on the last symbol, without n prints current symbol, doesn't move pointer
- input {n} - reads n lines and puts them into corresponding memory blocks, pointer stays on the first symbol, without n inputs one line
- while { commands } - executes commands until current value is not zero
- for {n} { commands } - executes command n times (n is required)
- if { commands } - executes commands once if current value is not zero

{ commands } blocks have to have symbol } and symbol { on separate lines from other code.

Spaces in the end or beginning of the line do not matter, but beetween different parts of command there should be at least one space.

Each line ends with endline symbol, no ';' is needed.
