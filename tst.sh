#!/bin/bash

# prepare all
aconnect -x
killall -9 pimidiclock
sleep 1

# start this app.
pimidiclock -n aaaabbbb -d sss -b 121.55 $@  &


