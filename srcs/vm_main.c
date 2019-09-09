/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm_main.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcarlier <bcarlier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 19:02:24 by bcarlier          #+#    #+#             */
/*   Updated: 2019/09/09 19:02:31 by bcarlier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define MAX_FILE_SIZE 1000000

typedef	struct			t_listread
{
	char 				*line;
	struct	t_listread	*next;
}						s_listread

void	ft_lstread_free(char *line)
{
	if(line)
		free(line);
	line = 0;
}

void	ft_lstread_del(t_listread	*lst, void (*del)(char *))
{
	t_listread *temp;

	if (!*alst)
		return ;
	del((*alst)->line);
	temp = (*alst)->next;
	free(*alst);
	while (temp)
	{
		(*alst) = temp;
		del((*alst)->line);
		temp = (*alst)->next;
		free(*alst);
	}
	*alst = 0;
}

void	ft_lstread_new(void const *content, size_t content_size)
{
	t_listread	*elem;

	if (!(elem = (t_list*)malloc(sizeof(*elem))))
		return (0);
	if (!content)
		elem->line = 0;
	else
	{
		if (!(elem->line = malloc(content_size)))
		{
			free(elem);
			return (0);
		}
		ft_memcpy(elem->line, content, content_size);
	}
	elem->next = 0;
	return (elem);
}

void	ft_lstread_insert(t_listread	**alst, t_listread	*new)
{
	t_listread	tmp;

	tmp.line = (*alst)->line;
	tmp.next = (*alst)->next;
	(*alst)->line = new->line;
	(*alst)->next = new;
	new->line = tmp.line;
	new->next = tmp.next;
}

static	int		read_cor_file(t_listread	*file_read)
{
	int			ret;
	int			file_size;
	char		buf[4096+1]
	t_listread	*tmp;

	file_size = 0;
	while (ret = read(STDIN_FILENO, buf, 4096) && ret != -1)
	{
		buf[ret] = '\0';
		// cas ou fichier > 1mb, on free la list et on return
		if ((file_size += ret) > MAX_FILE_SIZE)
		{
			ft_lstread_del(&(file_read), ft_lstread_free);
			return (-1);
		}
		// 1er cas : file_read == NULL, on creer le premier noeud
		// 2eme cas : file_read existe, on ajoute a la fin
		if (!file_read)
			if (!(file_read = ft_lstread_new((void *)buf, (size_t)ret)))
				return (-1);
		else
		{
			if(!(tmp = ft_lstread_new((void *)buf, (size_t)ret)))
				return (-1);
			ft_lstread_insert(&(file_read), tmp);
		}
	}
	return (0);
}

int	main(int argc, char **argv)
{
	void(argc);
	void(argv);
	t_listread	*file_read;

	// A TESTER, not done yet
	if (!(ret = read_cor_file(file_read)))
		ft_dprintf(STDERR_FILENO, "ERROR\n");
	else
		ft_printf("%s", "Parsing file in list done\n");
	return (0)
}
