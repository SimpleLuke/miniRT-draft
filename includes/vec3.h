/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 15:08:12 by llai              #+#    #+#             */
/*   Updated: 2024/04/22 13:05:12 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

#include "minirt.h"

typedef struct s_data t_data;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

t_vec3	set_vec3(double x, double y, double z);
t_vec3	set_viewport(double x, double y, t_data *data);
t_vec3	minus_vec3(t_vec3 lhs, t_vec3 rhs);
double	dot(t_vec3 v1, t_vec3 v2);

#endif // !VEC3_H
