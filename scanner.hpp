#ifndef scanner_hpp
#define scanner_hpp

#include <stdio.h>

typedef enum {
    _quest,
    _colon,
    _or,
    _and,
    _equal,
    _exclam,
    _lesstthan,
    _greatthan,
    _sum,
    _minus,
    _mult,
    _div,
    _not,
    _lpar,
    _rpar,
    _num,
    _id,
    _false,
    _true,
    _eof,
    _err
} token;

extern void open(const char *fname);
extern void close();
extern token next();

#endif /* scanner_hpp */
