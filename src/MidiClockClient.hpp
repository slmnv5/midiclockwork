#ifndef MIDICLOCKCLIENT_H
#define MIDICLOCKCLIENT_H
#include "pch.hpp"
#include "MidiClient.hpp"

class MidiClockClient : public MidiClient
{
private:
    float sleep_time = 2.0 / 96; // bar is 2 seconds
    bool stopped = true;
    bool ended = false;

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
    float get_sleep() const
    {
        return this->sleep_time;
    }

    void send_msg(unsigned char msg_type)
    {
        snd_seq_event_t *event;
        snd_seq_ev_clear(event);
        event->type = msg_type;
        send_event(event);
    }

    void start()
    {
        stopped = false;
        unsigned char msg = stopped ? 0xFC : 0xFA;
        this->send_msg(msg);
    }

    void stop()
    {
        stopped = true;
        unsigned char msg = stopped ? 0xFC : 0xFA;
        this->send_msg(msg);
    }

    void end()
    {
        ended = true;
    }
    void run();
};

#endif
