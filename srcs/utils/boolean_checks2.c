/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   boolean_checks2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: unmugviolet <unmugviolet@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 09:39:26 by pjaguin           #+#    #+#             */
/*   Updated: 2025/03/26 15:13:37 by unmugviolet      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_is_metacharset(char *str, char **metacharset)
{
	int	i;

	i = 0;
	while (metacharset[i])
	{
		if (!ft_strncmp(str, metacharset[i], ft_strlen(metacharset[i])))
			return (true);
		i++;
	}
	return (false);
}

char	*ft_single_token(t_lex *lex, char **metachar)
{
	while (lex)
	{
		if (lex->next && ft_is_metacharset(lex->content, metachar)
			&& ft_is_metacharset(lex->next->content, metachar))
			return (lex->next->content);
		lex = lex->next;
	}
	return (NULL);
}
