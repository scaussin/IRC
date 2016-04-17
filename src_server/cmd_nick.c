/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_nick.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 00:06:26 by scaussin          #+#    #+#             */
/*   Updated: 2016/04/18 00:07:18 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	cmd_nick(t_env *e, int cs, t_protocol msg)
{
	char	*prefix_tmp;
	char	*new_nick;

	if (check_error_nick(e, cs , msg, &new_nick) == 1)
	{
		prefix_tmp = gen_prefix(e->fds[cs]);
		send_protocol_to_chan(e, fill_protocol(prefix_tmp,
		"NICK", NULL, new_nick), cs);
		free(prefix_tmp);

		ft_strcpy(e->fds[cs].nick, new_nick);
		register_client(&e->fds[cs]);
	}		
}

int		check_error_nick(t_env *e, int cs, t_protocol msg, char **new_nick)
{
	if ((msg.params && (*new_nick = msg.params[0]) && msg.params[0][0]) 
		|| (*new_nick = msg.trailer))
	{
		if (ft_strlen(*new_nick) <= MAX_LEN_NICK)
			return (check_nick_in_use(e, cs, *new_nick));
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"ERR_ERRONEUSNICKNAME", NULL, "9 characters maximum"));
		return (-1);
	}
	else
	{
		send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"ERR_NONICKNAMEGIVEN", NULL, "No nickname given."));
		return (-1);
	}
}

int		check_nick_in_use(t_env *e, int cs, char *new_nick)
{
	int		i;
	char	**tmp_params;

	i = 0;
	while (i < e->maxfd)
	{
		if (!ft_strcmp(e->fds[i].nick, new_nick))
		{
			if (i == cs)
				return (0);	
			tmp_params = malloc_params(2);
			ft_strcpy(tmp_params[0], e->fds[i].nick);
			ft_strcpy(tmp_params[1], new_nick);
			send_protocol_to_client(&e->fds[cs], fill_protocol(NAME_SERVER,
			"ERR_NICKNAMEINUSE", tmp_params, "Nickname is already in use."));
			free(tmp_params);
			return (-1);
		}
		i++;
	}
	return (1);
}
