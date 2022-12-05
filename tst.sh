#!/bin/bash

# prepare all
aconnect -x
killall -9 pimidiclock

# start this app. bar length = 2.000 seconds
./pimidiclock_d  -d Sshpadnew -b 2.000 -vvv


