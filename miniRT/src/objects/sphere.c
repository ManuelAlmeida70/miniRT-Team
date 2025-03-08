/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalmeid <maalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:32 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/08 14:27:54 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Creates a new sphere object
 * @param center Center point of the sphere
 * @param diameter Diameter of the sphere
 * @param color Color of the sphere
 * @return Pointer to the newly created sphere
 */
t_sphere	*sphere_create(t_vec3 center, double diameter, t_color color)
{
	t_sphere	*sphere;

	sphere = (t_sphere *)malloc(sizeof(t_sphere));
	if (!sphere)
		return (NULL);
	sphere->center = center;
	sphere->diameter = diameter;
	sphere->color = color;
	return (sphere);
}

/**
 * Gets the normal vector at a point on a sphere
 * @param sphere Pointer to the sphere
 * @param point Point on the sphere
 * @return Normal vector at the point
 */
t_vec3	sphere_get_normal(t_sphere *sphere, t_vec3 point)
{
	t_vec3	normal;

	// Calculate normal vector (direction from center to point)
	normal = vec3_sub(point, sphere->center);
	return (vec3_normalize(normal));
}

/**
 * Translates a sphere by a given vector
 * @param sphere Pointer to the sphere
 * @param translation Translation vector
 */
void	sphere_translate(t_sphere *sphere, t_vec3 translation)
{
	sphere->center = vec3_add(sphere->center, translation);
}

/**
 * Rotating a sphere doesn't change its appearance
 * @param sphere Pointer to the sphere
 * @param rotation Rotation vector (unused)
 */
void	sphere_rotate(t_sphere *sphere, t_vec3 rotation)
{
	// Spheres look the same when rotated, so do nothing
	(void)sphere;
	(void)rotation;
}
