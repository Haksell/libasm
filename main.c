/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbrisse <axbrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/10 08:51:10 by axbrisse          #+#    #+#             */
/*   Updated: 2023/08/10 08:51:35 by axbrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

extern size_t	ft_strlen(const char *s);
extern char		*ft_strcpy(char *dest, const char *src);
extern int		ft_strcmp(const char *s1, const char *s2);

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

int	main(void)
{
	test_strlen();
	test_strcpy();
	test_strcmp();
	return (0);
}
