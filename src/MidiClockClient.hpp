#ifndef MIDICLOCKCLIENT_H
#define MIDICLOCKCLIENT_H
#include "pch.hpp"
#include "MidiClient.hpp"

class MidiClockClient : public MidiClient
{
private:
    double mBarSeconds = 2.0; // time for 1 bar is 2 seconds
    bool mStopped = false;
    bool mEnded = false;
    uint mBusyPct = 0;
    snd_seq_event_t mEvClock;
    snd_seq_event_t mEvStart;
    snd_seq_event_t mEvStop;

public:
    MidiClockClient(const char *clientName, const char *dstName) : MidiClient(clientName, nullptr, dstName)
    {
        snd_seq_ev_clear(&mEvClock);
        snd_seq_ev_clear(&mEvStart);
        snd_seq_ev_clear(&mEvStop);
        mEvClock.type = SND_SEQ_EVENT_CLOCK;
        mEvStart.type = SND_SEQ_EVENT_START;
        mEvStop.type = SND_SEQ_EVENT_STOP;
    }
    virtual ~MidiClockClient()
    {
    }
    int sleep(uint sleepMicro);
    void setBarSeconds(double barSeconds)
    {
        barSeconds = std::max(barSeconds, 0.05);
        barSeconds = std::min(barSeconds, 1000.0);
        this->mBarSeconds = abs(barSeconds);
    }
    double getBarSeconds() const
    {
        return this->mBarSeconds;
    }
    void setWaitBusyPct(uint busyPct)
    {
        busyPct = std::min(busyPct, 100U);
        this->mBusyPct = busyPct;
    }
    uint getWaitBusyPct()
    {
        return this->mBusyPct;
    }

    double getBpm() const
    {
        return 60 / this->mBarSeconds * 4;
    }
    void start()
    {
        mStopped = false;
        this->send_event(&mEvStart);
    }
    void stop()
    {
        mStopped = true;
        this->send_event(&mEvStop);
    }
    void end()
    {
        mEnded = true;
        stop();
    }
    void run(bool exact);
};

#endif
