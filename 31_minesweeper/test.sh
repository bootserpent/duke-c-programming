rm *~
make
valgrindCmd='valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all'
#$valgrindCmd ./minesweeper 3 3 1 2>&1
#$valgrindCmd ./minesweeper 1 1 1 2>&1
#$valgrindCmd ./minesweeper 10 10 100 2>&1
$valgrindCmd ./minesweeper 10 10 10 2>&1
