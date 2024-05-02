NAME		=	ft_ls
SRC			=	main.c \
				parsing_args.c \
				sort.c	\
				free.c	\
				print_minus_l.c \
				utils.c
RM			=	rm -rf
SRC_PATH	=	./src/
OBJ_PATH	=	./obj/
OBJ_DIRS	=	${OBJ_PATH}
OBJ			=	${addprefix ${OBJ_PATH},${SRC:.c=.o}}
LIBFT		=	libft/libft.a
PROGRESS	=	🔁
CHECK		=	✅

all:${NAME}

clean:
	@echo -n "\e[2K\r- \33[36mCleaning objects\33[0m [${PROGRESS}]"
	@${RM} ${OBJ_PATH}
	@echo -n "\e[2K\r- \33[31mCleaning objects\33[0m [${CHECK}]\n"

fclean:clean
	@echo -n "\e[2K\r- \33[36mCleaning execution file\33[0m [${PROGRESS}]"
	@${RM} ${NAME}
	@make fclean --no-print-directory -C libft/
	@echo -n "\e[2K\r- \33[31mCleaning execution file\33[0m [${CHECK}]\n"

re:fclean
	@make --no-print-directory all

${LIBFT}:
	@echo -n "\e[2K\r- \33[36mCompilation libft\33[0m [${PROGRESS}]"
	@make --no-print-directory -C libft/
	@echo -n "\e[2K\r- \33[1;32mCompilation libft\33[0m [${CHECK}]\n"

${OBJ_PATH}%.o:${SRC_PATH}%.c
	@echo -n "\e[2K\r- \33[1;34m$<\33[0m [${PROGRESS}]"
	@gcc -O3 -Wall -Wextra -c $< -o $@
	@echo -n "\e[2K\r- \33[1;32m$<\33[0m [${CHECK}]\n"

${OBJ_DIRS}:
	@mkdir ${OBJ_DIRS}

${NAME}:${OBJ_DIRS} ${OBJ} ${LIBFT}
	@echo -n "\e[2K\r- Build \33[1;33m${NAME}\33[0m [${PROGRESS}]"
	@gcc -O3 ${OBJ} -o ${NAME} ${LIBFT}
	@echo -n "\e[2K\r- Build \33[1;32m${NAME}\33[0m [${CHECK}]\n"


.PHONY:all clean fclean re