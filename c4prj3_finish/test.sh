rm *~
make
valgrindCmd='valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all'
$valgrindCmd ./poker ./provided-tests/test14.txt 2>&1
