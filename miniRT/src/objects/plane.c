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


// Verifica se um ponto está no plano (dentro de uma tolerância)
bool plane_contains_point(t_plane *plane, t_vec3 point)
{
    // Distância do ponto ao plano
    double distance = fabs(vec3_dot(vec3_subtract(point, plane->point), plane->normal));
    
    // Tolerância pequena para imprecisões de ponto flutuante
    return (distance < 1e-6);
}

// Calcula a normal do plano (que é constante)
t_vec3 plane_normal_at(t_plane *plane, t_vec3 point)
{
    // A normal de um plano é sempre a mesma, independente do ponto
    return (plane->normal);
}

// Verificação de interseção do raio com o plano
bool plane_intersect(t_plane *plane, t_vec3 ray_origin, t_vec3 ray_direction, double *t)
{
    // Cálculo de interseção de raio com plano
    double denom = vec3_dot(ray_direction, plane->normal);
    
    // Se o raio for paralelo ao plano
    if (fabs(denom) < 1e-6)
        return (false);
    
    *t = vec3_dot(vec3_subtract(plane->point, ray_origin), plane->normal) / denom;
    
    // Retorna verdadeiro se a interseção está à frente da origem do raio
    return (*t >= 0);
}