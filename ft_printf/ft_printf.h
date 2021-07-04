/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalim <kalim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/06 17:20:00 by kalim             #+#    #+#             */
/*   Updated: 2021/06/06 17:20:00 by kalim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <wchar.h>
# include <stdint.h>
# include <limits.h>

# define OUTPUT 1
# define YES 1
# define NO 0
# define ZEROS 1
# define SPACES 0

typedef struct s_wpvalue
{
	short	exist;
	int		value;
}				t_wpvalue;

typedef enum e_length
{
	NONE = 0,
	SHORT = 1,
	SHORT_SHORT = 2,
	LONG = 3,
	LONG_LONG = 4
}				t_length;

typedef enum e_type
{
	TBC = -1,
	CHAR = 'c',
	STRING = 's',
	POINTER = 'p',
	DECIMAL = 'd',
	INTEGER = 'i',
	UNSIGNED = 'u',
	HEX_LOWCASE = 'x',
	HEX_UPCASE = 'X',
	PERCENT = '%',
	NUMBER = 'n',
	FLOAT_LC = 'f',
	FLOAT_UC = 'F',
	GRAVITY_LC = 'g',
	GRAVITY_UC = 'G',
	EXPONENTIAL_LC = 'e',
	EXPONENTIAL_UC = 'E',
}				t_type;

typedef struct s_format
{
	short		flags[5];
	t_wpvalue	width;
	t_wpvalue	precision;
	t_length	length;
	t_type		type;
}				t_format;

typedef enum e_flag
{
	MINUS = 0,
	ZERO = 1,
	SHARP = 2,
	SPACE = 3,
	PLUS = 4
}				t_flag;

int			ft_printf(const char *str, ...);
int			process_input(char *input, va_list ap);

void		reset_format(t_format *format);
void		clear_format(t_format *format);
void		init_format(t_format *format);

void		process_type(int *printed_size, t_format format, va_list ap);
int			print_width(int width, short zero_pad);

short		parse_format(t_format *format, char **input, int *i, va_list ap);
void		parse_flags(t_format *format, char **input, int *i);
void		parse_width(t_format *format, char **input, int *i, va_list ap);
void		parse_precision(t_format *format, char **input, int *i,
				va_list ap);
void		parse_length(t_format *format, char **input, int *i);

void		process_char(int *printed_size, t_format format, va_list ap);
void		ft_prep_wchar(wchar_t c, char *unicode, int *bytes);
int			ft_print_wchar(wchar_t c);

void		process_string(int *printed_size, t_format format, va_list ap);
size_t		ft_wstrlen(const wchar_t *string);
void		ft_print_wstring(int *printed_size, t_format format,
				wchar_t *unistr);
void		print_string(int *printed_size, t_format format, char *str);
void		print_null(int *printed_size, t_format format);

void		process_decimal(int *printed_size, t_format format, va_list ap);
void		process_float(int *printed_size, t_format format, va_list ap,
				short uc);
void		print_float(int *printed_size, t_format format, double value,
				short uc);
void		process_gravity(int *printed_size, t_format format, va_list ap,
				short uc);
void		process_hexadecimal(int *printed_size, t_format format, va_list ap,
				short uc);
void		process_number(int *printed_size, t_format format, va_list ap);
void		process_percent(int *printed_size, t_format format);
void		process_pointer(int *printed_size, t_format format, va_list ap);
void		process_scientific(int *printed_size, t_format format, va_list ap,
				short uc);
void		print_scientific(int *printed_size, t_format format, double value,
				short uc);
void		process_unsigned(int *printed_size, t_format format, va_list ap);

int			ft_move_atoi(char **input, int *i);
char		*ft_ulltohex(unsigned long long nbr);
char		*ft_lltoa(long long nbr);
char		*ft_ulltoa(unsigned long long nbr);
char		*ft_dtoa(long double value, t_format format, int dec_places,
				short uc);
char		*ft_dtoe(double value, t_format format, int dec_places, short uc);
char		*ft_dtoa_sci(long double value, t_format format, int dp,
				long long *e);

int			ft_hexlen(unsigned long long nbr);
int			ft_longlonglen(long long nbr);
int			ft_ull_len(unsigned long long nbr);

int			ft_ld_finallen(long double value, int dec_places, short add_dot);
char		*ft_hardcodetoa(long double v, int dec_places, t_format format);
char		*ft_rvtoa(long double rv, int len, int dec_places,
				t_format format);
void		add_rvsign(long double value, t_format format, char *str);
void		convert_uc(char *temp, char **res, short uc);
long double	ft_round(long double value, int dec_places);

void		ft_sci_setup(double value, long double *mantissa,
				long long *exponent);
void		ft_sci_zero(double value, long double *mantissa,
				long long *exponent);
char		*ft_sci_join(long double m, long long e, int prec,
				t_format format);

char		*check_input(long double value, short uc);
short		is_not_a_num(long double n);
short		is_infinity(long double n);
short		is_neg_infinity(long double n);
short		is_negz(double value);

#endif