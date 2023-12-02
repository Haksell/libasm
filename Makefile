LIB		:= libasm.a
TEST	:= test
S		:= srcs
O		:= objs
SRCS	:= $(wildcard $S/*.s)
OBJS	:= $(SRCS:$S/%.s=$O/%.o)

PATH_SRCS := srcs
PATH_OBJS := objs

FILENAMES := $(notdir $(basename $(wildcard $(PATH_SRCS)/*.s)))
SRCS := $(addprefix $(PATH_SRCS)/, $(addsuffix .s, $(FILENAMES)))
OBJS := $(addprefix $(PATH_OBJS)/, $(addsuffix .o, $(FILENAMES)))

all: $(NAME)

$(NAME): $(OBJS)
	@echo "Compiling..."
	ar rcs $(NAME) $(OBJS)

$(PATH_OBJS):
	@mkdir $(PATH_OBJS)

$(OBJS): $(PATH_OBJS)/%.o: $(PATH_SRCS)/%.s | $(PATH_OBJS)
	nasm -f elf64 $< -o $@

clean:
	rm -rf $(PATH_OBJS)82cda007297423217eb

fclean: clean
	rm -rf $(LIB) $(TEST)

re: fclean all

run: all
	@echo "Running..."
	cc -fsanitize=address,undefined -o test main.c -L. -lasm
	@echo "========================================"
	@./test

rerun: fclean run
