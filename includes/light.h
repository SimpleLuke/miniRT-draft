/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 00:14:56 by llai              #+#    #+#             */
/*   Updated: 2024/04/23 00:45:17 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

#include "vec3.h"

typedef enum e_light_type {
	AMBIENT,
	POINT,
	DIRECTIONAL
}	t_light_type;

typedef struct s_light
{
	t_light_type	type;
	double			intensity;
	t_vec3			position;
	t_vec3			direction;
}	t_light;

#endif // !LIGHT_H
