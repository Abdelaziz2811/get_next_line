#!/bin/sh
cc main.c get_next_line_bonus.c get_next_line_utils_bonus.c -I . -D BUFFER_SIZE=10000000
./a.out