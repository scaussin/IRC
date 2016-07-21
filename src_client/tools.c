/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/20 16:50:48 by scaussin          #+#    #+#             */
/*   Updated: 2016/05/26 00:15:36 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "client_irc.h"

int		x_int(int err, int res, char *str, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n",
			str, file, line, strerror(errno));
		write_log("error", "FATAL");
	}
	return (res);
}

void	*x_void(void *err, void *res, char *str, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n",
			str, file, line, strerror(errno));
		write_log("error", "FATAL");
	}
	return (res);
}


void	write_log(char *type_error, char *msg)
{
	ft_printf("[%s] %s\n",type_error, msg);
	if (!ft_strcmp(type_error, "error"))
		exit(-1);
}

int		str_isalnum(char *str)
{
	int		i;

	i = 0;
	while (str && str[i])
	{
		if (!ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	free_parsing_client(t_parsing_client *msg)
{
	if (msg->command)
	{
		free(msg->command);
		msg->command = NULL;
	}
	if (msg->data)
	{
		free(msg->data);
		msg->data = NULL;
	}
}

int		str_equal(char *s1, char *s2)
{
	int		i;

	i = 0;
	if(s1 && s2)
	{
		while (s1[i] == s2[i])
		{
			if (s1[i] == 0)
				return (1);
			i++;
		}
		return (0);
	}
	else
	{
		if (s1 == s2)
			return (1);
	}
	return (0);
}
