if [ "$1" == "debug" ]; then
	make debug > /dev/null && ./debug.out
elif [ "$1" == "fsanitize" ]; then
	make fsanitize > /dev/null && ./fsanitize.out
elif [ "$1" == "e" ]; then
	gcc -E ./src/main.c -Iincludes
else
	make > /dev/null && ./a.out $@
fi
