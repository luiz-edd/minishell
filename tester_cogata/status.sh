#!/bin/bash

STATUS=0
RESULT=$(diff status_result status_ref_file) 
if [ "$RESULT" ]; then
	STATUS=1
fi
echo $STATUS