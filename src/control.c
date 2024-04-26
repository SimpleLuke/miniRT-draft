/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:53:23 by llai              #+#    #+#             */
/*   Updated: 2024/04/26 15:42:49 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"


int	key_down(int keycode, t_data *data)
{
	// printf("key: %d\n", keycode);
	// if (keycode == ESC_KEY)
	// {
	// 	destroy_window(data);
	// 	exit(EXIT_SUCCESS);
	// }
	if (keycode == W_KEY)
	{
		data->camera.position.y += 0.1;
		render(data);
	}
	else if (keycode == S_KEY)
	{
		data->camera.position.y -= 0.1;
		render(data);
	}
	else if (keycode == D_KEY)
	{
		data->camera.position.x += 0.1;
		render(data);
	}
	else if (keycode == A_KEY)
	{
		data->camera.position.x -= 0.1;
		render(data);
	}
	return (0);
}
