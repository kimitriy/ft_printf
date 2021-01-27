/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 15:11:43 by rburton           #+#    #+#             */
/*   Updated: 2020/12/20 14:24:19 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	nf_zero(t_fld *p)
{
	ft_bzero(p->flag, 2);
	p->wdth = 0;
	p->dot = '\0';
	p->prcsn = 0;
	p->type = '\0';
	p->sign = '\0';
	p->sxtn = "0123456789abcdef";
}

t_fld	*nf_calloc(void)
{
	t_fld	*p;

	if (!(p = (struct s_fld*)malloc(1 * sizeof(t_fld))))
		return (NULL);
	if (!(p->flag = (char*)malloc(2 * sizeof(char))))
		return (NULL);
	nf_zero(p);
	return (p);
}

void	nf_free(t_fld *nf)
{
	free(nf->flag);
	free(nf);
}

int		ft_printf(const char *str, ...)
{
	int		i;
	t_fld	*nf;
	va_list ap;

	nf = nf_calloc();
	nf->prntd = 0;
	va_start(ap, str);
	i = -1;
	while (++i < ft_strlen(str))
	{
		if (str[i] != '%')
		{
			write(1, &str[i], 1);
			nf->prntd++;
		}
		if (str[i] == '%')
		{
			i = prsr(i, (char*)str, &ap, nf);
			nf_zero(nf);
		}
	}
	va_end(ap);
	i = nf->prntd;
	nf_free(nf);
	return (i);
}
