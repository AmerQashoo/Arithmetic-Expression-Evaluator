# Arithmetic Expression Evaluator (C)

A university Data Structures project written in C. It reads arithmetic expressions from a text file and processes them using linked lists, stacks, and expression trees.

## Features

- Store input expressions in a linked list.
- Check bracket matching and expression validity.
- Convert valid infix expressions to postfix notation using a stack.
- Evaluate postfix expressions (integer `+`, `-`, `*`, `/`, `%`).
- Display invalid expressions and error messages.
- Build an expression tree and display inorder, preorder, and postorder traversals.
- Save the processed results in `output.txt`.

## Build and Run

Requires GCC or another C compiler supporting C99 or later.

```bash
gcc -std=c11 -Wall -Wextra main.c -o calculator
./calculator
```

On Windows PowerShell, run `./calculator.exe` (or `.\calculator.exe`).

## Example Input

The included `input.txt` contains example expressions, one per line:

```text
2+3*4
(8+2)/5
7%3
2+
(1+2)
8/0
```

From the menu, select **1** and enter `input.txt`, then select **2** to verify, **3** to convert, and **4** to evaluate. Choose **6** for expression tree operations and **7** to generate `output.txt`.

## Notes

- The calculator uses integer arithmetic, so integer division truncates the fractional part.
- Expressions should use non-negative integer literals, operators, and brackets without spaces. Unary minus and decimal literals are not supported.
- Division or modulo by zero is reported as an invalid expression during evaluation.
- This is an educational project rather than a general-purpose calculator. Very large numbers or arithmetic results may exceed the range of `int`.
