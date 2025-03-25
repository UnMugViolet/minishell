/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 12:24:45 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/25 12:20:52 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// size_t	

void	ft_print_exec(t_exec *exec)
{
    t_exec	*tmp;
    int		i;

    tmp = exec;
    i = 0;
    if (!tmp)
        printf("EXEC IS EMPTY\n");
    else
    {
        printf("EXEC ARRAY:\n");
        while (tmp)
        {
            printf("Chain nbr: %i\n", ++i);
            ft_print_array_str_fd(tmp->cmd, 1);
            printf("Path: %s\n", tmp->path ? tmp->path : "NULL");
            printf("Infile: %s\n", tmp->infile ? tmp->infile : "NULL");
            printf("Outfile: %s\n\n", tmp->outfile ? tmp->outfile : "NULL");
            tmp = tmp->next;
        }
    }
}
