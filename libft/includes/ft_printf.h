/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hulefevr <hulefevr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/23 14:46:03 by hulefevr          #+#    #+#             */
/*   Updated: 2025/01/16 17:21:04 by hulefevr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <unistd.h>
# define UPPER_HEX_BASE "0123456789ABCDEF"
# define LOWER_HEX_BASE "0123456789abcdef"

void	printf_putchar(char c, int *count);
void	printf_putstr(char *str, int *count);
void	printf_putnbr_hexa(unsigned long int nb, char *base, int *count);
void	printf_putptr(void *ptr, int *count);
void	printf_putnbr(long long int nb, char *base, int len, int *count);

int		ft_printf(const char *str, ...);

#endif
