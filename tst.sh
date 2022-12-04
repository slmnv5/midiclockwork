#!/bin/bash

# prepare all
aconnect -x
killall -9 pimidiclock_d
sleep 1

# start this app.
./pimidiclock_d  -d Sshpadnew -b 120.00 -vvv


