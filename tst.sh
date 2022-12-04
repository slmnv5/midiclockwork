#!/bin/bash

# prepare all
aconnect -x
killall -9 pimidiclock
sleep 1

# start this app.
./pimidiclock_d -n aaaabbbb -d Sshpadnew -b 121.55 -vvv


