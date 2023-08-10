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

int	main(void)
{
	const char		*test_str = "Hello, World!";
	const size_t	standard_len = strlen(test_str);
	const size_t	custom_len = ft_strlen(test_str);

	printf("Standard strlen: %zu\n", standard_len);
	printf("Custom ft_strlen: %zu\n", custom_len);

	return (0);
}
