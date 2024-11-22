/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:21:10 by ahlahfid          #+#    #+#             */
/*   Updated: 2024/11/22 16:43:14 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

// char *ft_free(char *str, char *buffer)
// {
// 	if (buffer)
// 		free(buffer);
// 	return(str);
// }
char	*ft_save(char *buffer)
{
	size_t	i;
	char	*left;

	if (!buffer)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i]) // No newline in buffer
		return (NULL);
	left = ft_strdup(buffer + i + 1);
	if (!left)
		return (NULL);
	return (left);
}

char	*ft_getline(char *buffer)
{
	size_t	i;
	char	*line;
	size_t	len;

	if (!buffer || !buffer[0]) // Handle NULL or empty buffer
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	len = i;
	if (buffer[i] == '\n')
		len += 1; // Include the newline character
	line = ft_substr(buffer, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_read(int fd, char *buffer)
{
	char	*buf;
	char	*to_free;
	int		count;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
	{
		//return(ft_free(NULL, buffer));
		 free(buffer);
		 return (NULL);
	}
	count = read(fd, buf, BUFFER_SIZE);
	while (count > 0)
	{
		buf[count] = '\0';
		to_free = buffer;
		buffer = ft_strjoin(buffer, buf);
		free(to_free);
		if (!buffer) // Handle malloc failure in ft_strjoin
		{
			//return(ft_free(NULL, buffer));
			free(buf);
			return (NULL);
		}
		if (ft_isnewline(buffer))
			break;
		count = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (count < 0) // Handle read failure
	{
		//return(ft_free(NULL, buffer));
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 0x7FFFFFFF)
		return (NULL);
	if (!buffer)
		buffer = ft_strdup(""); // Initialize static buffer
	if (!buffer)
		return (NULL);
	buffer = ft_read(fd, buffer);
	if (!buffer) // Handle read failure
		return (NULL);
	line = ft_getline(buffer);
	if (!line) // Handle malloc failure in ft_getline
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	temp = ft_save(buffer);
	free(buffer);
	buffer = temp; // Update static buffer with remaining data
	return (line);
}
