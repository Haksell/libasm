#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

extern int errno;

extern size_t	ft_strlen(const char *s);
extern char		*ft_strcpy(char *dest, const char *src);
extern int		ft_strcmp(const char *s1, const char *s2);
ssize_t			ft_write(int fd, const void *buf, size_t count);
ssize_t			ft_read(int fd, void *buf, size_t count);

void test_strlen() {
	const char		*test_str = "Hello, World!";
	const size_t	standard_len = strlen(test_str);
	const size_t	custom_len = ft_strlen(test_str);

	printf("strlen: %zu\n", standard_len);
	printf("ft_strlen: %zu\n", custom_len);
}

void test_strcpy() {
	char	dest[] = "abcdefghijklmnopqrstuvwxyz";
	char	src[] = "*****";
	char	*res = strcpy(dest, src);
	printf("strcpy: %s | %d\n", dest, dest == res);

	char	ft_dest[] = "abcdefghijklmnopqrstuvwxyz";
	char	ft_src[] = "*****";
	char	*ft_res = ft_strcpy(ft_dest, ft_src);
	printf("ft_strcpy: %s | %d\n", ft_dest, ft_dest == ft_res);
}

void test_strcmp() {
	printf("=== TEST STRCMP ===\n");

	char	a1[] = "abcde";
	char	a2[] = "abcde";
	printf("%s | %s | %d | %d\n", a1, a2, strcmp(a1, a2), ft_strcmp(a1, a2));

	char	b1[] = "abcde";
	char	b2[] = "abcda";
	printf("%s | %s | %d | %d\n", b1, b2, strcmp(b1, b2), ft_strcmp(b1, b2));

	char	c1[] = "abcde";
	char	c2[] = "abcdz";
	printf("%s | %s | %d | %d\n", c1, c2, strcmp(c1, c2), ft_strcmp(c1, c2));

	char	d1[] = "abcde";
	char	d2[] = "abcd";
	printf("%s | %s | %d | %d\n", d1, d2, strcmp(d1, d2), ft_strcmp(d1, d2));

	char	e1[] = "abcde";
	char	e2[] = "abcdef";
	printf("%s | %s | %d | %d\n", e1, e2, strcmp(e1, e2), ft_strcmp(e1, e2));
}

void test_write() {
	printf("=== TEST WRITE ===\n");
	errno = 0;
	printf("return value: %zd | ", write(1, "Wesh la famille !\n", 18));
	printf("errno: %d\n", errno);
	printf("return value: %zd | ", write(open("/dev/full", O_RDWR), "lol\n", 4));
	printf("errno: %d\n", errno);
	printf("return value: %zd | ", write(4162412, "lol\n", 4));
	printf("errno: %d\n", errno);
	printf("return value: %zd | ", write(1, NULL, 18));
	printf("errno: %d\n", errno);
	printf("=== TEST FT_WRITE ===\n");
	errno = 0;
	printf("return value: %zd | ", ft_write(1, "Wesh la famille !\n", 18));
	printf("errno: %d\n", errno);
	printf("return value: %zd | ", ft_write(open("/dev/full", O_RDWR), "lol\n", 4));
	printf("errno: %d\n", errno);
	printf("return value: %zd | ", ft_write(4162412, "lol\n", 4));
	printf("errno: %d\n", errno);
	printf("return value: %zd | ", ft_write(1, NULL, 18));
	printf("errno: %d\n", errno);
}

void test_read() {
	printf("=== TEST FT_READ ===\n");
	errno = 0;
	char buf[10];
	ssize_t ret = ft_read(open("Makefile", O_RDONLY), buf, sizeof(buf) - 1);
	buf[sizeof(buf) - 1] = '\0';
	printf("buf: %s | return value: %zd | errno: %d\n", buf, ret, errno);
}

int	main(void)
{
	test_strlen();
	test_strcpy();
	test_strcmp();
	test_write();
	test_read();
	return (0);
}
