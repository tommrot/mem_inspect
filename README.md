# # Data Inspector

A small C command-line program that **inspects the internal representation** of values (`int`, `float`, `char`, `string`) and arrays of such values: bits, hexadecimal, memory addresses, and — for expressions — the result of an arithmetic operation.

## Project structure

```
.
├── Makefile
├── main.c              # entry point, command-line argument parsing
├── take_data.c          # inspection of a single value (bits/hex/addresses/float)
├── take_data.h
├── take_arr.c           # inspection of an array of values
├── take_arr.h
├── compute_datas.c      # take_expression: arithmetic operations between two values
└── compute_datas.h
```

> Adjust the file names above to match the real ones in your project, if different.

## Build

A `Makefile` is included. Just run:

```bash
make
```

This compiles `main.c`, `take_data.c`, `compute_datas.c`, and `take_arr.c` into object files and links them into the `inspect` executable, using `-Wall -Wextra -g` (warnings on, debug symbols included for `gdb`/`valgrind`).

To clean up build artifacts:

```bash
make clean
```

## Usage

```bash
./inspect <type> <command> [arguments...]
```

where `<type>` is one of: `int`, `float`, `char`, `string`.

The program supports three modes, depending on the second argument (`<command>`):

### 1. Inspecting a single value

```bash
./inspect <type> <value>
```

Examples:
```bash
./inspect int 42
./inspect float 3.14
./inspect char A
./inspect string hello
```

For each value, the program prints:
- the **binary** representation (bit by bit; for `float`, sign/exponent/mantissa are shown separately)
- the **hexadecimal** representation
- the **memory addresses** of each byte

### 2. Inspecting an array

```bash
./inspect <type> arr <number_of_elements> <elem1> <elem2> ...
```

Examples:
```bash
./inspect int arr 3 10 20 30
./inspect string arr 2 hello world
```

Prints, for each array element, its binary representation byte by byte.

> ⚠️ For the `string` type, the array stores **pointers** to the strings (`char**`), so the bit output shows the bits of the pointer's memory address, not the bits of the string's characters.

### 3. Arithmetic expression between two values

```bash
./inspect <type> <operation> <value1> <value2>
```

where `<operation>` is one of: `add`, `sub`, `mul`, `div`.

Examples:
```bash
./inspect int add 5 7
./inspect float mul 2.5 4.0
```

For each operand, the full inspection (bits/hex) is printed, then the result is computed and printed (bits/hex). Only supported for `int` and `float`.

## Example output

```text
$ ./inspect int add 5 7
operator 1:
00000000000000000000000000000101
hexadecimal:
00000005
0x7ffee3a1b04c
0x7ffee3a1b04d
0x7ffee3a1b04e
0x7ffee3a1b04f
operation: add
operator 2:
00000000000000000000000000000111
hexadecimal:
00000007
...
result is:
00000000000000000000000000001100
hexadecimal:
0000000c
```

(Memory addresses vary on every run.)

## Known limitations and bugs

- **The `clean` rule in the Makefile may need a tab instead of spaces.** `make` traditionally requires recipe lines to be indented with a literal tab character; if `rm -f $(OBJS) $(TARGET)` is indented with spaces, some versions of `make` will reject it with a `missing separator` error. If `make clean` fails, check the indentation of that line in your editor.
- **No robust argument validation.** If too few arguments are passed for the requested command (e.g. `arr` without all elements specified, or an expression without both operands), the program may read past the bounds of `argv` or trigger undefined behavior (typically a crash). Always check `argc` against the expected argument count before accessing `argv[i]`.
- **Division by zero is not handled.** `div` with `value2 == 0` (for `int`) results in undefined behavior.
- **`atoi`/`atof` do not validate input.** A non-numeric string is silently interpreted as `0` (or partially parsed), with no error message.
- **In `take_arr`, the `size` for `float` is based on `sizeof(int)`**, not `sizeof(float)`. This only works correctly because `sizeof(int) == sizeof(float)` on almost all platforms — it's an implicit assumption, not something guaranteed by the C standard.
- **In `take_arr`, printing bits for the `string` type shows the pointer's address**, not the actual string content (see note above).
- **No check on the return value of `malloc`** in `take_data.c` and `compute_datas.c` (unlike `take_arr.c`, which does check `p == NULL`). On memory exhaustion, this would lead to a null pointer dereference.
- **Memory leaks, inherent to the program's design**: memory allocated with `malloc` is never freed in `take_data` (while `take_arr` correctly calls `free(p)` for the array, but never frees the individual strings allocated for `word` in the `string` case). Not a blocking issue for a short-lived program, but should be fixed if this code were reused in a larger context.

## Possible future improvements

- Thoroughly validate `argc` before every `argv` access.
- Handle division by zero with a proper error message.
- Properly free all allocated memory (including individual strings in `take_arr`).
- Add a Makefile to simplify the build process.
- Add automated tests (e.g. bash scripts or a framework like `Check`).