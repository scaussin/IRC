/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_server_1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/28 01:23:05 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/21 10:00:03 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

int		lexer_server(t_protocol *msg, t_ring_buf *buf)
{
	char	*end;
	char	*line;
	int		len;
	char	*tmp;

	ft_bzero(msg, sizeof(t_protocol));
	line = read_buf(*buf);
	tmp = line;
	if (check_error(line, &end, buf) == 0)
		return (0);
	*end = 0;
	len = end - line;
	buf->start = (buf->start + len + 2) % BUF_SIZE;
	buf->len = buf->len - (len + 2);
	if (extract_prefix(&(msg->prefix), &line) == -1
		|| extract_command(&(msg->command), &line) == -1)
	{
		free(tmp);
		return (-1);
	}
	extract_trailer(&(msg->trailer), &line);
	extract_params(&(msg->params), &line);
	free(tmp);
	return (1);
}

int		check_error(char *line, char **end, t_ring_buf *buf)
{
	if (!line)
		return (0);
	if ((*end = ft_strstr(line, END)) == 0)
	{
		write_log("warning", "msg not ending");
		free(line);
		return (0);
	}
	if (*end - line + 2 > MAX_SIZE_MSG_IRC)
	{
		write_log("warning", "msg too long");
		buf->len = 0;
		free(line);
		return (0);
	}
	return (1);
}

int		extract_prefix(char **prefix, char **msg)
{
	char	*end;

	if (!msg || !*msg || **msg != ':')
		return (0);
	if ((end = ft_strstr(*msg, " ")) == 0)
	{
		write_log("warning", "lexer no cmd");
		return (-1);
	}
	*prefix = (char *)Xv(NULL, malloc(end - *msg + 1), "malloc");
	ft_memcpy(*prefix, *msg, end - *msg);
	(*prefix)[end - *msg] = 0;
	*msg = end + 1;
	return (1);
}

int		extract_command(char **command, char **msg)
{
	char	*end;

	while (msg && *msg && **msg && **msg == ' ')
		*msg += 1;
	if (!msg || !*msg || !**msg)
	{
		write_log("warning", "lexer no cmd");
		return (-1);
	}
	if (!(end = ft_strstr(*msg, " ")))
		end = ft_strrchr(*msg, 0);
	(*command) = (char *)Xv(NULL, malloc((end - *msg) + 1), "malloc");
	ft_memcpy(*command, *msg, end - *msg);
	(*command)[end - *msg] = 0;
	if (end[0])
		*msg = end + 1;
	else
		*msg = end;
	return (1);
}
