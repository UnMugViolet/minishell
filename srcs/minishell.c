/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 17:38:07 by pjaguin           #+#    #+#             */
/*   Updated: 2025/04/08 19:29:06 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_resolve(t_data *data)
{
	if (!ft_is_correct_input(data->prompt))
		return ;
	ft_init_prompt_lexing(data);
	if (!ft_is_correct_token(data->lex, data->metachar))
	{
		ft_free_lex(data->lex);
		data->lex = NULL;
		ft_update_last_exit_value(data, 1);
		return ;
	}
	ft_parse_prompt(data);
	ft_execute_prompt(data);
	ft_free_lex(data->lex);
	ft_free_exec(data->exec);
	ft_close_fds(data);
	data->lex = NULL;
	data->exec = NULL;
	data->pid_count = 0;
	data->paths = ft_get_path_from_env(data, false);
}

static void	ft_start_minishell(t_data *data)
{
	while (true)
	{
		ft_get_current_dir(data);
		data->prompt = readline(data->curr_dir);
		if (data->prompt && *data->prompt == 0)
			continue ;
		else if (data->prompt)
		{
			add_history(data->prompt);
			if (!ft_is_closed_quotes(data->prompt))
				ft_fprintf(ERR_OUT, ERR_QUOTE);
			else
				ft_resolve(data);
		}
		else
			break ;
		free(data->prompt);
	}
	ft_exit_clean(data, 0);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	if (ac != 1)
		return (display_usage(), EXIT_FAILURE);
	(void)av;
	ft_setup_signals();
	ft_init_data_struct(&data, env);
	ft_start_minishell(&data);
	return (EXIT_SUCCESS);
}
