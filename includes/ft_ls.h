/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abureau <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/17 15:39:42 by abureau           #+#    #+#             */
/*   Updated: 2016/10/17 15:45:19 by abureau          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef _FT_LS_H
# define _FT_LS_H
# include <unistd.h>
# include "../libft/includes/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <dirent.h>
# include <sys/stat.h>

typedef unsigned long long	t_64;
typedef struct dirent		t_dir;

typedef struct			s_arglist{
	unsigned int		state : 3;
	char				*name;
	unsigned long long	size;
	struct stat			st;
	struct s_arglist	*content;
	struct s_arglist	*next;
	DIR			*dir;
}						t_larg;

typedef struct			s_lsparam{
	unsigned int		option : 5;
	t_larg				*l_arg;
}						t_ls;

void					recur_statement(int *state, t_larg **tmp, DIR **dir);
t_larg					*time_sort(t_larg **data);
t_larg					*revalpha_sort(t_larg **data);
t_larg					*alpha_sort(t_larg **data);
t_larg					*swap_e(t_larg *begin, t_larg **prev);
t_larg					*swap_elem(t_larg *begin, t_larg *prev);
t_larg					*l_mod2(t_larg *begin, void (*func)(t_larg*), int sta);
t_larg					*init_elem(char *str, DIR **dir);
t_larg					*sort_first(t_larg *begin);
t_larg					*sort(t_larg **data, int state);
char					*standardize(char *str);
char					*ft_lltoa_base(t_64 value, unsigned int base, int sig);
char					*secure_cat(char *dest, char *str);
void					size_setter(t_larg **data);
void					fold_a(t_larg *file);
void					print_type(t_larg *file);
void					print_perm(t_larg *file);
void					print_content(t_larg **data, t_larg **prev);
void					print_elem(t_larg *fold, t_larg *file);
void					print_fold(char *str);
void					p_date(char *str);
void					print_size(unsigned long long size);
void					ft_swap(t_larg **begin);
void					l_sort_revalpha(t_larg *elem);
void					l_sort_alpha(t_larg *elem);
void					l_sort_time(t_larg *elem);
void					l_mod(t_larg **begin, void (*func)(t_larg*));
void					option_parser(char *str, t_ls *option);
void					arg_parser(int nbarg, char **str);
void					l_f_mod(t_larg **begin);
void					read_content(t_larg **begin);
void					non_recursiv_read(t_larg **begin);
void					p_error(char *str);
void					init_p_error(t_larg **tmp, char *str);
void					size_content(t_larg **begin);
void					size_cho(t_larg **tmp);
void					non_recursiv_size(t_larg **begin);
int						is_sort(char *s1, char *s2);
int						is_sort_t(struct stat st1, struct stat st2);
int						is_list_sort_t(t_larg **begin);
int						is_list_sort_ra(t_larg **begin);
int						is_list_sort(t_larg **begin);
unsigned int			set_option(unsigned int option, int state);
unsigned long long		push_file(t_larg **l_arg, char *str, int state);
unsigned long long		init_file(t_larg **l_arg, char *str, int state);
int				t_s(t_larg *tmp, t_larg *tnext);
#endif
