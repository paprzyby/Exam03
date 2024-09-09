/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:25:53 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/09 16:26:59 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdarg.h>

void	print_string(char *str, int *len)
{
	if (!str)
		str = "(null)";
	while (*str)
	{
		write(1, str, 1);
		str++;
		(*len)++;
	}
}

void	print_digit(long long int num, int base, int *len)
{
	if (num < 0)
	{
		num = num * -1;
		write(1, "-", 1);
		(*len)++;
	}
	if (num >= base)
		print_digit(num / base, base, len);
	write(1, &("0123456789abcdef"[num % base]), 1);
	(*len)++;
}

int ft_printf(const char *str, ... )
{
	int		len;
	va_list	pointer;

	len = 0;
	va_start(pointer, str);
	while (*str)
	{
		if (*str == '%' && (*(str + 1) == 's' || *(str + 1) == 'd' || *(str + 1) == 'x'))
		{
			str++;
			if (*str == 's')
				print_string(va_arg(pointer, char *), &len);
			else if (*str == 'd')
				print_digit((long long int)va_arg(pointer, int), 10, &len);
			else
				print_digit((long long int)va_arg(pointer, unsigned int), 16, &len);
		}
		else
		{
			write(1, str, 1);
			len++;
		}
		str++;
	}
	va_end(pointer);
	return (len);
}

//Main function:

//#include <stdio.h>

//#ifndef REAL
//# define F	r += ft_printf
//#else
//# define F	r += printf
//#endif

//int
//	main(void)
//{
//	int	r;

//	r = 0;
//	F("Simple test\n");
//	F("");
//	F("--Format---");
//	F("\n");
//	F("%d\n", 0);
//	F("%d\n", 42);
//	F("%d\n", 1);
//	F("%d\n", 5454);
//	F("%d\n", (int)2147483647);
//	F("%d\n", (int)2147483648);
//	F("%d\n", (int)-2147483648);
//	F("%d\n", (int)-2147483649);
//	F("\n");
//	F("%x\n", 0);
//	F("%x\n", 42);
//	F("%x\n", 1);
//	F("%x\n", 5454);
//	F("%x\n", (int)2147483647);
//	F("%x\n", (int)2147483648);
//	F("%x\n", (int)-2147483648);
//	F("%x\n", (int)-2147483649);
//	F("%x\n", (int)0xFFFFFFFF);
//	F("\n");
//	F("%s\n", "");
//	F("%s\n", "toto");
//	F("%s\n", "wiurwuyrhwrywuier");
//	F("%s\n", NULL);
//	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
//	F("\n--Mixed---\n");
//	F("%d%x%d%x%d%x%d%x\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
//	F("-%d-%x-%d-%x-%d-%x-%d-%x-\n", 0, 0, 42, 42, 2147483647, 2147483647, (int)-2147483648, (int)-2147483648);
//	F("\n");
//	F("%s%s%s%s\n", "", "toto", "wiurwuyrhwrywuier", NULL);
//	F("-%s-%s-%s-%s-\n", "", "toto", "wiurwuyrhwrywuier", NULL);
//	printf("written: %d\n", r);
//}