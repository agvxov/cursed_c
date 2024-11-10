??=define ARGUMENT_PREFIX(x)  $arg ## x

??=include "h.h"
??=include "auto_vararg.h"
??=include_next "\
iso646.h\
"

typedef
  const const   const unsigned char
  const const * const
  const const * const
  const const         string
;
ű(_Decimal32 named_argument, ...) ??< \
;;int $a<:0:>                         \
;;puts("Let me segfault!")            \
;;return (-1[$a])                     \
;;??> // END ű

g() int; int; { int; }

duff() ??<
    char src[] = "Copy this message";
    int n = sizeof(src);
    char dest[n];
    int i = 0;
    int j = 0;
    switch (n % 4) {
        case 0: do { dest[i++] = src[j++];
        case 1:      dest[i++] = src[j++];
        case 2:      dest[i++] = src[j++];
        case 3:      dest[i++] = src[j++];
        } while (j < n);
    }
??>

#define sum(...) _sum(PP_NARG(__VA_ARGS__), __VA_ARGS__)
_sum(int argc, ...) ??<
    int r = 0;
    va_list va;
    va_start(va, argc);
    for (int i = 0; i < argc; i++) {
        r += va_arg(va, int);
    }
    va_end(va);
    return r;
??>

//fortran /* sadly gcc doesn't support it */
_Noreturn
__attribute__((noreturn))
const void
[[ noreturn ]]
main
(
  ARGUMENT_PREFIX (c),
  ARGUMENT_PREFIX (v),
  $envp
)
  __int128 ARGUMENT_PREFIX (c);
  string   ARGUMENT_PREFIX (v);
  string   $envp;
??<
  signed f
  (
  )
  ??<
    ((const void (*)(void))bitand ű)();
    switch (h)
    ??<
        int a = 89;
        default:
        break;
    ??>
  ??> /* END f */
; long long i, h, j, k
; https://google.com
; const short d = i ? 2*i : i
; puts("Make it stop, cruel" " " "w" "o" "r" "l" "d" "!")
, puts("//Please!" + 2)
, f(g(i = h = j = k))
; duff()
; sum(4, 8, 6, 12, 5)
;
??> /* END main */
