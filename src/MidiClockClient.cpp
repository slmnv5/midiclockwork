#include "pch.hpp"
#include "MidiClockClient.hpp"
#include <stdio.h>
#include <time.h>

void MidiClockClient::run()
{
    LOG(LogLvl::DEBUG) << "Start prepare clock event, type: " << SND_SEQ_EVENT_CLOCK;
    float sleep_time = bar_time / 96;
    LOG(LogLvl::DEBUG) << "Prepared clock event, sleep time: " << sleep_time;

    long miliseconds = sleep_time * 1000;
    struct timespec rem;
    struct timespec req = {
        (int)(miliseconds / 1000),     /* secs (Must be Non-Negative) */
        (miliseconds % 1000) * 1000000 /* nano (Must be in range of 0 to 999999999) */
    };
    while (!ended)
    {
        send_event(&event_start);
        LOG(LogLvl::DEBUG) << "Wait to start MIDI clock for 2 sec.";
        sleep(2);
        while (!stopped)
        {
            LOG(LogLvl::DEBUG) << "Sent one bar of MIDI clock";
            for (int k = 0; k < 96; k++)
            {
                nanosleep(&req, &rem);
                send_event(&event_clock);
            }
        }
    }
    send_event(&event_stop);
}
