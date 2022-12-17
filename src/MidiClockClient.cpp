#include "pch.hpp"
#include "lib/log.hpp"
#include "MidiClockClient.hpp"

using myclock = std::chrono::steady_clock;
using seconds = std::chrono::duration<double>;

void MidiClockClient::run()
{
    double sleep_time = bar_time / 96;
    uint sleep_time_s = std::ceil(sleep_time);
    uint sleep_time_ns = (sleep_time - sleep_time_s) * 10E9;
    struct timespec sleep = {
        sleep_time_s, /* secs (Must be Non-Negative) */
        sleep_time_ns /* nano (Must be in range of 0 to 999,999,999) */
    };

    LOG(LogLvl::DEBUG) << "Prepared clock event, clock sleep time (ms): " << sleep_time * 1000;

    while (!ended)
    {
        send_event(&event_start);
        LOG(LogLvl::DEBUG) << "MIDI clock running: " << !stopped;
        auto begin = myclock::now();
        double sum, max, min;
        while (!stopped)
        {
            sum = max = 0;
            min = 99999999999999;
            for (int k = 0; k < 96; k++)
            {
                nanosleep(&sleep, &sleep);
                send_event(&event_clock);
                auto end = myclock::now();
                seconds diff = end - begin;
                begin = end;
                auto secs = diff.count();
                max = std::max(max, abs(secs));
                min = std::min(min, abs(secs));
                sum += (secs);
            }
            auto aver = sum / 96;
            LOG(LogLvl::DEBUG) << std::fixed << std::setprecision(3)
                               << "\taver. error (ms): " << (aver - sleep_time) * 1000
                               << "\tspread (ms): " << (max - min) * 1000;
        }
    }
    send_event(&event_stop);
}
