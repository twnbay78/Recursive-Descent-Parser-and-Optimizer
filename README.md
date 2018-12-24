# Recursive-Descent-Parser-and-Optimizer
This is a recursive descent parser and optimizer written in the C language. The grammar that the parser accepts is defined as:


\<program> ::= \<stmt list> . <br>
\<stmt list> ::= \<stmt> \<morestmts><br>
\<morestmts> ::= ; \<stmt list> | epsilon <br>
\<stmt> ::= \<assign> | \<read> | \<print><br>
\<assign> ::= \<variable> = \<expr><br>
\<read> ::= ! \<variable><br>
\<print> ::= # \<variable><br>
\<expr> ::= + \<expr> \<expr> |<br>
- \<expr> \<expr> |<br>
* \<expr> \<expr> |<br>
\<variable> |<br>
\<digit><br>
\<variable> ::= a | b | c | d | e<br>
\<digit> ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9<br>

 
Examples of valid tinyL programs:<br>
!a;!b;c=+3*ab;d=+c1;#d. <br>
!a;b=-*+1+2a58;#b.<br>

Stage 1: The program creates assembled RISC instructions according to the input language, which simulates the compile stage. 

Stage 2: This program then takes the assembled RISC instructions and optimizes them through a peephole optimmizer. 

A constant propagation looks for a pattern of the following
form:

LOADI Rx #c1
LOADI Ry #c2
op Rz Rx Ry

If this pattern is detected, the value of constants c1 op c2 is computed as constant c3,
where op can be addition ADD, subtraction SUB, or multiplication MUL. The original sequence
of three instructions is then replaced by a single instruction of the form:

LOADI Rz #c3

If no pattern is detected, the window is moved one instruction down the list of instructions.
In the case of a successful match and code replacement, the rst instruction of the new window
is set to the instruction that immediately follows the three instructions of the pattern in the
original, unoptimized code.

LOADI Ra #1
LOADI Rb #1
ADD Rc Ra Rb
LOADI Rd #2
LOADI Re #2
ADD Rf Re Rd
ADD Rg Rf Rc

After one pass, it is optimized to

LOADI Rc #2
LOADI Rf #4
ADD Rg Rf Rc

It can be further optimized to

LOADI Rg #6
