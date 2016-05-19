/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_fd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 00:30:04 by scaussin          #+#    #+#             */
/*   Updated: 2016/04/27 11:16:30 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "bircd.h"

void	clean_fd(t_fd *fd)
{
	if (fd->host)
		free(fd->host);
	if (fd->name)
		free(fd->name);
	if (fd->chan)
		free(fd->chan);
	ft_bzero(fd, sizeof(t_fd));
	fd->type = FD_FREE;
}
