/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 11:56:06 by pjaguin           #+#    #+#             */
/*   Updated: 2025/04/04 12:03:57 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

static	bool	ft_is_numeric(char *str)
{
	if (!str || !*str)
		return (false);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (false);
		str++;
	}
	return (true);
}

void	ft_exit(t_data *data, char **cmd)
{
	int	exit_code;

	ft_putendl_fd("exit", STDOUT_FILENO);
	if (cmd[1] && !ft_is_numeric(cmd[1]))
	{
		ft_putstr_fd(ERR_EXIT_SYNTAX, ERR_OUT);
		ft_exit_clean(data, 255);
	}
	if (cmd[1] && cmd[2])
	{
		ft_putstr_fd(ERR_EXIT_TOO_MANY, ERR_OUT);
		ft_update_last_exit_value(data, 1);
		return ;
	}
	if (cmd[1])
	{
		exit_code = ft_atoi(cmd[1]);
		if (exit_code < 0)
			exit_code = 256 + exit_code;
	}
	else
		exit_code = 0;
	ft_exit_clean(data, exit_code);
}
