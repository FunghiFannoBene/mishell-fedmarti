dollar:
	clean
	gcc -g transform_dollar.c ../var3.c ../var.c -o dollar -L../libft -lft

command: command_list_new.c
	make clean && gcc -g command_list_new.c ../var3.c ../var.c -o command -L../libft -lft

all: command_list_new.c transform_dollar.c
	make clean && gcc -g transform_dollar.c command_list_new.c ../var3.c ../var.c -o final -L../libft -lft

clean:
	rm -f command
	rm -f dollar