/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olarseni <olarseni@student.42madrid.c      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:08:32 by olarseni          #+#    #+#             */
/*   Updated: 2025/09/21 23:08:48 by olarseni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_cmds(t_cmd *cmd_lst)
{
	int	count;

	count = 0;
	while (cmd_lst)
	{
		count++;
		cmd_lst = cmd_lst->next;
	}
	return (count);
}

static char	**args_to_argv(t_cmd *cmd)
{
	int		argc;
	t_args	*arg;
	char	**argv;
	int		i;

	argc = 0;
	arg = cmd->args;
	while (arg)
	{
		argc++;
		arg = arg->next;
	}
	argv = malloc(sizeof(char *) * (argc + 2));
	if (!argv)
		return (NULL);
	argv[0] = cmd->cmd_name;
	arg = cmd->args;
	i = 1;
	while (arg)
	{
		argv[i++] = arg->value;
		arg = arg->next;
	}
	argv[i] = NULL;
	return (argv);
}

static char *get_env_value(char **envp, const char *name)
{
    size_t len = ft_strlen(name);
	int i = 0;
	while (envp && envp[i])
	{
		if (ft_strncmp(envp[i], name, len) == 0 && envp[i][len] == '=')
			return envp[i] + len + 1;
		i++;
	}
    return NULL;
}

static char *find_executable_path(const char *cmd, char **envp)
{
	if (!cmd || !*cmd)
		return NULL;
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, X_OK) == 0)
			return ft_strdup(cmd);
		return NULL;
	}
	char *path_env = get_env_value(envp, "PATH");
	if (!path_env)
		return NULL;
		
	const char *p = path_env;
	while (*p)
	{
		const char *q = p;
		while (*q && *q != ':')
			q++;
		size_t dirlen = q - p;
		char *dir = malloc(dirlen + 1);
		if (!dir)
			return NULL;
		size_t i = 0;
		while (i < dirlen)
		{
			dir[i] = p[i];
			i++;
		}
		dir[dirlen] = '\0';
		size_t len = dirlen + ft_strlen(cmd) + 2;
		char *full_path = malloc(len);
		if (full_path)
		{
			size_t j = 0;
			while (j < dirlen)
			{
				full_path[j] = dir[j];
				j++;
			}
			full_path[j++] = '/';
			size_t k = 0;
			while (cmd[k])
			{
				full_path[j++] = cmd[k++];
			}
			full_path[j] = '\0';
			if (access(full_path, X_OK) == 0)
			{
				free(dir);
				return full_path;
			}
			free(full_path);
		}
		free(dir);
		if (*q == ':')
			p = q + 1;
		else
			break;
	}
	return NULL;
}

static int apply_redirections(t_redir *redirs)
{
    int fd;
    while (redirs)
    {
        if (redirs->type == REDIR_IN)
        {
            fd = open(redirs->file, O_RDONLY);
            if (fd < 0)
                return (-1);
            dup2(fd, 0);
            close(fd);
        }
        else if (redirs->type == REDIR_OUT)
        {
            fd = open(redirs->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd < 0)
                return (-1);
            dup2(fd, 1);
            close(fd);
        }
        else if (redirs->type == REDIR_APPEND)
        {
            fd = open(redirs->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (fd < 0)
                return (-1);
            dup2(fd, 1);
            close(fd);
        }
        redirs = redirs->next;
    }
    return (0);
}

void	ft_execute(t_sh *shell)
{
	int		n_cmds;
	int		i;
	int		k;
	int		prev_fd;
	int		pipefd[2];
	pid_t	*pids;
	t_cmd	*cmd;

	n_cmds = count_cmds(shell->cmd_lst);
	i = 0;
	prev_fd = -1;
	pids = malloc(sizeof(pid_t) * n_cmds);
	cmd = shell->cmd_lst;
	while (cmd)
	{
		if (cmd->next)
			pipe(pipefd);
		pid_t pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (cmd->next)
			{
				close(pipefd[0]);
				dup2(pipefd[1], 1);
				close(pipefd[1]);
			}
			if (apply_redirections(cmd->redirs) < 0)
			{
				write(2, "minishell: redirection error\n", 28);
				exit(1);
			}
			char **argv = args_to_argv(cmd);
			char **envp = ft_env_to_arr(shell->env);
			if (!argv || !envp)
				exit(1);
			char *exec_path = find_executable_path(cmd->cmd_name, envp);
			if (!exec_path)
			{
				write(2, cmd->cmd_name, ft_strlen(cmd->cmd_name));
				write(2, ": command not found\n", 20);
				k = 0;
				while (envp[k]) {
					free(envp[k]);
					k++;
				}
				free(envp);
				exit(127);
			}
			execve(exec_path, argv, envp);
			perror("execve");
			free(exec_path);
			k = 0;
			while (envp[k]) {
				free(envp[k]);
				k++;
			}
			free(envp);
			exit(1);
		}
		else if (pid < 0)
			perror("fork");
		pids[i++] = pid;
		if (prev_fd != -1)
			close(prev_fd);
		if (cmd->next)
		{
			close(pipefd[1]);
			prev_fd = pipefd[0];
		}
		cmd = cmd->next;
	}
	if (prev_fd != -1)
		close(prev_fd);
	int status = 0;
	shell->last_exit_status = 0;
	int j = 0;
	while (j < n_cmds)
	{
		waitpid(pids[j], &status, 0);
		if (shell->last_exit_status == 0 && status != 0)
			shell->last_exit_status = status;
		j++;
	}
	free(pids);
}
