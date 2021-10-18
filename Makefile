SRCSNAME=	ft_printf.c \
			flag/read_flag.c flag/print_flag.c flag/print_flag_utils.c \
			format/print_chars.c format/print_nbr.c format/print_nbr_utils.c
SRCSDIR	=	./srcs
SRCS	=	$(addprefix $(SRCSDIR)/, $(SRCSNAME))

OBJSNAME=	$(SRCSNAME:.c=.o)
OBJSDIR	=	./objs
OBJS	=	$(addprefix $(OBJSDIR)/, $(OBJSNAME))

INCLUDE	=	-I./includes
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
