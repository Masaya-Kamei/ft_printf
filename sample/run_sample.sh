#!/bin/zsh

LIBFTPRINTF_INCLUDE_DIR=../includes
LIBFTPRINTF_DIR=../

make -C ${LIBFTPRINTF_DIR}
gcc -w main.c -I${LIBFTPRINTF_INCLUDE_DIR} -L${LIBFTPRINTF_DIR} -lftprintf
echo "\n---sample---"
./a.out
