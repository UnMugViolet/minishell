/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionnary.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:30:32 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/26 11:28:42 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DICTIONNARY_H
# define DICTIONNARY_H

/*--------------------------------COLORS--------------------------------------*/

# define CYN "\x1B[36m"
# define BLK "\x1B[0m"

#define BOLD "\033[1m"
#define ITALIC "\033[3m"
#define UNDERLINE "\033[4m"
#define RESET "\033[0m" 

/*-------------------------------OPERATORS------------------------------------*/

# define ENPTY 0
# define WORD 1
# define PIPE 2
# define DOUBLE_PIPE 3
# define AMPERSAND 4
# define DOUBLE_AMPERSAND 5
# define LEFT_BRACKET 6
# define DOUBLE_LEFT_BRACKET 7
# define RIGHT_BRACKET 8
# define DOUBLE_RIGHT_BRACKET 9

/*---------------------------------TOKEN--------------------------------------*/

# define METACHAR "<< >> < > || | && &"

/*------------------------------- DEFAULT-------------------------------------*/

# define DEF_PATH "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin"
# define DEF_SHLVL "SHLVL=0"
# define DEF_LAST_ARG "_="

#endif
