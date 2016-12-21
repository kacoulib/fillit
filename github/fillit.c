/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:05:57 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/21 23:26:34 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

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

/*
 ** resolve te tetrimios
 */

int		ft_resolve_tetri(t_tetri s[], int i, int j, int k)
{
	int	x;

	if ((s[0].txt[0] == '#') && (s[0].txt[1] == '#') && (s[0].txt[5] == '#')
			&& (s[0].txt[6] == '#'))
		return (1);

	x = 4;
	j = 2;
	k = 0;
	while (x-- > 0)
	{
		while (j-- > 0)
		{
			k = (5 * j) + 3;

			printf("(j = %d\t\t%d)\n", j, k);
			//printf("(%d %d %d %d)", j, s[i + 1].x, s[i + 1].y, (s[i + 1].x * 5 + (s[i].x+ s[i + 1].y) + 3));
		}
		s[i + 1].y++;
		return (1);
		k++;
	}
	return (0);
}

/*
 ** Parse the array of tetrimios and print them by the order
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
			m++;
			j++;
		}
		printf("\n\n\n");
		j = 0;
	}
	return (map);
}

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
		py = 3;
		j = -1;
	}
	return (1);
}

/*
 ** Check if the file containe valid tetrimios. Each tetrimios should be in a
 ** grid of 4*4 folow by a new line except the last one, each piece be linked
 ** Check if the 4 point of the tetrimios are linked to each other
 ** otherwhise the form is invalid
*/

int				ft_check_file(t_tetri s[], short i, short j, short pr)
{
	while (++j < 19)
	{
		if (s[i].txt[j] == '#')
		{
			if ((((j >= 0 && j <= 2) || (j >= 5 && j <= 7) || (j >= 10 && j
				<= 12) || (j >= 15 && j <= 17)) && (s[i].txt[j + 1] == '#')) ||
				(((j >= 1 && j <= 3) || (j >= 6 && j <= 8) || (j >= 11 && j <=
				13)) && (s[i].txt[j - 1] == '#')) || (j >= 5 && (s[i].txt[j - 5]
				== '#')) || (j <= 13 && (s[i].txt[j + 5] == '#')))
				if (j - 5 == pr || j + 5 == pr || j + 1 == pr || j - 1 == pr)
					s[i].nb_hash++;
			pr = j;
		}
		else if (s[i].txt[j] == '.')
			s[i].nb_dot++;
		else if (s[i].txt[j] == '\n')
			s[i].nb_line++;
		else
			return (0);
	}
	if ((s->txt[0] == '#' && s->txt[1] == '#' && s->txt[5] == '#' & s->txt[6] ==
		'#') || ((s[i].nb_hash == 3 && s[i].nb_dot == 12 && s[i].nb_line == 3)))
		return ((s[i + 1].txt[0]) ? ft_check_file(&s[i + 1], i, -1, 100) : 1);
	return (0);
}

int				main(int ac, char *av[])
{
	t_main_var	v;
	t_tetri		tmp[26];
	int			j;

	j = 0;
	v = (t_main_var){0, open(av[1], O_RDONLY), 20, 0, NULL, NULL};
	v.buff = ft_memalloc(v.BUFF_SIZE + 1);
	if (ac == 1 || ac > 2 || !v.fd)
		v.error++;
	while ((v.i = read(v.fd, v.buff, v.BUFF_SIZE)))
	{
		v.buff[v.i] = '\0';
		if (v.BUFF_SIZE == 20)
		{
			tmp[j] = (t_tetri){-1, 0, 0, 0, 0, 0, 4, j + 65, {0}};
			ft_strncpy(tmp[j++].txt, v.buff, 19);
			ft_decale_top_left(&tmp[j - 1], 0, 5);
			v.BUFF_SIZE = 1;
		}
		else
			v.BUFF_SIZE = 20;
	}
	close(v.fd);
	ft_decale_top_left(tmp, 0, 5);
	if (!ft_check_file(tmp, 0, -1, 100) || !ft_resolve_tetri(tmp, 0, 4, 3))
		ft_putstr("error\n");
	return (0);
}
