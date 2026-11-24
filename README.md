Rebuildt xxd hex dump tool in C

Compile with: gcc --> Ex gcc hexdump.c -o hexdump

Tested cases: 0, 20, 32, and 44 byte files, random data, and the boundary bytes in edge.bin

Learned about needing to read fgetc as in int value since EOF is returned as -1. Adding args to main. Opening, reading, and closing files. Returning EXIT codes.