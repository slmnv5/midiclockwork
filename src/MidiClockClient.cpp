#include "pch.hpp"
#include "MidiClockClient.hpp"
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <math.h>

void MidiClockClient::run()
{
    LOG(LogLvl::DEBUG) << "Start prepare clock event, type: " << SND_SEQ_EVENT_CLOCK;
    float sleep_time = bar_time / 96;
    LOG(LogLvl::DEBUG) << "Prepared clock event, sleep time: " << sleep_time;

    long miliseconds = sleep_time * 1000;
    struct timespec req = {
        (int)(miliseconds / 1000),     /* secs (Must be Non-Negative) */
        (miliseconds % 1000) * 1000000 /* nano (Must be in range of 0 to 999999999) */
    };
    while (!ended)
    {
        send_event(&event_start);
        LOG(LogLvl::DEBUG) << "Wait to start MIDI clock for 2 sec.";

        auto begin = std::chrono::steady_clock::now();
        long sum, sum2;
        while (!stopped)
        {
            sum = sum2 = 0;
            for (int k = 0; k < 96; k++)
            {
                nanosleep(&req, nullptr);
                send_event(&event_clock);
                auto end = std::chrono::steady_clock::now();
                auto diff = (end - begin).count();
                begin = end;
                sum += (diff);
                sum2 += (diff * diff);
            }
            int sdev = sqrt(sum2 / (96 - 1));
            int aver = sum / 96;
            LOG(LogLvl::DEBUG) << "Time in ms. aver: " << aver << " std.dev.:" << sdev;
        }
    }
    send_event(&event_stop);
}
