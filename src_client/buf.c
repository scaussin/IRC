/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/22 00:29:47 by scaussin          #+#    #+#             */
/*   Updated: 2016/09/21 10:02:43 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "client_irc.h"

void	write_buf(t_ring_buf *buf, char *to_write, int size)
{
	int		i;

	if (size)
	{
		i = 0;
		if (buf->len + size > BUF_SIZE)
			write_log("error", "buf full");
		else
		{
			while (i < size)
			{
				buf->data[(buf->start + buf->len + i) % BUF_SIZE] = to_write[i];
				i++;
			}
			buf->len += i;
		}
	}
}

void	update_offset_buf(t_ring_buf *buf, int new_offset)
{
	if (new_offset > 0)
	{
		buf->start = (buf->start + new_offset) % BUF_SIZE;
		buf->len -= new_offset;
	}
}

char	*read_buf(t_ring_buf buf)
{
	char	*ret_data;
	int		i;

	ret_data = NULL;
	if (buf.len > 0)
	{
		ret_data = (char *)XV(NULL, malloc(buf.len + 1), "malloc");
		ft_bzero(ret_data, buf.len + 1);
		i = 0;
		while (i < buf.len)
		{
			ret_data[i] = buf.data[(buf.start + i) % BUF_SIZE];
			i++;
		}
	}
	return (ret_data);
}
