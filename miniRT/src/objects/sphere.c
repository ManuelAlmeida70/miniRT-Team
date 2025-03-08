/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maalmeid <maalmeid@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 09:49:32 by nkiampav          #+#    #+#             */
/*   Updated: 2025/03/07 07:58:07 by maalmeid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// Verifica se um ponto está dentro da esfera
bool sphere_contains_point(t_sphere *sphere, t_vec3 point)
{
    // Distância do ponto ao centro da esfera
    double distance = vec3_length(vec3_subtract(point, sphere->center));
    
    // Verifica se a distância é menor ou igual ao raio
    return (distance <= sphere->diameter / 2.0);
}

// Calcula a normal da esfera em um ponto
t_vec3 sphere_normal_at(t_sphere *sphere, t_vec3 point)
{
    // Normal é o vetor do centro da esfera ao ponto, normalizado
    return (vec3_normalize(vec3_subtract(point, sphere->center)));
}

// Verificação de interseção do raio com a esfera
bool sphere_intersect(t_sphere *sphere, t_vec3 ray_origin, t_vec3 ray_direction, double *t)
{
    // Vetor do centro da esfera à origem do raio
    t_vec3 oc = vec3_subtract(ray_origin, sphere->center);
    
    // Cálculos para a equação quadrática de interseção
    double a = vec3_dot(ray_direction, ray_direction);
    double b = 2.0 * vec3_dot(oc, ray_direction);
    double c = vec3_dot(oc, oc) - pow(sphere->diameter / 2.0, 2);
    
    // Discriminante
    double discriminant = b * b - 4 * a * c;
    
    // Sem interseção
    if (discriminant < 0)
        return (false);
    
    // Calcula as duas possíveis soluções
    double sqrt_disc = sqrt(discriminant);
    double t0 = (-b - sqrt_disc) / (2.0 * a);
    double t1 = (-b + sqrt_disc) / (2.0 * a);
    
    // Garante que t0 seja o primeiro ponto de interseção
    if (t0 > t1)
    {
        double temp = t0;
        t0 = t1;
        t1 = temp;
    }
    
    // Retorna o primeiro ponto de interseção válido
    if (t0 >= 0)
    {
        *t = t0;
        return (true);
    }
    
    if (t1 >= 0)
    {
        *t = t1;
        return (true);
    }
    
    return (false);
}