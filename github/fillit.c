/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:05:57 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/23 07:57:45 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"
#include <stdio.h>

int				ft_match_col(char s1[], char s2[], int i, int j)
{
	while (j < 15)
	{
		printf("%d, %d\n", i, j);
		if (s1[i + j] == '#' && s2[j] == '#')
			return (0);
		j += 5;
	}
	return (1);
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
 ** If the function find a position in the loop to place, it will call him self
 ** with the next tetrimios.
 **
 ** Else if it didn't found a place, it will call himself with the prev
 ** tetrimios
 */

int				ft_resolve_tetri(t_tetri s[], int i, int j, int *map_size)
{
	int			l;
	int			m;
	int			k;

//		return (1);
	k = 0;
	l = -1;
	m = 0;
	i = 2;
	j = 3;
	map_size++;
		printf("\n %d, %d\n", 4 - s[i].y, *map_size);
		return(1);
	while (s[i].y++ < 4)
	{// tant que pas sur fini colone en partant de 0
		while (++s[i].x < 4)
		{// tant que pas fini de lire la ligne en partant de 0
			k = (s[i].y * 5 - 2) + m;
			//while (++l < 4)
			//{
			//	if (s[i].txt[k - l] == '#' && s[j].txt[m] == '#')
			//		;
			//	else
			//		l = 3;
			//}
			ft_match_col(s[i].txt, s[j].txt, s[i].x, 0);
		//	printf("s1[%d] && s2[%d] == #\n", s[i].x + m ,  m);
			//return(0);
		//l = + 1;
			m += 5;
		}
		s[i].x = 0;
		m = 0;
	}
	//if ()
	//printf("\n\n\n%d %d", s[i].x, s[i].y);
	return (1);
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
			tmp[j] = (t_tetri){-1, 0, 0, 0, 0, 0, 0, j + 65, {0}};
			ft_strncpy(tmp[j++].txt, v.buff, 19);
			v.map_size += ft_decale_top_left(&tmp[j - 1], 0, 5);
			v.BUFF_SIZE = 1;
		}
		else
			v.BUFF_SIZE = 20;
	}
	close(v.fd);
	if (!ft_check_tetri(tmp, 0, -1) || !ft_resolve_tetri(tmp, 0, 0, &v.map_size))
		ft_putstr("error\n");
	return (0);
}
