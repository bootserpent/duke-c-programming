make
valgrindCmd='valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all'
$valgrindCmd ./kv_test

