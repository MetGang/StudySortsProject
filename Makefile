release:
	gcc main.c -std=c99 -Wall -Wextra -Wpedantic
	@ a.exe
debug:
	gcc main.c -std=c99 -Wall -Wextra -Wpedantic -DDBG
	@ a.exe