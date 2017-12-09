# bind
This is a tiny proof of concept for binding parameters to functions with [x86-64 calling conventions][0], under the System V ABI.

See `main.c` for a basic code example.

### A word on how it works
Let's say we have the `puts` function, and a string `"lala"` that we want to bind to it, in order to obtain a function `print_lala`.

This function obviously only needs to do something like calling `puts` with `"lala"` as a parameter.
Well, that is what we'll do: generate code that loads bound arguments in the corresponding registers, and then jumps to the bound function.
That code will just be made of a few `mov` instructions (one for each bound argument), followed by the appropriate `jmp`.

[0]: https://en.wikipedia.org/wiki/X86_calling_conventions#System_V_AMD64_ABI
