/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:05:57 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/18 21:15:46 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

char			ft_strcpy_from(char *des, char *src, int i)
{
	while (src[i])
	{
		des[i] = src[i];
		printf("%c", des[i]);
		i++;
	}
	return (*des);
}

/*
 ** check if an axe x or y is empty
*/

int				ft_is_empty_x(t_tetri *tmp, int i)
{
	return ((tmp->txt[i] == '.' && tmp->txt[i + 5] == '.' &&
		tmp->txt[i + 10] == '.' && tmp->txt[i + 15] == '.') ? 1 : 0);
}

int				ft_is_empty_y(t_tetri *tmp, int i)
{
	return ((tmp->txt[i] == '.' && tmp->txt[i + 1] == '.' &&
		tmp->txt[i + 2] == '.' && tmp->txt[i + 3] == '.') ? 1 : 0);
}

/*
 ** decale all tetrimios to the Top-Left recursively
*/

int				ft_decale_top_left(t_tetri *s, int i, int decale, char *axe)
{
	if ((ft_indexof(axe, 'T') >= 0) && ((s->txt[0] == '.') && (s->txt[1] == '.')
				&& (s->txt[2] == '.') && (s->txt[3] == '.')))
		decale = 5;
	else if ((ft_indexof(axe, 'L') >= 0) && (s->txt[0] == '.') &&
			(s->txt[5] == '.') && ((s->txt[10] == '.') && (s->txt[15] == '.')))
		decale = 1;
	else
		decale = 0;
	while (s->txt[i] && decale)
	{
		if ((decale == 5 && s->txt[i] != '\n' && i < 14))
			ft_swap_char(&s->txt[i], &s->txt[i + 5]);
		if ((decale == 1 && s->txt[i] != '\n' && s->txt[i + 1] != '\n'))
			ft_swap_char(&s->txt[i], &s->txt[i + 1]);
		i++;
	}
	return ((!decale) ? 1 : ft_decale_top_left(s, 0, decale, axe));
}

/*
 ** Parse the array of tetrimios and print the by the order
 ** and remove all extra part
 */

char			*ft_render(t_tetri tmp[], char *map, int i, int j)
{
	unsigned short m;

	m = 17;
	map = ft_strcpy(map, tmp[i].txt);
	while (tmp[++i].txt[j])
	{
		while (tmp[i].txt[j])
		{
			m = ((((i * 20) - 15) + j) - 1) - tmp[i].offset;
			if ((!ft_isalpha(map[m]) && (map[m] != '#')) && j % 4 != 0)
			{
				map[m] = tmp[i].letter;
			}
//			printf("\n -%d- %c | %d\n", m, tmp[i].txt[j], m % 4);
			m++;
			j++;
		}
		printf("\n\n\n");
		j = 0;
	}
	//printf("\n%s\n", map);
	return (map);
}

/*
 ** Try to fit the the curent tetrimios with his precedent
 ** if he can't then he make on step down and retry
 */

int				ft_place_tetri(t_tetri *tmp, int i, int j)
{
	int			py;

	py = 3;
	while (tmp[i++].txt[++j])
	{
		while (py > 0)
		{
			if (!ft_is_empty_y(&tmp[i - 1], py) &&
				!ft_is_empty_y(&tmp[i], 0))
				tmp[i].offset++;
			py--;
		}
//		printf("\n%d = %d\n", i,  tmp[i].offset);
		py = 3;
		j = -1;
	}
	return (1);
}

/*
 ** Check if the 4 point of the tetrimios are linked to each other
 ** otherwhise the form is invalid
*/

int				ft_are_touch(char *s, short i)
{
	short		j;
	int			found;
	int			pr;

	pr = 2;
	found = 0;
	j = -1;
	while (j++ < 20 && ++i >= 0)
	{
		if (s[i] == '#')
		{
			if ((((j >= 0 && j <= 2) || (j >= 5 && j <= 7) || (j >= 10 && j
				<= 12) || (j >= 15 && j <= 17)) && (s[i + 1] == '#')) ||
				(((j >= 1 && j <= 3) || (j >= 6 && j <= 8) ||
				(j >= 11 && j <= 13)) && (s[i - 1] == '#')) ||
				(j >= 5 && (s[i - 5] == '#')) || (j <= 13 && (s[i + 5] == '#')))
			{
				if (i - 5 == pr || i + 5 == pr || i + 1 == pr || i - 1 == pr)
					found++;
				pr = i;
			}
		}
	}
	return (found == 3 ? 1 : 0);
}

/*
 ** Check if the file containe valid tetrimios. Each tetrimios should be in a
 ** grid of 4*4 folow by a new line except the last one, each piece be linked
*/

int				ft_check_file(char *s, short i, t_tetri tmp[], short j)
{
	while (s[i] && ++j >= 0)
	{
		while (tmp[j].i < 20)
		{
			if (s[i] == '#')
				tmp[j].nb_hash++;
			else if (s[i] == '.')
				tmp[j].nb_dot++;
			else if (s[i] == '\n')
				tmp[j].nb_newline++;
			else
				return (0);
			tmp[j].txt[tmp[j].i++] = s[i];
			i++;
		}
//	printf("%c %d %d %d\n%s", tmp[j].letter, tmp[j].nb_hash, tmp[j].nb_dot, tmp[j].nb_newline, tmp[j].txt);
		if (!(tmp[j].nb_hash == 4 && tmp[j].nb_dot == 12 &&
					tmp[j].nb_newline == 4) || !ft_are_touch(
						s, (((i - i / 20 + 1) - 20) + i % 20) - 1))
			return (0);
		if (s[i] == '\n')
			i++;
		if (!(s[i] == '\0'))
			return (1);
		tmp[j + 1] = (t_tetri){0, 0, 0, 0, 0, tmp[j].letter + 1, {0}};
		i++;
	}
	return (1);
}

int				main(int ac, char *av[])
{
	t_main_var	v;
	t_tetri		tmp[26];
	int			j;
	int			k;

	j = 0;
	k = 0;
	v = (t_main_var){0, open(av[1], O_RDONLY), 20, 0, NULL, {{0}}, NULL};
	v.buff = ft_memalloc(v.BUFF_SIZE + 1);
	tmp[0] = (t_tetri){0, 0, 0, 0, 0, 'A', {0}};
	if (ac == 1 || ac > 2 || !v.fd)
		v.error++;
	while ((v.i = read(v.fd, v.buff, v.BUFF_SIZE + 1)))
	{
		v.buff[v.i] = '\0';
		if (v.BUFF_SIZE == 20)
		{
			ft_strcpy_from(v.r[j], v.buff, 0);
			v.BUFF_SIZE = 1;
		}
		else
			v.BUFF_SIZE = 20;
		
		k = 1;
		//printf("%d\n%s\n", j, v.r[j]);
		j++;
	}
	//return(0);
	close(v.fd);
	v.i = 0;
	/*
	if (!ft_check_file(v.buff, 0, tmp, -1))
	{
		ft_putstr("error\n");
		return (0);
	}
	v.i = -1;
	ft_decale_top_left(&tmp[v.i], 0, 5, "L");
	//ft_place_tetri(tmp, 0, -1);
*/	
	j = -1;
	v.i = 0;
	while (v.r[j++][0])
	{
		//ft_decale_top_left(&tmp[v.i], 0, 5, "L");
		//printf("%d\n%s\n", j,v.r[j]);
	}
//	if ((v.map = ft_memalloc(84)))
//		v.map = ft_render(tmp, v.map, 0, 0);
//		*/
	return (0);
}
