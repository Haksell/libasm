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
ssize_t ft_read(int fd, void* buf, size_t count);
char* ft_strchr(const char* s, int c);
extern int ft_strcmp(const char* s1, const char* s2);
extern char* ft_strcpy(char* dest, const char* src);
char* ft_strdup(const char* s);
extern size_t ft_strlen(const char* s);
ssize_t ft_write(int fd, const void* buf, size_t count);

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

void display_title(char* s) { printflush("%s=== %s ===\n%s", BOLDBLUE, s, RESET); }

void ft_assert(char* test_name, bool result) {
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
	printflush("%s[%s] %s\n%s", color, verdict, test_name, RESET);
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
			sprintf(buf, "ft_strchr('%s', %d) -> \"%s\" instead of \"%s\"", test, i, ft_res, res);
			ft_assert(buf, false);
			return;
		}
	}
	ft_assert("ft_strchr", true);
}

void test_write() {
	display_title("WRITE");
	errno = 0;
	printflush("return value: %zd | ", write(1, "Wesh la famille !\n", 18));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ", write(open("/dev/full", O_RDWR), "lol\n", 4));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ", write(4162412, "lol\n", 4));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ", write(1, NULL, 18));
	printflush("errno: %d\n", errno);
	display_title("FT_WRITE");
	errno = 0;
	printflush("return value: %zd | ", ft_write(1, "Wesh la famille !\n", 18));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ", ft_write(open("/dev/full", O_RDWR), "lol\n", 4));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ", ft_write(4162412, "lol\n", 4));
	printflush("errno: %d\n", errno);
	printflush("return value: %zd | ", ft_write(1, NULL, 18));
	printflush("errno: %d\n", errno);
}

void test_read() {
	char buf[32];
	ssize_t ret = 0;

	display_title("READ");
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

	display_title("FT_READ");
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

void test_atoi_base() {
	printflush("=== TEST ATOI BASE ===\n");
	printflush("%d ", ft_atoi_base("42", "aa"));
	printflush("%d ", ft_atoi_base("42", "abca"));
	printflush("%d ", ft_atoi_base("42", "abc "));
	printflush("%d ", ft_atoi_base("42", "ab\tc"));
	printflush("%d ", ft_atoi_base("42", "ab\tc"));
	printflush("%d ", ft_atoi_base("42", "-0+"));
	printflush("%d ", ft_atoi_base("42", "-42"));
	printflush("%d ", ft_atoi_base("42", "42+"));
	printflush("%d ", ft_atoi_base("42", ""));
	printflush("%d ", ft_atoi_base("42", "0"));
	printflush("| ");
	printflush("%d ", ft_atoi_base("423", "01"));
	printflush("%d ", ft_atoi_base("  -4233", "0123456789"));
	printflush("%d ", ft_atoi_base("\t42333", "0123456789ABCDEF"));
	printflush("%d ", ft_atoi_base("\t  --++-12354", "0123456789ABCDEF"));
	printflush("\n");
}

int main(void) {
	test_write();
	test_read();
	display_title("TESTER");
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_strchr();
	test_strdup();
	test_isspace();
	test_atoi_base();
	return (1 - perfect);
}
