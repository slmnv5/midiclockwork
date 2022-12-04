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

public:
    MidiClockClient(const char *clientName, const char *dstName) : MidiClient(clientName, nullptr, dstName)
    {
    }
    virtual ~MidiClockClient()
    {
    }
    void set_bar_time(float bar_time)
    {
        this->bar_time = bar_time;
    }
    float get_bar_time() const
    {
        return this->bar_time;
    }

    void send_msg(unsigned char msg_type)
    {
        snd_seq_event_t event;
        snd_seq_ev_clear(&event);
        event.type = msg_type;
        send_event(&event);
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
        stop();
    }
    void run();
};

#endif
