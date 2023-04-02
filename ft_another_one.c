#include <unistd.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
//#include "hex.c"

//ft_len_str
size_t	ft_len_str(char *str)
{
	size_t	i;

	i = -1;
	if (!str || str == NULL)
		return (0);
	while (str[++i])
		;
	return (i);
}
////////////////////////////

//ft_putchar
char	*ft_putchar(char c)
{
	char	*res;

	if (!c)
		return (ft_putchar('0'));
	res = malloc(sizeof(char) * (2));
	if (!res)
		return (0);
	res[0] = c;
	res[1] = '\0';
	return (res);
}
////////////////////////////////////

///ft_str ; mettre une sring dans le tableau
char	*ft_str(char *a_cop)
{
	size_t	i;
	size_t	j;
	char	*string;

	if (!a_cop || a_cop == NULL)
		return (ft_str(("(null)")));
	i = ft_len_str(a_cop);
	if (i >= 0)
	{
		if (i == 0)
		{
			string = ft_putchar(a_cop[0]);
			return (string);
		}
		j = -1;
		string = malloc(sizeof(char) * (i + 1));
		if (!string)
			return (0);
		while (++j < i)
			string[j] = a_cop[j];
		string[j] = '\0';
		return (string);
	}
	return (ft_str("(null)"));;
}
///////////////////////////////////

///ft_itoa
int	ft_int_len(long long nb, int base)
{
	int len;

	len = 1;
	if (!nb || !base)
		return (0);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb /= base)
		len++;
	return (len);
}

char	*ft_itoa_base(long long nb, int base, char *digits)
{
	int	sign;
	int	len;
	char	*str;
	int	i;

	sign = 0;
	if (nb < 0)
	{
		nb = -nb;
		sign = 1;
	}
	len = ft_int_len(nb, base);
	str = (char *)malloc(sizeof(char) * (len + sign + 1/*2*/));
	str[len + sign] = '\0';
	i = len + sign - 1;
	while (nb > 0)
	{
		str[i] = digits[nb % base];
		nb /= base;
		i--;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}

char	*ft_itoa(long long nb, char *base_digits)
{
	int	base = ft_len_str(base_digits);

	if (!nb || !base_digits)
		return (NULL);
	if (nb == 0)
		return ("0");
	else if (nb >= 0 && ft_len_str(base_digits) == 16)
		return (ft_itoa_base(nb, base, base_digits));
	else
		return (ft_itoa_base(nb, base, base_digits));
}
/////////////////////////////////////

///ft_numb_if_strings
int	ft_is_in(char c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == c)
			return (1);
	return (0);
}

size_t	ft_numb_of_strings(char const *str)
{
	size_t	num;
	char	*pos;
	int	i;

	if (!str)
		return (0);
	pos = "lhocspiudxX%";
	i = 0;
	num = 0;
	while (str[i])
	{
		if (str[i] == '%' && ft_is_in(str[i + 1], pos) == 1)//
			num++;
		i++;
	}
	return (num);
}
/////////////////////////////////////////

//char *ft_strjoin
char	*ft_strjoin(char *s1, char *s2)
{
	int	i;
	int	j;
	int	len;
	char	*res;

	i = -1;
	j = -1;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	if (!s1 && !s2)
		return (ft_str("(null)"));
	len = ft_len_str(s1) + ft_len_str(s2);
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while (s1[++i])
		res[i] = s1[i];
	while (s2[++j])
		res[i + j] = s2[j];
	res[i + j] = '\0';
	return (res);

}

//ft_dispatch ==> renvoi la string avce le résultat pour aller dans le char **
char	*ft_dispatch(va_list *lst, char *string, char c)
{
	if (c == 'd' || c == 'i' || c == 'l' || c == 'h')
		return (string = ft_itoa((va_arg(*lst, int)), "0123456789"));
	else if (c == 'u')
		return (string = ft_itoa((va_arg(*lst, unsigned int)), "0123456789"));
	else if  (c == 's')
		return (string = ft_str(va_arg(*lst, char *)));
	else if (c == 'c')
		return (string = ft_putchar(va_arg(*lst, int)));
	else if (c == '%')
		return (string = ft_putchar('%'));
	else if (c == 'x')
		return (string = ft_itoa((va_arg(*lst, unsigned int)), "0123456789abcdef"));
	else if (c == 'X')
		return (string = ft_itoa((va_arg(*lst, unsigned int)), "0123456789ABCDEF"));
	else if (c == 'p')
		return (string = ft_strjoin("0x", ft_itoa((va_arg(*lst, unsigned long int)), "0123456789abcdef")));
	else if (c == 'o')
		return (string = ft_itoa((va_arg(*lst, int)), "01234567"));
	return (string = ft_str("(null)"));
}
//////////////////////////////////////////////

///ft_printf_2 ==> cree le tableau en 2D content les résultats des opérattions
char	**ft_printf_2(char const *str, va_list ag)
{
	size_t		i;
	size_t		j;
	char		**res;

	i = 0;
	j = -1;
	res = malloc(sizeof(char *) * ((ft_numb_of_strings(str)) + 1));
	if (!res)
		return (0);
	while (str[i] && ft_numb_of_strings(str) != 0)
	{
		if (str[i] && str[i] == '%' && ++j <= ft_numb_of_strings(str) && ft_is_in(str[i + 1], "hlocspiudxX%") == 1)
		{
			res[j] = ft_dispatch(&ag, res[j], str[i + 1]);
			while (str[i]  && ft_is_in(str[i + 1], "hlocspiudxX") == 1)
				i++; 
		}
		if (str[i] && str[i] != '%')
			i++;
		else
			i++;
	}
	res[++j] = NULL;
	return (res);
}
////////////////////////////////////////////////////

///ft_len_res
size_t	ft_len_res(char const *str, char **tab)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	if (!str)
		return (0);
	len += ft_len_str(((char *)str));
	if (!tab)
		return (len);
	while (tab[i])
	{
		len+= ft_len_str(tab[i]);
		i++;
	}
	return (len);
}
////////////////////////////////////////////////////

///ft_printf
void	ft_pts(char *s, size_t size)
{
	size_t	i;

	i = -1;
	while (++i < size)
		write (1, &s[i], 1);
}

int	ft_printf(char const *str, ...)
{
	va_list		ag;
	char		**res;
	size_t		i;
	size_t		j;

	va_start(ag, str);
	if (ag == NULL)
		return (0);
	res = ft_printf_2(str, ag);
	va_end(ag);
	i = -1;
	j = -1;
	while (++i < ft_len_str((char *)str))
	{
		if (str[i] == '%' && ft_is_in(str[i + 1], "hlocsipudxX%") == 1 && ++j < ft_numb_of_strings(str) && i++)
		{
			ft_pts(res[j], ft_len_str(res[j]));
			while (str[i] && str[i + 1] && ft_is_in(str[i + 1] , "hlocspiudxX") == 1)
				++i;
		}
		else
			write (1, &str[i], 1);
	}
	if (!res)
		return (0);
	return (ft_len_res(((char *)str), res));
}
//////////////////////////////////

int	main()
{
	int i = 42;
	char c = 'a';
	char *s = "Hello, world!";
	double d = 3.14159;

	ft_printf("Integer: %d\n", i);
	ft_printf("Character: %c\n", c);
	ft_printf("String: %s%s\n", s, s);
	ft_printf("Double: %f\n", d);
	ft_printf("Hexadecimal: %x\n", i);
	ft_printf("Octal: %o\n", i);
	ft_printf("Long integer: %ld\n", (long)i);//////////////////////
	ft_printf("Long long integer: %lld\n", (long long)i);
	ft_printf("Short integer: %hd\n", (short)i);
	ft_printf("Unsigned integer: %u\n", (unsigned int)i);
	ft_printf("Long unsigned integer: %lu\n", (unsigned long)i);
	ft_printf("Long long unsigned integer: %llu\n", (unsigned long long)i);
	ft_printf("Pointer address: %p\n", (void *)&i);
	ft_printf("Scientific notation: %e\n", d);
	ft_printf("Scientific notation with uppercase: %E\n", d);

	//TEST OK
//	int	n = -70;
//	unsigned int nb = 100;
//	unsigned int *p = &nb;

//	unsigned int n = 17208;
//	unsigned int *s_2 = &n;
//	char *l = NULL;
//	int k[] = {1, 2, 3, 4, 5};

//	int	m = 0;
//	while (k[m] && m != 5)
//	{
//		printf("%d\n", k[m]);
//		printf("%d\n", k[m]);
//		m++;
//	}
	
//	ft_printf("bonjour %s\n", "bonjour");
//	ft_printf("ft_printf ; %i, %d, %u, %x, %X, %d%%, %p, %p\n", n, n, n, n, n, n, p, s_2);
//	printf("printf ; %i, %d, %u, %x, %X, %d%%, %p, %p\n", n, n, n, n, n, n,p, s_2);

//OK ft_printf("%x, %d, %i, %u, %d%%, %s, %X, %u\n", 200, 100, 50, 30, 20, "bonjour", 27, nb); printf("%x, %d, %i, %u, %d%%, %s, %X, %u\n", 200, 100, 50, 30, 20, "bonjour", 27, nb);
//test OK char	*str;str = ft_str(str, "bonjour");printf("str dans main <<%s>>\n", str);
//test OK int res = ft_numb_of_strings("bonjour %d, %s, %K, %s");	printf("%d\n", res);
//test Ok ft_printf("%d, %d, %d, %d, %d, %d\n", 10, 20, 30, 40, 50, 60);
//test OK char	*str = ft_putchar('a');	printf("%s\n", str);
//test OK char	*str = ft_itoa(1234);	printf("%s\n", str);
//test OK printf("nb 1 len ==>%zu\nnb 10 len ==> %zu\nnb -100 ==> %zu\n", ft_len(1), ft_len(10), ft_len(-100));
}
