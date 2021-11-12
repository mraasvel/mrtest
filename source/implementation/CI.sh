python3 combine_files.py
gcc -Wall -Wextra -Werror -g3 -fsanitize=address mrtest.c easy_main.c -o ci.out && ./ci.out
