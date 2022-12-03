#ifndef MIDICLOCKCLIENT_H
#define MIDICLOCKCLIENT_H
#include "pch.hpp"
#include "MidiClient.hpp"

class MidiClockClient : public MidiClient
{
private:
    float sleep_time = 2.0 / 96; // bar is 2 seconds
    bool stopped = true;

public:
    MidiClockClient(const char *clientName, const char *dstName) : MidiClient(clientName, nullptr, dstName)
    {
    }
    virtual ~MidiClockClient()
    {
    }
    void set_sleep(float sleep_time)
    {
        this->sleep_time = sleep_time;
    }

    void send_external(unsigned char msg_type)
    {
        snd_seq_event_t *event;
        snd_seq_ev_clear(event);
        event->type = msg_type;
        send_event(event);
    }

    void start_stop()
    {
        stopped = !stopped;
        unsigned char msg = stopped ? 0xFC : 0xFA;
        this->send_external(msg);
    }
    void run();
};

#endif
