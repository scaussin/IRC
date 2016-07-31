/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 20:17:28 by scaussin          #+#    #+#             */
/*   Updated: 2016/07/30 22:06:07 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

int		lexer_client(t_client *e, t_parsing_client *msg)
{
	char	*line;
	char	*tmp;
	char	*end;

	line = read_buf(e->buf_read_client);
	tmp = line;
	if (!line)
	{
		free(tmp);
		return (0);
	}
	if (!(end = ft_strstr(line, "\n")))
	{
		free(tmp);
		write_log("warning", "msg not ending");
		return (0);
	}
	update_offset_buf(&e->buf_read_client, (end - line) + 1);
	*end = 0;
	if (ft_strlen(line) > 0)
	{
		extract_cmd_client(&line, msg);
		extract_data_client(line, msg);
	}
	free(tmp);
	return (1);
}

int		extract_cmd_client(char **str, t_parsing_client *msg)
{
	char	*end;

	msg->command = NULL;

	if (*str[0] == '/' && ft_isalnum((*str)[1]))
	{
		end = ft_strchr(*str, ' ');
		if (end)
			*end = 0;
		msg->command = ft_strdup(*str);
		if (end)
			*str = end + 1;
		else
			*str[0] = 0;
		return (1);
	}
	return (0);
}

int		extract_data_client(char *str, t_parsing_client *msg)
{
	msg->data = NULL;
	if (ft_strlen(str) > 0)
	{
		msg->data = ft_strdup(str);
		return (1);
	}
	return (0);
}
