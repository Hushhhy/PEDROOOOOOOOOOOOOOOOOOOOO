/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acarpent <acarpent@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 14:47:02 by codespace         #+#    #+#             */
/*   Updated: 2024/10/25 17:12:46 by acarpent         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executioner_utils(t_ms *ms, int x)
{
	close(ms->pipefd[1]);
	if (x > 0)
		close(ms->previous_fd);
	ms->previous_fd = ms->pipefd[0];
}

int	executioner(t_ms *ms)
{
	int			x;
	t_cmdline	*head;

	x = 0;
	head = ms->cmdlines;
	while (ms->cmdlines)
	{
		pipe(ms->pipefd);
		ms->pid[x] = fork();
		if (ms->pid[x] == -1)
			exit(1);
		signal(SIGQUIT, ft_sigquit_child);
		signal(SIGINT, sigint_here_doc);
		if (ms->pid[x] == 0)
		{
			//signaux
			child_process(ms);
		}
		else
			executioner_utils(ms, x);
		ms->cmdlines = ms->cmdlines->next;
		x++;
	}
	ms->cmdlines = head;
	return (wait_da_boy(ms));
}

int	executor(t_ms *ms)
{
	int	v_return;

	v_return = 0;
	ms->envi = the_env(ms->env);
	if (ms->envi == NULL)
	{
		ft_putstr_fd("Error: couldn't allocate memory\n", 2);
		return (1);
	}
	the_cmdlines(ms);
	// display_cmdlines(ms->cmdlines);
	ms->c_count = cmdlines_counter(ms->cmdlines);
	if (ms->c_count == 1)
		v_return = builtins(ms);
	ms->pid = malloc(sizeof(int) * ms->c_count);
	if (!ms->pid)
		return (ft_putstr_fd("Error : malloc failed", 2), 1);
	if (ms->b == false)
		v_return = executioner(ms);
	clear_cmdlines(&ms->cmdlines);
	ft_free_tab(ms->envi);
	free(ms->pid);
	close(ms->pipefd[0]);
	close(ms->pipefd[1]);
	return (v_return);
}
