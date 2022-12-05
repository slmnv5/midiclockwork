# pimidiclock
## Send MIDI clock from raspberry Pi, measure jitter and delay

Send MIDI clock with specified frequency (given as seconds per bar) and measure average and standard deviation of time between them. Use it to test MIDI clock jitter and delay on your Linux system or as a prototype for MIDI clock generator.

This application creates input and output MIDI ports with given name, optionally connects to some other MIDI port to send MIDI clock messages.
Then it starts generating MIDI clock messages for given bar length in seconds (BPM is displayed on screen). It measures and displays actual time intervals, report average, standard deviation and their ratio for every bar. 



![Alt text](./MIDI_demo.png  "Example")


