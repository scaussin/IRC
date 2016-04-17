/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_join.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 00:11:54 by scaussin          #+#    #+#             */
/*   Updated: 2016/04/18 00:12:38 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

int		check_error_join(t_env *e, int cs, char **params)
{
	if (!params || !params[0] || !params[0][0] || params[0][0] != '#' 
		|| !ft_isprint(params[0][1]))
	{
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"ERR_NEEDMOREPARAMS", NULL, "need chan name"));
		return (-1);
	}
	if (ft_strlen_2d(params) > 1)
	{
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"ERR_TOOMANYCHANNELS", NULL, "You can join one channel at a time"));
		return (-1);
	}
	return (1);
}

void	cmd_join(t_env *e, int cs, t_protocol msg)
{
	if (check_error_join(e, cs, msg.params) == -1)
		return ;
	//quit chan
	//free if already in chan
	e->fds[cs].chan = ft_strdup(msg.params[0]);
	send_protocol_to_client(&e->fds[cs], fill_protocol(
		"scaussin!~Adium@127.0.0.1",
		"JOIN", msg.params, NULL));
	cmd_names(e, cs, msg);
}
