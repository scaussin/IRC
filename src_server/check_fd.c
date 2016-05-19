/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/27 11:13:27 by scaussin          #+#    #+#             */
/*   Updated: 2016/04/27 11:16:22 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	check_fd(t_env *e)
{
	int	i;
	i = 0;

	while ((i < e->maxfd) && (e->r > 0))
	{
		if (FD_ISSET(i, &e->fd_read))
		{
			e->fds[i].fct_read(e, i);
			e->r--;
		}
		if (FD_ISSET(i, &e->fd_write))
		{
			e->fds[i].fct_write(e, i);
			e->r--;
		}
		i++;
	}
}
