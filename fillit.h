/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:02:30 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/18 19:40:58 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# define FT_REPLACE (a, b) (a[i] == '#') ? a = b

# include <unistd.h>
# include <fcntl.h>
# include "src/libft/libft.h"

typedef struct	s_tetri
{
	short		nb_newline;
	short		nb_dot;
	short		nb_hash;
	short		i;
	short		offset;
	char		letter;
	char		txt[20];
}				t_tetri;

typedef struct	s_main_var
{
	short		i;
	char		fd;
	int			BUFF_SIZE;
	int			error;
	char		*buff;
	char		r[26][20];
	char		*map;
}				t_main_var;
#endif
