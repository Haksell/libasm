# all: $(LIB)

# $(LIB): $(OBJS)
# 	@echo "$(GREEN)=> Building $@$(RESET)"
# 	@ar rcs $(LIB) $(OBJS)

# %.o: %.s
# 	@$(NASM) $(NASM_FLAGS) $<
# 	@echo "$(GREEN)✓ $@ compiled$(RESET)"

# .PHONY: all clean fclean re run rerun

LIB		:= libasm.a
TEST	:= test
S		:= srcs
O		:= objs
SRCS	:= $(wildcard $S/*.s)
OBJS	:= $(SRCS:$S/%.s=$O/%.o)

RESET	:= \033[0m
GREEN	:= \033[1m\033[32m

all: $(LIB)

$O:
	@mkdir -p $O

$O/%.o: $S/%.s | $O
	@nasm -f elf64 $< -o $@
	@echo "$(GREEN)✓ $@ compiled$(RESET)"

$(LIB): $(OBJS)
	@ar rcs $@ $^
	@echo "$(GREEN)=> $@ compiled$(RESET)"

clean:
	rm -rf $O

fclean: clean
	rm -rf $(LIB) $(TEST)

re: fclean all

run: all
	@cc -o ./test main.c -L. -lasm
	@echo "$(GREEN)=> Running tests$(RESET)"
	@./test
	@rm ./test

rerun: fclean run

.PHONY: all clean