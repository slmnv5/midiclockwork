#ifndef MIDICLIENT_H
#define MIDICLIENT_H
#include "pch.hpp"

int find_midi_client(const std::string &name_part, unsigned int capability, int &cli_id, int &cli_port);

class MidiClient
{
protected:
	int client = -1;
	int inport = -1;
	int outport = -1;
	snd_seq_t *seq_handle = nullptr;

public:
	MidiClient(const char *clientName, const char *srcName, const char *dstName)
	{
		open_alsa_connections(clientName, srcName, dstName);
	}
	virtual ~MidiClient()
	{
	}

protected:
	void send_event(snd_seq_event_t *event) const;
	virtual void open_alsa_connections(const char *clientName, const char *srcName, const char *dstName);

private:
	void subscribe(const char *name_part, bool is_input) const
	{
		if (nullptr == name_part)
		{
			return;
		}

		int id, port, result;
		unsigned int capability = is_input ? SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ : SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE;
		result = find_midi_client(name_part, capability, id, port);
		std::string msg(name_part + is_input ? " input " : " output ");
		if (result < 0)
		{
			throw std::runtime_error("Error finding source MIDI port: " + std::string(name_part));
		}
		LOG(LogLvl::INFO) << "Connected to MIDI port: " << name_part << (is_input ? " input " : " output ") << id << ":" << port;
	}
};

#endif
