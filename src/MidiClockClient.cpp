#include "pch.hpp"
#include "lib/log.hpp"
#include "MidiClockClient.hpp"

using myclock = std::chrono::steady_clock;
using seconds = std::chrono::duration<double>;

int MidiClockClient::sleep(uint sleepMicro)
{
    if (mBusyPct == 0)
    {
        return usleep(sleepMicro);
    }
    else
    {
        auto stopAt = myclock::now() + std::chrono::microseconds(sleepMicro);
        int result = usleep(sleepMicro * mBusyPct / 100);
        do
        {
        } while (myclock::now() < stopAt);

        return result;
    }
}

void MidiClockClient::run()
{
    double sleepSec = mBarSeconds / 96;
    uint sleepMicro = sleepSec * 1.0E6;
    LOG(LogLvl::DEBUG) << "Prepared clock event, clock sleep time (ms): " << sleepSec * 1.0E3;

    while (!mStopped)
    {
        send_event(&mEvStart);
        LOG(LogLvl::DEBUG) << "MIDI clock running: " << !mStopped;
        auto begin = myclock::now();
        double sum, max, min;
        while (!mStopped)
        {
            sum = max = 0;
            min = 1.0E6;
            for (int k = 0; k < 96; k++)
            {
                this->sleep(sleepMicro);
                send_event(&mEvClock);
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
                               << "\taver. error (ms): " << (aver - sleepSec) * 1000
                               << "\tspread (ms): " << (max - min) * 1000;
        }
    }
    send_event(&mEvStop);
}
