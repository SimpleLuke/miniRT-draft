/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shape.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llai <llai@student.42london.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:15:33 by llai              #+#    #+#             */
/*   Updated: 2024/04/25 18:35:54 by llai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPE_H
# define SHAPE_H

# include "vec3.h"

typedef struct s_sphere
{
	t_vec3	center;
	double	radius;
	int		color;
	double	specular;
	double	reflective;
}	t_sphere;

#endif // !SHAPE_H
