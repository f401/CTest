#!/bin/bash

objcopy -I binary -O elf64-x86-64  my.png my.o
echo "These vars are avaible: "
nm my.o | awk '{print $3}'
