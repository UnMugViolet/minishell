/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pjaguin <pjaguin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 13:08:53 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/20 10:29:20 by pjaguin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
	Check the inputs from the user, exit if the value entered is incorrect
	@param t_data*data
	@return void
*/
void	ft_parse_prompt(t_data *data)
{
	ft_replace_env_variable(data);
	if (!ft_strncmp(data->lex->content, "unset", 6))
		ft_delete_env_var(data, data->lex->next->content);
	if (!ft_strncmp(data->prompt, "exit", 5))
		ft_exit_clean(data);
	if ((!ft_strncmp(data->lex->content, "env", 4)))
		ft_print_array_str_fd(data->env, 1);
	if (!ft_strncmp(data->lex->content, "export", 7) && data->lex->next
		&& data->lex->next->type == WORD)
		ft_create_env_var(data, data->lex->next->content);
}
