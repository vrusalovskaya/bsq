/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuiko <vbuiko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:34:33 by vbuiko            #+#    #+#             */
/*   Updated: 2026/03/24 18:34:53 by vbuiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char	*buffer_append(char *content, int total, char *buf, int bytes)
{
	char	*result;
	int		i;

	result = malloc(total + bytes + 1);
	if (!result)
	{
		free(content);
		return (NULL);
	}
	i = 0;
	while (i < total)
	{
		result[i] = content[i];
		i++;
	}
	i = 0;
	while (i < bytes)
	{
		result[total + i] = buf[i];
		i++;
	}
	result[total + bytes] = '\0';
	free(content);
	return (result);
}

char	*read_file(char *path)
{
	int		fd;
	char	buf[4096];
	char	*content;
	int		total;
	int		bytes;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (NULL);
	content = NULL;
	total = 0;
	bytes = read(fd, buf, 4096);
	while (bytes > 0)
	{
		content = buffer_append(content, total, buf, bytes);
		if (!content)
			break ;
		total += bytes;
		bytes = read(fd, buf, 4096);
	}
	close(fd);
	if (bytes >= 0 && content)
		return (content);
	free(content);
	return (NULL);
}

int	is_printable(char c)
{
    return (c >= 32 && c <= 126);
}

int	parse_number_from_header(char *str, int end)
{
	int	result;
	int		i;

	result = 0;
	i = 0;
	while (i < end)
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return result;
}

int	validate_characters(char a, char b, char c)
{
	if (!is_printable(a) || !is_printable(b) || !is_printable(c))
      return (0);
	if (a == b || a == c || b == c)
		return (0);
	return (1);
}

int	parse_header(t_map_structure *map_structure, int *j)
{
   int	i;
	int	number;
	char *str;

	str = map_structure->file_content;
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (i < 4)
		return (0);
	number = parse_number_from_header(str, i-3);
	if (number <= 0)
	 return (0);
	map_structure->rows = number;
   if (!validate_characters(str[i-3], str[i-2], str[i-1]))
		return (0);
	map_structure->empty = str[i-3];
   	map_structure->obstacle = str[i-2];
   	map_structure->full = str[i-1];
   if (str[i] != '\n')
        return (0);
   *j = i + 1;
   return (1);
}

int	check_line(int start, t_map_structure *map_structure, int *len)
{
    int	i;
    int	count;
	 char *str;

	 i = start;
	 count = 0;
	 str = map_structure->file_content;
    while (str[i] && str[i] != '\n')
    {
        if (str[i] != map_structure->empty && str[i] != map_structure->obstacle)
            return (-1);
        count++;
        i++;
    }
    if (str[i] != '\n')
        return (-1);
    if (*len == -1)
        *len = count;
    else if (*len != count)
        return (-1);
    return (i + 1); 
}

void	split_lines(char *str, char **arr)
{
	int	i;
	int	start;
	int	j;

	i = 0;
	while (str[i] != '\n')
		i++;
	i++;
	start = i;
	j = 0;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			str[i] = '\0';
			arr[j++] = str + start;
			start = i + 1;
		}
		i++;
	}
	arr[j++] = str + start;
}

int	parse_map(char *path, t_map_structure *map_structure)
{
	int	i;
	int	line_len;
	int	lines;
	int	next;

	i = 0;
	line_len = -1;
	lines = 0;
	map_structure->file_content = read_file(path);
	if (!map_structure->file_content)
		return (0);
	if(!parse_header(map_structure, &i))
		return(0);
	if (map_structure->file_content[i] == '\0')
		return (0);
	while (map_structure->file_content[i])
    {
        next = check_line(i, map_structure, &line_len);
        if (next == -1)
            return (0);
        i = next;
        lines++;
    }
    if (lines != map_structure->rows)
        return (0);
    if (line_len <= 0)
        return (0);
    map_structure->columns = line_len;
	 map_structure->lines = malloc(sizeof(char*) * (lines));
	 if (!map_structure->lines)
	 	return (0);
	 split_lines(map_structure->file_content, map_structure->lines);
    return (1);
}