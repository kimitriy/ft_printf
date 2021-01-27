/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hndlr1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/13 16:58:34 by rburton           #+#    #+#             */
/*   Updated: 2020/12/20 14:22:03 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	type_xx(va_list *ap, t_fld *nf)
{
	unsigned int	n;
	char			*str;
	int				len;

	n = va_arg(*ap, unsigned int);
	len = nbr_length(n, 16);
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
	nbr2str((long long int)n, str, nf);
	frmt_nbr(nf, str);
}

void	type_p(va_list *ap, t_fld *nf)
{
	long long int	n;
	const char		*str0x = "0x";
	char			*str;
	char			*strleak;

	n = (long long int)va_arg(*ap, void *);
	str = ft_calloc(nbr_length(n, 16) + 1, sizeof(char));
	nbr2str((long long int)n, str, nf);
	strleak = str;
	if (n == 0 && nf->dot == '.')
		str = ft_strjoin(str0x, "");
	else
		str = ft_strjoin(str0x, str);
	frmt_nbr(nf, str);
	free(strleak);
}

void	type_s(va_list *ap, t_fld *nf)
{
	int		i;
	int		len;
	char	*str;
	char	*str_f;

	str = va_arg(*ap, char *);
	if (str == NULL)
		str = "(null)";
	len = ft_strlen(str);
	if (len == 0)
		len = 1;
	if (nf->prcsn < 0)
		nf->prcsn = len;
	str_f = ft_calloc(len + 1, sizeof(char));
	i = -1;
	while (++i < len)
		str_f[i] = str[i];
	frmt_str(nf, str_f);
}

void	type_c(va_list *ap, t_fld *nf)
{
	char	ch;
	char	*str;

	ch = (char)va_arg(*ap, int);
	str = ft_calloc(2, sizeof(char));
	str[0] = ch;
	frmt_str(nf, str);
}

void	type_prcnt(t_fld *nf)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	str[0] = '%';
	frmt_str(nf, str);
}
