/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 14:39:23 by pjaguin           #+#    #+#             */
/*   Updated: 2025/04/03 19:18:37 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/*
	Handle the echo builtin command. It prints the arguments passed to it
	and adds a newline at the end if the `-n` option is not used.
	@param char**cmd
	@return void
*/
int	ft_echo(char **cmd)
{
	int		i;
	bool	newline;

	newline = true;
	i = 1;
	if (!cmd[1])
		return (ft_putstr_fd("\n", STDOUT_FILENO), 0);
	if (!ft_strncmp(cmd[1], "-n", 3))
	{
		newline = false;
		i++;
	}
	while (cmd[i])
	{
		ft_putstr_fd(cmd[i], STDOUT_FILENO);
		if (cmd[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (newline)
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (0);
}
