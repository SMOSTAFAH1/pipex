/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shashemi <shashemi@student.42madrid.com>   #+#  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025-06-12 17:53:46 by shashemi          #+#    #+#             */
/*   Updated: 2025-06-12 17:53:46 by shashemi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <stdarg.h>

int		error_handler(int error_code, const char *arg);
int		execute_cmd(char *command_name, char **envp, int in_fd, int out_fd);
pid_t	execute_first(char *argv[], char **envp, int pipe_fd[2]);
pid_t	execute_second(char *argv[], char **envp, int pipe_fd[2]);
int		get_cmd_path(char **cmd_path, const char *cmd_name, char **envp);
char	**ft_split(const char *s, char c);
char	**ft_freestrarr(char ***arr);
char	*ft_freestr(char **str);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*ft_substr(char const *s, unsigned int start, size_t len);

#endif