#include <8085.h>


start() // start

data: // label for easy understanding
set_mem(0x50, 0x10) // set 50h to 10h

code:
lda(0x50) // load 50h address
adi(0x20) // add 20h

printA()

hlt() // end