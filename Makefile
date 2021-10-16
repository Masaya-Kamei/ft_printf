SRCSDIR	=	.
SRCSNAME=	ft_printf.c print_cs.c print_pdiux.c
SRCS	=	$(addprefix $(SRCSDIR)/, $(SRCSNAME))

OBJSDIR	=	./objs
OBJSNAME=	$(SRCSNAME:.c=.o)
OBJS	=	$(addprefix $(OBJSDIR)/, $(OBJSNAME))

INCLUDE	=	-I./
NAME	=	libftprintf.a

CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror
AR		=	ar rc
RM		=	rm -f

LIBFTDIR    := ./libft
LIBFTTARGET	:= all
LIBFT		:= ./libft/libft.a

LIBINCLUDEDIR	:= -I./libft
LIBDIR      	:= -L${LIBFTDIR}
LIBLINK			:= -lft
LIB				:= $(LIBINCLUDEDIR) $(LIBDIR) $(LIBLINK)

all		:	$(NAME)

$(NAME)	:	$(LIBFT) $(OBJS)
			cp $(LIBFT) $(NAME)
			$(AR) $(NAME) $(OBJS)

$(OBJSDIR)/%.o	:	$(SRCSDIR)/%.c
			@mkdir -p $(dir $@)
			$(CC) $(CFLAGS) $(INCLUDE) $(LIBINCLUDEDIR) -o $@ -c $<

$(LIBFT):
			make -C $(LIBFTDIR) $(LIBFTTARGET)

clean	:
			$(RM) $(OBJS)
			make -C $(LIBFTDIR) clean

fclean	:	clean
			$(RM) $(NAME)
			make -C $(LIBFTDIR) fclean

re		:	fclean all

address	:	LIBFTTARGET	=	address
address	:	CC			=	clang
address	:	CFLAGS 		+= 	-g -fsanitize=address
address	:	re

leak	:	LIBFTTARGET	=	leak
leak	:	CC			=	clang
leak	:	CFLAGS		+= 	-g -fsanitize=leak
leak	:	re

.PHONY	:	all clean fclean re address leak
