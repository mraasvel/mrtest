if [ "$1" == "debug" ]; then
	make debug > /dev/null && ./debug.out
elif [ "$1" == "fsanitize" ]; then
	make fsanitize > /dev/null && ./fsanitize.out
else
	make > /dev/null && ./a.out $@
fi
