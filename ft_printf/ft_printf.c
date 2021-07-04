/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kalim <kalim@student.42kl.edu.my>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 11:11:11 by kalim             #+#    #+#             */
/*   Updated: 2021/06/02 11:11:11 by kalim            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
			if (!parse_format(&format, &input, &i, ap))
				return (-1);
			process_type(&printed_size, format, ap);
		}
		else
		{
			ft_putchar_fd(input[i], 1);
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
	input = ft_strdup(str);
	printed_size = process_input(input, ap);
	va_end(ap);
	free(input);
	return (printed_size);
}
