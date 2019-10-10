/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mde-laga.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:51:15 by bcarlier          #+#    #+#             */
/*   Updated: 2019/10/10 15:53:42 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MDE_LAGA_H
# define MDE_LAGA_H

#include "libft.h"
#include <stdlib.h>
#include <stdint.h>

int				ft_isblank(int c);
int				ft_isint(char *str);
int				ft_islong(char *str);
int				ft_ismxdigit(int c);
int				ft_ismxlong(char *str);
int				ft_isspace(int c);
int				ft_str_is_mxdigit(char *str);
int				ft_str_is_numeric(char *str);

long			ft_atol_base(char *str, char *base);
long			ft_atol(const char *str);
char			*ft_ltoa(int64_t nb);
char			*ft_lutoa_base(uint64_t value, int base, int cas);
char			*ft_lconvert_base(char *nbr, char *base_from, char *base_to);

int				ft_cpos(char *str, char c);
char			*ft_joincstr(char c, char const *s2);

void			ft_free_strtab(char **str);
char			*ft_strjfree(char *s1, char *s2);
char			*ft_strsubfree(char *s, unsigned int start, size_t len);
char			*ft_strtrimfree(char *s);

#endif
