/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_verify_label.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkrief <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 16:52:40 by rkrief            #+#    #+#             */
/*   Updated: 2018/06/04 14:04:08 by rkrief           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/asm.h"

void	ft_initialize(int *i, int *ok, char **res)
{
	*i = 0;
	*ok = 0;
	*res = NULL;
}

t_chain	*ft_increment(int *j, int *ok, t_chain *start)
{
	*j = *j + 1;
	*ok = 0;
	return (start);
}

void	ft_is_not_ok(int ok, char *res, int i, char *str)
{
	if (!ok)
	{
		ft_putstr("Sorry but the label you put doesn't exist\n");
		ft_putendl(res);
		ft_strdel(&res);
		ft_is_an_error(str, i);
	}
}

char	*ft_take_the_res(char *str, int *i, int *j)
{
	char	*res;
	char	*tmp;

	tmp = NULL;
	res = NULL;
	if ((str[*j] == DIRECT_CHAR && str[*j + 1] == LABEL_CHAR) ||
			(str[*j] == LABEL_CHAR && ft_strchr(LABEL_CHARS, str[*j + 1])))
	{
		if (str[*j] == LABEL_CHAR)
			*i = *j + 1;
		else
			*i = *j + 2;
		while (str[*j] && (str[*j] > 32 && str[*j] != SEPARATOR_CHAR))
			*j = *j + 1;
		res = ft_strnmdup(str, *i, *j);
		tmp = res;
		res = ft_strjoin(tmp, ":");
		ft_strdel(&tmp);
		return (res);
	}
	else
		return (NULL);
}

void	ft_verify_label(char *str, int j, t_chain *block)
{
	int		i;
	int		ok;
	char	*res;
	t_chain	*start;

	ft_initialize(&i, &ok, &res);
	start = block;
	while (str[j])
	{
		if (res)
			ft_strdel(&res);
		if ((res = ft_take_the_res(str, &i, &j)))
		{
			while (block->next)
			{
				if (ft_strequ(block->category, "LABEL") &&
						ft_strequ(block->content, res))
					ok = 1;
				block = block->next;
			}
			ft_is_not_ok(ok, res, i, str);
		}
		block = ft_increment(&j, &ok, start);
	}
	ft_strdel(&res);
}
