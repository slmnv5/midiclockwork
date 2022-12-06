#include "pch.hpp"
#include "MidiClockClient.hpp"
#include <stdio.h>
#include <time.h>
#include <chrono>
#include <math.h>

void MidiClockClient::run()
{
    float sleep_time = bar_time / 96;
    LOG(LogLvl::DEBUG) << "Prepared clock event, clock sleep time, seconds: " << sleep_time;
    long int miliseconds = sleep_time * 1000;
    struct timespec req = {
        int(sleep_time),               /* secs (Must be Non-Negative) */
        (miliseconds % 1000) * 1000000 /* nano (Must be in range of 0 to 999999999) */
    };
    while (!ended)
    {
        send_event(&event_start);
        LOG(LogLvl::DEBUG) << "MIDI clock running: " << !stopped;
        auto begin = std::chrono::steady_clock::now();
        double sum, sum2;
        while (!stopped)
        {
            sum = sum2 = 0;
            for (int k = 0; k < 96; k++)
            {
                nanosleep(&req, nullptr);
                send_event(&event_clock);
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> diff = end - begin;
                begin = end;
                auto secs = diff.count();
                sum += (secs);
                sum2 += (secs * secs);
            }
            auto aver = sum / 96;
            auto aver2 = sum2 / 96;
            auto stdev = sqrt(aver2 - aver * aver);
            LOG(LogLvl::DEBUG) << "\taverage delay (ms): " << (aver - sleep_time) * 1000
                               << "\tstd. dev (ms): " << stdev * 1000
                               << "\tratio (%): " << (stdev / sleep_time * 100);
        }
    }
    send_event(&event_stop);
}
