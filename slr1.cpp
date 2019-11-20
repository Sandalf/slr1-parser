#include <iostream>
#include <stack>
#include <typeinfo>
#include <map>
#include "scanner.hpp"
#include "slr1.hpp"

using namespace std;

token tok;

enum generator { main, quest, prop, clause, rel, exp, term, fact };

enum action_type { op_s, op_r, op_a, op_e };

struct action {
    action_type type;
    generator generator;
    int n = 0;
};

extern bool slr1(const char *fname)
{
    open(fname);
    
    action ac_s = { .type = op_s };
    action ac_f1 = { .type = op_r, .generator = fact, .n = 1 };
    action ac_f2 = { .type = op_r, .generator = fact, .n = 2 };
    action ac_f3 = { .type = op_r, .generator = fact, .n = 3 };
    action ac_t1 = { .type = op_r, .generator = term, .n = 1 };
    action ac_t3 = { .type = op_r, .generator = term, .n = 3 };
    action ac_e1 = { .type = op_r, .generator = exp, .n = 1 };
    action ac_e3 = { .type = op_r, .generator = exp, .n = 3 };
    action ac_r1 = { .type = op_r, .generator = rel, .n = 1 };
    action ac_r3 = { .type = op_r, .generator = rel, .n = 3 };
    action ac_r4 = { .type = op_r, .generator = rel, .n = 4 };
    action ac_c1 = { .type = op_r, .generator = clause, .n = 1 };
    action ac_c3 = { .type = op_r, .generator = clause, .n = 3 };
    action ac_p1 = { .type = op_r, .generator = prop, .n = 1 };
    action ac_p3 = { .type = op_r, .generator = prop, .n = 3 };
    action ac_q1 = { .type = op_r, .generator = quest, .n = 1 };
    action ac_q5 = { .type = op_r, .generator = quest, .n = 5 };
    action ac_a = { .type = op_a };
    action ac_e = { .type = op_e };
    
    action T[49][20] = {
        /*           ?    :    or    and    =    !      <    >      +     -    *     /    not    (     )    num    id   FALSE TRUE   $  */
        /* 0 */  { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 1 */  { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_a },
        /* 2 */  { ac_s, ac_q1, ac_s, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_q1, ac_e, ac_e, ac_e, ac_e, ac_q1 },
        /* 3 */  { ac_p1, ac_p1, ac_p1, ac_s, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_p1, ac_e, ac_e, ac_e, ac_e, ac_p1 },
        /* 4 */  { ac_c1, ac_c1, ac_c1, ac_c1, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_c1, ac_e, ac_e, ac_e, ac_e, ac_c1 },
        /* 5 */  { ac_r1, ac_r1, ac_r1, ac_r1, ac_s, ac_s, ac_s, ac_s, ac_s, ac_s, ac_e, ac_e, ac_e, ac_e, ac_r1, ac_e, ac_e, ac_e, ac_e, ac_r1 },
        /* 6 */  { ac_e1, ac_e1, ac_e1, ac_e1, ac_e1, ac_e1, ac_e1, ac_e1, ac_e1, ac_e1, ac_s, ac_s, ac_e, ac_e, ac_e1, ac_e, ac_e, ac_e, ac_e, ac_e1 },
        /* 7 */  { ac_t1, ac_t1, ac_t1, ac_t1, ac_t1, ac_t1, ac_t1, ac_t1, ac_t1, ac_t1, ac_t1, ac_t1, ac_e, ac_e, ac_t1, ac_e, ac_e, ac_e, ac_e, ac_t1 },
        /* 8 */  { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 9 */  { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 10 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 11 */ { ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_e, ac_e, ac_f1, ac_e, ac_e, ac_e, ac_e, ac_f1 },
        /* 12 */ { ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_e, ac_e, ac_f1, ac_e, ac_e, ac_e, ac_e, ac_f1 },
        /* 13 */ { ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_e, ac_e, ac_f1, ac_e, ac_e, ac_e, ac_e, ac_f1 },
        /* 14 */ { ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_f1, ac_e, ac_e, ac_f1, ac_e, ac_e, ac_e, ac_e, ac_f1 },
        /* 15 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 16 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 17 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 18 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 19 */ { ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e },
        /* 20 */ { ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e },
        /* 21 */ { ac_e, ac_s, ac_e, ac_e, ac_s, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 22 */ { ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 23 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 24 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 25 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 26 */ { ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_e, ac_e, ac_f2, ac_e, ac_e, ac_e, ac_e, ac_f2 },
        /* 27 */ { ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_f2, ac_e, ac_e, ac_f2, ac_e, ac_e, ac_e, ac_e, ac_f2 },
        /* 28 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_e, ac_e, ac_e },
        /* 29 */ { ac_e, ac_s, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e },
        /* 30 */ { ac_p3, ac_p3, ac_p3, ac_s, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_p3, ac_e, ac_e, ac_e, ac_e, ac_p3 },
        /* 31 */ { ac_c3, ac_c3, ac_c3, ac_c3, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_c3, ac_e, ac_e, ac_e, ac_e, ac_c3 },
        /* 32 */ { ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e, ac_e, ac_e, ac_e, ac_e3, ac_e, ac_e, ac_e, ac_e, ac_e3 },
        /* 33 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 34 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 35 */ { ac_r3, ac_r3, ac_r3, ac_r3, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_r3, ac_e, ac_e, ac_e, ac_e, ac_r3 },
        /* 36 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 37 */ { ac_r3, ac_r3, ac_r3, ac_r3, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_r3, ac_e, ac_e, ac_e, ac_e, ac_r3 },
        /* 38 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 39 */ { ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e3, ac_e, ac_e, ac_e, ac_e, ac_e3, ac_e, ac_e, ac_e, ac_e, ac_e3 },
        /* 40 */ { ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_e, ac_e, ac_t3, ac_e, ac_e, ac_e, ac_e, ac_t3 },
        /* 41 */ { ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_t3, ac_e, ac_e, ac_t3, ac_e, ac_e, ac_e, ac_e, ac_t3 },
        /* 42 */ { ac_f3, ac_f3, ac_f3, ac_f3, ac_f3, ac_f3, ac_f3, ac_f3, ac_f3, ac_f3, ac_f3, ac_f3, ac_e, ac_e, ac_f3, ac_e, ac_e, ac_e, ac_e, ac_f3 },
        /* 43 */ { ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_s, ac_e, ac_e, ac_s, ac_s, ac_e, ac_s, ac_s, ac_s, ac_s, ac_e },
        /* 44 */ { ac_r4, ac_r4, ac_r4, ac_r4, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_r4, ac_e, ac_e, ac_e, ac_e, ac_r4 },
        /* 45 */ { ac_r4, ac_r4, ac_r4, ac_r4, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_r4, ac_e, ac_e, ac_e, ac_e, ac_r4 },
        /* 46 */ { ac_r4, ac_r4, ac_r4, ac_r4, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_r4, ac_e, ac_e, ac_e, ac_e, ac_r4 },
        /* 47 */ { ac_r4, ac_r4, ac_r4, ac_r4, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_r4, ac_e, ac_e, ac_e, ac_e, ac_r4 },
        /* 48 */ { ac_e, ac_q5, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_e, ac_q5, ac_e, ac_e, ac_e, ac_e, ac_q5 }
    };
    
    int R[49][27] = {
        /*         ?   :  or  and   =   !  <    >   +   -   *   /   not  (   ) num  id FALSE TRUE main quest prop clause rel exp term fact  */
        /* 0 */  { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1,  1,  2,  3,  4,  5,  6, 7 },
        /* 1 */  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 2 */  { 15, -1, 16, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 3 */  { -1, -1, -1, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 4 */  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 5 */  { -1, -1, -1, -1, 19, 20, 21, 22, 23, 18, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 6 */  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 24, 25, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 7 */  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 8 */  { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, -1, -1, 26 },
        /* 9 */  { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, -1, -1, 27 },
        /* 10 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, 28,  2,  3,  4,  5,  6,  7 },
        /* 11 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 12 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 13 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 14 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 15 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, 29,  2,  3,  4,  5,  6, 7 },
        /* 16 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, 30,  4,  5,  6, 7 },
        /* 17 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, 31,  5,  6, 7 },
        /* 18 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, -1, 32, 7 },
        /* 19 */ { -1, -1, -1, -1, 33, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 20 */ { -1, -1, -1, -1, 34, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 21 */ { -1, -1, -1, -1, 36, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, 35,  6,  7 },
        /* 22 */ { -1, -1, -1, -1, 38, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, 37,  6,  7 },
        /* 23 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, -1, 39,  7 },
        /* 24 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, -1, -1, 40 },
        /* 25 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, -1, -1, 41 },
        /* 26 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 27 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 28 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 42, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 29 */ { -1, 43, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 30 */ { -1, -1, -1, 17, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 31 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 32 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 33 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, 44,  6,  7 },
        /* 34 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, 45,  6,  7 },
        /* 35 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 36 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, 46,  6,  7 },
        /* 37 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 38 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, -1, -1, -1, -1, 47,  6,  7 },
        /* 39 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 40 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 41 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 42 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 43 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1,  9, 10, -1, 11, 12, 13, 14, -1, 48,  2,  3,  4,  5,  6, 7 },
        /* 44 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 45 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 46 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 47 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
        /* 48 */ { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
    };
    
    stack<int> s;
    s.push(0);
    tok = next();
    
    do {
        int v = s.top();
        action op = v >= 0 ? T[v][tok] : ac_e;
        
        switch (op.type) {
            case op_s:
                s.push(R[v][tok]);
                tok = next();
                break;
            case op_r: {
                int gen = -1;
                int n = op.n;
                while(n--) {
                    s.pop();
                }
                if (op.generator == fact) { gen = 26; }
                else if (op.generator == term) { gen = 25; }
                else if (op.generator == exp) { gen = 24; }
                else if (op.generator == rel) { gen = 23; }
                else if (op.generator == clause) { gen = 22; }
                else if (op.generator == prop) { gen = 21; }
                else if (op.generator == quest) { gen = 20; }
                else if (op.generator == main) { gen = 19; }
                else { s.push(-1); break; }
                s.push(R[s.top()][gen]);
                break;
            }
            case op_e:
                return false;
                break;
            case op_a: {
                while(!s.empty()) {
                    s.pop();
                }
                break;
            }
            default:
                break;
        }
    } while (!s.empty());
    
    close();
    
    return true;
}


