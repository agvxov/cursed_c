# Cursed Legacy C
> [!NOTE] This document facilitates Cursed C that can
> no longer be compiled on a reasonable system.

# K&R edge-case
Consider the following function:
```c
g() int; int; { int; }
```
This is an egde-case merge of two K&R syntax properties:
* an empty parameter list on definitions marks that arbitrary arguments could be passed
* the section between the classical head and tail of the function defines the types of the parameters

The stray `int` at the end being an artistic descision and, quote "useless type name in empty declaration".

What happens when we attempt to do both?
We don't know, it was never standardized.
GCC ~14 used to be ok with this,
after all my empty declarations
do not name undeclared symbols.

However, as K&R is being rolled out for good, the parser appears to have changed.

# Function calling conventions
Imagine this;
it is the year of our Lord circa 1975 and
you are a rockstar Fortran/C developer.
A problem you encounter is that you want to implement *some* function in C,
but use it in Fortran.
Our hell, use that cool library you got from the network!
(Social network, and you are mainly referring to Joe who works at the adjacent laboratoire.)

This is exactly the situation John DOS found himself in,
therefor the DOS platform's C compiler had a language extension of the form:
```c
fortran void f(void);
```

In fact, the standard mentions this as a common extension:
> The fortran function specifier may be used in a function declaration to indicate that calls suitable
> for FORTRAN should be generated, or that a different representation for the external name is to be
> generated (6.7.4).

This is even more obscure but there existed compilers which did the same with `pascal`.

Thankfully, we have much better tooling nowadays.
If anyone ever wanted to implement functions in C for another language,
or simply wrap an existing C library,
they should go for [Swig](https://www.swig.org/).
