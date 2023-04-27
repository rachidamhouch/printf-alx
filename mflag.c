#include "main.h"

/**
 * helpswitch - printf implementation
 * @s: the char to be checked as a specefier.
 * @args: the argument to match the speci
 * @len: the lgnth to be a return value
 * Return: the wanted result as printf would print
 */
static int helpswitch(char s, va_list args, int *len)
{
	switch (s)
	{
		case 'S':
			Non_printable(va_arg(args, char *), len);
			break;
		case 'p':
			print_ptr((unsigned long)va_arg(args, void *), len);
			break;
		case 'R':
			rot13(va_arg(args, char *), len);
			break;
		case 'r':
			print_rev(va_arg(args, char *), len);
			break;
		default:
			return (1);
	}
	return (0);
}

/**
 * _switch - printf implementation
 * @s: the char to be checked as a specefier.
 * @args: the argument to match the speci
 * @len: the lgnth to be a return value
 * Return: the wanted result as printf would print
 */
static int _switch(char s, va_list args, int *len)
{
	char	a;

	switch (s)
	{
		case 'c':
			a = va_arg(args, int);
			*len += write(1, &a, 1);
			break;
		case 's':
			*len += printstr(va_arg(args, char *));
			break;
		case '%':
			*len += write(1, "%", 1);
			break;
		case 'd': case 'i':
			print_num(va_arg(args, int), 10, 1, 0, len);
			break;
		case 'b':
			print_num(va_arg(args, int), 2, 0, 0, len);
			break;
		case 'u':
			print_num(va_arg(args, int), 10, 0, 0, len);
			break;
		case 'o':
			print_num(va_arg(args, int), 8, 0, 0, len);
			break;
		case 'x':
			print_num(va_arg(args, int), 16, 0, 0, len);
			break;
		case 'X':
			print_num(va_arg(args, int), 16, 0, 1, len);
			break;
		default:
			a = helpswitch(s, args, len);
			if (a == 1)
				return (1);
	}
	return (0);
}

/**
 * my_atoi - atoi
 * @format: the input format.
 * @x: the number of arguements.
 * Return: the legnth.
 */
int my_atoi(const char *format, int *x)
{
	int	i = 0;

	*x += 2;
	while (format[*x] && format[*x] >= '0' && format[*x] <= '9')
	{
		i *= 10;
		i += format[*x] - '0';
		*x += 1;
	}
	if (!format[*x])
		return (-1);
	return (i);
}

/**
 * mflag - flag -.
 * @args: the arguements.
 * @len: the legnth of it.
 * @x: the inputs.
 * @format: the output speci.
 * Return: 0.
 */
int mflag(va_list args, int *len, int *x, const char *format)
{
	int	n, m;

	n = my_atoi(format, x);
	if (n == -1)
		return (-1);
	m = *len;
	if (_switch(format[*x], args, len))
	{
		*len += write(1, "%", 1);
		print_num(n, 10, 0, 0, len);
		*len += write(1, format + *x, 1);
		return (0);
	}
	n -= *len - m;
	while (n-- > 0)
		*len += write(1, " ", 1);
	*x -= 1;
	return (0);
}
