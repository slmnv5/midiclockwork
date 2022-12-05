# pimidiclock
## Send MIDI clock from raspberry Pi, measure jitter and delay

Send MIDI clock with specified frequency (given as seconds per bar) and measure average and standard deviation of time between them. Use it to test MIDI clock jitter and delay on your Linux system or as a prototype for MIDI clock generator.

This application creates input and output MIDI ports with given name, optionally connects to some other MIDI port to send MIDI clock messages.
Then it starts generating MIDI clock messages for given bar length in seconds (BPM is displayed on screen). It measures and displays actual time intervals, report average, standard deviation and their ratio for every bar. 

Example:

 ./pimidiclock  -n testMidi -d Sshpadnew -b 1.000 -vvv
INFO: MIDI clock client name: testMidi
INFO: MIDI ports created: IN=129:0 OUT=129:1
INFO: Found MIDI: Sshpadnew -- 128:0
INFO: Connected to MIDI port: Sshpadnew output 128:0
INFO: Starting MIDI clock, bar time: 1,  BPM: 240
DEBUG: Prepared clock event, clock sleep time, seconds: 0.0104167
DEBUG: MIDI clock running: 1
DEBUG: Average: 0.010209 std. dev: 9.2554e-05 variability ratio: 0.00906589
DEBUG: Average: 0.0100922 std. dev: 2.14905e-05 variability ratio: 0.00212942