# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sdemaude <sdemaude@student.42lehavre.fr>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/02/25 17:41:22 by sdemaude          #+#    #+#              #
#    Updated: 2024/03/18 13:42:05 by sdemaude         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= philo

CC 			= cc
RM			= rm -f

CFLAGS 		= -Wall -Wextra -Werror -fsanitize=address #-fsanitize=thread #-fsanitize=address 
CLINKS		= -pthread

SRCDIR		= src
SRCFILE		= main\
		  init\
		  routine\
			  philo\
			  philo_utils
			  
SRC 		= $(addprefix $(SRCDIR)/,$(addsuffix .c,$(SRCFILE)))

OBJDIR		= obj
OBJ 		= $(addprefix $(OBJDIR)/,$(addsuffix .o,$(SRCFILE)))

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir $(OBJDIR)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(CLINKS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ)
	$(RM) -r $(OBJDIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all

c: all clean

.PHONY:		all bonus clean fclean re c
