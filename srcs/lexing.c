/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 09:03:08 by unmugviolet       #+#    #+#             */
/*   Updated: 2025/03/13 18:26:45 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_get_type(char *str)
{
	if (!ft_strncmp(str, "<<", 3))
		return (DOUBLE_LEFT_BRACKET);
	if (!ft_strncmp(str, ">>", 3))
		return (DOUBLE_RIGHT_BRACKET);
	if (!ft_strncmp(str, "<", 2))
		return (LEFT_BRACKET);
	if (!ft_strncmp(str, ">", 2))
		return (RIGHT_BRACKET);
	if (!ft_strncmp(str, "||", 3))
		return (DOUBLE_PIPE);
	if (!ft_strncmp(str, "|", 2))
		return (PIPE);
	if (!ft_strncmp(str, "&&", 3))
		return (DOUBLE_AMPERSAND);
	if (!ft_strncmp(str, "&", 2))
		return (AMPERSAND);
	if (!ft_strncmp(str, "$", 2))
		return (DOLLAR);
	return (WORD);
}

/*	That function take the data struct and populate the chained list lex.
	The struct contain the `content` `type` `size`
	@param t_data data
	@return void
*/
void	ft_init_lex_prompt(t_data *data)
{
	int		i;
	size_t	type;
	char	**array;
	t_lex	*new_lex;

	i = 0;
	array = ft_split_strset_quote(data->prompt, data->metachar);
	while (array[i])
	{
		type = ft_get_type(array[i]);
		new_lex = ft_lexnew(type, ft_strdup(array[i]));
		if (!data->lex)
			data->lex = new_lex;
		else
			ft_lexadd_back(&data->lex, new_lex);
		i++;
	}
	ft_print_lex(data->lex);
	ft_free_array_str(array);
	data->lex_size = ft_lexsize(data->lex);
}
