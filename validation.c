#include "validation.h"
#include <fcntl.h>
#include <stdio.h>

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

int	parse_header(char *str, t_map *map, int *j)
{
   int	i;
	int	number;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (i < 4)
		return (0);
	number = parse_number_from_header(*str, i-3);
	if (number <= 0)
	 return (0);
	map->rows = number;
	validate_characters(str[i-3], str[i-2], str[i-1]);
   if (!validate_characters)
		return (0);
	map->empty = str[i-3];
   map->obstacle = str[i-2];
   map->full = str[i-1];
   if (str[i] != '\n')
        return (0);
   j = i + 1;
   return (1);
}

int	check_line(char *str, int start, t_map *map, int *len)
{
    int	i;
    int	count;

	 i = start;
	 count = 0;
    while (str[i] && str[i] != '\n')
    {
        if (str[i] != map->empty && str[i] != map->obstacle)
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

int	parse_map(char *path)
{
	char	*content;
	t_map	map;
	int	i;
	int	line_len;
   int	lines;
   int	next;

	i = 0;
	line_len = -1;
	lines = 0;
	content = read_file(path);
	if (!content)
		return (0);
	if(!parse_header(content, &map, &i))
		return(0);
	if (content[i] == '\0')
		return (0);
	while (content[i])
    {
        next = check_line(content, i, &map, &line_len);
        if (next == -1)
            return (0);
        i = next;
        lines++;
    }
    if (lines != map.rows)
        return (0);
    if (line_len <= 0)
        return (0);
    map.columns = line_len;
    return (1);
}