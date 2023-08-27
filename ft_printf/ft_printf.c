#include <stdlib.h> // for mallic, free
#include <unistd.h> // for write
#include <stdarg.h> // for va_va_start, va_arg, va_copy, va_end
/* #include <stdio.h> // for real printf */

int	ft_printf_write(int c, int i)
{
	i++;
	write(1, &c, 1);
	return (i);
}

int	ft_found_d(int d, int i)
{
	if (d == -2147483648)
	{
		write (1, "-2147483648", 11);
		i = i + 11;
	}
	else if (d < 0)
	{
		i = ft_printf_write('-', i);
		i = ft_found_d(-d, i);
	}
	else if (d >= 0 && d < 10)
		i = ft_printf_write(d + '0', i);
	else
	{
		i = ft_found_d(d / 10, i);
		i = ft_printf_write(d % 10 + '0', i);
	}
	return (i);
}

int	ft_found_s(char *s, int i)
{
	if (!s)
		i = ft_found_s("(null)", i);
	else
	{
		while (*s)
		{
			i = ft_printf_write(*s, i);
			s++;
		}
	}
	return (i);
}

int	ft_found_x(unsigned int u, int i)
{
	if (u == 0)
		i = ft_printf_write('0', i);
	else if (u >= 16)
	{
		i = ft_found_x(u / 16, i);
		i = ft_found_x(u % 16, i);
	}
	else
	{
		if (u <= 9)
			i = ft_printf_write(u + '0', i);
		else
			i = ft_printf_write(u + 'a' - 10, i);
	}
	return (i);
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		j;

	i = 0;
	j = -1;
	va_start(args, format);
	while (format[++j])
	{
		if (format[j] == '%')
		{
			j++;
			if (format[j] == 's')
				i = ft_found_s(va_arg(args, char *), i);
			if (format[j] == 'd')
				i = ft_found_d(va_arg(args, int), i);
			if (format[j] == 'x')
				i = ft_found_x(va_arg(args, unsigned int), i);
		}
		else
			i = ft_printf_write(format[j], i);
	}
	va_end(args);
	return (i);
}

/*
int main(void)
{
    int i;

    // i = printf("hi\n");
    // printf("i: %i\n", i);

    // ft_printf("MIN number: %i", INT32_MIN);
    // printf("MIN number: %i", INT32_MIN);

    i = ft_printf("me   --> hello 42!\ns: %s, d: %d, x: %x\n", NULL, 42, 42);
    printf("i: %i\n\n", i);
    i = printf("real --> hello 42!\ns: %s, d: %d, x: %x\n", NULL, 42, 42);
    printf("i: %i\n\n", i);
    
    // ft_printf("%s\n", "toto");
    // ft_printf("Magic %s is %d", "number", 42);
    // ft_printf("Hexadecimal for %d is %x\n", 42, 42);
    // printf("%s\n", "toto");
    // printf("Magic %s is %d", "number", 42);
    // printf("Hexadecimal for %d is %x\n", 42, 42);
    return (0);
}
*/