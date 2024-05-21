#!/bin/bash

STATUS=0
./minishell < file > outfile_final 2>&1
grep -v "minishell>" outfile_final | head -n -1 > result
grep -v "minishell>" outfile_final | tail -n 1  > status_result
RESULT=$(diff result ref_file) 
if [ "$RESULT" ]; then
	STATUS=1
fi
echo $STATUS