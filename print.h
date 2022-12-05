#if !defined(PRINT_H_INCL)
#include <stdio.h>
#define PRINT_H_INCL

#if __STRICT_ANSI__
# define ARG_LENGTH(...) __builtin_choose_expr(sizeof (#__VA_ARGS__) == 1,  \
        0,                                                                  \
        ARG_LENGTH__(__VA_ARGS__))
#else /* !__STRICT_ANSI__ */
# define ARG_LENGTH(...) ARG_LENGTH__(__VA_ARGS__)
#endif /* !__STRICT_ANSI__ */

# define ARG_LENGTH__(...) ARG_LENGTH_(,##__VA_ARGS__,                         \
    63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45,\
    44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26,\
    25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6,\
    5, 4, 3, 2, 1, 0)
# define ARG_LENGTH_(_, _63, _62, _61, _60, _59, _58, _57, _56, _55, _54, _53, \
    _52, _51, _50, _49, _48, _47, _46, _45, _44, _43, _42, _41, _40, _39, _38, \
    _37, _36, _35, _34, _33, _32, _31, _30, _29, _28, _27, _26, _25, _24, _23, \
    _22, _21, _20, _19, _18, _17, _16, _15, _14, _13, _12, _11, _10, _9, _8,   \
    _7, _6, _5, _4, _3, _2, _1, Count, ...) Count

#define print____sp printf(" ")

// printf wrappers for print
int print____int(int x) { return printf("%d", x); }
int print____uint(unsigned int x) { return printf("%u", x); }
int print____short(short x) { return printf("%hi", x); }
int print____ushort(unsigned short x) { printf("%hu", x); }
int print____long(long x) { return printf("%li", x); }
int print____ulong(unsigned long x) { return printf("%lu", x); }
int print____double(double x) { return printf("%.15g", x); }
int print____float(float x) { return print____double((double)x); }
int print____string(const char * x) { printf("%s", x); }
int print____char(char x) { return printf("%c", x); }

int print____unknown() { return printf("\n`print()` doesn't recognize the type to print.\n"); }

// print function macros
#define print____wn(toPrint) printwrap(toPrint)(toPrint)
#define printwrap(x) _Generic((x),\
    default: (*print____unknown),\
    short: print____short,\
    unsigned short: print____ushort,\
    int: print____int,\
    unsigned int: print____uint,\
    long: print____long,\
    unsigned long: print____ulong,\
    float: print____float,\
    double: print____double,\
    char: print____char,\
    char *: print____string,\
    const char *: print____string\
)

#define print_____wn(v, p) ((v)?(print____wn(p)):(0))
// #define print____wn[n] \
(validate, a, b, c ...i, p, dummyarg...) if v: print____wn[n-1](v,a,b,c,...,h) && print____sp && print____wn(p) else 0

#define print____wn1(v,p,an...) print_____wn(v, p)
#define print____wn2(v,a,p,an...) print_____wn(v, a) && print____sp && print_____wn(v, p)
#define print____wn3(v,a,b,p,an...) print____wn2(v,a,b) && print____sp && print_____wn(v, p)
#define print____wn4(v,a,b,c,p,an...) print____wn3(v,a,b,c) && print____sp && print_____wn(v,p)
#define print____wn5(v,a,b,c,d,p,an...) print____wn4(v,a,b,c,d) && print____sp && print_____wn(v,p)
#define print____wn6(v,a,b,c,d,e,p,an...) print____wn5(v,a,b,c,d,e) && print____sp && print_____wn(v,p)
#define print____wn7(v,a,b,c,d,e,f,p,an...) print____wn6(v,a,b,c,d,e,f) && print____sp && print_____wn(v,p)
#define print____wn8(v,a,b,c,d,e,f,g,p,an...) print____wn7(v,a,b,c,d,e,f,g) && print____sp && print_____wn(v,p)
#define print____wn9(v,a,b,c,d,e,f,g,h,p,an...) print____wn8(v,a,b,c,d,e,f,g,h) && print____sp && print_____wn(v,p)
#define print____wn10(v,a,b,c,d,e,f,g,h,i,p,an...) print____wn9(v,a,b,c,d,e,f,g,h,i)&& print____sp && print____wn(v,p)

#define print_wn(args...) print____internal_wn(0, ## args)
#define print(args...) print____internal_wn(0, ## args); printf("\n")

#define print____internal_wn(a, args...)\
(( ARG_LENGTH(1 ,## args) == 1 )                                                   \
        ? (print____wn(""))                                                       \
:(( ARG_LENGTH(1, ## args) == 2 )                                                  \
        ? (print____wn1(ARG_LENGTH(1, ## args)-1 , ##args, 0, 0))                       \
:(( ARG_LENGTH(1, ## args) == 3 )                                                  \
        ? (print____wn2(ARG_LENGTH(1, ## args)-1 , ##args, 0, 0, 0))                    \
:(( ARG_LENGTH(1, ## args) == 4 )                                                  \
        ? (print____wn3(ARG_LENGTH(1, ## args)-1 , ##args, 0, 0, 0, 0))                 \
:(( ARG_LENGTH(1, ## args) == 5 )                                                  \
        ? (print____wn4(ARG_LENGTH(1, ## args)-1 , ##args, 0, 0, 0, 0, 0))             \
:(( ARG_LENGTH(1, ## args) == 6 )                                                  \
        ? (print____wn5(ARG_LENGTH(1, ## args)-1 , ##args, 0, 0, 0, 0, 0, 0))             \
:(( ARG_LENGTH(1, ## args) == 7 )                                                  \
        ? (print____wn6(ARG_LENGTH(1, ## args)-1 , ##args, 0, 0, 0, 0, 0, 0, 0))             \
:(( ARG_LENGTH(1, ## args) == 8 )                                                  \
        ? (print____wn7(ARG_LENGTH(1, ## args)-1 , ##args, 0, 0, 0, 0, 0, 0, 0, 0))             \
:(( ARG_LENGTH(1, ## args) == 9 )                                                  \
        ? (print____wn4(ARG_LENGTH(1, ## args)-1 , ##args, 0, 0, 0, 0, 0, 0, 0, 0, 0))             \
:(( ARG_LENGTH(1, ## args) == 10 )                                                  \
        ? (print____wn4(ARG_LENGTH(1, ## args)-1 , ##args, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0))             \
:(         print____wn3(1, "\nMore than 10 arguments in `print()` is not supported. you provided:",\
                        ARG_LENGTH(1, ## args)-1, "Arguments.\n", 0)\
)))))))))))

#endif // PRINT_H_INCL
