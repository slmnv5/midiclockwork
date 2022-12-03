#ifndef MIDICLOCKCLIENT_H
#define MIDICLOCKCLIENT_H
#include "pch.hpp"
#include "MidiClient.hpp"

class MidiClockClient : public MidiClient
{
private:
    float sleep_time = 2.0 / 96; // bar is 2 seconds
    bool stopped = false;

public:
    MidiClockClient(const char *clientName, const char *dstName);
    virtual ~MidiClockClient()
    {
    }
    void set_sleep(float sleep_time)
    {
        this->sleep_time = sleep_time;
    }

    void send_external(unsigned byte msg_type )
    {
        snd_seq_event_t *event;
        snd_seq_ev_clear(event);
        event->type = msg_type;
        send_event(event);
    }

private:
    void run();
};

#endif
