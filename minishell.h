/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: spitt <spitt@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/06 15:51:06 by mmonte            #+#    #+#             */
/*   Updated: 2021/04/07 18:06:24 by spitt            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <string.h>
# include <signal.h>
# include <errno.h>
# include <curses.h>
# include <term.h>
# include "./libft/libft.h"

# define BUFFER_SIZE 1

typedef enum		e_codes
{
	SUCCESS,
	EXIT,
	MALLOC
}					t_codes;

typedef struct		s_rdir
{
	char			*sc;
	char			**arg;
	int				dir;
	int				into_arg;
	char			**com;
	int				into_com;
	struct s_rdir	*next;
}					t_rdir;

typedef struct		s_pipe
{
	t_rdir			*redir;
	t_rdir			*act_rd;
	struct s_pipe	*next;
}					t_pipe;

typedef struct		s_job
{
	t_pipe			*pipe;
	t_pipe			*act_pip;
}					t_job;

typedef struct		s_main
{
	t_job			*job;
	t_list			*lexer;
	t_list			*current_lexer;
	t_rdir			*current_command;
	char			*hstry[1100];
	int				sum_hstry;
	int				dir_hstry[2];
	int				fd[2];
	int				rfd[2];
	int				temp0fd;
	int				c_hstry;
	char			**envp;
	char			*name_shell;
	char			*str;
	int				cursor;
	int				ap_flag;
	int				dap_flag;
	int				car;
	int				rdir_acc;
	int				exit;
	int				n_count;
	int				err;
	int				pid;
	struct termios	term;
}					t_main;

t_main				*g_mn;

int					executer(t_main *mn);
void				check_var_export(t_main *mn, char *arg);
void				error_cmd(t_main *mn, t_rdir *rdir, int dir);
void				errno_cmd(t_main *mn);
int					validate_var_str(char *arg, int eq);
int					external_funcs(t_main *mn, t_pipe *piptmp);
void				exec_redirs(t_main *mn, t_pipe *piptmp);
int					buildin_funcs(t_main *mn, t_pipe *piptmp);
void				run_unset(t_main *mn, t_pipe *piptmp);
int					run_export(t_main *mn, t_pipe *piptmp);
void				run_env(t_main *mn, int export);
int					run_cd(t_main *mn, t_rdir *rdir);
void				run_echo(t_main *mn, t_pipe *piptmp);
char				*search_env(t_main *mn, char *var);
void				addnew_env(t_main *mn, char *arg);
int					search_env_index(t_main *mn, char *var);
void				print_export(char **arr);
void				ft_exit(t_main *mn, t_pipe *piptmp, int status);
int					ft_isspace(char c);
char				**addtoarr(char **arr, char *str);
int					count_all_args(t_pipe *piptmp);
int					ft_symbols(char s);
int					ft_strisdigit(char *str);
void				*ft_null_error(int s, t_main *mn, void *str);
int					ft_errors(int s);
int					ft_error_sschar(char **str, int i, char *s);
void				error_var(t_main *mn, char *cmd, char *arg);
int					ft_error_tocken(t_main *mn, int sig, char *c);
int					get_next_line(int fd, t_main *mn);
int					get_next_line_classic(int fd, char **line);
void				ft_signal(int sig);
void				ft_quit(int sig);
int					lexer_parser(t_main *mn);
int					ft_check_tockens(t_main *mn);
int					ft_cmp_after_while(t_main *mn, int last_char);
int					ft_new_line_write(t_main *mn, int last_char);
int					parser_shell(t_main *mn);
int					redirect_searcher(t_main *mn, char *str, t_job **new_job);
t_list				*ft_string_rewriter(t_main *mn);
int					ft_the_razdelitel(int c);
int					ft_specsymb_searcher(int c);
int					ft_print_symbs(int c);
int					ft_lenght_new_string(t_main *mn);
int					ft_from_env_len(t_main *mn);
int					ft_write_new_string(t_main *mn,
							t_list **lst, int len, char *str);
int					ft_from_env_write(t_main *mn, int len, char *src);
void				ft_more_elements_history(t_main *mn);
void				ft_elements_history(t_main *mn);
int					ft_create_hstry_in_main(t_main *mn);
void				ft_refresh_hstry(t_main *mn);
void				ft_save_history(t_main *mn);
int					ft_int(int i);
void				ft_canon_mode(void);
void				ft_noncanon_mode(void);
int					ft_specsymb_operator(t_main *mn, char *buff, int fd_r);
t_job				*ft_job_creater(t_main *mn, char *str);
int					ft_job_clear(t_job **lst, int sig);
t_pipe				*ft_pipe_creater(t_main *mn, char *str);
t_pipe				*ft_pipelast(t_pipe *lst);
void				ft_pipe_addback(t_pipe **lst, t_pipe *ft_new);
void				ft_pipe_clear(t_pipe **lst);
t_rdir				*ft_rdir_creater(t_main *mn, char *str);
t_rdir				*ft_rdirlast(t_rdir *lst);
void				ft_rdir_addback(t_rdir **lst, t_rdir *ft_new, t_main *mn);
void				ft_rdir_clear(t_rdir **lst, int i);
void				ft_search_vol_bucks(int *i, char *src);
int					ft_err_with_free(int i, char *s);

#endif
