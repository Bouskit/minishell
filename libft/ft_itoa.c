/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: xiazhang <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 18:30:41 by xiazhang          #+#    #+#             */
/*   Updated: 2024/10/30 18:30:47 by xiazhang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n <= 0)
		count = 1;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*result;
	int				n_digit;
	unsigned int	num;

	n_digit = count_digits(n);
	result = (char *)malloc((n_digit + 1) * sizeof(char));
	if (!result)
		return (NULL);
	result[n_digit] = '\0';
	if (n < 0)
	{
		result[0] = '-';
		num = -n;
	}
	else
		num = n;
	while (n_digit > 0 && num != 0)
	{
		result[--n_digit] = (num % 10) + '0';
		num /= 10;
	}
	if (n == 0)
		result[0] = '0';
	return (result);
}
