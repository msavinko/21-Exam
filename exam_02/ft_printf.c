#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

int g_result, g_wide, g_prec;

static void ft_putchar(char c)
{
	write(1, &c, 1);
	g_result++;
}
static void ft_putstr(char *str, int length)
{
	int i = 0;
	while (i < length)
		ft_putchar(str[i++]);
}
static int ft_strlen(char *str)
{
	int i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}
static char *ft_itoa(unsigned long int num, int base)
{
	char *str = NULL;
	unsigned long int temp = num;
	int len = 0;
	if (num == 0)
		len++;
	while (temp > 0)
	{
		temp /= base;
		len++;
	}
	str = malloc(len +1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	while (len > 0)
	{
		if (num % base > 9)
			str[len - 1] = (num % base) + 'a' - 10;
		else
			str[len - 1] = (num % base) + '0';
		num /= base;
		len--;
	}
	return (str);
}
static void ft_print_s(char *str)
{
	if (!str)
		str = "(null)";
	int len = ft_strlen(str);
	if (g_prec < len && g_prec != -1)
		len = g_prec;
	while (g_wide-- > len)
		ft_putchar(' ');
	ft_putstr(str, len);
}
static void ft_print_d(long int num)
{
	int minus = 0;
	if (num < 0)
	{
		num *= -1;
		minus = 1;
		if (g_wide > 0)
			g_wide--;
	}
	char *str = ft_itoa(num, 10);
	int len = ft_strlen(str);
	if ((g_prec > len && g_prec != -1) || (g_prec == 0 && num == 0))
		len = g_prec;
	while (g_wide-- > len)
		ft_putchar(' ');
	if (minus)
		ft_putchar('-');
	while (len-- > ft_strlen(str))
		ft_putchar('0');
	if (!(g_prec == 0 && num == 0))
		ft_putstr(str, ft_strlen(str));
	free(str);
}
static void ft_print_x(unsigned long int num)
{
	char *str = ft_itoa(num, 16);
	int len = ft_strlen(str);
	if ((g_prec > len && g_prec != -1) || (g_prec == 0 && num == 0))
		len = g_prec;
	while (g_wide-- > len)
		ft_putchar(' ');
	while (len-- > ft_strlen(str))
		ft_putchar('0');
	if (!(g_prec == 0 && num == 0))
		ft_putstr(str, ft_strlen(str));
	free(str);
}
int ft_printf(const char *format,... )
{
	va_list ap;
	g_result = 0;
	va_start(ap, format);
	
	while(*format)
	{
		g_wide = 0;
		g_prec = -1;
		if (*format == '%')
		{
			format++;
			while (*format >= '0' && *format <= '9')
				g_wide = (g_wide * 10) + (*format++) - '0';
			if (*format == '.')
			{
				g_prec = 0;
				format++;
				while (*format >= '0' && *format <= '9')
					g_prec = (g_prec * 10) + (*format++) - '0';
			}
			if (*format == 's')
				ft_print_s(va_arg(ap, char *));
			else if (*format == 'd')
				ft_print_d(va_arg(ap, int));
			else if (*format == 'x')
				ft_print_x(va_arg(ap, unsigned int));
		}
		else
			ft_putchar(*format);
		format++;
	}
	va_end(ap);
	return (g_result);
}