
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkiampav <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 12:30:15 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/08 12:30:19 by nkiampav         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

/**
 * Parse a vector from a string (format: x,y,z)
 */
t_vec3	parse_vector(char *str)
{
	t_vec3	vector;
	char	**parts;
	int		i;

	parts = ft_split(str, ',');
	if (!parts)
		return (vec3_create(0, 0, 0));
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		free_split(parts);
		return (vec3_create(0, 0, 0));
	}
	vector = vec3_create(
		ft_atof(parts[0]),
		ft_atof(parts[1]),
		ft_atof(parts[2])
	);
	free_split(parts);
	return (vector);
}

/**
 * Parse a color from a string (format: R,G,B)
 */
t_color	parse_color(char *str)
{
	t_color	color;
	char	**parts;
	int		i;

	parts = ft_split(str, ',');
	if (!parts)
		return (color_create(0, 0, 0));
	i = 0;
	while (parts[i])
		i++;
	if (i != 3)
	{
		free_split(parts);
		return (color_create(0, 0, 0));
	}
	color = color_create(
		ft_atoi(parts[0]),
		ft_atoi(parts[1]),
		ft_atoi(parts[2])
	);
	free_split(parts);
	return (color);
}

/**
 * Parse a double from a string
 */
double	parse_double(char *str)
{
	return (ft_atof(str));
}

/**
 * Validate that a vector is normalized (or close to being normalized)
 */
int	validate_vector_normalized(t_vec3 vector)
{
	double	length;

	// Check if vector is close to zero
	if (fabs(vector.x) < EPSILON && 
		fabs(vector.y) < EPSILON && 
		fabs(vector.z) < EPSILON)
		return (0);
	
	// Check if length is close to 1
	length = vec3_length(vector);
	if (fabs(length - 1.0) > 0.1) // Allow for some imprecision
		return (0);
	
	return (1);
}

/**
 * Validate a color's components are within the valid range (0-255)
 */
int	validate_color_values(t_color color)
{
	if (color.r < 0 || color.r > 255 ||
		color.g < 0 || color.g > 255 ||
		color.b < 0 || color.b > 255)
		return (0);
	return (1);
}

/**
 * Convert from string to double (supports decimal points)
 * This function should be in libft, but in case it's not
 */
double	ft_atof(const char *str)
{
	double	result;
	double	decimal;
	int		sign;
	int		i;

	result = 0.0;
	decimal = 0.0;
	sign = 1;
	i = 0;
	// Skip whitespace
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	// Handle sign
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	// Parse integer part
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10.0 + (str[i] - '0');
		i++;
	}
	// Parse decimal part
	if (str[i] == '.')
	{
		double divisor = 10.0;
		i++;
		while (str[i] && str[i] >= '0' && str[i] <= '9')
		{
			decimal += (str[i] - '0') / divisor;
			divisor *= 10.0;
			i++;
		}
	}
	return (sign * (result + decimal));
}
