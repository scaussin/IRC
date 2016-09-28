/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/18 00:10:04 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/28 12:28:49 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bircd.h"

void	init_ptr_func(t_ptr_func *ptr_func)
{
	ptr_func[0].name = "USER";
	ptr_func[0].func = cmd_user;
	ptr_func[1].name = "NICK";
	ptr_func[1].func = cmd_nick;
	ptr_func[2].name = "PING";
	ptr_func[2].func = cmd_ping;
	ptr_func[3].name = "PRIVMSG";
	ptr_func[3].func = cmd_privmsg;
	ptr_func[4].name = "AWAY";
	ptr_func[4].func = cmd_away;
	ptr_func[5].name = "JOIN";
	ptr_func[5].func = cmd_join;
	ptr_func[6].name = "NAMES";
	ptr_func[6].func = cmd_names;
	ptr_func[7].name = "WHO";
	ptr_func[7].func = cmd_who;
	ptr_func[8].name = "USERS";
	ptr_func[8].func = cmd_users;
	init_ptr_func_2(ptr_func);
}

void	init_ptr_func_2(t_ptr_func *ptr_func)
{
	ptr_func[9].name = "PART";
	ptr_func[9].func = cmd_part;
	ptr_func[10].name = "QUIT";
	ptr_func[10].func = cmd_quit;
	ptr_func[11].name = "leave";
	ptr_func[11].func = cmd_part;
	ptr_func[12].name = "who";
	ptr_func[12].func = cmd_names;
	ptr_func[13].name = "LIST";
	ptr_func[13].func = cmd_list;
}

char	*gen_prefix(t_fd client)
{
	char	*prefix;

	prefix = (char *)XV(NULL, malloc(MAX_SIZE_MSG_IRC), "malloc");
	ft_strcpy(prefix, client.nick);
	ft_strcat(prefix, "!");
	ft_strcat(prefix, client.name);
	ft_strcat(prefix, "@");
	ft_strcat(prefix, client.host);
	return (prefix);
}

void	free_params(char **params)
{
	int		i;

	i = 0;
	if (params)
	{
		while (params[i])
		{
			free(params[i]);
			i++;
		}
		free(params);
	}
}

char	**malloc_params(int size)
{
	char	**params;
	int		i;

	i = 0;
	params = (char **)XV(NULL, malloc(sizeof(char *) * (size + 1)), "malloc");
	params[size] = NULL;
	while (i < size)
	{
		params[i] = (char *)XV(NULL, malloc(sizeof(char) * MAX_SIZE_MSG_IRC)
			, "malloc");
		ft_bzero(params[i], MAX_SIZE_MSG_IRC);
		i++;
	}
	return (params);
}
