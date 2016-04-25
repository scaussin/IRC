
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bircd.h"

int		x_int(int err, int res, char *str, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n", 
			str, file, line, strerror(errno));
		write_log(ERROR_FATAL);
	}
	return (res);
}

void	*x_void(void *err, void *res, char *str, char *file, int line)
{
	if (res == err)
	{
		fprintf(stderr, "%s error (%s, %d): %s\n", 
			str, file, line, strerror(errno));
		write_log(ERROR_FATAL);
	}
	return (res);
}

void	write_log(e_error_code error)
{
	if (error < 100)
		ft_printf("[SUCCES] code: %d\n", error);
	else if (error < 200)
	{
		ft_printf("[ERROR] code: %d\n", error);
		exit (-1);
	}
	else if (error < 300)
		ft_printf("[WARNING] code: %d\n", error);
	else if (error < 400)
		ft_printf("[INFO] code: %d\n", error);
}

void	print_buf(t_ring_buf buf)
{
	char	*data_buf;

	data_buf = read_buf(buf);
	ft_printf("###########\n\
start: %d\n\
len:   %d\n\
data:  |%s|\n\n", buf.start, buf.len, data_buf);
	free (data_buf);
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
