#include "pch.hpp"
#include "utils.hpp"
#include "MidiClient.hpp"
#include "MidiClockClient.hpp"

using namespace std;

void help();

int main(int argc, char *argv[])
{

	const char *clientName = nullptr;
	const char *dstName = nullptr;
	const char *bpm = nullptr;

	LOG::ReportingLevel() = LogLvl::ERROR;

	for (int i = 1; i < argc; i++)
	{
		if (strcmp(argv[i], "-n") == 0 && i + 1 < argc)
		{
			clientName = argv[i + 1];
		}
		else if (strcmp(argv[i], "-d") == 0 && i + 1 < argc)
		{
			dstName = argv[i + 1];
		}
		else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc)
		{
			bpm = argv[i + 1];
		}
		else if (strcmp(argv[i], "-v") == 0)
		{
			LOG::ReportingLevel() = LogLvl::WARN;
		}
		else if (strcmp(argv[i], "-vv") == 0)
		{
			LOG::ReportingLevel() = LogLvl::INFO;
		}
		else if (strcmp(argv[i], "-vvv") == 0)
		{
			LOG::ReportingLevel() = LogLvl::DEBUG;
		}
		else if (strcmp(argv[i], "-h") == 0)
		{
			help();
			return 0;
		}
	}

	if (clientName == nullptr)
		clientName = "miclock";

	LOG(LogLvl::INFO) << "MIDI clock client name: " << clientName;
	MidiClockClient *midiClockClient = nullptr;

	try
	{

		midiClockClient = new MidiClockClient(clientName, dstName);
		float fbpm = atof(bpm);
		float sleep_time = 60 / fbpm / 96;
		midiClockClient->set_sleep(sleep_time);

		LOG(LogLvl::INFO) << "Using typing MIDI clock destination: " << dstName;
		LOG(LogLvl::INFO) << "Starting MIDI clock sending BPM: " << bpm << " sleep: " << sleep_time;
	}
	catch (exception &e)
	{
		LOG(LogLvl::ERROR) << "Completed with error: " << e.what();
		return 1;
	}
}

void help()
{
	cout << "Usage: mimap5 -r <file> [options] \n"
			"  -d <dstName> MIDI port to connect and send clock\n"
			"  -n [name] name of my MIDI port\n"
			"  -v verbose output\n"
			"  -vv more verbose\n"
			"  -vvv even more verbose\n"
			"  -h displays this info\n";
}
