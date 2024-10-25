/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_opener.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:28:01 by codespace         #+#    #+#             */
/*   Updated: 2024/10/23 22:52:16 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_file_opener(t_ms *ms)
{
	t_redirs	*current;
	int			last_fd_in;

	current = ms->cmdlines->cmd->redirs;
	last_fd_in = -1;
	while (current)
	{
		if (current->in_flag == true || current->hd_flag == true)
		{
			_maybe_fd_closing(last_fd_in);
			if (access(current->infile, F_OK) != 0)
			{
				perror(current->infile);
				exit(1);
			}
			last_fd_in = open(current->infile, O_RDONLY);
			if (last_fd_in < 0)
			{
				perror(current->infile);
				exit(1);
			}
		}
		current = current->next;
	}
	redirect_and_close(last_fd_in, STDIN_FILENO);
}

void	outfile_opener(t_ms *ms)
{
	t_redirs	*current;
	int			last_fd_out;

	current = ms->cmdlines->cmd->redirs;
	last_fd_out = -1;
	while (current)
	{
		if (current->out_flag == true || current->out_app == true)
		{
			_maybe_fd_closing(last_fd_out);
			if (current->out_flag == true)
				last_fd_out = open(current->outfile,
						O_WRONLY | O_CREAT | O_TRUNC, 0644);
			else if (current->out_app == true)
				last_fd_out = open(current->outfile,
						O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (last_fd_out < 0)
			{
				perror(current->outfile);
				exit(1);
			}
		}
		current = current->next;
	}
	redirect_and_close(last_fd_out, STDOUT_FILENO);
}

void	ft_open_files(t_ms *ms)
{
	in_file_opener(ms);
	outfile_opener(ms);
}
