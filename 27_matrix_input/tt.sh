test=$1
valgrind -v --track-origins=yes --leak-check=full ./rotate $test
