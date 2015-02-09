# Expression-Parser
Implement a scaled down version of a prefix expression tree parser. 
### Problem Definition
We need to implement a simple expression parser similar to the Lisp interpreter.  
The parser needs to interpret and evaluate the following commands -  
1. Expressions for ADD like (add 4 5)
2. Expressions for MUL like (mul 3 4)
3. Any combination of the above two (mul 5 (add (mul 2 3) 7))
4. A LET operation in the beginning to initalize variables (let ((X 4)) (add X 10))

A simple C++ implementation of the same is given here.
