make clean
make

valgrindCmd='valgrind -v --track-origins=yes --leak-check=full --show-leak-kinds=all
'
echo
echo "testing stdin"
printf "%s\n%s\n%s\n" "This is a sample test case" "it checks your program's one argument behavior" "go!" | tee | $valgrindCmd ./sortLines
echo
echo "testing with 1 file"
$valgrindCmd ./sortLines input1.txt
echo
echo "testing with 2 files"
$valgrindCmd ./sortLines input1.txt input2.txt
echo
echo "testing no newline EOF file"
$valgrindCmd ./sortLines inputeof.txt
echo
echo "testing with very long files"
$valgrindCmd ./sortLines toomanylines.txt
