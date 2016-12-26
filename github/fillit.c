/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:05:57 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/26 14:21:00 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

/*
 ** decale all tetrimios to the Top-Left recursively
 */

int				ft_decale_top_left(t_tetri *s, int i, int decale)
{
	if (((s->txt[0] == '.') && (s->txt[1] == '.') && (s->txt[2] == '.')
				&& (s->txt[3] == '.')))
		decale = 5;
	else if ((s->txt[0] == '.') && (s->txt[5] == '.') && ((s->txt[10] == '.')
				&& (s->txt[15] == '.')))
		decale = 1;
	else
		decale = 0;
	while (s->txt[i] && decale)
	{
		if ((decale == 5 && s->txt[i] != '\n' && i < 14))
			ft_swap_char(&s->txt[i], &s->txt[i + 5]);
		if ((decale == 1 && s->txt[i] != '\n' && s->txt[i + 1] && s->txt[i + 1]
					!= '\n'))
			ft_swap_char(&s->txt[i], &s->txt[i + 1]);
		i++;
	}
	return ((!decale) ? 1 : ft_decale_top_left(s, 0, decale));
}


int			ft_reset_tetri(t_tetri *s, char *map, int *map_size)
{
	int		i;

	i = -1;
	while (map[++i])
	{
		map[i] = '.';
		if (s[i].txt[0])
		{
			s[i].x = 0;
			s[i].y = 0;
		}
	}
	s[0].x = ++s[0].offset;
	s[0].y = s[0].x / *map_size;
	//if (s[0].x == *map_size && s[0].y == *map_size)
	//	*map_size += 1;
	return (1);
}

int				ft_isresolved(t_tetri s[], char *map, int *map_size)
{
	int			i;
	int			j;

	i = -1;
	j = i + 1;
	while (s[++i].txt[0])
	{
		while (s[++j].txt[0])
		{
			if (s[i].x == s[j].x || s[j].x >= *map_size)
			{
				ft_reset_tetri(s, map, map_size);
				return (0);
			}
		}
		j = i + 1;
	}
	j = 1;
	while (map[++j])
		if (j % (*map_size / i)== 0)
			map[j] = '\n';
	printf("%s\n", map);
	return (1);
}
int				ft_test_tetri(t_tetri *s, char *map, int map_size)
{
	int			i;
	int			j;

	i = -1;
	j = s->x;
	while (++i < 19)
	{
		if (s->txt[i] == '#')
		{
			if (ft_isalnum(map[j]) || j >= map_size || map[j] == '\n')
				return (0);
			s->i++;
		}
		j++;
	}
	return (1);
}


/*
 ** resolve te tetrimios
 ** If the function find a position in the loop to place, it will call him self
 ** with the next tetrimios.
 **
 ** Else if it didn't found a place, it will call himself with the prev
 ** tetrimios
 */

int				ft_resolve_tetri(t_tetri s[], char *map, int i, int *map_size)
{
	int			j;
	int			stop;

	j = -1;
	stop = 0;
	while (s[++i].txt[0])
	{
		while (s[i].x < *map_size && !stop)
		{
			if (ft_test_tetri(&s[i], map, *map_size))
			{
				while ((++j + s[i].x) < *map_size)
				{
					if (s[i].txt[j] == '#')
						map[s[i].x + j] = s[i].letter;
					if (!ft_isalnum(map[s[i].x + j]) || s[j].txt[j] == '\n')
						map[s[i].x + j] = '.';
					stop = 1;
				}
			}
			else
				s[i].x++;
		}
		j = -1;
		stop = 0;
	}
	//printf("\n%d %d", ft_isresolved(s, map, map_size), s[0].x);
	//printf("\n%s", map);
	//printf("\n%d", s[0].x);
	//printf("\n%d", s[1].x);
	//printf("\n%d", s[2].x);

	return (ft_isresolved(s, map, map_size) ? 1 : ft_resolve_tetri(s, map, -1, map_size));
}

/*
 ** Check if the file containe valid tetrimios. Each tetrimios should be in a
 ** grid of 4*4 folow by a new line except the last one, each piece be linked
 ** Check if the 4 point of the tetrimios are linked to each other
 ** otherwhise the form is invalid
 */

int				ft_check_tetri(t_tetri s[], short i, short j)
{
	while (++j < 19)
	{
		if (s[i].txt[j] == '#')
		{
			if (s[i].txt[j + 1] == '#')
				s[i].nb_hash++;
			if (j > 0 && s[i].txt[j - 1] == '#')
				s[i].nb_hash++;
			if (j > 4 && s[i].txt[j - 5] == '#')
				s[i].nb_hash++;
			if (j < 15 && s[i].txt[j + 5] == '#')
				s[i].nb_hash++;
		}
		else if (s[i].txt[j] == '.')
			s[i].nb_dot++;
		else if (s[i].txt[j] == '\n')
			s[i].nb_line++;
		else
			return (0);
	}
	if ((((s[i].nb_hash == 6 || s[i].nb_hash == 8) && s[i].nb_dot == 12
		&& s[i].nb_line == 3)))
		return ((s[i + 1].txt[0]) ? ft_check_tetri(&s[i + 1], i, -1) : 1);
	return (0);
}

int				main(int ac, char *av[])
{
	t_main_var	v;
	t_tetri		tmp[26];
	char		*map;
	int			j;

	j = 0;
	v = (t_main_var){0, open(av[1], O_RDONLY), 20, 0, 0, NULL};
	v.buff = ft_memalloc(v.BUFF_SIZE + 1);
	if (ac == 1 || ac > 2 || !v.fd)
		v.error++;
	while ((v.i = read(v.fd, v.buff, v.BUFF_SIZE)))
	{
		v.buff[v.i] = '\0';
		if (v.BUFF_SIZE == 20)
		{
			tmp[j] = (t_tetri){0, 0, 0, 0, 0, 0, 0, j + 65, {0}};
			ft_strncpy(tmp[j++].txt, v.buff, 19);
			v.map_size += ft_decale_top_left(&tmp[j - 1], 0, 5);
			v.BUFF_SIZE = 1;
		}
		else
			v.BUFF_SIZE = 20;
	}
	close(v.fd);
	v.map_size = (v.map_size <= 4 ) ? 20 : v.map_size * 4 + 1;
	//printf("\n%d", v.map_size);
	map = ft_memalloc(v.map_size);
	if (!map)
		return (0);
	if (!ft_check_tetri(tmp, 0, -1) || !ft_resolve_tetri(tmp, map, -1, &v.map_size))
		ft_putstr("error\n");
	return (0);
}
