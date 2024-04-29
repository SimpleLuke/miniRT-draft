/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 14:53:23 by llai              #+#    #+#             */
/*   Updated: 2024/04/26 16:27:32 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"
#include <stdio.h>


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
	else if (keycode == X_KEY)
	{
		data->camera.position.z += 0.1;
		render(data);
	}
	else if (keycode == Z_KEY)
	{
		data->camera.position.z -= 0.1;
		render(data);
	}
	return (0);
}

int	mouse_hook(int mousecode, t_data *data)
{
	// int	a = 5;
	(void)data;
	// printf("mouse: %d\n", mousecode);
	// printf("%f\n", data->camera.position.z);
	if (mousecode == MOUSE_UP)
	{
		// printf("UP\n");
		// data->camera.position.z += 0.1;
		// printf("%f\n", data->camera.position.z);
		// data->camera.position.z = 10;
		// render(data);
	}
	else if (mousecode == MOUSE_DOWN)
	{
		// printf("DOWN\n");
		// data->camera.position.z -= 0.1;
		// render(data);
	}
	return (0);
}
