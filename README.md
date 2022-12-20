# pimidiclock
## Send MIDI clock from Linux, measure jitter and delay

Send MIDI clock with specified frequency (given as seconds per bar) and measure average delay (actual-planned) and average spread (max-min) time between sent messages. This is used to test MIDI clock jitter and delay on Linux system.
Busy wait is a way to increase precision of wait time, it may be used with a paramter. 

Application creates input and output MIDI ports, optionally connects to another MIDI port to send clock signal.

![Sample output](demo.png)


Usage: ./pimidiclock -s <seconds_per_bar> [options]
  -b [busyPercent] percent of busy wait, optional
  -n [name] name of created MIDI port, optional
  -d [dstName] destination port to connect, optional
  -v verbose output
  -vv more verbose
  -vvv even more verbose
  -h displays this info




