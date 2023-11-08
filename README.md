# Cursed C
> An attempt to create the worst C program ever by repeated abusing obsecure features.
See `c.c` for the core code.
Note that there are no version restrains were inposed and
extensions are also included.

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
Basically built in macros.
Under `gcc` the `-trigraphs` flag is actually required to make them available.

The ones relevant here are:
```
		??=    :    #
		??<    :    {
		??>    :    }
```

So for example `??=define` really is just equivalent to `#define`.

## $$$
The dollar sign is valid to be the first (and only the first) char of a symbol name.
My guess is that it is so for stubborn people
who prefer their variable names to start with a '$' as it has to in some other languages.
Perhaps it's for anchient parsers/syntax highlighters?
Create an issue if you know better.

## Concetanation macro operator
`##` is a special operator available inside macro definitions.
It will literally glue together the arguments on it's 2 sides.
Historically it has been used to generate symbol names.

## include\_next
Including is surprisingly highlevel with search paths and precedence.
Turns out this happens to open a whole in functionality,
which is otherwise absent from C.

So,
`#include <myheader.h>` will start trying to include the file 'myheader.h'
searching for in whetever directories the linker considers to contain system header files.
Then,
`#include "myheader.h"`
start from the current directory,
but falls back to the `<>` behaviour.
In either case,
whatever is found first to satisfy the file name is taken.
Now, what happens if we do not want the first?
Or rather, we must have another.

As the GNU documentation explains it through an example,
say you wish to override a system header -say wrap it,
but your own header depends on the original one.
Standard C provides no way to resolve the situation.

For this reason `#include_next` was added as a widely accepted extension,
which excludes the current path from the list of searchable path
to prohibit recursive inclusion.

## iso646.h
From what I've seen,
this perfectly standard header that tends to be relatively little known.
If you know C++ and about its keyword operators,
then this is what defines their equivelents in C.
E.g `and`, `or`, etc.

Later down it's abused to get the address of `ű`:
```C++
bitand ű
```
Where -you guessed it,
`bitand` is just macrod to be`&` at the end of the day.

## \_Decimal32
It's exactly what it sounds like,
a decimal fraction available in C.
Here, as a GNU extension.

## Dot dot dot
Not nearly as obsecure as the rest, but worth including.
`...` signals to the compiler that any number of values may be pushed into the stack
on any call to this function.
Normally `stdarg.h` and it's va\_list ("Variable Argument LIST") would be used or
some pointer magic applied by hand to read said values,
but here they are just left unused.

The most famous function using this feature has to be `printf`.
In glibc it's define as:
```C
extern int printf (const char *__restrict __format, ...);
```
That's why it can handle both`printf("%d", 1)` and `printf("%d %d", 1, 2)`.

## const const const
The specifier `const` turns out to be infinitly stackable.
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
I guess it's self evident that C being whitespace agnostic,
starting every line with ';' instead of closing them with it,
is valid,
however it's a rarely though about possibility.
Also, semi-colons are stackable.

**Pro-tip:** the next time someone proposes identing with spaces to you,
suggest identing with semi-colons.

### 'a' array
When accessing an array element,
`a[n]` is equivalent to `&a + n`.
Note that the addess is taken only figuratively,
the array `a` decays to a pointer to the first element,
so the more scientific notation is `*(a + n)`
#### Smiles
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
Relative to Assembly, C is highlevel.
And in many cases,
for Assembly programmers,
the `return` statement highlevel enough to be considered many ways similar to a function.
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
Attributes tend to be left out from text books,
but they are extremely cool.
They provide ways to both aid the compiler (or make it shutup)
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

### K&R arguments
The language design of C is truely genious.
Brian Kernighan and Dennis Ritchie got so many things perfectly right.
One clear exception is their original function declaration syntax.
Not that it doesn't make sense or does not have historical reasons,
but damn is it to ugly and confusing.
+ TODO: expand on those historical reasons; mention how it's responsible for `void func()` being valid

### Nested functions
+ TODO
You would be surprised to know how popular these things used to be in the past.
And I'm not talking about C in particular.

### String literal concetanation
Adjacent string literals are always (compile time) concetanated.
Therefor:
```C
    "Make it stop, cruel" " " "w" "o" "r" "l" "d" "!"
```
Costlessly becomes:
```C
    "Make it stop, cruel world!"
```
Why is it cursed? Ask who ever fears using it like so:
```C
puts("Message line 1");
puts("Message line 2");
```
Used instead of:
```C
puts("Message line 1"
     "Message line 2");
```

### Literal pointer artimetrics
A string literal "decays" into a const char pointer,
therefor `puts("//Please!" + 2)` is just the heretic way of saying:
```C
const char * s = "//Please!";
puts(s + 2);
```

### Batch assignment
The assignment operator is not particularly "special" in C.
It does the actual value copying,
but then plainly "returns" a value of it's own.
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

### Coma operator
The coma operator evaluates the expressions on both sides,
then returns the value returned by the right hand side.
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
>      - Repeater, https://cplusplus.com/forum/beginner/272615/ 

## Challange
+ Try to make the project worse
