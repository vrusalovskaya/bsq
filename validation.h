/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbuiko <vbuiko@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:34:40 by vbuiko            #+#    #+#             */
/*   Updated: 2026/03/24 18:34:52 by vbuiko           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#ifndef VALIDATION_H
# define VALIDATION_H

typedef struct s_map_structure
{
	int rows;
	int  columns;
	char empty;
	char obstacle;
	char full;
	char **lines;
	char *file_content;
}	t_map_structure;

int	parse_map(char *path, t_map_structure *map_structure);

#endif