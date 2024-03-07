# Cursed C
> An attempt to create the worst C program ever by repeatedly abusing obscure features.
See `c.c` for the core code.
Note that there were no version restraints imposed and
extensions are also included.

---

![demo](media/cursed_c_1.mini.jpeg)

---

## Rationale
+ it was fun
+ perhaps it will be educational for someone


## Break down

### File naming
`c.c` is the least descriptive name imaginable to man.
It neither marks what project it belongs to or what purpose it has inside the project.

### Trigraph characters
There used to be a time when there were computers widely in use
without the ability to type some "normal" characters.
So alternative representations were added to replace them.
Basically built-in macros.
Under `gcc` the `-trigraphs` flag is actually required to make them available.

The ones relevant here are:
```
??=    :    #
??<    :    {
??>    :    }
```

So for example `??=define` really is just equivalent to `#define`.

### \$\$\$
The dollar sign is valid to be the first (and only the first) char of a symbol name.
My guess is that it is so for stubborn people
who prefer their variable names to start with a '$' as it has to in some other languages.
Perhaps it's for ancient parsers/syntax highlighters?
Create an issue if you know better.

### Concatenation macro operator
`##` is a special operator available inside macro definitions.
It will literally glue together the arguments on its 2 sides.
Historically it has been used to generate symbol names.

### include\_next
Including is surprisingly high-level with search paths and precedence.
Turns out this happens to open a hole in functionality,
which is otherwise absent from C.

So,
`#include <myheader.h>` will start trying to include the file 'myheader.h'
searching for in whatever directories the linker considers to contain system header files.
Then,
`#include "myheader.h"`
start from the current directory,
but falls back to the `<>` behavior.
In either case,
whatever is found first to satisfy the file name is taken.
Now, what happens if we do not want the first?
Or rather, we must have another.

As the GNU documentation explains it through an example,
say you wish to override a system header -say wrap it,
but your own header depends on the original one.
Standard C provides no way to resolve the situation.

For this reason `#include_next` was added as a widely accepted extension,
which excludes the current path from the list of searchable paths
to prohibit recursive inclusion.

### iso646.h
From what I've seen,
this perfectly standard header that tends to be relatively little known.
If you know C++ and about its keyword operators,
then this is what defines their equivalents in C.
E.g `and`, `or`, etc.

Later down it's abused to get the address of `ű`:
```C++
bitand ű
```
Where -you guessed it,
`bitand` is just macrod to be `&` at the end of the day.

### \_Decimal32
It's exactly what it sounds like,
a decimal fraction available in C.
Here, as a GNU extension.

### Dot dot dot
Not nearly as obscure as the rest, but worth including.
`...` signals to the compiler that any number of values may be pushed into the stack
on any call to this function.
Normally `stdarg.h` and it's va\_list ("Variable Argument LIST") would be used or
some pointer magic applied by hand to read said values,
but here they are just left unused.

The most famous function using this feature has to be `printf`.
In glibc it's defined as:
```C
extern int printf (const char *__restrict __format, ...);
```
That's why it can handle both`printf("%d", 1)` and `printf("%d %d", 1, 2)`.

### const const const
The specifier `const` turns out to be infinitely stackable.
In fact, it can be applied to the wrong spot too.

```C
const const int i;
```
Reduces to:
```C
const int i;
```

This program makes both the pointed value and the pointer constant,
then reiterates it a few times for good measure.

With a bit of simplification:
```C
   const char const * const;
//   ^          ^       ^
//   |          |       |
//   |          |  constant pointer
//   |          |
//   |  const... air? for no effect
//   |
// constant character value
```

### Naming
Having multi-char long variable names is bloat.
Naming everything a single letter is the way of the warrior.
#### Ű
'ű' is letter in the Hungarian alphabet.
The reason it was chosen is because it is non-ascii.
Don't like it?
Perhaps switch it out for a '😁',
which is also valid due to the same mechanic.

### Haskel style semi-colons
I guess it's self-evident that C being whitespace agnostic,
starting every line with ';' instead of closing them with it,
is valid,
however it's a rarely thought about possibility.
Also, semi-colons are stackable.

**Pro-tip:** the next time someone proposes indenting with spaces to you,
suggest indenting with semi-colons.

### 'a' array
When accessing an array element,
`a[n]` is equivalent to `&a + n`.
Note that the address is taken only figuratively,
the array `a` decays to a pointer to the first element,
so the more scientific notation is `*(a + n)`
#### Smiles
Like trigraphs, but they are too hard to type? Digraphs are for you! :>
```
%:    :    #
<%    :    {
%>    :    }
<:    :    [
:>    :    ]
```
#### Reverse reference
```C
-1[$a];
```
No, we are not trying to access the `$a`th element of `-1`.
Addition commutative, hence `*(a + n)` == `*(n + a)`.

The above evaluates exactly like:
```C
$a[-1];
```
#### Negative index
Since `a + (-n)` is `a - n`,
it just werks™.

### Puts call
Perhaps you noticed `#include <stdio.h>` missing.
Don't worry,
the compiler will implicitly handle it for us!

### Return
Relative to Assembly, C is high-level.
And in many cases,
for Assembly programmers,
the `return` statement high-level enough to be considered many ways similar to a function.
For this reason they may stick to the following syntax:
```C
return(0);
```

### END comments
Large blocks being closed with their type/name explicitly mentioned
tend to be more readable than otherwise.
With C however a nice balance of size is attainable.
Overshoot a bit and you get people pretending comments are significant.
Wait 30 years and -looking for a more radical solution-
they form a cult around DRY.

### Attributes
Attributes tend to be left out from textbooks,
but they are extremely cool.
They provide ways to both aid the compiler (or make it shut up)
and make code self-documenting.

Too bad that C botched the syntax.
Consider the following:

Both of these specify that `func` will never return.

C:
```C
__attribute__((noreturn))
```
C++:
```C++
[[ noreturn ]]
```

### Google?
Google.
```C
; https://google.com
```
URLs happen to be valid C.
More precisely,
they are -due to pure chance- a label plus a comment.
You can only have one per protocol per function,
choose wisely.

The address was chosen in particular,
because hard coding google endpoints into source is as evil
(or rather, no longer "don't be evil")
as it gets.

### ?
If one asks a C programmer
"can the ternary operator be used to conditionally declare a (const) variable"
even if he never needed to use it,
he will instinctively answer yes.
Yet,
no one seems to ever state this -truth be told, rare times, but- very useful feature.
Instead, its main purpose is to serve as premature formatting.

While the functionality is not cursed,
the poor operator itself seems to be.

### Nested functions
You would be surprised to know how popular these things used to be in the past.
And I'm not talking about C in particular.

> In the case of nested procedures, the scope rules permit, for example, the definition
> of a procedure to include the definition of subsidiary procedures without concern for
> interference with other global procedures. This capability facilitates writing pro-
> cedures and often simplifies their usage.
>
> -- David R. Hanson; Is Block Structure Necessary? (1981)

Yet,
they have fallen out from the public's taste so much that C++ disallows it.
Nested classes seem to be looked down upon too now days,
even in bloody Java tutorials where providing a single file would
be so damn much clearer and easier,
but I digress.

### Code in switch
A switch statement is just a fancy code block with a bunch of labels and a jump-table.
So, in our:
```C
    switch (h) {
        int a = 89;
        default: break;
    }
```
expression,
the available value mappings (none) are compared to h,
then execution jumps to `default` as no match was found.
Now the question becomes:
how is that `a` is defined to 89?
Easy. It's not.
`a` gets defined, but its assignment is skipped.
It's because variable declarations always result in allocations at the start of the scope,
no further questions asked.
For all the compiler cares,
`int a;` might as well have been written under `default:`.
However, the value copy is skipped.

### String literal concatenation
Adjacent string literals are always (compile time) concatenated.
Therefore:
```C
"Make it stop, cruel" " " "w" "o" "r" "l" "d" "!"
```
Costlessly becomes:
```C
"Make it stop, cruel world!"
```
Why is it cursed? Ask who ever does this:
```C
puts("Message line 1");
puts("Message line 2");
```
Instead of:
```C
puts("Message line 1\n"
     "Message line 2");
```

### Literal pointer arithmetics
A string literal "decays" into a const char pointer,
therefore `puts("//Please!" + 2)` is just the heretic way of saying:
```C
const char * s = "//Please!";
puts(s + 2);
```

### Batch assignment
The assignment operator is not particularly "special" in C.
It does the actual value copying,
but then plainly "returns" a value of its own.
Which happens to be defined as the one assigned.

"Tricks" like this and such:
```C
    do {
        // ...
    } while(i = fun());
```
tend to be pretty neat.

However,
for wholeness,
it stacks.
```C
i = h = j = k
```
Is evaluated right to left.
I.e. it becomes "assign k to j; assign j to h; assign h to i;".
So what value does `i` hold after the operation?
No one knows, since `k` was never initialized!

### Comma operator
The comma operator evaluates the expressions on both sides,
then returns the value returned by the right-hand side.
Again, it's stackable.

This -similar to the wise usage of assignments,-
opens a little door for playing with loop conditions.
```C
do {
    // ...
} while((fun(&a), a));
```


But also, if you ever wanted to make semi-colons jealous to make them love you more,
here is your chance.
```C
fun1(), fun2(), fun3(), fun4()
```

> Do not use the comma operator.
> 
> Do not use the comma operator.
> 
> Do not use the comma operator.
> 
> [...]
> 
> Do not use the comma operator.
> 
> Do not use the comma operator.
> 
> Do not use the comma operator.
> 
> -- Repeater, https://cplusplus.com/forum/beginner/272615/ 

### K&R arguments
The language design of C is truly genius.
Brian Kernighan and Dennis Ritchie got so many things perfectly right.
One clear exception is their original function declaration syntax.
Not that it doesn't make sense or does not have historical reasons,
but damn is it to ugly and confusing.

A reasonably cleaned up version of our `main()` would look like this:
```C
void main(argc, argv, envp)
int argc;
char * * argv;
char * * envp;
{ ; }
```
Where our parameters are named first,
then their type is specified.
This original way,
used to be the only way to do it.
It may look like absolutely useless typing at first,
but there are a few things to consider.

1. it roots from B syntax,
which is typeless:
```B
main(argc, argv, envp) {
    ;
}
```

2. One doesn't specify the types of your arguments
until the function definition:
```C

void main(argc, argv, envp);

void main(argc, argv, envp)
char * * argv;
int argc;
char * * envp;
{ ; }
```
Which implies that
a) you don't have to keep your declarations and definitions in sync
b) calls can compile without type checking

3. It blends with other syntax rules, allowing this:
```C
void main(argc, argv, envp)
char * * argv;
int argc;
char * * envp;
{ ; }
```
And this:
```C
void main(argc, argv, envp)
int argc;
char * * argv, * * envp;
{ ; }
```

### I would like to declare the type of nothing
```C
g() int; int; { int; }
```
GCC allows you have a typename on its own line.
Not even a warning in sight.

Why does it allow it? Good question.

### h.h
As you know, this project compiles under gcc,
Still, catting out h.h should make you raise your eyebrow.
```C
#error
```
Its impossible that that's the actual header included and
I must have messed with the compiler, right?
Well, yes, but not the way you think.
If you wanted to prove me guilty of manipulating the include path
by inspecting the build script,
you could not:
```sh
gcc c.c -trigraphs -Wall -Wextra -Wpedantic
```
Tho, there is also something suspicious going on with `h.h`:
```sh
gcc detention/h.h -o ./h.h.gch
```
Where the contents of `detention/h.h` seems like something that would translate.
That is a good lead, however `detention/` is hardly a standard folder to override with.

The solution is in the `.gch` extension as in "GNU Compiled Header".
Its what it sounds like, a header processed by gcc.
After the header is compiled once,
its code can be included in multiple source files without it being reprocessed.
This trick can significantly speed up compile times.
Well, when it works that is.

For example if it was 1 line lower in the source,
it would make the operation `#error` out.
The documentation lists 10 reasons why a compiled header could be rejected
and `iso646.h` breaks *one* of those.
Considering that's a standard header with around a dozen defines,
you can guess how stable it is.
Not to mention it fails silently.
gcc provides no feedback whether it did or did not use a compiled header,
let alone why.
Pessimism aside,
compiled headers are great as long as you can make sure
they are at the top of the source (with an `-include` perhaps)
and seem way more reliable with clang (because they have their own version too).

### Empty parenthesis 
How would you declare a function with no parameters?
If you answered the following:
```C
f();
```
Then you just found a footgun!
That actually signals how the function takes...
well,
we don't know what it takes, so better allow anything!
Take a look at `g`:
```C
g() int; int; { int; }
```
Ignoring those `int`s,
one could assume it takes 0 arguments,
yet if you glimpse at how it's called:
```C
g(i = h = j = k)
```
You will see how passing one int is valid, in fact, it doesn't even warrant a warning!
This,
again routes from the K&R style,
where as established before,
arguments where not expected to be type checked.

Sooo,
is `g()` equivalent to `g(...)`?
No!
For one,
`...` required a named argument before itself until C2X.
However,
in the case of `g()` the compiler not required to perform type promotions.
Also,
the generated assembly is... strange.
That's what `g().c` and `g(...).c` are here for.
Here is the relevant part of their disassembly:
```Asm
// @BAKE gcc -g -O0 "$@" -o "$*"                                |  // @BAKE gcc -g -O0 "$@" -o "$*" -Wall -Wpedantic

g() {                                                           |  g(...) {
    1129:       f3 0f 1e fa             endbr64                        1129:       f3 0f 1e fa             endbr64
    112d:       55                      push   %rbp                    112d:       55                      push   %rbp
    112e:       48 89 e5                mov    %rsp,%rbp               112e:       48 89 e5                mov    %rsp,%rbp
                                                                >      1131:       48 83 ec 38             sub    $0x38,%rsp
                                                                >      1135:       48 89 bd 50 ff ff ff    mov    %rdi,-0xb0(%rbp)
                                                                >      113c:       48 89 b5 58 ff ff ff    mov    %rsi,-0xa8(%rbp)
                                                                >      1143:       48 89 95 60 ff ff ff    mov    %rdx,-0xa0(%rbp)
                                                                >      114a:       48 89 8d 68 ff ff ff    mov    %rcx,-0x98(%rbp)
                                                                >      1151:       4c 89 85 70 ff ff ff    mov    %r8,-0x90(%rbp)
                                                                >      1158:       4c 89 8d 78 ff ff ff    mov    %r9,-0x88(%rbp)
                                                                >      115f:       84 c0                   test   %al,%al
                                                                >      1161:       74 20                   je     1183 <g+0x5a>
                                                                >      1163:       0f 29 45 80             movaps %xmm0,-0x80(%rbp
                                                                >      1167:       0f 29 4d 90             movaps %xmm1,-0x70(%rbp
                                                                >      116b:       0f 29 55 a0             movaps %xmm2,-0x60(%rbp
                                                                >      116f:       0f 29 5d b0             movaps %xmm3,-0x50(%rbp
                                                                >      1173:       0f 29 65 c0             movaps %xmm4,-0x40(%rbp
                                                                >      1177:       0f 29 6d d0             movaps %xmm5,-0x30(%rbp
                                                                >      117b:       0f 29 75 e0             movaps %xmm6,-0x20(%rbp
                                                                >      117f:       0f 29 7d f0             movaps %xmm7,-0x10(%rbp
        return 2;                                                          return 2;
    1131:       b8 02 00 00 00          mov    $0x2,%eax        |      1183:       b8 02 00 00 00          mov    $0x2,%eax
}                                                                  }
    1136:       5d                      pop    %rbp             |      1188:       c9                      leave
    1137:       c3                      ret                     |      1189:       c3                      ret
```
On the right side,
`g(...)` actually reads a bunch of values from the stack into registers.
What I *think* is happening is that the compiler would really like to optimize
arguments being read from the stack directly,
but since -O0 was on,
it was not allowed to make any assumptions about,
how `g` will be called,
hence it loads as much as it can.

(If you know better, please correct me!)

---

## Challenge
+ Try to make the project worse
### Completionists
* SurmanPP
