/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fillit.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kacoulib <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/13 21:02:30 by kacoulib          #+#    #+#             */
/*   Updated: 2016/12/23 07:57:35 by kacoulib         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLIT_H
# define FILLIT_H

# include <unistd.h>
# include <fcntl.h>
# include "src/libft/libft.h"

typedef struct	s_tetri
{
	short		x;
	short		y;
	short		nb_line;
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
	int			map_size;
	int			error;
	char		*buff;
}				t_main_var;
#endif
