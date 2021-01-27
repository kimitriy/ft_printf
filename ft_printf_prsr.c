/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_prsr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:11:43 by rburton           #+#    #+#             */
/*   Updated: 2020/12/20 14:22:28 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		fprsr(int indx, char *str, t_fld *nf)
{
	int			i;
	int			f;
	const char	flag[] = "-0";

	i = indx;
	f = 0;
	while (ft_strchr(flag, str[i]) != NULL)
	{
		if (ft_strchr(nf->flag, str[i]) == NULL)
		{
			nf->flag[f] = str[i];
			f++;
		}
		i++;
	}
	if (nf->flag[1] == '-')
		nf->flag[0] = nf->flag[1];
	return (i);
}

int		wprsr(int indx, char *str, t_fld *nf, va_list *ap)
{
	int		w;
	char	dgts[11];

	w = 0;
	while (w < 11)
		dgts[w++] = '\0';
	w = 0;
	if (ft_isdigit(str[indx]) == 1)
	{
		while (ft_isdigit(str[indx]) == 1)
			dgts[w++] = str[indx++];
		nf->wdth = ft_atoi(dgts);
	}
	else if (str[indx] == 42)
	{
		nf->wdth = va_arg(*ap, int);
		if (nf->wdth < 0)
		{
			nf->flag[0] = '-';
			nf->wdth = (-1) * nf->wdth;
		}
		indx++;
	}
	return (indx);
}

int		pprsr(int indx, char *str, t_fld *nf, va_list *ap)
{
	int		i;
	int		p;
	char	dgts[11];

	i = indx;
	p = 0;
	while (p < 11)
		dgts[p++] = '\0';
	p = -1;
	if (ft_isdigit(str[i]) == 1)
	{
		while (ft_isdigit(str[i]) == 1)
			dgts[++p] = str[i++];
		nf->prcsn = ft_atoi(dgts);
	}
	else if (str[i] == 42)
	{
		nf->prcsn = va_arg(*ap, int);
		i++;
	}
	return (i);
}

int		tprsr(int indx, char *str, t_fld *nf)
{
	int			i;
	const char	type[] = "cspdiuxX%";

	i = indx;
	if (ft_strchr(type, str[i]) != NULL)
	{
		if (str[i] == 'i')
			nf->type = 'd';
		else
			nf->type = str[i];
	}
	return (i);
}

int		prsr(int indx, char *str, va_list *ap, t_fld *nf)
{
	int		i;

	i = indx + 1;
	i = fprsr(i, str, nf);
	i = wprsr(i, str, nf, ap);
	if (str[i] == 46)
	{
		nf->dot = 46;
		i++;
	}
	i = pprsr(i, str, nf, ap);
	i = tprsr(i, str, nf);
	hndlr(ap, nf);
	return (i);
}
