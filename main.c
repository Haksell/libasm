// TODO actual tester with red KO, green OK

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define RESET "\033[0m"
#define BOLDBLUE "\033[1m\033[34m"
#define RED "\033[31m"
#define GREEN "\033[32m"

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

extern int errno;

bool perfect = true;

int printflush(const char* format, ...) {
	va_list args;
	va_start(args, format);
	int ret = vprintf(format, args);
	va_end(args);
	fflush(stdout);
	return ret;
}

void print_title(char* s) {
	printflush("%s=== %s ===\n%s", BOLDBLUE, s, RESET);
}

void ft_assert(char* message, bool result) {
	char* color;
	char* verdict;

	if (result) {
		color = GREEN;
		verdict = "OK";
	} else {
		color = RED;
		verdict = "KO";
		perfect = false;
	}
	printflush("%s[%s] %s\n%s", color, verdict, message, RESET);
}

void test_strlen() {
	char* tests[] = {"", "coucou", "Hello, World!", NULL};

	for (size_t i = 0; tests[i]; ++i) {
		size_t res = strlen(tests[i]);
		size_t ft_res = ft_strlen(tests[i]);
		if (res != ft_res) {
			char buf[128] = {};
			sprintf(buf, "ft_strlen(\"%s\") -> %zu", tests[i], ft_res);
			ft_assert(buf, false);
			return;
		}
	}
	ft_assert("ft_strlen", true);
}

void test_strcpy() {
	char dest[] = "abcdefghijklmnopqrstuvwxyz";
	char ft_dest[] = "abcdefghijklmnopqrstuvwxyz";
	char src[] = "*****";

	strcpy(dest, src);
	ft_strcpy(ft_dest, src);
	ft_assert("ft_strcpy", strcmp(dest, ft_dest) == 0);
}

void test_strcmp() {
	char* test = "abcde";
	char* tests[] = {"", "abcde", "abcda", "abcdz", "abcd", "abcdef", NULL};

	for (size_t i = 0; tests[i]; ++i) {
		int res = strcmp(test, tests[i]);
		int ft_res = ft_strcmp(test, tests[i]);
		if (!res != !ft_res) {
			char buf[128] = {};
			sprintf(buf, "ft_strcmp(\"%s\") -> %d", tests[i], ft_res);
			ft_assert(buf, false);
			return;
		}
	}
	ft_assert("ft_strcmp", true);
}

void test_strchr() {
	char* test = "abcde";
	char* tests = "aceg";

	for (int i = -42; i <= 500; ++i) {
		char* res = strchr(test, i);
		char* ft_res = ft_strchr(test, i);
		if (!res != !ft_res) {
			char buf[128] = {};
			sprintf(buf, "ft_strchr('%s', %d) -> \"%s\" instead of \"%s\"",
					test, i, ft_res, res);
			ft_assert(buf, false);
			return;
		}
	}
	ft_assert("ft_strchr", true);
}

void test_write() {
	print_title("WRITE");
	errno = 0;
	printflush("return value: %zd | ", write(1, "Wesh la famille !\n", 18));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ",
			   write(open("/dev/full", O_RDWR), "lol\n", 4));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ", write(4162412, "lol\n", 4));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ", write(1, NULL, 18));
	printflush("errno: %d\n", errno);
	print_title("FT_WRITE");
	errno = 0;
	printflush("return value: %zd | ", ft_write(1, "Wesh la famille !\n", 18));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ",
			   ft_write(open("/dev/full", O_RDWR), "lol\n", 4));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ", ft_write(4162412, "lol\n", 4));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ", ft_write(1, NULL, 18));
	printflush("errno: %d\n", errno);
}

void test_read() {
	char buf[32];
	ssize_t ret = 0;

	print_title("READ");
	errno = 0;
	ret = 0;
	bzero(buf, sizeof(buf));
	ret = read(open("Makefile", O_RDONLY), buf, sizeof(buf) - 1);
	printflush("buf: %s | return value: %zd | errno: %d\n", buf, ret, errno);
	bzero(buf, sizeof(buf));
	ret = read(open(".gitignore", O_RDONLY), buf, sizeof(buf) - 1);
	printflush("buf: %s | return value: %zd | errno: %d\n", buf, ret, errno);
	bzero(buf, sizeof(buf));
	ret = read(open("jexistepas", O_RDONLY), buf, sizeof(buf) - 1);
	printflush("buf: %s | return value: %zd | errno: %d\n", buf, ret, errno);
	bzero(buf, sizeof(buf));
	ret = read(open("srcs", O_RDONLY), buf, sizeof(buf) - 1);
	printflush("buf: %s | return value: %zd | errno: %d\n", buf, ret, errno);

	print_title("FT_READ");
	errno = 0;
	ret = 0;
	bzero(buf, sizeof(buf));
	ret = ft_read(open("Makefile", O_RDONLY), buf, sizeof(buf) - 1);
	printflush("buf: %s | return value: %zd | errno: %d\n", buf, ret, errno);
	bzero(buf, sizeof(buf));
	ret = ft_read(open(".gitignore", O_RDONLY), buf, sizeof(buf) - 1);
	printflush("buf: %s | return value: %zd | errno: %d\n", buf, ret, errno);
	bzero(buf, sizeof(buf));
	ret = ft_read(open("jexistepas", O_RDONLY), buf, sizeof(buf) - 1);
	printflush("buf: %s | return value: %zd | errno: %d\n", buf, ret, errno);
	bzero(buf, sizeof(buf));
	ret = ft_read(open("srcs", O_RDONLY), buf, sizeof(buf) - 1);
	printflush("buf: %s | return value: %zd | errno: %d\n", buf, ret, errno);
}

void test_strdup() {
	char* tests[] = {"", "coucou", NULL};

	for (size_t i = 0; tests[i]; ++i) {
		char* dup = ft_strdup(tests[i]);
		int diff = strcmp(tests[i], dup);
		free(dup);
		if (diff) {
			char buf[128] = {};
			sprintf(buf, "ft_strdup(\"%s\")", tests[i]);
			ft_assert(buf, false);
			return;
		}
	}
	ft_assert("ft_strdup", true);
}

void test_isspace() {
	for (int i = 0; i < 1000; ++i) {
		if (!isspace(i) != !ft_isspace(i)) {
			char buf[16] = {};
			sprintf(buf, "ft_isspace(%d)", i);
			ft_assert(buf, false);
			return;
		}
	}
	ft_assert("ft_isspace", true);
}

void test_atoi_base_bad_bases() {
	char* bad_bases[] = {"aa",	"abca", "abc ", "ab\tc", "-0+",
						 "-42", "42+",	"",		"0",	 NULL};
	for (size_t i = 0; bad_bases[i]; ++i) {
		int ret = ft_atoi_base(bad_bases[i], bad_bases[i]);
		if (ret != 0) {
			char buf[128] = {};
			sprintf(buf, "ft_atoi_base(..., \"%s\") returned %d instead of 0",
					bad_bases[i], ret);
			ft_assert(buf, false);
			return;
		}
	}
	ft_assert("ft_atoi bad bases", true);
}

typedef struct s_atoi_base_test {
	char* str;
	char* base;
	int expected_result;
} t_atoi_base_test;

void test_atoi_base_decimal() {
	t_atoi_base_test tests[] = {{"111", "0123456789", 111},
								{"  -4233", "0123456789", -4233},
								{"\t+--42333", "0123456789", 42333},
								{"\t  --++-12345lol42", "0123456789", -12345},
								{"xd42", "0123456789", 0},
								{"+ 42", "0123456789", 0},
								{"", "0123456789", 0},
								{"0000", "0123456789", 0},
								{"0000042", "0123456789", 42},
								{"-2147483649", "0123456789", 2147483647},
								{"-2147483648", "0123456789", -2147483648},
								{"-123456789", "0123456789", -123456789},
								{"2147483647", "0123456789", 2147483647},
								{"2147483648", "0123456789", -2147483648},
								{}};
	for (size_t i = 0; tests[i].str; ++i) {
		int ret = ft_atoi_base(tests[i].str, "0123456789");
		if (ret != tests[i].expected_result) {
			char buf[128] = {};
			sprintf(buf, "ft_atoi_base(\"%s\", ...) returned %d instead of %d",
					tests[i].str, ret, tests[i].expected_result);
			ft_assert(buf, false);
			return;
		}
	}
	ft_assert("ft_atoi decimal base", true);
}

void test_atoi_base_other_bases() {
	t_atoi_base_test tests[] = {{"101010", "01", 42},
								{"2A", "0123456789ABCDEF", 42},
								{"topo", "pouet", 526},
								{NULL, 0}};
	for (size_t i = 0; tests[i].str; ++i) {
		int ret = ft_atoi_base(tests[i].str, tests[i].base);
		if (ret != tests[i].expected_result) {
			char buf[128] = {};
			sprintf(buf,
					"ft_atoi_base(\"%s\", \"%s\") returned %d instead of %d",
					tests[i].str, tests[i].base, ret, tests[i].expected_result);
			ft_assert(buf, false);
			return;
		}
	}
	ft_assert("ft_atoi other bases", true);
}

void test_atoi_base() {
	print_title("FT_ATOI_BASE");
	test_atoi_base_bad_bases();
	test_atoi_base_decimal();
	test_atoi_base_other_bases();
}

void print_list(t_list* lst, bool is_string) {
	printflush("[%d elems]", ft_list_size(lst));
	while (lst) {
		printflush(is_string ? " %s" : " %lu", lst->data);
		lst = lst->next;
		if (lst) printflush(" ->");
	}
	printflush("\n");
}

int increasing(void* data1, void* data2) { return data1 > data2 ? 1 : -1; }
int decreasing(void* data1, void* data2) { return data1 < data2 ? 1 : -1; }
int digit(void* data1, void* data2) {
	return (size_t)data1 % 10 > (size_t)data2 % 10 ? 1 : -1;
}

int remove_same(void* data1, void* data2) { return data1 - data2; }
int remove_same_digit(void* data1, void* data2) {
	return (size_t)data1 % 10 - (size_t)data2 % 10;
}
int remove_all(void* data1, void* data2) {
	(void)data1;
	(void)data2;
	return 0;
}

void dont_free(void* data) { (void)data; }

void test_lists_size_t() {
	print_title("LISTS OF SIZE_T");
	t_list* lst = NULL;
	print_list(lst, false);
	ft_list_push_front(&lst, (void*)1);
	print_list(lst, false);
	ft_list_push_front(&lst, (void*)0);
	print_list(lst, false);
	ft_list_push_front(&lst, (void*)34);
	print_list(lst, false);
	ft_list_push_front(&lst, (void*)5);
	ft_list_push_front(&lst, (void*)0);
	ft_list_push_front(&lst, (void*)0);
	ft_list_push_front(&lst, (void*)2);
	ft_list_push_front(&lst, (void*)0);
	ft_list_push_front(&lst, (void*)144);
	ft_list_push_front(&lst, (void*)3);
	ft_list_push_front(&lst, (void*)89);
	ft_list_push_front(&lst, (void*)8);
	ft_list_push_front(&lst, (void*)13);
	ft_list_push_front(&lst, (void*)0);
	ft_list_push_front(&lst, (void*)21);
	ft_list_push_front(&lst, (void*)1);
	ft_list_push_front(&lst, (void*)55);
	ft_list_push_front(&lst, (void*)0);
	print_list(lst, false);
	print_title("FT_LIST_REMOVE_IF");
	for (size_t i = 0; i <= 4; ++i) {
		ft_list_remove_if(&lst, (void*)i, remove_same, dont_free);
		print_list(lst, false);
	}
	print_title("FT_LIST_SORT");
	ft_list_sort(&lst, increasing);
	print_list(lst, false);
	ft_list_sort(&lst, decreasing);
	print_list(lst, false);
	ft_list_sort(&lst, digit);
	print_list(lst, false);
	print_title("FT_LIST_REMOVE_IF");
	for (size_t i = 4; i <= 7; ++i) {
		ft_list_remove_if(&lst, (void*)i, remove_same_digit, dont_free);
		print_list(lst, false);
	}
	ft_list_remove_if(&lst, NULL, remove_all, dont_free);
	print_list(lst, false);
}

void test_lists_string() {
	print_title("LISTS OF STRINGS");
	t_list* lst = NULL;
	ft_list_push_front(&lst, ft_strdup("wololo"));
	ft_list_push_front(&lst, ft_strdup("danil"));
	ft_list_push_front(&lst, ft_strdup("axel"));
	ft_list_push_front(&lst, ft_strdup("lol"));
	print_list(lst, true);
	ft_list_sort(&lst, (int (*)(void*, void*))strcmp);
	print_list(lst, true);
	ft_list_remove_if(&lst, "danil", (int (*)(void*, void*))strcmp, free);
	print_list(lst, true);
	ft_list_remove_if(&lst, NULL, remove_all, free);
	print_list(lst, true);
}

void test_output() {
	print_title("OUTPUT");
	ft_putstr("Je m'appelle");
	ft_putchar(' ');
	ft_putendl("Axel.");
	ft_putstr("J'ai ");
	ft_putunbr(25);
	ft_putendl(" ans et j'aime le chocolat.");
}

int main(void) {
	print_title("STRINGS");
	test_isspace();
	test_strchr();
	test_strcmp();
	test_strcpy();
	test_strdup();
	test_strlen();
	test_atoi_base();
	test_write();
	test_read();
	test_lists_size_t();
	test_lists_string();
	test_output();
	return (1 - perfect);
}
