/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuiko <vbuiko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:34:23 by vbuiko            #+#    #+#             */
/*   Updated: 2026/03/24 18:34:51 by vbuiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void	ft_putstr_err(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int i;
	char *path;
	t_map_structure map_structure;

	i = 1;
	if (argc > 1)
	{
		while (i < argc)
		{	
			path = argv[i++];
			if (!parse_map(path, &map_structure))
				{
					free(map_structure.file_content);
					free(map_structure.lines);
					ft_putstr_err("map error\n");
					return (1);
				}
			free(map_structure.file_content);
			free(map_structure.lines);
		}
	}
	return (0); 
}