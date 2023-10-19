dollar:
	clean
	gcc -g transform_dollar.c /home/shhuang/Desktop/mishell-fedmarti/var3.c /home/shhuang/Desktop/mishell-fedmarti/var.c -o dollar -L/home/shhuang/Desktop/mishell-fedmarti/libft -lft

command: command_list_new.c
	make clean && gcc -g command_list_new.c /home/shhuang/Desktop/mishell-fedmarti/var3.c /home/shhuang/Desktop/mishell-fedmarti/var.c -o command -L/home/shhuang/Desktop/mishell-fedmarti/libft -lft

all: command_list_new.c transform_dollar.c
	make clean && gcc -g transform_dollar.c command_list_new.c /home/shhuang/Desktop/mishell-fedmarti/var3.c /home/shhuang/Desktop/mishell-fedmarti/var.c -o final -L/home/shhuang/Desktop/mishell-fedmarti/libft -lft

clean:
	rm -f command
	rm -f dollar