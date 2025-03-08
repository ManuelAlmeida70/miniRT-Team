/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalmeid <maalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:46 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/07 08:00:07 by maalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Creates a new plane object
 * @param point Point on the plane
 * @param normal Normal vector of the plane
 * @param color Color of the plane
 * @return Pointer to the newly created plane
 */
t_plane	*plane_create(t_vec3 point, t_vec3 normal, t_color color)
{
	t_plane	*plane;

	plane = (t_plane *)malloc(sizeof(t_plane));
	if (!plane)
		return (NULL);
	plane->point = point;
	plane->normal = vec3_normalize(normal);	// Ensure normal is normalized
	plane->color = color;
	return (plane);
}


/**
 * Gets the normal vector at a point on a plane
 * @param plane Pointer to the plane
 * @param point Point on the plane (unused)
 * @return Normal vector of the plane
 */
t_vec3	plane_get_normal(t_plane *plane, t_vec3 point)
{
	(void)point;	// Plane normal is same at all points
	return (plane->normal);
}

/**
 * Translates a plane by a given vector
 * @param plane Pointer to the plane
 * @param translation Translation vector
 */
void	plane_translate(t_plane *plane, t_vec3 translation)
{
	plane->point = vec3_add(plane->point, translation);
}

/**
 * Rotates a plane by a given rotation vector
 * @param plane Pointer to the plane
 * @param rotation Rotation vector (in radians)
 */
void	plane_rotate(t_plane *plane, t_vec3 rotation)
{
	// Rotate normal vector
	plane->normal = vec3_rotate_x(plane->normal, rotation.x);
	plane->normal = vec3_rotate_y(plane->normal, rotation.y);
	plane->normal = vec3_rotate_z(plane->normal, rotation.z);
	plane->normal = vec3_normalize(plane->normal);
}
