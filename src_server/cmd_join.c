/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 00:11:54 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/28 12:20:10 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int		check_error_join(t_env *e, int cs, char **params)
{
	if (!params || !params[0] || !params[0][0] || params[0][0] != '#'
		|| !ft_isprint(params[0][1]))
	{
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"461", NULL, "need chan name"));
		return (-1);
	}
	if (ft_strlen_2d(params) > 1)
	{
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"405", NULL, "You can join one channel at a time"));
		return (-1);
	}
	return (1);
}

void	cmd_join(t_env *e, int cs, t_protocol msg)
{
	char	*prefix;

	if (check_error_join(e, cs, msg.params) == -1)
		return ;
	if (e->fds[cs].chan)
	{
		cmd_part(e, cs, msg);
	}
	prefix = gen_prefix(e->fds[cs]);
	e->fds[cs].chan = ft_strdup(msg.params[0]);
	send_protocol_to_chan(e, cs,
		fill_protocol(prefix, "JOIN", msg.params, NULL));
	free(prefix);
	cmd_names(e, cs, msg);
}

void	cmd_part(t_env *e, int cs, t_protocol msg)
{
	char	*prefix;
	char	**params;

	msg = *(&msg);
	if (e->fds[cs].chan)
	{
		prefix = gen_prefix(e->fds[cs]);
		params = malloc_params(1);
		ft_strcpy(params[0], e->fds[cs].chan);
		send_protocol_to_chan(e, cs,
		fill_protocol(prefix, "PART", params, NULL));
		free(e->fds[cs].chan);
		e->fds[cs].chan = NULL;
		free_params(params);
		free(prefix);
	}
	else
	{
		send_protocol_to_client(&e->fds[cs],
			fill_protocol(NAME_SERVER, "442", NULL, "Not on channel."));
	}
}
