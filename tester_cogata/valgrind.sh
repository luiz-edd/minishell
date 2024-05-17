#!/bin/bash

STATUS=0
VALGRIND_LOG=valgrind.log
valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=../readline.supp --log-file=$VALGRIND_LOG ../minishell < file > /dev/null
VALGRIND_STATUS=$(cat $VALGRIND_LOG)
if [ "$VALGRIND_STATUS" ]; then
	STATUS=1
fi
echo $STATUS
# rm -f $VALGRIND_LOG