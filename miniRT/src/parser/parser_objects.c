/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:10:15 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/08 12:10:19 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Parse a sphere from the scene file
 * Format: sp x,y,z r R,G,B
 * Returns 0 on success, -1 on error
 */
int	parse_sphere(char **elements, t_scene *scene)
{
	t_object	*sphere;
	t_vec3		center;
	double		radius;
	t_color		color;
	int			count;

	count = count_elements(elements);
	if (count != 4)
		return (print_error("Invalid sphere format\n"), -1);
	
	// Parse sphere parameters
	center = parse_vector(elements[1]);
	radius = parse_double(elements[2]) / 2.0;
	color = parse_color(elements[3]);
	
	if (!validate_color_values(color))
		return (print_error("Invalid sphere color\n"), -1);
	
	// Create sphere object
	sphere = object_create_sphere(center, radius, color);
	if (!sphere)
		return (print_error(ERR_MEMORY), -1);
	
	// Add sphere to scene
	if (scene_add_object(scene, sphere) < 0)
	{
		object_free(sphere);
		return (print_error(ERR_MEMORY), -1);
	}
	
	return (0);
}

/**
 * Parse a plane from the scene file
 * Format: pl x,y,z nx,ny,nz R,G,B
 * Returns 0 on success, -1 on error
 */
int	parse_plane(char **elements, t_scene *scene)
{
	t_object	*plane;
	t_vec3		point;
	t_vec3		normal;
	t_color		color;
	int			count;

	count = count_elements(elements);
	if (count != 4)
		return (print_error("Invalid plane format\n"), -1);
	
	// Parse plane parameters
	point = parse_vector(elements[1]);
	normal = parse_vector(elements[2]);
	color = parse_color(elements[3]);
	
	if (!validate_vector_normalized(normal) || !validate_color_values(color))
		return (print_error("Invalid plane parameters\n"), -1);
	
	// Normalize the normal vector
	normal = vec3_normalize(normal);
	
	// Create plane object
	plane = object_create_plane(point, normal, color);
	if (!plane)
		return (print_error(ERR_MEMORY), -1);
	
	// Add plane to scene
	if (scene_add_object(scene, plane) < 0)
	{
		object_free(plane);
		return (print_error(ERR_MEMORY), -1);
	}
	
	return (0);
}

/**
 * Parse a cylinder from the scene file
 * Format: cy x,y,z nx,ny,nz d h R,G,B
 * Returns 0 on success, -1 on error
 */
int	parse_cylinder(char **elements, t_scene *scene)
{
	t_object	*cylinder;
	t_vec3		center;
	t_vec3		axis;
	double		diameter;
	double		height;
	t_color		color;
	int			count;

	count = count_elements(elements);
	if (count != 6)
		return (print_error("Invalid cylinder format\n"), -1);
	
	// Parse cylinder parameters
	center = parse_vector(elements[1]);
	axis = parse_vector(elements[2]);
	diameter = parse_double(elements[3]);
	height = parse_double(elements[4]);
	color = parse_color(elements[5]);
	
	if (!validate_vector_normalized(axis) || diameter <= 0 || height <= 0 || 
		!validate_color_values(color))
		return (print_error("Invalid cylinder parameters\n"), -1);
	
	// Normalize the axis vector
	axis = vec3_normalize(axis);
	
	// Create cylinder object
	cylinder = object_create_cylinder(center, axis, diameter / 2.0, height, color);
	if (!cylinder)
		return (print_error(ERR_MEMORY), -1);
	
	// Add cylinder to scene
	if (scene_add_object(scene, cylinder) < 0)
	{
		object_free(cylinder);
		return (print_error(ERR_MEMORY), -1);
	}
	
	return (0);
}
