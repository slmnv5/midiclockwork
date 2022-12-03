#include "pch.hpp"
#include "utils.hpp"
#include "MidiClockClient.hpp"
#include <fcntl.h>
#include <linux/input.h>

MidiClockClient::MidiClockClient(const char *clientName, const char *dstName) : MidiClient(clientName, nullptr, dstName)
{
    run()
}

void MidiClockClient::run()
{
    snd_seq_event_t event;
    snd_seq_ev_clear(&event);
    event.type = SND_SEQ_EVENT_CLOCK;
    event.data.note.channel = 0;

    while (!stopped)
    {
        for (k = 0; k < 96; k++)
        {
            usleep((sleep_time * 1000000.0));
            send_event(&event);
        }
    }
}
