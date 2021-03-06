/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 15:02:50 by user42            #+#    #+#             */
/*   Updated: 2020/08/03 15:42:15 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_init_info(t_param *param, int *check_double)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		check_double[i] = 0;
		i++;
	}
	param->infomap.string = ft_strnew(0);
	param->infomap.nb_line_map = 0;
	param->infomap.tabmap = NULL;
	param->infomap.position_map = 0;
	param->infomap.other = 0;
}

void	ft_check_all_parameter(t_param *param)
{
	int j;

	j = 0;
	while (j < 8)
	{
		if (param->check_double[j] != 1)
			ft_free_all(param, 4);
		j++;
	}
}

void	ft_get_info(int fd, t_param *param)
{
	int		ret;
	char	*line;
	int		error;

	ret = 0;
	line = NULL;
	error = 0;
	ft_init_info(param, param->check_double);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		error = ft_parse_line(line, param, error);
		free(line);
		line = NULL;
		if (error != 0)
			ft_free_all(param, error);
	}
	error = ft_parse_line(line, param, error);
	free(line);
	line = NULL;
	if (error != 0)
		ft_free_all(param, error);
	ft_check_all_parameter(param);
	ft_check_correct_map(param);
	ft_create_tab_map(param);
	free(param->infomap.string);
}
