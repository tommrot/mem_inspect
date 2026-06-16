#ifndef TAKE_DATA_H
#define TAKE_DATA_H

void take_data(char *type, char* value);
void print_bits(char *type, void* value);
void print_float(float *value);
void print_hex(char *type, void *value);
void print_addresses(char *type, void *value);

#endif