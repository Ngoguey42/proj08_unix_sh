#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ngoguey <ngoguey@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2014/11/04 11:28:17 by ngoguey           #+#    #+#              #
#    Updated: 2015/01/16 10:02:09 by ngoguey          ###   ########.fr        #
#                                                                              #
#******************************************************************************#

NAME = ft_minishell1

# LIBFT
LFTPATH = libft/
LFTIPATH = -I $(LFTPATH)includes/
LFT = -L $(LFTPATH) -lft

OBJPATH = obj
SRCPATH = .
INCLUDE = -I ./

CC = gcc

LIBS = $(LFT)
INCLUDES = $(INCLUDE) $(LFTIPATH)

BASEFLAGS = -Wall -Wextra
CFLAGS = $(BASEFLAGS) -Werror -O2
DEBUGFLAGS = $(BASEFLAGS) -g

LFTCALL = all
LFTRE = re
LFTG = g
LFTGRE = gre

SRCSFILES = main.c prompts.c init_msh.c environ.c msh_pause.c\
tokenize.c token_new.c\
token_checkerr.c\
\
cmds_get.c cmds_get_av.c cmds_get_cmd.c\
cmds_get_redir.c cmds_get_redir_pertype.c cmds_get_heredoc.c\
\
cmds_errprint.c\
cmds_exec.c cmds_exec_redir_in.c cmds_exec_redir_out.c cmds_exec_pipes.c\
signals.c\
\
builtins_cc.c builtins_cc_pipes.c builtins_cc_redirs.c\
builtin_env.c builtin_cd.c\
msh_debug.c msh_error.c msh_header.c

SRC = $(addprefix $(SRCPATH)/,$(SRCSFILES))
OBJECTS = $(SRC:$(SRCPATH)/%.c=$(OBJPATH)/%.o)

RM = rm -rf

Y = \033[0;33m
R = \033[0;31m
G = \033[0;32m
E = \033[39m

W = 0

all: l $(NAME)

$(NAME): $(OBJECTS)
	@echo -e "$(Y)[COMPILING SH] $(G) $(CC) -o $@ $(CFLAGS) objs.o $(LIBS) $(E)"
	$(CC) -o $@ $(CFLAGS) $(OBJECTS) $(INCLUDES) $(LIBS)
	@echo -e "$(Y)[COMPILING SH]$(E)"

$(OBJECTS): $(OBJPATH)/%.o : $(SRCPATH)/%.c
	@if [ $(W) -eq 0 ] ; then printf "$(R)%-10s$(E): %s\n$(R)%-10s$(E): %s\n$(R)%-10s$(E): %s\n$(R)%-10s$(E): %s\n"\
		"=>COMPILER"\
		"$(CC)"\
		"=>CFLAGS"\
		"$(CFLAGS)"\
		"=>INCLUDES"\
		"$(INCLUDES)"\
		"=>LIBS"\
		"$(LIBS)" ;\
	fi
	$(eval W = 1)
	@mkdir -p $(dir $@)
	@echo -e "$(R)COMPILER$(E) -o $@ $(R)CFLAGS INCLUDES LIBS$(E) -c [...].c"
	@$(CC) -o $@ $(CFLAGS) $(INCLUDES) $(LIBS) -c $<

clean:
	$(RM) $(OBJPATH)

fclean: clean
	$(RM) $(NAME)

l:
	@echo -e "$(Y)[COMPILING LIBFT] $(G) make -C $(LFTPATH) $(LFTCALL) $(E)"
	@$(MAKE) -C $(LFTPATH) $(LFTCALL)
	@echo -e "$(Y)[COMPILING LIBFT DONE]$(E)"

g: _g _gft all

# re rules
re: fclean all
rel: _relft l
rea: _relft re

# gre rules
gre: _g re
grel: _greft l
grea: _g _greft re

# eval rules
_g:
	$(eval CFLAGS = $(DEBUGFLAGS))
_relft:
	$(eval LFTCALL = $(LFTRE))
_gft:
	$(eval LFTCALL = $(LFTG))
_greft:
	$(eval LFTCALL = $(LFTGRE))
