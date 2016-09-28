/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 11:05:09 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/28 12:28:08 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	cmd_ping(t_env *e, int cs, t_protocol msg)
{
	char	*tmp;
	char	*str;

	if (msg.params && msg.params[0])
		str = ft_strjoin("PONG :", msg.params[0]);
	else
		str = ft_strjoin("PONG :", "");
	tmp = str;
	str = ft_strjoin(str, "\r\n");
	free(tmp);
	send_str_to_client(&e->fds[cs], str);
	free(str);
}

void	cmd_away(t_env *e, int cs, t_protocol msg)
{
	char	*tmp;
	char	*str;

	msg = *(&msg);
	str = ft_strjoin(":irc_scaussin 305 ", e->fds[cs].nick);
	tmp = str;
	str = ft_strjoin(str, " :You are no longer marked as being away\r\n");
	free(tmp);
	send_str_to_client(&e->fds[cs], str);
	free(str);
}

int		str_isalnum(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]))
			return (-1);
		i++;
	}
	return (1);
}

void	cmd_users(t_env *e, int cs, t_protocol msg)
{
	msg = *(&msg);
	send_protocol_to_client(&e->fds[cs],
		fill_protocol(NAME_SERVER, "446", NULL,
			"cmd USERS disabled"));
}

int		extract_params(char ***params, char **msg)
{
	if (!msg || !*msg || !**msg)
		return (0);
	(*params) = ft_strsplit(*msg, ' ');
	return (1);
}
