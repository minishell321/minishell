/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rburri <rburri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 07:32:37 by rburri            #+#    #+#             */
/*   Updated: 2022/03/01 18:05:44 by vbotev           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


// This function is meant to test how a table of strings could be created by having
// the first element in the table as the cmd and the remaining elements being the
// arg which correspond to this command
// !!! CURRENTLY THE FUNCTION HAS A BUG AND IS NOT CORRECTLY INCLUDING THE BUGS
// !!! ALSO AS IT IS MEANT AS A TEST IT ONLY HANDLES ONE COMMAND BUT THE CONCEPT CAN
// BE EXTENDED USING A LINKED LIST
int cmd_table(t_data *data)
{
	t_token *tmp;
	tmp = data->cmds;
	char	**cmd_table;
	int j = 0;
	int	cnt_cmd = 0;
	int cnt_arg = 0;

	while (tmp)
	{
		tmp = tmp->next;
		cnt_cmd++;
	}
	tmp = data->cmds;
	if (tmp->args)
	{
		t_token *tmp_arg;
		tmp_arg = tmp->args;
		while (tmp_arg)
		{
			tmp_arg = tmp_arg->next;
			cnt_arg++;
		}
	}
	printf("cnt_arg = %d\n", cnt_arg);
	cmd_table = (char **)malloc(sizeof(char *) * (cnt_arg + 2));
	cmd_table[0] = data->cmds->str;
	tmp = data->cmds->args;
	while (cnt_arg > 0)
	{
		cmd_table[cnt_arg--] = tmp->str;
		tmp = tmp->next;
	}
	cmd_table[cnt_arg + 1] = NULL;
	j = 0;
	while (cmd_table[j] != 0)
	{
		printf("cmd_table[%d] = %s\n", j, cmd_table[j]);
		j++;
	}



	/*
	while (tmp)
	{
		printf("cmd[%d]: %s\n", j, tmp->str);
		if (tmp->args)
		{
			t_token *tmp_arg;
			tmp_arg = tmp->args;
			int i = 0;
			while (tmp_arg)
			{
				printf("arg[%d]: %s\n", i, tmp_arg->str);
				tmp_arg = tmp_arg->next;
				i++;
			}
		}
		tmp = tmp->next;
		j++;
	}
	*/
	return (0);
}

int create_token(t_data *data, char *str, int type)
{
	t_token *new_token;
	new_token = malloc(sizeof(t_token));
	if (new_token == NULL)
		return (1);
	new_token->type = type;
	new_token->str = str;
	new_token->next = NULL;
	new_token->args = NULL;
	if (new_token->type == CMD)
	{
		new_token->next = data->cmds;
		data->cmds = new_token;
	}
	else if (new_token->type == ARG)
	{
		
		new_token->next = data->cmds->args;
		data->cmds->args = new_token;
	}
	printf("token type : %d\n", new_token->type);
	return (0);
}

char *send_quoted_string(char *str, int *i)
{
	char *new_str;
	int	j;
	int	k;
	
	j = 0;
	k = 1;
	while (str[j] != str[k])
		k++;
	new_str = (char *)malloc(sizeof(char) * ++k + 1);
	if (new_str == NULL)
		return (NULL);
	printf("QUOTED: k = %d\n", k);
	while (j <= k)
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j] = '\0';
	*i += (k);
	return (new_str);
}

char *send_unquoted_string(char *str, int *i)
{
	char *new_str;
	int	j;
	int	k;
	
	j = 0;
	k = 0;
	while (str[k] && str[k] != ' ')
		k++;
	printf("UNQUOTED: k = %d\n", k);
	new_str = (char *)malloc(sizeof(char) * k + 2);
	if (new_str == NULL)
		return (NULL);
	while (j <= k)
	{
		new_str[j] = str[j];
		j++;
	}
	new_str[j] = '\0';
	*i += (k );
	return (new_str);
}

int get_fd_out_append(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*fd_name;

	j = 0;
	k = 0;
	while (str[j] == '>' || str[j] == ' ')
		j++;
//	while (str[k] != ' ')
	while (str[k + j] != ' ')
		k++;
	*i += (j + k);
	/*
	fd_name = (char *)malloc(sizeof(char) * k + 1);
	if (fd_name == NULL)
		return (1);
	fd_name[k--] = '\0';
	while (k >= 0)
	{
		fd_name[k] = str[k];
		k--;
	}
	data->fd_output = open(fd_name, O_RDWR | O_APPEND, 0777);
	if (data->fd_output == -1)
	{
			free(fd_name);
			return (1);
	}
	free(fd_name);
	*/
	return (0);	
}

int get_fd_here_doc(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*delim;

	j = 0;
	k = 0;

	while (str[j] == '<' || str[j] == ' ')
		j++;
	while (str[k + j] != ' ')
		k++;
	*i += (j + k);
	delim = ft_substr(str, j, k);
	if (delim == 0)
		return (1);
	printf("HEREDOC delim = %s\n", delim);
	free(delim);
	return (0);
}

int get_fd_out(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*fd_name;

	j = 0;
	k = 0;
	printf("...str : %s\n", str);
	while (str[j] == '>' || str[j] == ' ')
		j++;
//	while (str[k] != ' ')
	while (str[k + j] != ' ')
		k++;
	*i += (j + k);
	/*
	fd_name = (char *)malloc(sizeof(char) * k + 1);
	if (fd_name == NULL)
		return (1);
	fd_name[k--] = '\0';
	while (k >= 0)
	{
	//	fd_name[k] = str[k];
		fd_name[k] = str[k + j];
		k--;
	}
	//	data->fd_output = open(str, O_RDWR | O_CREAT, 0777);
	data->fd_output = open(fd_name, O_RDWR | O_CREAT, 0777);
	if (data->fd_output == -1)
	{
			free(fd_name);
			return (1);
	}
	free(fd_name);
	*/
	return (0);	
}

int get_fd_in(t_data *data, char *str, int *i)
{
	int		j;
	int		k;
	char	*fd_name;

	j = 0;
	k = 0;
	while (str[j] == '<' || str[j] == ' ')
		j++;
//	while (str[k] != ' ')
	while (str[k + j] != ' ')
		k++;
	*i += (j + k);
	/*
	fd_name = (char *)malloc(sizeof(char) * k + 1);
	if (fd_name == NULL)
		return (1);
	fd_name[k--] = '\0';
	while (k >= 0)
	{
		fd_name[k] = str[k];
		k--;
	}
	data->fd_output = open(str, O_RDWR | O_CREAT, 0777);
	if (data->fd_output == -1)
	{
			free(fd_name);
			return (1);
	}
	free(fd_name);
	*/
	return (0);	
}

int	redir_out(t_data *data, char *str, int *i)
{
	int	j;
	
	j = 0;
	printf("^^^str = %s\n", str);
	if (str[j + 1] == '>')
	{
		if (get_fd_out_append(data, str, i))
			return (1);
	}
	else
	{
		if (get_fd_out(data, str, i))
			return (1);
	}
	return (0);
}

int	redir_in(t_data *data, char *str, int *i)
{
	int	j;
	
	j = 0;
	if (str[j + 1] == '<')
	{
		if (get_fd_here_doc(data, str, i))
			return (1);
	}
	else
	{
		if (get_fd_in(data, str, i))
			return (1);
	}
	return (0);
}

int	find_token(t_data *data, char *cmd_str)
{
	int	i;
	int type;

	type = 1;
	i = 0;
	while (cmd_str[i])
	{
		if (cmd_str[i] ==  ' ')
		{
			printf("******************i value before ++ %d\n", i);
			i++;
		}
		if (cmd_str[i] == '\'' || cmd_str[i] == '\"')
		{
			if (create_token(data, send_quoted_string(cmd_str + i, &i), type))
			{
				ft_putstr_fd("Error create token\n", 2);
				return (1);
			}
			type = 2;
		}
		else if (cmd_str[i] == '|')
		{
			type = 1;
			data->num_of_pipe += 1;
			i++;
		}
		else if (cmd_str[i] == '<')
		{
			//if (redir_out(data, cmd_str + i, &i))
			if (redir_in(data, cmd_str + i, &i))
			{
				ft_putstr_fd("Error redirection\n", 2);
			}
		}
		else if (cmd_str[i] == '>')
		{
			printf("---HERE--- i = %d; cmd_str = %s\n", i, cmd_str+i);
			//if (redir_in(data, cmd_str + i, &i))
			if (redir_out(data, cmd_str + i, &i))
			{
				ft_putstr_fd("Error redirection\n", 2);
			}
		}
		else if (cmd_str[i] == '$')
		{
			//do something
		}
		else 
		{
			if (create_token(data, send_unquoted_string(cmd_str + i, &i), type))
			{
				ft_putstr_fd("Error create token\n", 2);
				return (1);
			}
			type = 2;
		}
		// printf("******************i value before ++ %d\n", i);
		// i++;
	}
	if (cmd_table(data))
	{
		printf("Error: generation of command table\n");
		return (1);
	}
	return (0);
}

void print_token_stack(t_data *data)
{
	t_token *tmp;
	tmp = data->cmds;
	int j = 0;
	while (tmp)
	{
		printf("cmd[%d]: %s\n", j, tmp->str);
		if (tmp->args)
		{
			t_token *tmp_arg;
			tmp_arg = tmp->args;
			int i = 0;
			while (tmp_arg)
			{
				printf("arg[%d]: %s\n", i, tmp_arg->str);
				tmp_arg = tmp_arg->next;
				i++;
			}
		}
		tmp = tmp->next;
		j++;
	}
}
