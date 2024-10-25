/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 15:13:11 by acarpent          #+#    #+#             */
/*   Updated: 2024/09/26 15:13:11 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

typedef struct s_export
{
	t_env	*exist;
	char	*name;
	char	*value;
	t_env	*new;
}			t_export;

void	init_export(t_export *export)
{
	export->name = NULL;
	export->value = NULL;
	export->new = NULL;
}

void	print_export(t_env *env)
{
	no_args(env);
	while (env)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(env->name, 1);
		if (env->equal_sign == 1)
			ft_putstr_fd("=", 1);
		if (env->value)
			ft_putstr_fd(env->value, 1);
		ft_putstr_fd("\n", 1);
		env = env->next;
	}
}

char	*find_name(char *str, char *name, int *equal_sign)
{
	int	i;
	int	j;

	i = 0;
	j = i;
	if (str[0] == '=')
	{
		export_error(str);
		return (NULL);
	}
	while (str[i] && str[i] != '=')
	{
		if ((!ft_isalpha(str[i]) && str[i] != '_'))
		{
			export_error(str);
			return (NULL);
		}
		i++;
	}
	if (str[i] == '=' || str[i] == '\0')
	{
		if (str[i] == '=')
			*equal_sign = 1;
		name = ft_substr(str, j, i - j);
	}
	return (name);
}

char	*find_value(char *str, char *val)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	if (str[i] != '\0' && str[i + 1] != '\0')
	{
		i++;
		j = i;
		while (str[i])
			i++;
		val = ft_substr(str, j, i - j);
	}
	return (val);
}

int	ft_export(t_ms *ms)
{
	t_export	exp;
	int			i;
	int			equal_sign;

	i = 0;
	equal_sign = 0;
	init_export(&exp);
	if (!ms->cmdlines->cmd->cmds[1])
		print_export(ms->env);
	else
	{
		i++;
		while (ms->cmdlines->cmd->cmds[i])
		{
			exp.name = find_name(ms->cmdlines->cmd->cmds[i], exp.name, &equal_sign);
			if (!exp.name)
				return (1);
			exp.value = find_value(ms->cmdlines->cmd->cmds[i], exp.value);
			exp.exist = find_env(ms->env, exp.name);
			if (exp.exist)
				alr_exist(exp.exist, exp.value);
			else
				add_new(&ms->env, exp.name, exp.value, equal_sign);
			i++;
		}
	}
	return (0);
}
