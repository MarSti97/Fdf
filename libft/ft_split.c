/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstiedl <mstiedl@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 09:30:55 by mstiedl           #+#    #+#             */
/*   Updated: 2022/11/15 18:16:50 by mstiedl          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	counter(char const *str, char c)
{
	int	i;
	int	count;
	int	skip;

	i = 0;
	count = 0;
	skip = 0;
	while (str[i])
	{
		if (str[i] != c && skip == 0)
		{
			count += 1;
			skip = 1;
		}
		i++;
		while (str[i] == c && str[i])
		{
			skip = 0;
			i++;
		}
	}
	return (count);
}

static void	mem_all(char const *str, char c, char **res)
{
	int		i;
	int		count;
	int		size;

	count = 0;
	i = 0;
	size = 0;
	while (str[size])
	{
		while (str[size] != c && str[size])
			size++;
		res[count] = ft_calloc(sizeof(char), ((size - i) + 1));
		ft_memcpy(res[count], &str[i], (size - i));
		count++;
		while (str[size] == c && str[size])
				size++;
		i = size;
	}
}

char	**ft_split(char const *str, char c)
{
	char	**res;
	int		words;
	char	*ptr;

	words = counter(str, c);
	ptr = ft_strtrim(str, (char *)&c);
	if (!ptr)
		return (NULL);
	res = (char **)malloc(sizeof(char *) * (words + 1));
	mem_all(ptr, c, res);
	if (!res)
		return (NULL);
	res[words] = NULL;
	free (ptr);
	return (res);
}

/* int main()
{
    char const str[] = "tripouille";
    char c = 0;
	char **res = ft_split(str, c);
	
	printf("%i\n", counter(str, c));
	printf("Result word 1: %s\n", res[0]);
	printf("Result word 2: %s\n", res[1]);
	printf("Result word 3: %s\n", res[2]);
	printf("Result word 4: %s\n", res[3]);
	printf("Result word 5: %s\n", res[4]);
	printf("Result word NULL: %s\n", res[5]);
} */
