/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionnary.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yguinio <yguinio@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:30:32 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/19 12:18:12 by yguinio          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONNARY_H
# define DICTIONNARY_H

/*--------------------------------COLORS--------------------------------------*/

# define CYN "\x1B[36m"
# define BLK "\x1B[0m"

/*-------------------------------OPERATORS------------------------------------*/

# define WORD 0
# define PIPE 1
# define DOUBLE_PIPE 2
# define AMPERSAND 3
# define DOUBLE_AMPERSAND 4
# define LEFT_BRACKET 5
# define DOUBLE_LEFT_BRACKET 6
# define RIGHT_BRACKET 7
# define DOUBLE_RIGHT_BRACKET 8

/*---------------------------------TOKEN--------------------------------------*/

# define METACHAR "<< >> < > || | && &"

/*------------------------------- DEFAULT-------------------------------------*/

# define DEF_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define DEF_SHLVL "SHLVL=0"
# define DEF_LAST_ARG "_="

#endif
