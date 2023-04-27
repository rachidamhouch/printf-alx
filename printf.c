#include "main.h"

/**
 * hswitch - printf implementation
 * @s: the char to be checked as a specefier.
 * @args: the argument to match the speci
 * @len: the lgnth to be a return value
 * @x: arg 4.
 * @format: arg 5.
 * Return: the wanted result as printf would print
 */
static int hswitch(char s, va_list args, int *len, int *x, const char *format)
{
	if (!s)
		return (2);
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
		case '-':
			if (mflag(args, len, x, format) == -1)
				return (2);
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
 * @x: arg 4.
 * @format: arg 5.
 * Return: the wanted result as printf would print
 */
static int _switch(char s, va_list args, int *len, int *x, const char *format)
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
			a = hswitch(s, args, len, x, format);
			if (a == 1)
				return (1);
			if (a == 2)
				return (2);
	}
	return (0);
}

/**
 * _printf - printf implementation function that
 * produces output according to a format just like the built-in function.
 * @format: the input
 * Return: the wanted result as printf would print
 */
int _printf(const char *format, ...)
{
	int x, len, m;
	va_list args;

	va_start(args, format);
	x = 0;
	len = 0;
	if (format == NULL)
		return (-1);
	while (format[x])
	{
		if (format[x] == '%')
		{
			m = _switch(format[x + 1], args, &len, &x, format);
			if (m == 2)
				return (-1);
			else if (m == 1)
				len += write(1, format + x, 1);
			else
				x++;
		}
		else
			len += write(1, format + x, 1);
		x++;
	}
	va_end(args);
	return (len);
}
