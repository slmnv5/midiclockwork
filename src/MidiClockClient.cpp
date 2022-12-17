#include "pch.hpp"
#include "MidiClockClient.hpp"
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <iomanip>
#include <chrono>

void MidiClockClient::run()
{
    float sleep_time = bar_time / 96;
    float sleep_time_ms = sleep_time * 1000;
    float sleep_time_us = sleep_time * 1000000;
    LOG(LogLvl::DEBUG) << "Prepared clock event, clock sleep time (ms): " << sleep_time_ms;

    while (!ended)
    {
        send_event(&event_start);
        LOG(LogLvl::DEBUG) << "MIDI clock running: " << !stopped;
        auto begin = std::chrono::steady_clock::now();
        double sum, sum2, max;
        while (!stopped)
        {
            sum = sum2 = max = 0;
            for (int k = 0; k < 96; k++)
            {
                usleep(sleep_time_us);
                send_event(&event_clock);
                auto end = std::chrono::steady_clock::now();
                std::chrono::duration<double> diff = end - begin;
                begin = end;
                auto secs = diff.count();
                max = std::max(max, abs(secs));
                sum += (secs);
                sum2 += (secs * secs);
            }
            auto aver = sum / 96;
            auto aver2 = sum2 / 96;
            auto stdev = sqrt(aver2 - aver * aver);
            LOG(LogLvl::DEBUG) << std::fixed << std::setprecision(3)
                               << "\taver. error (ms): " << (aver - sleep_time) * 1000
                               << "\tstd. dev (ms): " << stdev * 1000
                               << "\tmax (ms): " << max * 1000
                               << "\trel. error (%): " << (stdev / sleep_time * 100);
        }
    }
    send_event(&event_stop);
}
