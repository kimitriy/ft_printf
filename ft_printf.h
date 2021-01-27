/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburton <rburton@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 19:54:23 by mspinnet          #+#    #+#             */
/*   Updated: 2020/12/20 14:24:16 by rburton          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdlib.h>
# include <unistd.h>
# include <stdarg.h>

typedef struct	s_fld
{
	char		*flag;
	int			wdth;
	char		dot;
	int			prcsn;
	char		type;
	char		sign;
	int			prntd;
	char		*sxtn;
}				t_fld;

int				ft_printf(const char *str, ...);
t_fld			*nf_calloc(void);
void			nf_zero(t_fld *p);
void			nf_free(t_fld *nf);

int				prsr(int indx, char *str, va_list *ap, t_fld *nf);
int				fprsr(int indx, char *str, t_fld *nf);
int				wprsr(int indx, char *str, t_fld *nf, va_list *ap);
int				pprsr(int indx, char *str, t_fld *nf, va_list *ap);
int				tprsr(int indx, char *str, t_fld *nf);

void			hndlr(va_list *ap, t_fld *nf);
int				nbr_length(long long int n, int base);
void			nbr2str(long long int n, char *str, t_fld *nf);
void			type_di(va_list *ap, t_fld *nf);
void			type_u(va_list *ap, t_fld *nf);

void			type_xx(va_list *ap, t_fld *nf);
void			type_p(va_list *ap, t_fld *nf);
void			type_s(va_list *ap, t_fld *nf);
void			type_c(va_list *ap, t_fld *nf);
void			type_prcnt(t_fld *nf);

void			fsn(t_fld *nf, char *str, int len, int s);
void			fss(t_fld *nf, char *str, int s, int lim);
void			fzn(t_fld *nf, char *str, int len, int z);
void			frmt_nbr(t_fld *nf, char *str);
void			frmt_str(t_fld *nf, char *str);

void			write_space(t_fld *nf, int	s);
void			write_zero(t_fld *nf, int	z);
void			write_minus(t_fld *nf);
void			write_str(t_fld *nf, char *str, int lim);

int				f2up(int c);
int				ft_isdigit(int c);
void			ft_bzero(void *s, size_t n);
char			*ft_strchr(const char *s, int c);
int				ft_strlen(const char *s);

int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
char			*ft_strjoin(char const *s1, char const *s2);

#endif
