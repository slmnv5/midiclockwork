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
    int sleep(bool exactTime, uint sleepMicro);
    void setBarTime(float bar_time)
    {
        this->mBarSeconds = abs(bar_time);
    }
    float getBarTime() const
    {
        return this->mBarSeconds;
    }
    float getBpm() const
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
