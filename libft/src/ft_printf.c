/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mortins- <mortins-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 18:23:13 by mortins-          #+#    #+#             */
/*   Updated: 2023/08/31 13:46:51 by mortins-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printf_str(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (printf_str("(null)"));
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

int	printf_ptr(unsigned long n, int x)
{
	int	i;

	i = 0;
	if (n == 0)
		return (printf_str("(nil)"));
	if (x)
		i += printf_str("0x");
	if (n >= 16)
		i += printf_ptr((n / 16), 0);
	return (i + write(1, &"0123456789abcdef"[n % 16], 1));
}

int	printf_base(long long n, char *base)
{
	int	i;
	int	a;

	a = 0;
	while (base[a])
		a++;
	i = 0;
	if (n < 0)
	{
		i += write(1, "-", 1);
		n *= -1;
	}
	if (n >= a)
		i += printf_base((n / a), base);
	return (i + write(1, &base[n % a], 1));
}

int	printf_sort(char c, va_list arg)
{
	char	a;

	if (c == 'c')
	{
		a = va_arg(arg, int);
		return (write(1, &a, 1));
	}
	else if (c == 's')
		return (printf_str(va_arg(arg, char *)));
	else if (c == 'p')
		return (printf_ptr(va_arg(arg, unsigned long), 1));
	else if (c == 'd' || c == 'i')
		return (printf_base(va_arg(arg, int), "0123456789"));
	else if (c == 'u')
		return (printf_base(va_arg(arg, unsigned int), "0123456789"));
	else if (c == 'x')
		return (printf_base(va_arg(arg, unsigned int), "0123456789abcdef"));
	else if (c == 'X')
		return (printf_base(va_arg(arg, unsigned int), "0123456789ABCDEF"));
	else if (c == '%')
		return (write(1, "%%", 1));
	return (0);
}

int	ft_printf(const char *s, ...)
{
	va_list	arg;
	int		i;

	va_start(arg, s);
	i = 0;
	while (*s)
	{
		if (*s != '%')
			i += write(1, &*s, 1);
		else
			i += printf_sort(*++s, arg);
		s++;
	}
	va_end(arg);
	return (i);
}
