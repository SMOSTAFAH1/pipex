/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-12 17:53:37 by shashemi          #+#    #+#             */
/*   Updated: 2025-06-12 17:53:37 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "pipex.h"

int	get_envp_paths(char	***path, char **envp)
{
	char	*tmp;
	size_t	i;

	i = 0;
	while (envp != NULL && envp[i] != NULL)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			*path = ft_split(envp[i] + 5, ':');
			if (*path == NULL)
				return (errno = ENOMEM, -1);
			i = 0;
			while (*path != NULL && (*path)[i] != NULL)
			{
				tmp = ft_strjoin((*path)[i], "/");
				if (tmp == NULL)
					return (ft_freestrarr(path), errno = ENOMEM, -1);
				ft_freestr(&(*path)[i]);
				(*path)[i++] = tmp;
			}
			return (0);
		}
		i++;
	}
	return (-1);
}

int	get_cmd_path(char **cmd_path, const char *cmd_name, char **envp)
{
	size_t	i;
	char	**paths;

	if (ft_strchr(cmd_name, '/') != NULL)
	{
		*cmd_path = ft_strdup(cmd_name);
		if (*cmd_path == NULL)
			return (errno = ENOMEM, -1);
		return (0);
	}
	paths = NULL;
	if (get_envp_paths(&paths, envp) == -1)
		return (errno = ENOENT, -1);
	i = 0;
	while (paths != NULL && paths[i] != NULL)
	{
		*cmd_path = ft_strjoin(paths[i], cmd_name);
		if (*cmd_path == NULL)
			return (ft_freestrarr(&paths), errno = ENOMEM, -1);
		if (access(*cmd_path, F_OK) == 0)
			return (ft_freestrarr(&paths), errno = 0, 0);
		ft_freestr(cmd_path);
		i++;
	}
	return (ft_freestrarr(&paths), errno = ENOENT, -1);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen <= start)
		return (ft_strdup(""));
	if (slen - start < len)
		len = slen - start;
	res = (char *) malloc((len + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	if (len > 0)
	{
		while (s[start + i] && i < len)
		{
			res[i] = s[start + i];
			i++;
		}
	}
	res[i] = 0;
	return (res);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_freestr(char **str)
{
	if (str != NULL && *str != NULL)
	{
		free(*str);
		*str = NULL;
	}
	return (NULL);
}
