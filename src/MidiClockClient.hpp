#ifndef MIDICLOCKCLIENT_H
#define MIDICLOCKCLIENT_H
#include "pch.hpp"
#include "MidiClient.hpp"

class MidiClockClient : public MidiClient
{
private:
    float bar_time = 2.0; // time for 1 bar is 2 seconds
    bool stopped = false;
    bool ended = false;
    snd_seq_event_t event_clock;
    snd_seq_event_t event_start;
    snd_seq_event_t event_stop;

public:
    MidiClockClient(const char *clientName, const char *dstName) : MidiClient(clientName, nullptr, dstName)
    {
        snd_seq_ev_clear(&event_clock);
        snd_seq_ev_clear(&event_start);
        snd_seq_ev_clear(&event_stop);
        event_clock.type = SND_SEQ_EVENT_CLOCK;
        event_start.type = SND_SEQ_EVENT_START;
        event_stop.type = SND_SEQ_EVENT_STOP;
    }
    virtual ~MidiClockClient()
    {
    }
    void set_bar_time(float bar_time)
    {
        this->bar_time = abs(bar_time);
    }
    float get_bar_time() const
    {
        return this->bar_time;
    }
    float get_bpm() const
    {
        return 60 / this->bar_time * 4;
    }
    void start()
    {
        stopped = false;
        snd_seq_event ev = stopped ? event_stop : event_start;
        this->send_event(&ev);
    }
    void stop()
    {
        stopped = true;
        snd_seq_event ev = stopped ? event_stop : event_start;
        this->send_event(&ev);
    }
    void end()
    {
        ended = true;
        stop();
    }
    void run();
};

#endif
