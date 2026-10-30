#include "./serial.h"
#include "./x86.h"

#define SERIAL_COM1 0x3f8

void serial_put(char c)
{
    outb(SERIAL_COM1, c);
}

void serial_write(char const* data, i32 size)
{
    for (i32 i = 0; i < size; i++)
        serial_put(data[i]);
}

