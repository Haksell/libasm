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

void test_strlen()
{
	const char		*test_str = "Hello, World!";
	const size_t	standard_len = strlen(test_str);
	const size_t	custom_len = ft_strlen(test_str);

	printf("strlen: %zu\n", standard_len);
	printf("ft_strlen: %zu\n", custom_len);
}

void test_strcpy()
{
	char	dest[] = "abcdefghijklmnopqrstuvwxyz";
	char	src[] = "*****";
	char	*res = strcpy(dest, src);
	printf("strcpy: %s | %d\n", dest, dest == res);

	char	ft_dest[] = "abcdefghijklmnopqrstuvwxyz";
	char	ft_src[] = "*****";
	char	*ft_res = ft_strcpy(ft_dest, ft_src);
	printf("ft_strcpy: %s | %d\n", ft_dest, ft_dest == ft_res);
}

int	main(void)
{
	test_strlen();
	test_strcpy();
	return (0);
}
