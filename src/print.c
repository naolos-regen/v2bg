#include "../includes/v2bg.h"
#include <stdarg.h>
#include <stddef.h>

static int	append_str(char *buf, size_t size, size_t *pos, const char *s)
{
	while (*s && *pos + 1 < size)
		buf[(*pos)++] = *s++;
	return (0);
}

static	int	append_unsigned_long(char *buf, size_t size, size_t *pos, unsigned long val)
{
	char tmp[21];
	int i;
	i = 20;
	tmp[i--] = 0;
	do 
		tmp[i--] = '0' + (val % 10);
	while ((val /= 10) && i >= 0);
	return (append_str(buf, size, pos, &tmp[i + 1]));
}

static int	append_int(char *buf, size_t size, size_t *pos, int val)
{
	char	tmp[12];
	int		i;
	int		neg;

	i = 11;
	neg = val < 0;
	if (neg)
		val = -val;
	tmp[i--] = 0;
	do
		tmp[i--] = '0' + (val % 10);
	while ((val /= 10) && i >= 0);
	if (neg)
		tmp[i--] = '-';
	return (append_str(buf, size, pos, &tmp[i + 1]));
}

static int	append_char(char *buf, size_t size, size_t *pos, char c)
{
	if (*pos + 1 < size)
		buf[(*pos)++] = c;
	return (0);
}

int	ft_snprintf(char *buf, size_t size, const char *fmt, ...)
{
	va_list	args;
	size_t	pos;

	va_start(args, fmt);
	pos = 0;
	while (*fmt && pos + 1 < size)
	{
		if (*fmt == '%')
		{
			fmt++;
			if (*fmt == 's')
				append_str(buf, size, &pos, va_arg(args, char *));
			else if (*fmt == 'd')
				append_int(buf, size, &pos, va_arg(args, int));
			else if (*fmt == 'c')
				append_char(buf, size, &pos, (char)va_arg(args, int));
			else if (*fmt == 'l' && *(fmt + 1) == 'u')
				append_unsigned_long(buf, size, &pos, va_arg(args, unsigned long)), fmt++;
			else
				append_char(buf, size, &pos, '%'), append_char(buf, size, &pos,	*fmt);
		}
		else
			append_char(buf, size, &pos, *fmt);
		fmt++;
	}
	if (size)
		buf[pos] = 0;
	va_end(args);
	return ((int)pos);
}
