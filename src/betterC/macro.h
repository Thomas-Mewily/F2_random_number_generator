#ifndef betterC_macro
#define betterC_macro

#define to_string(a) to_string_instant(a)
#define to_string_instant(a) #a

#define glue_instant(a,b) a ## b
#define glue(a,b) glue_instant(a, b)

#define twice(x) x x

#define unused(x) (void)(x)

#define as_struct(c, type) ((type*)(c))

#define priv private:
#define pub  public:

#endif