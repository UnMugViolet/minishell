/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:08:53 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/24 15:17:52 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_create_exec_tree(t_data *data)
{
	size_t	i;
	t_lex	*tmp;

	i = 0;
	tmp = data->lex;
	ft_get_heredocs(data);
	ft_get_infiles(data);
	ft_get_outfile(data);
	ft_get_commands(data);
	// ft_get_pipes(data);
	// ft_get_infiles(data);
}

/*
	Builtins are commands that are built into the shell. The shell must interpret
	them and display the result. If the cmd is not a builtin nothing is triggered.
	The builtins are: `pwd` `env` `unset` `exit` `export` `echo -n`
	@param t_data*data
	@param char*str
	@return void
*/
static void	ft_exec_builtins(t_data *data, char *str)
{
	if (!ft_strncmp(str, "pwd", 4))
		ft_putendl_fd(ft_get_env_var_adress(data, "PWD") + 4, STDOUT_FILENO);
	else if ((!ft_strncmp(str, "env", 4)))
		ft_print_array_str_fd(data->env, 1);
	else if (!ft_strncmp(str, "unset", 6))
		ft_delete_env_var(data, data->lex->next->content);
	else if (!ft_strncmp(data->prompt, "exit", 5))
		ft_exit_clean(data);
	else if (!ft_strncmp(str, "export", 7) && data->lex->next
		&& data->lex->next->type == WORD)
		ft_create_env_var(data, data->lex->next->content);
	else if (!ft_strncmp(str, "echo", 5))
		;
	else
		return ;
}

/*
	Check the inputs from the user, exit if the value entered is incorrect
	@param t_data*data
	@return void
*/
void	ft_parse_prompt(t_data *data)
{
	// ft_replace_env_variable(data); Not to be implemented yet
	ft_exec_builtins(data, data->lex->content);
	ft_create_exec_tree(data);
}

/* int	ft_echo(t_data *data)
{
	t_exec	*tmp;

	tmp = data->exec;
	while (data->exec && data->exec->type == WORD)
	{
		write(data->exec->cmd)
	}
}
 */
