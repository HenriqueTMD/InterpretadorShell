# InterpretadorShell
Henrique Thalison - 5983
Thiago Ferreira - 5991

>>Bugs conhecidos:

Caso na linha de comando tenha a palavra quit o programa é encerrado, ou seja os seguintes comandos enceram o programa sem executar qualquer comando, mesmo que valido, na linha:

ls, quit

quit, ls

touch quit.txt

quit

Caso na linha de comando tenham comandos com apenas argumentos " " ocorrera um erro no qual os comandos validos na linha podem não ser executados. Por exemplo:

ls, , , , , ,ls

 , cat file , grep foo file2
 
cat file , , grep foo file2

>>Passo a passo de como executar:

Abra o terminal.

Entre na pasta que contenha os arquivos contidos no '.zip'.

Execute o comando 'make'.

Siga as instruções gerada pelo arquivo make.

>>Alguns exemplos de comandos funcionais:

ls

ls -ll -la

cd documentos

ls, touch exemplo.txt

cat ProjetoShell.c

grep include ProjetoShell.c

ls,,,,,,,,,ls

,cat file , grep foo file2

cat file ,, grep foo file2




