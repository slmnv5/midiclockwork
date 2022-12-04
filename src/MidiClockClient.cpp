#include "pch.hpp"
#include "utils.hpp"
#include "MidiClockClient.hpp"

void MidiClockClient::run()
{
    snd_seq_event_t event;
    snd_seq_ev_clear(&event);
    event.type = SND_SEQ_EVENT_CLOCK;
    while (!ended)
    {
        LOG(LogLvl::DEBUG) << "Wait to start MIDI clock for 2 sec.";
        usleep(2000000);
        while (!stopped)
        {
            LOG(LogLvl::DEBUG) << "Sent one bar of MIDI clock";
            for (int k = 0; k < 96; k++)
            {
                usleep((sleep_time * 1000000.0));
                send_event(&event);
            }
        }
    }
    send_msg(0xFC);
}
