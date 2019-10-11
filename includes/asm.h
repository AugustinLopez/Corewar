/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:56:16 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/11 18:24:28 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libft.h"
# include "op.h"
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>

# define USAGE			"Usage: ./asm [-b] <file.s>"
# define MALL_ERR		"Malloc error"
# define OPEN_ERR		"Can't open file"
# define WREND			"Missing terminating '\\n'"
# define EMPTY_FILE		"File is empty"
# define INV_F			"File is invalid"
# define NOT_NC			"Not a name nor a comment"
# define DUP_N			"Duplicate name"
# define DUP_C			"Duplicate comment"
# define LONG_N			"Name too long"
# define LONG_C			"Comment too long"
# define INFO_ERR		"Invalid information format"
# define EMPTY_N		"Name is empty"
# define EMPTY_C		"Comment is empty"
# define INV_LABCHAR	"Label contains invalid character"
# define INV_OP			"Invalid operation"
# define INV_NB_PAR		"Invalid param number for op"
# define INV_PAR		"Invalid parameter"
# define PAR_OP			"Invalid param for op"
# define EMPTY_CODE		"Empty code"
# define SIZE_ERR		"Program size exceeds VM size"

typedef	struct		s_rd
{
	char			*data;
	struct s_rd		*next;
}					t_rd;

typedef	struct		s_oplist
{
	int				op;
	int				ocp;
	char			**p;
	char			*lab;
	struct s_oplist	*next;
}					t_oplist;

typedef	struct		s_label
{
	char			*name;
	int				address;
	struct s_label	*next;
}					t_label;

typedef	struct		s_op
{
	int				op;
	char			*name;
	int				nsize;
	int				nbparam;
	int				ocp[10];
	int				dir_sz;
}					t_op;

typedef	struct		s_struct
{
	t_rd			*rd;
	int				rderr;
	t_header		header;
	t_oplist		*oplist;
	t_label			*lab;
	int				line;
	char			*fname;
	char			*fcor;
	int				index;
	int				last_opcode;
	unsigned char	*prog;
	int				bonus;
}					t_struct;

t_struct			*ft_init_s(int ac, char **av);

t_rd				*ft_read(t_struct *s, int fd, int beg);

void				ft_getheader(t_struct *s);

void				ft_getcode(t_struct *s);

void				ft_checkparam(t_struct *s, char **param, int oplist);

void				ft_next_rd(t_struct *s);
t_label				*ft_init_lab(t_struct *s, char *lab);
t_oplist			*ft_init_oplab(t_struct *s, char *lab);
void				ft_pushback_op(t_struct *s, t_oplist *oplist);
void				ft_pushback_lab(t_struct *s, t_label *lab);

char				**ft_getparam(t_struct *s, int i);
int					ft_ocp(int op, char **param);

int					ft_isskip(char *str);
int					ft_isinfo(char *str);
int					ft_islabchar(char c);
int					ft_islab(char *str);
int					ft_isop(char *str, int i, t_struct *s);

int					ft_isreg(char *str);
int					ft_isdir(char *str);
int					ft_isind(char *str);
int					ft_isparam(char *str);

void				ft_free_s(t_struct *s);

void				ft_error(t_struct *s, char *str, int par);

void				write_cor(t_struct *s);

void				write_param(t_struct *s, char *param, int opc);
int					is_four_dir(int opc);

extern t_op			g_optab[];

int					ft_isblank(int c);
int					ft_isint(char *str);
int					ft_islong(char *str);
int					ft_ismxdigit(int c);
int					ft_ismxlong(char *str);
int					ft_isspace(int c);
int					ft_str_is_mxdigit(char *str);
int					ft_str_is_numeric(char *str);

long				ft_atol_base(char *str, char *base);
long				ft_atol(const char *str);
char				*ft_ltoa(int64_t nb);
char				*ft_lutoa_base(uint64_t value, int base, int cas);
char				*ft_lconvert_base(char *nbr, char *base_from, char *base_to);

int					ft_cpos(char *str, char c);
char				*ft_joincstr(char c, char const *s2);

void				ft_free_strtab(char **str);
char				*ft_strjfree(char *s1, char *s2);
char				*ft_strsubfree(char *s, unsigned int start, size_t len);
char				*ft_strtrimfree(char *s);

char				*ft_strnjoin(char const *s1, char const *s2, size_t n);
unsigned int		ft_reverse_bytes(unsigned int nb);

#endif
