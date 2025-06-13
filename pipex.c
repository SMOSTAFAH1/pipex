/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-12 17:53:41 by shashemi          #+#    #+#             */
/*   Updated: 2025-06-12 17:53:41 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*r;
	size_t	s1_len;
	size_t	s2_len;
	size_t	i;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	r = (char *)malloc(sizeof(char) * (s1_len + s2_len + 1));
	if (r == NULL)
		return (NULL);
	i = 0;
	while (i < s1_len || i < s2_len)
	{
		if (i < s1_len)
			r[i] = s1[i];
		if (i < s2_len)
			r[s1_len + i] = s2[i];
		i++;
	}
	r[s1_len + s2_len] = '\0';
	return (r);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*c1;
	unsigned char	*c2;
	size_t			i;

	c1 = (unsigned char *)s1;
	c2 = (unsigned char *)s2;
	i = 0;
	while ((c1[i] || c2[i]) && i < n)
	{
		if (c1[i] != c2[i])
			return (c1[i] - c2[i]);
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[], char **envp)
{
	int		pipe_fd[2];
	int		status;
	pid_t	pid_first;
	pid_t	pid_second;

	if (argc != 5)
		exit(error_handler(1, argv[0]));
	if (pipe(pipe_fd) == -1)
		exit(error_handler(0, NULL));
	pid_first = execute_first(argv, envp, pipe_fd);
	if (pid_first == -1)
		exit(error_handler(0, NULL));
	pid_second = execute_second(argv, envp, pipe_fd);
	waitpid(pid_first, NULL, 0);
	if (pid_second == -1)
		exit(error_handler(0, NULL));
	waitpid(pid_second, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (WTERMSIG(status) + 128);
	return (EXIT_FAILURE);
}

static int	word_count_and_fill(const char *s, char c, char **res, int mode)
{
	int	vars[4];

	vars[0] = 0;
	vars[1] = 0;
	vars[2] = 0;
	vars[3] = 0;
	while (*(s + vars[0]))
	{
		if (*(s + vars[0]) == c)
			vars[3] = 0;
		else if (vars[3] == 0 && ++vars[1] && mode == 1)
		{
			vars[3] = 1;
			vars[2] = 0;
			while (*(s + vars[0] + vars[2]) && *(s + vars[0] + vars[2]) != c)
				++vars[2];
			res[vars[1] - 1] = ft_substr(s, vars[0], vars[2]);
			if (res[vars[1] - 1] == NULL)
				return (-1);
			vars[0] += vars[2] - 1;
		}
		++vars[0];
	}
	return (vars[1]);
}

char	**ft_split(const char *s, char c)
{
	int		words;
	char	**res;

	words = word_count_and_fill(s, c, NULL, 0);
	res = (char **) malloc((words + 1) * sizeof(char *));
	if (res == NULL)
		return (NULL);
	res[words] = NULL;
	if (word_count_and_fill(s, c, res, 1) == -1)
	{
		while (--words >= 0)
			free(res[words]);
		free(res);
		return (NULL);
	}
	return (res);
}
