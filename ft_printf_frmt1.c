/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_frmt1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 17:03:29 by rburton           #+#    #+#             */
/*   Updated: 2020/12/20 14:21:50 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_minus(t_fld *nf)
{
	write(1, "-", 1);
	nf->sign = '\0';
	nf->prntd++;
}

void	write_space(t_fld *nf, int s)
{
	int		i;

	i = 0;
	while (i < s)
	{
		write(1, " ", 1);
		nf->prntd++;
		i++;
	}
}

void	write_zero(t_fld *nf, int z)
{
	int		i;

	i = 0;
	while (i < z)
	{
		write(1, "0", 1);
		nf->prntd++;
		i++;
	}
}

void	write_str(t_fld *nf, char *str, int lim)
{
	int		i;

	i = 0;
	if ((nf->type == 'd' || nf->type == 'u' || nf->type == 'x') &&
	nf->dot == '.' && nf->wdth == 0 && nf->prcsn == 0 && str[0] == '0')
		return ;
	else if ((nf->type == 'd' || nf->type == 'u' || nf->type == 'x')
	&& nf->dot == '.' && nf->prcsn == 0 && str[0] == '0')
	{
		write(1, " ", 1);
		nf->prntd++;
		return ;
	}
	while (i < lim)
	{
		write(1, &str[i], 1);
		nf->prntd++;
		i++;
	}
}
