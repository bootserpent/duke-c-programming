rm *~
make
valgrindCmd='valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all'
#$valgrindCmd ./minesweeper 3 3 1 2>&1
#$valgrindCmd ./minesweeper 1 1 1 2>&1
#printf "%d\n%d\n%s\n%d\n%d\n%s" 7 7 "yes" 9 0 "no" | $valgrindCmd ./minesweeper 10 10 100 2>&1
printf "%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%s" 0 0 9 0 9 0 0 9 "no" | $valgrindCmd ./minesweeper 10 10 10 2>&1
