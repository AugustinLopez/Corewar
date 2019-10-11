/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_bytes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mde-laga <mde-laga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 14:00:40 by algautie          #+#    #+#             */
/*   Updated: 2019/10/10 13:44:54 by mde-laga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_reverse_bytes(unsigned int nb)
{
	unsigned int	ret;
	int				i;

	i = 4;
	while (--i >= 0)
	{
		((char*)(&ret))[i] = ((char*)(&nb))[0];
		nb = nb >> 8;
	}
	return (ret);
}
