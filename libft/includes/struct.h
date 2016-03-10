/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scaussin <scaussin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/22 13:44:42 by scaussin          #+#    #+#             */
/*   Updated: 2015/02/19 15:27:40 by scaussin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <string.h>
# include <stdarg.h>

typedef struct		s_list
{
	void			*content;
	size_t			content_size;
	struct s_list	*next;
}					t_list;

typedef int(*t_tab)(va_list);

typedef struct		s_fct
{
	char			c;
	t_tab			fnct;
}					t_fct;

/*
** get_next_line
*/
typedef struct		s_gnl
{
	char			buf[BUFF_SIZE];
	int				i;
	int				r;
	int				s;
}					t_gnl;

typedef struct		s_norme
{
	int				f;
	char			*n;
	int				l;
	int				t;
}					t_norme;

#endif
