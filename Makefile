NAME = libasm.a

NASM = nasm
NASM_FLAGS = -f elf64

SRCS = ft_strcpy.s ft_strlen.s
OBJS = $(SRCS:.s=.o)

all: $(NAME)
	echo "Compiling..."

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

%.o: %.s
	$(NASM) $(NASM_FLAGS) $<

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) ./test

re: fclean all

run: all
	echo "Running..."
	cc -o test main.c -L. -lasm
	./test

.PHONY: all clean fclean re run

.SILENT: all run