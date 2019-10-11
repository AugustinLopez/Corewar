/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 10:59:13 by mde-laga          #+#    #+#             */
/*   Updated: 2019/10/11 15:36:21 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		ft_error(t_struct *s, char *str, int par)
{
	if (par == -1)
		ft_dprintf(STDERR_FILENO, "%sError: %s\n%s", FT_RED, str, FT_EOC);
	else if (!par)
		ft_dprintf(STDERR_FILENO
			, "%sError: %s at line %d%s\n", FT_RED, str, s->line, FT_EOC);
	else
		ft_dprintf(STDERR_FILENO, "%sError: Param %d is invalid at line %d%s\n"
			, FT_RED, par, s->line, FT_EOC);
	if (s)
		ft_free_s(s);
	exit(-1);
}

static void	ft_checkfile(int ac, char **av)
{
	if (ac < 1 || ac > 3)
		ft_error(NULL, NULL, -1);
	if (av[ac - 1][ft_strlen(av[ac - 1]) - 2] != '.'
		|| av[ac - 1][ft_strlen(av[ac - 1]) - 1] != 's')
		ft_error(NULL, USAGE, -1);
}

static void	ft_getrd(t_struct *s, int ac, char **av)
{
	int			fd;
	char		c;

	if ((fd = open(av[ac - 1], O_RDONLY)) == -1)
		ft_error(s, OPEN_ERR, 0);
	lseek(fd, -1, SEEK_END);
	read(fd, &c, 1);
	lseek(fd, 0, SEEK_SET);
	if (c != '\n')
	{
		close(fd);
		ft_error(NULL, WREND, -1);
	}
	if (!(s->rd = ft_read(s, fd, 1)))
		ft_error(s, EMPTY_FILE, 0);
	if (s->rderr)
		ft_error(s, INV_F, -1);
	close(fd);
}

int			main(int ac, char **av)
{
	t_struct	*s;

	ft_checkfile(ac, av);
	s = ft_init_s(ac, av);
	ft_getrd(s, ac, av);
	ft_getheader(s);
	ft_getcode(s);
	write_cor(s);
	ft_free_s(s);
	return (0);
}
