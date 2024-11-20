/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahlahfid <ahlahfid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 11:21:10 by ahlahfid          #+#    #+#             */
/*   Updated: 2024/11/20 17:14:58 by ahlahfid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	char *temp;

	if (!(fd >= 0 && BUFFER_SIZE >= 0))
		return (NULL);
	
	buffer = ft_read(fd, buffer);
	if(!buffer)
		return (NULL);
	
	line = ft_getline(buffer);
	temp = ft_save(buffer);
	free(buffer); ///////
	buffer = temp; ///////
	return (line);
}