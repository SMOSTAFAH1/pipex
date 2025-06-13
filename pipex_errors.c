/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-12 17:53:20 by shashemi          #+#    #+#             */
/*   Updated: 2025-06-12 17:53:20 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_strdup(const char *src)
{
	int		i;
	char	*dest;

	if (!src)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(src) + 1));
	i = 0;
	if (dest == 0)
		return (0);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

static void	p_error_command(char *msg, const char *command)
{
	int		i;

	write(STDERR_FILENO, "pipex: ", 7);
	write(STDERR_FILENO, msg, ft_strlen(msg));
	write(STDERR_FILENO, ": ", 2);
	if (!command)
	{
		write(STDERR_FILENO, "\n", 1);
		return ;
	}
	i = 0;
	while (command[i] && command[i] == ' ')
		i++;
	if (!command[i])
	{
		write(STDERR_FILENO, command, ft_strlen(command));
		write(STDERR_FILENO, "\n", 1);
		return ;
	}
	while (command[i] && command[i] != ' ')
		write(STDERR_FILENO, &command[i++], 1);
	write(STDERR_FILENO, "\n", 1);
}

int	ft_perror(int errnum, const char *arg)
{
	if (errnum == 0 && arg == NULL)
	{
		write(STDERR_FILENO, "unknown error\n", 14);
		return (errnum);
	}
	if (errnum != 0)
	{
		if (arg != NULL)
		{
			write(STDERR_FILENO, strerror(errnum), ft_strlen(strerror(errnum)));
			write(STDERR_FILENO, ": ", 2);
			write(STDERR_FILENO, arg, ft_strlen(arg));
			write(STDERR_FILENO, "\n", 1);
			return (errnum);
		}
		write(STDERR_FILENO, strerror(errnum), ft_strlen(strerror(errnum)));
		write(STDERR_FILENO, "\n", 1);
		return (errnum);
	}
	write(STDERR_FILENO, arg, ft_strlen(arg));
	write(STDERR_FILENO, "\n", 1);
	return (errnum);
}

int	error_handler(int error_code, const char *arg)
{
	int	errnum;

	if (error_code == 1)
	{
		write(STDERR_FILENO, "pipex: usage: ", 14);
		write(STDERR_FILENO, arg, ft_strlen(arg));
		write(STDERR_FILENO, " file1 cmd1 cmd2 file2\n", 23);
		return (EXIT_FAILURE);
	}
	else if (error_code == 2)
	{
		p_error_command("command not found", arg);
		return (127);
	}
	else if (error_code == 3)
	{
		p_error_command("permission denied", arg);
		return (126);
	}
	errnum = errno;
	write(STDERR_FILENO, "pipex: ", 7);
	ft_perror(errnum, arg);
	return (EXIT_FAILURE);
}

char	**ft_freestrarr(char ***arr)
{
	size_t	i;

	if (arr == NULL || *arr == NULL)
		return (NULL);
	i = 0;
	while ((*arr)[i] != NULL)
	{
		ft_freestr(&(*arr)[i]);
		i++;
	}
	free(*arr);
	*arr = NULL;
	return (NULL);
}
