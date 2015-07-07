# calcul_parser

Expression Parser written in C++

Author: Leon(sjzlyl406)
Date:   28 June 2015

Module to parse arithmetic expressions. For details see:

http://sjzlyl406.github.io


(C) Copyright Leon(sjzlyl406) 2015. Permission to copy, use, modify, sell and
distribute this software is granted provided this copyright notice appears
in all copies. This software is provided "as is" without express or implied
warranty, and with no claim as to its suitability for any purpose.""

Compile & run :
```
./configure --prefix=/address
make
./calcultor
```

Example usage:

```
$ ./calcultor
2 + 3
2 + 3 = 5

3 + 3.4*2
3 + 3.4*2 = 9.8

2*(3+4)/2
2*(3+4)/2 = 7

2+3e-4 * 1e2
2+3e-4 * 1e2 = 2.03

2+sin(2*3)
2+sin(2*3) = 1.72059

exit
$ 
```
