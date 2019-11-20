# slr(1) parser

## Grammar

```
main -> quest
quest -> prop ? quest : quest | prop
prop -> prop or clause | clause
clause -> clause and rel | rel
rel -> exp == exp | exp != exp | exp < exp | exp > exp | exp <= exp | exp >= exp | exp
exp -> exp + term | exp - term | term
term -> term * fact | term / fact | fact
fact -> - fact | not fact | ( quest ) | num | id | false | true
```
