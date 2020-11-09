build: greetings projetoshell
greetings:
	@echo "Seja bem-vindo ao meu shell, ./projetoshell o executará"
projetoshell: ProjetoShell.c
	gcc ProjetoShell.c -o projetoshell

