KEY=$1
FILE=$2
valgrind -v --track-origins=yes --leak-check=full ./encrypt $KEY $FILE
