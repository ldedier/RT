/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tracer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcavalle <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/17 00:31:37 by lcavalle          #+#    #+#             */
/*   Updated: 2018/05/21 22:09:01 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_hit				*retfree(int r, t_hit **hit)
{
	if (r != 1)
	{
		free(*hit);
		*hit = NULL;
	}
	return (*hit);
}

t_line				ft_transform_line(t_object object, t_line t)
{
	t_line line;

	line.o = ft_point3d_mat4_mult(t.o, object.transform_pos_inv);
	line.v = normalize(ft_point3d_mat4_mult(t.v, object.transform_dir_inv));
	return line;
}

struct perlin
{
	int p[512];
};

static int permutation[] = { 151,160,137,91,90,15,
	131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
	190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
	88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
	77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
	102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
	135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
	5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
	223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
	129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
	251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
	49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
	138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180
};

static double fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}
static double lerp(double t, double a, double b) {
	return a + t * (b - a);
}
static double grad(int hash, double x, double y, double z) {
	int h = hash & 15;                      // CONVERT LO 4 BITS OF HASH CODE
	double u = h<8||h==12||h==13 ? x : y,   // INTO 12 GRADIENT DIRECTIONS.
		   v = h<4||h==12||h==13 ? y : z;
	return ((h&1) == 0 ? u : -u) + ((h&2) == 0 ? v : -v);
}

double noise(double x, double y, double z) {

	struct perlin	myPerlin;
	for (int i=0; i < 256 ; i++) {
		myPerlin.p[256+i] = myPerlin.p[i] = permutation[i];
	}
	int X = (int)floor(x) & 255,                  // FIND UNIT CUBE THAT
		Y = (int)floor(y) & 255,                  // CONTAINS POINT.
		Z = (int)floor(z) & 255;
	x -= floor(x);                                // FIND RELATIVE X,Y,Z
	y -= floor(y);                                // OF POINT IN CUBE.
	z -= floor(z);
	double u = fade(x),                                // COMPUTE FADE CURVES
		   v = fade(y),                                // FOR EACH OF X,Y,Z.
		   w = fade(z);
	int A = myPerlin.p[X  ]+Y, AA = myPerlin.p[A]+Z, AB = myPerlin.p[A+1]+Z,      // HASH COORDINATES OF
		B = myPerlin.p[X+1]+Y, BA = myPerlin.p[B]+Z, BB = myPerlin.p[B+1]+Z;      // THE 8 CUBE CORNERS,

	return lerp(w, lerp(v, lerp(u, grad(myPerlin.p[AA  ], x  , y  , z   ),  // AND ADD
					grad(myPerlin.p[BA  ], x-1, y  , z   )), // BLENDED
				lerp(u, grad(myPerlin.p[AB  ], x  , y-1, z   ),  // RESULTS
					grad(myPerlin.p[BB  ], x-1, y-1, z   ))),// FROM  8
			lerp(v, lerp(u, grad(myPerlin.p[AA+1], x  , y  , z-1 ),  // CORNERS
					grad(myPerlin.p[BA+1], x-1, y  , z-1 )), // OF CUBE
				lerp(u, grad(myPerlin.p[AB+1], x  , y-1, z-1 ),
					grad(myPerlin.p[BB+1], x-1, y-1, z-1 ))));
}

void				ft_transform_hit_back(t_hit *hit)
{
	t_hit tmp;

	tmp = *hit;
	hit->old_point = hit->point;
	hit->old_normal = hit->normal;
	hit->point = ft_point3d_mat4_mult(tmp.point, tmp.obj.transform_pos);
	hit->normal = normalize(ft_point3d_mat4_mult(tmp.normal, tmp.obj.transform_dir));

	/*
	float noiseCoefx = (float)(noise(0.1 * (double)(hit->point.x), 0.1 * (double)(hit->point.y), 0.1 * (double)(hit->point.z)));
	float noiseCoefy = (float)(noise(0.1 * (double)(hit->point.y), 0.1 * (double)(hit->point.z), 0.1 * (double)(hit->point.x)));
	float noiseCoefz = (float)(noise(0.1 * (double)(hit->point.z), 0.1 * (double)(hit->point.x), 0.1 * (double)(hit->point.y)));
	hit->normal.x = (1.0f - 0.8 ) * hit->normal.x + 0.8 * noiseCoefx;
	hit->normal.y = (1.0f - 0.8 ) * hit->normal.y + 0.8 * noiseCoefy;
	hit->normal.z = (1.0f - 0.8 ) * hit->normal.z + 0.8 * noiseCoefz;
	hit->normal = normalize(hit->normal);
	*/
}

t_hit				*trace(t_line line, t_cobjlist *cobjlist)
{
	t_hit		newhit;
	t_hit		*hit;
	t_cobject	cobj;
	t_object	obj;
	t_line		tmp;

	tmp = line;
	hit = ft_memalloc(sizeof(t_hit));
	hit->t = -1;
	while (cobjlist)
	{
		cobj = *(cobjlist->cobject);
		while(cobj.objlist)
		{
			obj = *(cobj.objlist->object);
			line = ft_transform_line(obj, tmp);
			if ((obj.intersect_func(line, obj, &newhit)) &&
					(newhit.t > 0 && (newhit.t < hit->t || hit->t == -1)))
			{
				newhit.obj = obj;
				ft_transform_hit_back(&newhit);
				*hit = newhit;
			}
			cobj.objlist = cobj.objlist->next;
		}
		cobjlist = cobjlist->next;
	}
	if (dotprod(newvector(tmp.o, hit->point), tmp.v) > 0 && hit->t > 0)
	{
		hit->bounce = reflection(hit->normal, tmp.v);
		return (retfree(1, &hit));
	}
	return (retfree(0, &hit));
}
