/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 16:09:44 by pjaguin           #+#    #+#             */
/*   Updated: 2025/04/03 17:39:25 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exec_heredoc(t_data *data, t_exec *exec, char *limiter)
{
	char	*line;
	size_t	limiter_len;

	limiter_len = ft_strlen(limiter);
	if (data->pipe_fd[0] != -1)
		close(data->pipe_fd[0]);
	if (pipe(data->pipe_fd) == -1)
		ft_fprintf(ERR_OUT, STDRD_ERR_SINGLE, strerror(errno));
	while (true)
	{
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(0);
		if (!line || (!ft_strncmp(line, limiter, limiter_len)
				&& line[limiter_len] == '\n'))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, data->pipe_fd[1]);
		free(line);
	}
	ft_print_exec(data->exec);
	close(data->pipe_fd[1]);
	if (ft_get_next_word(exec))
	{
		ft_get_next_word(exec)->in_fd = data->pipe_fd[0];
	}
}
// Tu t'emmerdes pour rien la !!
// Moi j'aurais pas fait comme ca !
