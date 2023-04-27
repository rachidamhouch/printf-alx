#include "main.h"

/**
 * printstr - print string.
 * @str: string.
 * Return: the length of string.
 */
int	printstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
	{
		write(1, str + i, 1);
		i++;
	}
	return (i);
}
/**
 * Non_printable - print non printable chars
 * @c: the char to be tested if printed or not
 * @len: the length of the array.
 */
void Non_printable(char *c, int *len)
{
	int	i = 0;

	if (!c)
		c = "(null)";
	while (c[i])
	{
		if (c[i] >= 32 && c[i] < 127)
			*len += write(1, c + i, 1);
		else
		{
			*len += write(1, "\\x", 2);
			if (c[i] < 16)
				*len += write(1, "0", 1);
			print_num(c[i], 16, 1, 1, len);
		}
		i++;
	}
}
/**
 * rot13 - encodes the string into rot13 code
 * @k: the string given to be converted into rot13
 * @len: the length of the string.
 * Return: string in rot13 code or -1
 */
char *rot13(char *k, int *len)
{
	char a[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char rot13[] = "nopqrstuvwxyzabcdefghijklmNOPQRSTUVWXYZABCDEFGHIJKLM";
	int h = 0, m = 0, c;
	char t[] = "(null)";

	if (!k)
		k = t;
	while (k[h] != '\0')
	{
		c = 1;
		for (m = 0; a[m]; m++)
		{
			if (k[h] == a[m])
			{
				*len += write(1, &rot13[m], 1);
				c = 0;
				break;
			}
		}
		if (c)
			*len += write(1, &k[h], 1);
		h++;
	}
	return (k);
}
/**
 * print_rev - prints a string reversed
 * @s: the string to be reversed
 * @len: the length of the string
 * Return: void
 */
void print_rev(char *s, int *len)
{
	int k = 0;

	if (!s)
		s = "(null)";

	while (k >= 0)
	{
		if (s[k] == '\0')
			break;
		k++;
	}
	for (k--; k >= 0; k--)
		*len += write(1, s + k, 1);
}
