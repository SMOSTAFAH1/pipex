/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-12 17:53:31 by shashemi          #+#    #+#             */
/*   Updated: 2025-06-12 17:53:31 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

static void	exit_execute_error(int errnum, char *command_name)
{
	int	status;

	errno = errnum;
	if (errnum == ENOENT)
		status = error_handler(2, command_name);
	else if (errnum == EACCES)
		status = error_handler(3, command_name);
	else
		status = error_handler(0, command_name);
	exit(status);
}

int	execute_cmd(char *command_name, char **envp, int in_fd, int out_fd)
{
	char	**argv;
	char	*pathname;

	if (command_name == NULL)
		return (errno = ENOENT, -1);
	argv = ft_split(command_name, ' ');
	if (argv == NULL)
		return (errno = ENOMEM, -1);
	if (argv[0] == NULL || argv[0][0] == '\0')
		return (ft_freestrarr(&argv), errno = ENOENT, -1);
	pathname = NULL;
	if (get_cmd_path(&pathname, argv[0], envp) == -1)
		return (ft_freestrarr(&argv), ft_freestr(&pathname), -1);
	if (in_fd != STDIN_FILENO)
	{
		dup2(in_fd, STDIN_FILENO);
		close(in_fd);
	}
	if (out_fd != STDOUT_FILENO)
	{
		dup2(out_fd, STDOUT_FILENO);
		close(out_fd);
	}
	execve(pathname, argv, envp);
	return (ft_freestrarr(&argv), ft_freestr(&pathname), -1);
}

pid_t	execute_first(char *argv[], char **envp, int pipe_fd[2])
{
	pid_t	pid;
	int		in_fd;
	int		errnum;

	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), close(pipe_fd[1]), -1);
	if (pid == 0)
	{
		in_fd = open(argv[1], O_RDONLY);
		close(pipe_fd[0]);
		if (in_fd == -1)
			exit(error_handler(0, argv[1]));
		if (execute_cmd(argv[2], envp, in_fd, pipe_fd[1]) == -1)
		{
			errnum = errno;
			close(pipe_fd[1]);
			close(in_fd);
			exit_execute_error(errnum, argv[2]);
		}
	}
	close(pipe_fd[1]);
	return (pid);
}

pid_t	execute_second(char *argv[], char **envp, int pipe_fd[2])
{
	pid_t	pid;
	int		out_fd;
	int		errnum;

	pid = fork();
	if (pid == -1)
		return (close(pipe_fd[0]), -1);
	if (pid == 0)
	{
		out_fd = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (out_fd == -1)
		{
			close(pipe_fd[0]);
			exit(error_handler(0, argv[4]));
		}
		if (execute_cmd(argv[3], envp, pipe_fd[0], out_fd) == -1)
		{
			errnum = errno;
			close(out_fd);
			exit_execute_error(errnum, argv[3]);
		}
	}
	close(pipe_fd[0]);
	return (pid);
}

char	*ft_strchr(const char *s, int c)
{
	unsigned char	*p;

	if (s == NULL)
		return (NULL);
	p = (unsigned char *)s;
	while (*p)
	{
		if (*p == (unsigned char)c)
			return ((char *)p);
		p++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)p);
	return (NULL);
}
