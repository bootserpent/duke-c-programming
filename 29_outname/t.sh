FILE=$1
make
rm *.count
valgrind -v --track-origins=yes --leak-check=full ./outname $FILE
