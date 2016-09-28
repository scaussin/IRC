/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/26 15:49:45 by scaussin          #+#    #+#             */
/*   Updated: 2016/08/27 01:08:06 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	cmd_list(t_env *e, int cs, t_protocol msg)
{
	char	*(params[2]);
	char	**array_list;
	int		i;

	msg = *(&msg);
	i = 0;
	params[1] = NULL;
	array_list = get_chan_list(e);
	send_protocol_to_client(&e->fds[cs],
		fill_protocol(NAME_SERVER, "321", NULL, "start list"));
	while (array_list[i])
	{
		params[0] = array_list[i];
		send_protocol_to_client(&e->fds[cs],
			fill_protocol(NAME_SERVER, "322", params, NULL));
		free(array_list[i]);
		i++;
	}
	send_protocol_to_client(&e->fds[cs],
		fill_protocol(NAME_SERVER, "323", NULL, "end list"));
	free(array_list);
}

char	**get_chan_list(t_env *e)
{
	int		i;
	int		j;
	char	**chan_list;

	i = 0;
	j = 0;
	chan_list = (char **)XV(NULL,
		malloc((e->max + 1) * sizeof(char *)), "malloc");
	ft_bzero(chan_list, (e->max + 1) * sizeof(char *));
	while (i <= e->max)
	{
		if (e->fds[i].type == FD_CLIENT_REGISTER &&
			e->fds[i].chan && !str_exist_in_array(chan_list, e->fds[i].chan))
		{
			chan_list[j] = ft_strdup(e->fds[i].chan);
			j++;
		}
		i++;
	}
	return (chan_list);
}

int		str_exist_in_array(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (ft_strcmp(array[i], str) == 0)
			return (1);
		i++;
	}
	return (0);
}
