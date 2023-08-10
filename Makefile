NAME = libasm.a

NASM = nasm
NASM_FLAGS = -f elf64

SRCS	:= ft_strlen.s
OBJS	:= $(SRCS:.s=.o)

RESET	:= \033[0m
RED		:= \033[31m
GREEN	:= \033[32m

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(GREEN)=> Building $@$(RESET)"
	@ar rcs $(NAME) $(OBJS)

%.o: %.s
	@$(NASM) $(NASM_FLAGS) $<
	@echo "$(GREEN)✓ $@ compiled$(RESET)"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME) ./test

re: fclean all

run: all
	@cc -o ./test main.c -L. -lasm
	@echo "$(GREEN)=> Running tests$(RESET)"
	@./test
	@rm ./test

rerun: fclean run

.PHONY: all clean fclean re run rerun
