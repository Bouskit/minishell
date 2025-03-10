/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bboukach <bboukach@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 22:10:43 by bboukach          #+#    #+#             */
/*   Updated: 2024/11/06 00:08:52 by bboukach         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	percent(const char *str, size_t i, va_list args, int *len)
{
	if (str[i] == 'd' || str[i] == 'i')
		ft_putnbr_len(va_arg(args, int), len);
	if (str[i] == 'u')
		ft_uputnbr_len(va_arg(args, unsigned int), len);
	if (str[i] == 'c')
		ft_putchar_len(va_arg(args, int), len);
	if (str[i] == 's')
		ft_putstr_len(va_arg(args, char *), len);
	if (str[i] == 'x')
		ft_hexa_len(va_arg(args, unsigned int), "0123456789abcdef", len);
	if (str[i] == 'X')
		ft_hexa_len(va_arg(args, unsigned int), "0123456789ABCDEF", len);
	if (str[i] == 'p')
		ft_adresse(va_arg(args, unsigned long long), len);
	if (str[i] == '%')
		ft_putchar_len('%', len);
	else
		return ;
}

int	ft_printf(const char *str, ...)
{
	int		len;
	int		i;
	va_list	args;

	len = 0;
	i = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i + 1])
		{
			i++;
			percent(str, i, args, &len);
			i++;
		}
		else
		{
			ft_putchar_len(str[i], &len);
			i++;
		}
	}
	va_end(args);
	return (len);
}
