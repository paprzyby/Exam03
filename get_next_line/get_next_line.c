/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paprzyby <paprzyby@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:16:40 by paprzyby          #+#    #+#             */
/*   Updated: 2024/09/09 16:20:09 by paprzyby         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	ft_strcpy(char *dest, char *src)
{
	int	i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
}

char	*ft_strjoin(char *str1, char *str2)
{
	char	*new;

	if (!str1 || !str2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
	if (!new)
		return (NULL);
	ft_strcpy(new, str1);
	ft_strcpy(new + ft_strlen(str1), str2);
	free(str1);
	return (new);
}

char	*ft_strchr(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (&str[i]);
		else
			i++;
	}
	return (NULL);
}

char	*ft_strdup(char *src)
{
	char	*dest;

	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!dest)
		return (NULL);
	ft_strcpy(dest, src);
	return (dest);
}

char *get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*line;
	char		*new_line_position;
	int			read_len;

	line = ft_strdup(buffer);
	while (!(new_line_position = ft_strchr(line, '\n')) && (read_len = read(fd, buffer, BUFFER_SIZE)))
	{
		buffer[read_len] = '\0';
		line = ft_strjoin(line, buffer);
	}
	if (ft_strlen(line) == 0)
	{
		free(line);
		return (NULL);
	}
	if (new_line_position)
	{
		ft_strcpy(buffer, new_line_position + 1);
		*(new_line_position + 1) = '\0';
	}
	else
		buffer[0] = '\0';
	return (line);
}

//Main function:

//#include <stdio.h>
//#include <fcntl.h>

//int main(void)
//{
//	int fd;
//	char *line;

//	fd = open("subject.en.txt", O_RDONLY);
//	while ((line = get_next_line(fd)) != NULL)
//	{
//		printf("%s", line);
//		free(line);
//	}
//	close(fd);
//	return (0);
//}