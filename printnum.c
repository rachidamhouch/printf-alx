#include "main.h"

/**
 * print_nums - prints a signed number
 * @nb: number entered as an argument.
 * @str: the string to be printed.
 * @base: the base of the number
 * @len: the length and the return value
 */
void print_nums(long nb, char *str, int base, int *len)
{
	if (nb < 0)
	{
		nb *= -1;
		*len += write(1, "-", 1);
	}
	if (nb < base)
		*len += write(1, str + nb, 1);
	else
	{
		print_nums(nb / base, str, base, len);
		print_nums(nb % base, str, base, len);
	}
}

/**
 * print_numu - prints a unsigned number
 * @nb: the unsigned unmber to be entered as argument
 * @str: the containing string
 * @base: the number base that provides it's converting
 * @len: length of array.
 */
void print_numu(unsigned int nb, char *str, int base, int *len)
{
	if (nb < (unsigned int)base)
		*len += write(1, str + nb, 1);
	else
	{
		print_nums(nb / base, str, base, len);
		print_nums(nb % base, str, base, len);
	}
}

/**
 * print_num - prints a number within integer specified
 * @n: number to be given as argument
 * @base: the number base that simplify the converting
 * @signedd: to let us know whether it's signed or not
 * @capital: the char size
 * @len: the length of the array
 */
void print_num(int n, int base, int signedd, int capital, int *len)
{
	long nbs;
	unsigned int nbu;
	char *str = "0123456789abcdef";

	nbs = n;
	if (capital)
		str = "0123456789ABCDEF";
	nbu = n;
	if (signedd)
		print_nums(nbs, str, base, len);
	else
		print_numu(nbu, str, base, len);
}

/**
 * print_ptr - prints an unsigned number point
 * @nb: the unsigned number to be printed
 * @len: the legnth and return type
 */
void print_ptr(unsigned long nb, int *len)
{
	char *str = "0123456789abcdef";

	if (!nb)
	{
		*len += write(1, "(nil)", 5);
		return;
	}
	*len += write(1, "0x", 2);
	if (nb < 16)
		*len += write(1, str + nb, 1);
	else
	{
		print_nums(nb / 16, str, 16, len);
		print_nums(nb % 16, str, 16, len);
	}
}
