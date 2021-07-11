/*
** Requirements for old ft_printf
**
** Type		: %c, %s, %p, %i, %d, %u, %x, %X, %%, %n, %f, %g, %e
** Width	: YES (including *)
** Precision: YES (including *)
** Flags	: '-', '0', '#', ' ', '+'
** Length	: l, ll, h, hh
*/

/*
** Type		: %s, %d, %x
** Width	: YES (excluding *)
** Precision: YES (excluding *)
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdarg.h>

#define YES 1
#define NO 0
#define ZEROS 1
#define SPACE 0

typedef struct s_wpvalue
{
	short	exist;
	int		value;
}				t_wpvalue;

typedef enum e_type
{
	TBC = -1,
	STRING = 's',
	DECIMAL = 'd',
	HEX_LOWCASE = 'x',
}				t_type;

typedef struct s_format
{
	t_wpvalue	width;
	t_wpvalue	precision;
	t_type		type;
}				t_format;



// Simple Libft Functions

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	ft_min(int a, int b)
{
	if (a <= b)
		return (a);
	else
		return (b);
}

int	ft_max(int a, int b)
{
	if (a >= b)
		return (a);
	else
		return (b);
}

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (1);
	else
		return (0);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_putstrn_fd(char *s, size_t n, int fd)
{
	size_t	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] && i < n)
	{
		write(fd, &s[i], 1);
		i++;
	}
}

int	print_width(int width, short zero_pad)
{
	int	print_count;

	print_count = 0;
	while (print_count++ < width)
	{
		if (zero_pad)
			write(1, "0", 1);
		else
			write(1, " ", 1);
	}
	return (print_count);
}



// Converter functions

int	ft_move_atoi(char **input, int *i)
{
	int	res;

	res = 0;
	while (ft_isdigit((*input)[*i]))
	{
		res *= 10;
		res += (*input)[*i] - '0';
		(*i)++;
	}
	return (res);
}

char	*ft_itoa_base(long long nbr, int base)
{
	long long	num;
	int			len;
	char		*res;
	char		*base_value;
	
	num = nbr;
	len = 1;
	if (num < 0)
		len += 1;
	while (num / base)
	{
		len++;
		num /= base;
	}

	res = (char *)malloc(sizeof(char) * len + 1);
	if (!res)
		return (0);
	res[len] = 0;
	res[0] = '0';
	if (nbr < 0)
		res[0] = '-';
	
	base_value = "0123456789abcdef";
	while (nbr)
	{
		res[--len] = base_value[ft_abs((int)(nbr % base))];
		nbr /= base;
	}
	return (res);
}



// Processor functions

void	reset_format(t_format *format)
{
	format->width.exist = NO;
	format->precision.exist = NO;
	format->type = TBC;
}

short	parse_format(t_format *format, char **input, int *i)
{
	char	c;

	c = (*input)[*i];
	if (ft_isdigit(c))
	{
		format->width.exist = YES;
		format->width.value = ft_move_atoi(input, i);
	}

	if ((*input)[*i] == '.')
	{
		c = (*input)[++(*i)];
		format->precision.exist = YES;
		if (ft_isdigit(c))
			format->precision.value = ft_move_atoi(input, i);
		else
			format->precision.value = 0;
	}

	c = (*input)[*i];
	if (c != STRING && c != DECIMAL && c != HEX_LOWCASE)
		return (0);
	format->type = c;

	return (1);
}



// Process Types %s, %d, %x

void	process_string(int *printed_size, t_format format, va_list ap)
{
	char	*str;
	int		adjusted_strlen;

	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	adjusted_strlen = ft_strlen(str);
	if (format.precision.exist)
		adjusted_strlen = ft_min(ft_strlen(str), format.precision.value);
	if (format.width.exist)
		*printed_size += print_width(format.width.value - adjusted_strlen, SPACE);
	ft_putstrn_fd(str, adjusted_strlen, 1);
	*printed_size += adjusted_strlen;
}

void	process_number(int *printed_size, t_format format, va_list ap, int base)
{
	long long	nbr;
	short		sign;
	int			numlen;
	char		*num;

	nbr = va_arg(ap, int);
	num = ft_itoa_base(nbr, base);
	numlen = ft_strlen(num);

	sign = 0;
	if (nbr < 0)
		sign = 1;
	
	if (format.precision.exist)
		numlen = ft_max(ft_strlen(num), sign + format.precision.value);
	if (format.precision.exist && format.precision.value == 0 && nbr == 0)
	{
		num[0] = 0;
		numlen = 0;
	}

	if (format.width.exist)
		*printed_size += print_width(format.width.value - numlen, SPACE);
	if (nbr < 0)
	{
		write(1, "-", 1);
		*printed_size += 1;
	}
	if (format.precision.exist)
		*printed_size += print_width(numlen - ft_strlen(num), ZEROS);
	
	if (nbr < 0)
	{
		ft_putstrn_fd(num + 1, ft_strlen(num) - 1, 1);
		*printed_size += (ft_strlen(num) - 1);
	}
	else
	{
		ft_putstrn_fd(num, ft_strlen(num), 1);
		*printed_size += ft_strlen(num);
	}
	free(num);
}

void	process_type(int *printed_size, t_format format, va_list ap)
{
	if (format.type == STRING)
		process_string(printed_size, format, ap);
	else if (format.type == DECIMAL)
		process_number(printed_size, format, ap, 10);
	else if (format.type == HEX_LOWCASE)
		process_number(printed_size, format, ap, 16);
}



// printf functions

int	process_input(char *input, va_list ap)
{
	int			printed_size;
	int			i;
	t_format	format;

	i = 0;
	printed_size = 0;
	while (input[i])
	{
		if (input[i] == '%' && input[i + 1])
		{
			i++;
			reset_format(&format);
			if (!parse_format(&format, &input, &i))
				return (-1);
			process_type(&printed_size, format, ap);
		}
		else
		{
			write(1, &input[i], 1);
			printed_size += 1;
		}
		i++;
	}
	return (printed_size);
}

int	ft_printf(const char *str, ...)
{
	va_list		ap;
	char		*input;
	int			printed_size;

	va_start(ap, str);
	printed_size = process_input((char *)str, ap);
	va_end(ap);
	return (printed_size);
}


int	main(void)
{
	ft_printf("Hey\n");
	ft_printf("|%.5s|\n|%.9s|\n|%9.5s|\n|%5.9s|\n|%12.9s|\n", "I'm Kai", "I'm Kai", "I'm Kai", "I'm Kai", "I'm Kai");
	ft_printf("%d\n", 12345);
	ft_printf("%x\n", 12345);
}