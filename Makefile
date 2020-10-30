SRCS	= ./ft_printf.c
OBJS	= $(SRCS:.c=.o)
INCLUDE	= -I./
NAME	= libftprintf.a
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
LIBDIR	= ./libft/
LIBNAME = libft.a
LIB		= ./libft/libft.a

all		:	$(NAME)

.c.o	:
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME)	:	$(LIBNAME) $(OBJS)
			cp $(LIB) $(NAME)
			ar rc $(NAME) $(OBJS)

$(LIBNAME):
			make -C $(LIBDIR)

clean	:
			$(RM) $(OBJS)
			make clean -C $(LIBDIR)

fclean	:	clean
			$(RM) $(NAME)
			make fclean -C $(LIBDIR)

re		:	fclean all

.PHONY	:	all clean fclean re
