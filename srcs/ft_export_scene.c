/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_scene.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherriau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 16:31:29 by aherriau          #+#    #+#             */
/*   Updated: 2018/06/10 08:08:45 by aherriau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ft_print_camera(t_world *world, int fd)
{
	dprintf(fd,"\t<camera>\n");
	dprintf(fd,"\t\t<positionXYZ>");
	dprintf(fd,"%f %f %f", world->cam->o.x, world->cam->o.y, world->cam->o.z);
	dprintf(fd,"</positionXYZ>\n");
	dprintf(fd,"\t\t<rotationXYZ>");
	dprintf(fd,"%f %f %f", world->cam->rotation.x, world->cam->rotation.y,
			world->cam->rotation.z);
	dprintf(fd,"</rotationXYZ>\n");
	dprintf(fd,"\t</camera>\n");
}

static void	ft_print_filter(t_world *world, int fd)
{
	if (world->filters[0] == 1)
		dprintf(fd,"\t<filter type=\"gauss blur\"></filter>\n");
	else if (world->filters[1] == 1)
		dprintf(fd,"\t<filter type=\"sharpen\"></filter>\n");
	else if (world->filters[2] == 1)
		dprintf(fd,"\t<filter type=\"sobel\"></filter>\n");
	else if (world->filters[3] == 1)
		dprintf(fd,"\t<filter type=\"emboss\"></filter>\n");
	else if (world->filters[4] == 1)
		dprintf(fd,"\t<filter type=\"grey\"></filter>\n");
}

static void	ft_print_others(t_world *world, int fd)
{
	dprintf(fd,"\t<ambientlight>\n");
	dprintf(fd,"\t\t<intensity>");
	dprintf(fd,"%f", world->ambient.in);
	dprintf(fd,"</intensity>\n");
	dprintf(fd,"\t\t<color>");
	dprintf(fd,"0x%X", world->ambient.color.col);
	dprintf(fd,"</color>\n");
	dprintf(fd,"\t</ambientlight>\n");

	dprintf(fd,"\t<fog>\n");
	dprintf(fd,"\t\t<intensity>");
	dprintf(fd,"%f", world->fog.in);
	dprintf(fd,"</intensity>\n");
	dprintf(fd,"\t\t<color>");
	dprintf(fd,"0x%X", world->fog.color.col);
	dprintf(fd,"</color>\n");
	dprintf(fd,"\t</fog>\n");

	ft_print_filter(world, fd);

	if (world->shader == 1)
		dprintf(fd,"\t<shader type=\"normal\"></shader>\n");
	else if (world->shader == 2)
		dprintf(fd,"\t<shader type=\"cartoon\"></shader>\n");
}

static void	ft_print_light(t_world *world, int fd, char *type, int i)
{
	dprintf(fd,"\t\t<light type=\"%s\">\n", type);
	dprintf(fd,"\t\t\t<positionXYZ>");
	dprintf(fd,"%f %f %f", world->lights[i].o.x, world->lights[i].o.y,
			world->lights[i].o.z);
	dprintf(fd,"</positionXYZ>\n");
	dprintf(fd,"\t\t\t<rotationXYZ>");
	dprintf(fd,"%f %f %f", world->lights[i].v.x, world->lights[i].v.y,
			world->lights[i].v.z);
	dprintf(fd,"</rotationXYZ>\n");
	dprintf(fd,"\t\t\t<color>");
	dprintf(fd,"0x%X", world->lights[i].c.col);
	dprintf(fd,"</color>\n");
	dprintf(fd,"\t\t\t<intensity>");
	dprintf(fd,"%f", world->lights[i].intensity);
	dprintf(fd,"</intensity>\n");
	dprintf(fd,"\t\t\t<angle>");
	dprintf(fd,"%f", world->lights[i].angle);
	dprintf(fd,"</angle>\n");
	dprintf(fd,"\t\t</light>\n");
}

static void	ft_print_lights(t_world *world, int fd)
{
	int		i;
	char	*type;

	if (world->nlights > 0)
	{
		dprintf(fd,"\t<lightlist>\n");
		i = 0;
		while (i < world->nlights)
		{
			if (world->lights[i].type == 'p')
				type = "point";
			else if (world->lights[i].type == 's')
				type = "spotlight";
			else if (world->lights[i].type == 'd')
				type = "directional";
			else
				type = "UNKNOWN";
			ft_print_light(world, fd, type, i);
			i++;
		}
		dprintf(fd,"\t</lightlist>\n");
	}
}

void		ft_print_sphere_caracteristics(t_object obj, int fd)
{
	dprintf(fd,"\t\t\t\t<radius>%f</radius>\n",
			obj.object_union.sphere.radius);
}

void		ft_print_plane_caracteristics(t_object obj, int fd)
{
	dprintf(fd,"\t\t\t\t<texture_stretch_x>%f</texture_stretch_x>\n",
			obj.object_union.plane.texture_stretch_x);
	dprintf(fd,"\t\t\t\t<texture_stretch_y>%f</texture_stretch_y>\n",
			obj.object_union.plane.texture_stretch_y);
	dprintf(fd,"\t\t\t\t<texture_trans_x>%d</texture_trans_x>\n",
			obj.object_union.plane.texture_trans_x);
	dprintf(fd,"\t\t\t\t<texture_trans_y>%d</texture_trans_y>\n",
			obj.object_union.plane.texture_trans_y);
}

void		ft_print_cone_caracteristics(t_object obj, int fd)
{
	dprintf(fd,"\t\t\t\t<angle>%f</angle>\n",
			obj.object_union.cone.angle);
}

void		ft_print_cylinder_caracteristics(t_object obj, int fd)
{
	dprintf(fd,"\t\t\t\t<radius>%f</radius>\n",
			obj.object_union.cylinder.radius);
}

void		ft_print_ellipsoid_caracteristics(t_object obj, int fd)
{
	dprintf(fd,"\t\t\t\t<radius>%f</radius>\n",
			obj.object_union.ellipsoid.radius);
	dprintf(fd,"\t\t\t\t<ellipsoidABC>%f %f %f</ellipsoidABC>\n",
			obj.object_union.ellipsoid.abc.x, obj.object_union.ellipsoid.abc.y,
			obj.object_union.ellipsoid.abc.z);
}

void		ft_print_torus_caracteristics(t_object obj, int fd)
{
	dprintf(fd,"\t\t\t\t<small_radius>%f</small_radius>\n",
			obj.object_union.torus.small_rad);
	dprintf(fd,"\t\t\t\t<big_radius>%f</big_radius>\n",
			obj.object_union.torus.big_rad);
}

void		ft_print_goursat_caracteristics(t_object obj, int fd)
{
	dprintf(fd,"\t\t\t\t<goursatAB>%f %f</goursatAB>\n",
			obj.object_union.goursat.a, obj.object_union.goursat.b);
}

void		ft_print_lemniscate_caracteristics(t_object obj, int fd)
{
	(void)obj;
	(void)fd;
}

void		ft_print_roman_caracteristics(t_object obj, int fd)
{
	(void)obj;
	(void)fd;
}

void		ft_print_piriform_caracteristics(t_object obj, int fd)
{
	(void)obj;
	(void)fd;
}

void		ft_print_hyperboloid_caracteristics(t_object obj, int fd)
{
	dprintf(fd,"\t\t\t\t<radius>%f</radius>\n",
			obj.object_union.hyperboloid.radius);
}

void		ft_print_paraboloid_caracteristics(t_object obj, int fd)
{
	(void)obj;
	(void)fd;
}

void		ft_print_triangle_caracteristics(t_object obj, int fd)
{
	dprintf(fd,"\t\t\t\t<vertexA>%f %f %f</vertexA>\n",
			obj.object_union.triangle.v1.x, obj.object_union.triangle.v1.y,
			obj.object_union.triangle.v1.z);
	dprintf(fd,"\t\t\t\t<vertexB>%f %f %f</vertexB>\n",
			obj.object_union.triangle.v2.x, obj.object_union.triangle.v2.y,
			obj.object_union.triangle.v2.z);
	dprintf(fd,"\t\t\t\t<vertexC>%f %f %f</vertexC>\n",
			obj.object_union.triangle.v3.x, obj.object_union.triangle.v3.y,
			obj.object_union.triangle.v3.z);
}

static void	ft_print_cut(t_cut cut, int fd)
{
	dprintf(fd,"\t\t\t\t\t<cutXYZ>");
	dprintf(fd,"%f %f %f", cut.cut_xyz.x, cut.cut_xyz.y, cut.cut_xyz.z);
	dprintf(fd,"</cutXYZ>\n");

	if (cut.inequality == bigger_than)
		dprintf(fd,"\t\t\t\t\t<inequality>more than</inequality>\n");
	else if (cut.inequality == less_than)
		dprintf(fd,"\t\t\t\t\t<inequality>less than</inequality>\n");
	else if (cut.inequality == less_than_or_equal)
		dprintf(fd,"\t\t\t\t\t<inequality>less than or equal</inequality>\n");
	else if (cut.inequality == bigger_than_or_equal)
		dprintf(fd,"\t\t\t\t\t<inequality>more than or equal</inequality>\n");
	else
		dprintf(fd,"\t\t\t\t\t<inequality>UNKNOWN</inequality>\n");

	dprintf(fd,"\t\t\t\t\t<value>");
	dprintf(fd,"%f", cut.value);
	dprintf(fd,"</value>\n");
}

static void	ft_print_object_cuts(t_object obj, int fd)
{
	t_list	*lst;
	t_cut	*cut;
	char	*type;

	lst = obj.cuts;
	while (lst != NULL)
	{
		cut = (t_cut *)(lst->content);
		if (cut->relative == 1 && cut->circular == 1)
			type = "circular";
		else if (cut->relative == 1)
			type = "relative";
		else if (cut->relative == 0)
			type = "absolute";
		else
			type = "UNKNOWN";
		dprintf(fd,"\t\t\t\t<cut type=\"%s\">\n", type);
		ft_print_cut(*cut, fd);
		dprintf(fd,"\t\t\t\t</cut>\n");
		lst = lst->next;
	}
}

static char	*ft_get_object_name(t_object obj)
{
	if (obj.intersect_func == intersect_sphere)
		return ("sphere");
	if (obj.intersect_func == intersect_plane)
		return ("plane");
	if (obj.intersect_func == intersect_cone)
		return ("cone");
	if (obj.intersect_func == intersect_cylinder)
		return ("cylinder");
	if (obj.intersect_func == intersect_ellipsoid)
		return ("ellipsoid");
	if (obj.intersect_func == intersect_torus)
		return ("torus");
	if (obj.intersect_func == intersect_goursat)
		return ("goursat");
	if (obj.intersect_func == intersect_lemniscate)
		return ("lemniscate");
	if (obj.intersect_func == intersect_roman)
		return ("roman");
	if (obj.intersect_func == intersect_piriform)
		return ("piriform");
	if (obj.intersect_func == intersect_hyperboloid)
		return ("hyperboloid");
	if (obj.intersect_func == intersect_paraboloid)
		return ("paraboloid");
	if (obj.intersect_func == intersect_triangle)
		return ("triangle");
	return ("UNKNOWN");
}

static void	ft_print_obj_perturbation(t_object obj, int fd)
{
	char	*type;

	if (obj.pert == e_none)
		type = "none";
	else if (obj.pert == e_waves)
		type = "waves";
	else if (obj.pert == e_ripple)
		type = "ripple";
	else if (obj.pert == e_noise)
		type = "noise";
	else if (obj.pert == e_chess)
		type = "chess";
	else if (obj.pert == e_perlin)
		type = "perlin";
	else if (obj.pert == e_marble)
		type = "marble";
	else
		type = "UNKNOWN";
	dprintf(fd,"\t\t\t\t<perturbation name=\"%s\"></perturbation>\n", type);
}

static void	ft_print_object(t_object obj, int fd)
{
	char		*shape;

	shape = ft_get_object_name(obj);
	dprintf(fd,"\t\t\t<object name=\"%s\">\n", shape);
	dprintf(fd,"\t\t\t\t<positionXYZ>");
	dprintf(fd,"%f %f %f", obj.o.x, obj.o.y, obj.o.z);
	dprintf(fd,"</positionXYZ>\n");
	dprintf(fd,"\t\t\t\t<rotationXYZ>");
	dprintf(fd,"%f %f %f", obj.r.x, obj.r.y, obj.r.z);
	dprintf(fd,"</rotationXYZ>\n");
	dprintf(fd,"\t\t\t\t<scaleXYZ>");
	dprintf(fd,"%f %f %f", obj.s.x, obj.s.y, obj.s.z);
	dprintf(fd,"</scaleXYZ>\n");
	dprintf(fd,"\t\t\t\t<color>0x%X</color>\n", obj.c.col);
	dprintf(fd,"\t\t\t\t<shine>%f</shine>\n", obj.shine);
	dprintf(fd,"\t\t\t\t<reflection>%f</reflection>\n", obj.reflect);
	dprintf(fd,"\t\t\t\t<refraction>%f</refraction>\n", obj.refract);
	dprintf(fd,"\t\t\t\t<transparency>%f</transparency>\n", obj.transp);
	//dprintf(fd,"\t\t\t\t<negative>%d</negative>\n", obj.negative);
	obj.print_caracteristics(obj, fd);
	ft_print_obj_perturbation(obj, fd);
	ft_print_object_cuts(obj, fd);
	dprintf(fd,"\t\t\t</object>\n");
}

static void	ft_print_cobj_perturbation(t_cobject cobj, int fd)
{
	char	*type;

	if (cobj.pert == e_none)
		type = "none";
	else if (cobj.pert == e_waves)
		type = "waves";
	else if (cobj.pert == e_ripple)
		type = "ripple";
	else if (cobj.pert == e_noise)
		type = "noise";
	else if (cobj.pert == e_chess)
		type = "chess";
	else if (cobj.pert == e_perlin)
		type = "perlin";
	else if (cobj.pert == e_marble)
		type = "marble";
	else
		type = "UNKNOWN";
	dprintf(fd,"\t\t\t<perturbation name=\"%s\"></perturbation>\n", type);
}

static void	ft_print_cobject(t_cobject cobj, int fd)
{
	dprintf(fd,"\t\t<cobject>\n");
	dprintf(fd,"\t\t\t<positionXYZ>");
	dprintf(fd,"%f %f %f", cobj.o.x, cobj.o.y, cobj.o.z);
	dprintf(fd,"</positionXYZ>\n");
	dprintf(fd,"\t\t\t<rotationXYZ>");
	dprintf(fd,"%f %f %f", cobj.r.x, cobj.r.y, cobj.r.z);
	dprintf(fd,"</rotationXYZ>\n");
	dprintf(fd,"\t\t\t<scaleXYZ>");
	dprintf(fd,"%f %f %f", cobj.s.x, cobj.s.y, cobj.s.z);
	dprintf(fd,"</scaleXYZ>\n");
	dprintf(fd,"\t\t\t<color>");
	dprintf(fd,"0x%X", cobj.c.col);
	dprintf(fd,"</color>\n");
	dprintf(fd,"\t\t\t<shine>%f</shine>\n", cobj.shine);
	dprintf(fd,"\t\t\t<reflection>%f</reflection>\n", cobj.reflect);
	dprintf(fd,"\t\t\t<refraction>%f</refraction>\n", cobj.refract);
	dprintf(fd,"\t\t\t<transparency>%f</transparency>\n", cobj.transp);
	ft_print_cobj_perturbation(cobj, fd);
	//dprintf(fd,"\t\t\t<negative>%d</negative>\n", cobj.negative);
}

int			ft_export_scene(t_world *world)
{
	int			fd;
	char		*name;
	t_cobjlist	*lst;
	t_objlist	*lst2;

	name = ft_get_name(".xml");
	if ((fd = open(name, O_RDWR | O_CREAT, 0644)) == -1)
		return (-1);
	dprintf(fd,"<scene>\n");
	ft_print_camera(world, fd);
	lst = world->cobjlist;
	if (lst != NULL)
	{
		dprintf(fd,"\t<objlist>\n");
		while (lst != NULL)
		{
			ft_print_cobject(*(lst->cobject), fd);
			lst2 = lst->cobject->objlist;
			while(lst2 != NULL)
			{
				ft_print_object(*(lst2->object), fd);
				lst2 = lst2->next;
			}
			dprintf(fd,"\t\t</cobject>\n");
			lst = lst->next;
		}
		dprintf(fd,"\t</objlist>\n");
	}
	ft_print_lights(world, fd);
	ft_print_others(world, fd);
	dprintf(fd,"</scene>\n");
	free(name);
	close(fd);
	return (1);
}
