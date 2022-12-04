# pimidiclock
## Send MIDI clock from raspberry Pi, measure jitter

Send MIDI clock of specific duration (seconds per bar) and measure average and standard deviation. Use it to test MIDI clock JITTER on your linux box.
This uses nanosleep function and non-busy sleep.