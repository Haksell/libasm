NAME := libasm.a
HEADER := libasm.h
TEST := test

PATH_SRCS := srcs
PATH_OBJS := objs

FILENAMES := $(notdir $(basename $(wildcard $(PATH_SRCS)/*.s)))
FILENAMES_NO_BONUS := $(filter-out %_bonus, $(FILENAMES))

ifeq ($(MAKECMDGOALS),all)
	FILENAMES := $(FILENAMES_NO_BONUS)
endif
ifeq ($(MAKECMDGOALS),)
	FILENAMES := $(FILENAMES_NO_BONUS)
endif

SRCS := $(addprefix $(PATH_SRCS)/, $(addsuffix .s, $(FILENAMES)))
OBJS := $(addprefix $(PATH_OBJS)/, $(addsuffix .o, $(FILENAMES)))

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling..."
	ar rcs $(NAME) $(OBJS)

$(PATH_OBJS):
	@mkdir $(PATH_OBJS)

$(OBJS): $(PATH_OBJS)/%.o: $(PATH_SRCS)/%.s $(HEADER) | $(PATH_OBJS)
	nasm -f elf64 $< -o $@

clean:
	rm -rf $(PATH_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST)

re: fclean all

test: bonus
	@echo "Testing..."
	cc -fsanitize=address,undefined -o $(TEST) main.c -L. -lasm
	@echo "========================================"
	@./$(TEST)

retest: fclean test