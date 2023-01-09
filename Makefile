CC_OPT:=-Wall -Wextra -Werror
PROJ:="my_ls"

all:
	gcc ${CC_OPT} my_ls.c -o ${PROJ} 
