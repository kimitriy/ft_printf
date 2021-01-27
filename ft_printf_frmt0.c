/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_frmt0.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/03 12:14:01 by rburton           #+#    #+#             */
/*   Updated: 2020/12/20 14:24:45 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fsn(t_fld *nf, char *str, int len, int s)
{
	if (nf->flag[0] != '-')
	{
		if (nf->flag[0] == '0' && nf->dot != '.')
		{
			if (nf->sign == '-')
				write_minus(nf);
			write_zero(nf, s);
		}
		else
			write_space(nf, s);
		if (nf->sign == '-')
			write_minus(nf);
	}
	if (nf->wdth > nf->prcsn && nf->prcsn >= len)
		return ;
	if (nf->sign == '-')
		write_minus(nf);
	write_str(nf, str, len);
	if (nf->flag[0] == '-')
		write_space(nf, s);
}

void	fss(t_fld *nf, char *str, int s, int lim)
{
	if (nf->flag[0] != '-')
	{
		if (nf->flag[0] == '0')
			write_zero(nf, s);
		else
			write_space(nf, s);
	}
	write_str(nf, str, lim);
	if (nf->flag[0] == '-')
		write_space(nf, s);
}

void	fzn(t_fld *nf, char *str, int len, int z)
{
	if (nf->sign == '-')
	{
		write(1, "-", 1);
		nf->prntd++;
	}
	write_zero(nf, z);
	write_str(nf, str, len);
}

void	frmt_nbr(t_fld *nf, char *str)
{
	int		len;
	int		s;

	len = ft_strlen(str);
	if (len >= nf->wdth && len >= nf->prcsn)
		fsn(nf, str, len, 0);
	if (nf->prcsn > len && nf->prcsn >= nf->wdth)
		fzn(nf, str, len, nf->prcsn - len);
	if (nf->wdth > len && len > nf->prcsn)
	{
		s = nf->sign == '-' ? nf->wdth - len - 1 : nf->wdth - len;
		fsn(nf, str, len, s);
	}
	if (nf->wdth > nf->prcsn && nf->prcsn >= len)
	{
		s = nf->sign == '-' ? nf->wdth - nf->prcsn - 1 : nf->wdth - nf->prcsn;
		if (nf->flag[0] != '-')
			fsn(nf, str, len, s);
		fzn(nf, str, len, nf->prcsn - len);
		if (nf->flag[0] == '-')
			write_space(nf, s);
	}
	free(str);
}

void	frmt_str(t_fld *nf, char *str)
{
	int		len;

	if (nf->type == 'c' && str[0] == '\0')
		len = 1;
	else
		len = ft_strlen(str);
	if (nf->dot != '.')
	{
		if (nf->wdth > len)
			fss(nf, str, nf->wdth - len, len);
		else
			fss(nf, str, 0, len);
	}
	else
	{
		if (len > nf->prcsn && nf->wdth > nf->prcsn)
			fss(nf, str, nf->wdth - nf->prcsn, nf->prcsn);
		if (len > nf->prcsn && nf->prcsn >= nf->wdth)
			fss(nf, str, 0, nf->prcsn);
		if (nf->prcsn >= len && len >= nf->wdth)
			fss(nf, str, 0, len);
		if (nf->prcsn >= len && nf->wdth > len)
			fss(nf, str, nf->wdth - len, len);
	}
	free(str);
}
