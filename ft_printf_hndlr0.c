/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hndlr0.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:11:43 by rburton           #+#    #+#             */
/*   Updated: 2020/12/20 14:21:56 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		nbr_length(long long int n, int base)
{
	size_t	i;

	i = 0;
	if (n < 0)
	{
		n = -n;
		i++;
	}
	while (n >= base)
	{
		n = n / base;
		i++;
	}
	i += 1;
	return (i);
}

void	nbr2str(long long int n, char *str, t_fld *nf)
{
	int				i;
	int				bs;
	long long int	in;

	in = n;
	if (nf->type == 'x' || nf->type == 'X' || nf->type == 'p')
		bs = 16;
	else
		bs = 10;
	i = nbr_length(in, bs) - 1;
	while (i >= 0)
	{
		str[i] = nf->type == 'X' ? f2up(nf->sxtn[in % bs]) : nf->sxtn[in % bs];
		in = in / bs;
		i--;
	}
	if (nf->type == 'X')
		nf->type = 'x';
}

void	type_di(va_list *ap, t_fld *nf)
{
	long int	n;
	char		*str;
	int			len;

	n = va_arg(*ap, int);
	if (n < 0)
	{
		nf->sign = '-';
		n = -n;
	}
	len = nbr_length(n, 10);
	if (nf->flag[0] == '0' && nf->wdth == 0 && nf->prcsn < 0)
		nf->prcsn = 1;
	else if (nf->flag[0] == '0' && nf->wdth != 0
	&& nf->prcsn < 0 && nf->sign == '-')
		nf->prcsn = nf->wdth - 1;
	else if (nf->flag[0] == '0' && nf->wdth != 0 && nf->prcsn < 0)
		nf->prcsn = nf->wdth;
	else if (nf->flag[0] != '0' && nf->prcsn < 0)
		nf->prcsn = len;
	str = ft_calloc(len + 1, sizeof(char));
	nbr2str(n, str, nf);
	frmt_nbr(nf, str);
}

void	type_u(va_list *ap, t_fld *nf)
{
	unsigned int	n;
	char			*str;
	int				len;

	n = va_arg(*ap, unsigned int);
	len = nbr_length(n, 10);
	if (nf->flag[0] == '0' && nf->wdth == 0 && nf->prcsn < 0)
		nf->prcsn = 1;
	else if (nf->flag[0] == '0' && nf->wdth != 0
	&& nf->prcsn < 0 && nf->sign == '-')
		nf->prcsn = nf->wdth - 1;
	else if (nf->flag[0] == '0' && nf->wdth != 0 && nf->prcsn < 0)
		nf->prcsn = nf->wdth;
	else if (nf->flag[0] != '0' && nf->prcsn < 0)
		nf->prcsn = len;
	str = ft_calloc(nbr_length(n, 10) + 1, sizeof(char));
	nbr2str((long long int)n, str, nf);
	frmt_nbr(nf, str);
}

void	hndlr(va_list *ap, t_fld *nf)
{
	if (nf->type == 'd' || nf->type == 'i')
		type_di(ap, nf);
	if (nf->type == 'u')
		type_u(ap, nf);
	if (nf->type == 'x' || nf->type == 'X')
		type_xx(ap, nf);
	if (nf->type == 'p')
		type_p(ap, nf);
	if (nf->type == 's')
		type_s(ap, nf);
	if (nf->type == 'c')
		type_c(ap, nf);
	if (nf->type == '%')
		type_prcnt(nf);
}
