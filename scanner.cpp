#include "scanner.hpp"
#include <cstdio>
#include <ctype.h>
#include <cstdlib>
#include <map>
#include <string>

FILE *file;
long q;
long lastq = -1;
const int udef = -1;

std::map<std::string, token> reserved_words = {
    { "or", _or },
    { "and", _and },
    { "not", _not },
    { "false", _false },
    { "true", _true }
};

void open(const char *fname) {
    file = fopen(fname, "r");
    if(file == 0) {
        perror("fopen");
        exit(1);
    }
    q = 0;
}

void close() {
    fclose(file);
}

char read() {
    return fgetc(file);
}

void success() {
    lastq = q;
    q = ftell(file);
}

void fallback() {
    fseek(file, -1, SEEK_CUR);
}

void fail() {
    fseek(file, q, SEEK_SET);
}

bool isnatural(char c) {
    switch (c) {
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            return true;
            break;
    }
    
    return false;
}

token ids() {
    int actual = 0;
    int prior = 0;
    char match[100] = "";
    int i = 0;
    
    while(actual != udef) {
        prior = actual;
        char c = read();
        
        switch (actual) {
            case 0:
                if(isalpha(c)) actual = 1;
                else actual = udef;
                break;
            case 1:
                if(isalpha(c));
                else actual = udef;
                break;
            default: break;
        }
        
        if (actual != udef) {
            match[i] = c;
            i += 1;
        }
    }
    
    bool isReservedWord = reserved_words.count(match) > 0;
    if (prior == 1 || isReservedWord) {
        fallback();
        success();
        return isReservedWord ? reserved_words[match] : _id;
    }
    
    fail();
    return _err;
}

token num() {
    int actual = 0;
    int prior = 0;
    
    while(actual != udef) {
        prior = actual;
        char c = read();
        
        switch (actual) {
            case 0:
                if(isnatural(c)) actual = 1;
                else if (c == '0') actual = 2;
                else actual = udef;
                break;
            case 1:
                if(isdigit(c));
                else if (c == '.') actual = 3;
                else actual = udef;
                break;
            case 2:
                if(isdigit(c) || c == '_') actual = 4;
                else if (c == '.') actual = 3;
                else actual = udef;
                break;
            case 3:
                if(isdigit(c)) actual = 5;
                else actual = udef;
                break;
            case 4:
                if(isdigit(c));
                else if (c == '.') actual = 3;
                else actual = udef;
                break;
            case 5:
                if(isdigit(5));
                else actual = udef;
                break;
        }
    }
    
    if (prior == 1 || prior == 2 || prior == 5) {
        fallback();
        success();
        return _num;
    }
    
    fail();
    return _err;
}

bool wsp() {
    while(isspace(read()));
    
    fallback();
    success();
    
    return true;
}

bool eof() {
    if (!feof(file)) return true;
    return false;
}

bool character(char c) {
    if (read() == c) {
        success();
        return true;
    }
    
    fallback();
    return false;
}

token next() {
    wsp();
    token tid = ids();
    if (tid != _err) return tid;
    
    token tnum = num();
    if (tnum != _err) return tnum;
    
    if (character('?')) { return _quest; }
    if (character(':')) { return _colon; }
    if (character('=')) { return _equal; }
    if (character('!')) { return _exclam; }
    if (character('<')) { return _lesstthan; }
    if (character('>')) { return _greatthan; }
    if (character('+')) { return _sum; }
    if (character('-')) { return _minus; }
    if (character('*')) { return _mult; }
    if (character('/')) { return _div; }
    if (character('(')) { return _lpar; }
    if (character(')')) { return _rpar; }
    
    if (eof()) return _eof;
    
    return _err;
}
