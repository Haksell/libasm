#ifndef LIBASM_H
#define LIBASM_H

#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>

int ft_atoi_base(char* str, char* base);
int ft_isspace(int c);
void ft_putchar(char c);
void ft_putendl(char* s);
void ft_putstr(char* s);
void ft_putunbr(size_t n);
ssize_t ft_read(int fd, void* buf, size_t count);
char* ft_strchr(const char* s, int c);
extern int ft_strcmp(const char* s1, const char* s2);
extern char* ft_strcpy(char* dest, const char* src);
char* ft_strdup(const char* s);
extern size_t ft_strlen(const char* s);
ssize_t ft_write(int fd, const void* buf, size_t count);

typedef struct s_list {
	void* data;
	struct s_list* next;
} t_list;

void ft_list_push_front(t_list** begin_list, void* data);
void ft_list_remove_if(t_list** begin_list, void* data_ref,
					   int (*cmp)(void*, void*), void (*free_fct)(void*));
int ft_list_size(t_list* begin_list);
void ft_list_sort(t_list** begin_list, int (*cmp)(void*, void*));

#endif