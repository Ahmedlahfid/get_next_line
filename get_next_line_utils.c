/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:21:08 by ahlahfid          #+#    #+#             */
/*   Updated: 2024/11/20 17:15:07 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read(int fd, char *buffer)
{
	char	*buf;
	char	*to_free;
	int		count;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	count = read(fd, buf, BUFFER_SIZE);
	while (count > 0)
	{
		buf[count] = '\0';
		to_free = buffer;
   		buffer = ft_strjoin(buffer, buf);
		free(to_free);
   		if (ft_isnewline(buffer))
			break;
		count = read(fd, buf, BUFFER_SIZE);
	}
	free(buf);
	if (count < 0)
	{
		free(buffer);
		return (NULL);
	}
	return (buffer);
}

int ft_isnewline(char *s)
{
    if (!s)
        return (0);
    while (*s)
    {
        if (*s == '\n')
            return (1);
        s++;
    }
    return (0);
}


char	*ft_getline(char *buffer)
{
	size_t	i;
	char	*line;
	size_t	len;

	if (!buffer || !buffer[0])
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')  // Search for newline or end of string
		i++;
	len = i;
	if (buffer[i] == '\n')
		len += 1;  // Include '\n' in the substring
	line = ft_substr(buffer, 0, len);
	if (!line)
		return (NULL);
	return (line);
}

char	*ft_save(char *buffer)
{
	size_t	i;
	char	*left;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])  // No newline found, return NULL
	{
		return (NULL); ////////
	}
	left = ft_strdup(buffer + i + 1);
	return (left);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	i;
	size_t	j;
	char	*arr;
	char	*result;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_strdup(s2));
	if (!s2)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	arr = malloc((i + j + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	result = arr;
	while (*s1)
		*arr++ = *s1++;
	while (*s2)
		*arr++ = *s2++;
	*arr = '\0';
	return (result);
}

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *) malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!str)
		return (NULL);
	while (s[i])
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	i;
	char	*arr;
	char	*str;

	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		return (ft_strdup(""));
	if (len > str_len - start)
		len = str_len - start;
	arr = malloc(len + 1);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		arr[i] = s[start + i];
		i++;
	}
	arr[i] = '\0';
	
	return (arr);
}

size_t ft_strlen(const char *s)
{
    size_t len = 0;

    while (s && s[len])
        len++;
    return len;
}

