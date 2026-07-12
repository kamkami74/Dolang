#ifndef IO_H
#define IO_H

void init_file(char* fp);
char consume_char(void);
void close_file(void);

int get_col(void);
int get_row(void);

char* get_filename(void);

#endif 
