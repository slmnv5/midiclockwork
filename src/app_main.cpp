#include "pch.hpp"
#include "MidiClient.hpp"
#include "MidiClockClient.hpp"

using namespace std;

void help();

int main(int argc, char *argv[])
{

	const char *clientName = nullptr;
	const char *dstName = nullptr;
	const char *bar_time = nullptr;

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
			bar_time = argv[i + 1];
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
		clientName = "pimidiclock";

	LOG(LogLvl::INFO) << "MIDI clock client name: " << clientName;
	MidiClockClient *mcc = nullptr;

	try
	{

		mcc = new MidiClockClient(clientName, dstName);
		float fbt = std::stof(std::string(bar_time));
		fbt = max(fbt, 0.5F);
		fbt = min(fbt, 60.0F);
		mcc->set_bar_time(fbt);

		LOG(LogLvl::INFO) << "Using MIDI clock destination: " << dstName;
		LOG(LogLvl::INFO) << "Starting MIDI clock, bar time: " << mcc->get_bar_time() << " BPM: " << mcc->get_bpm();
		mcc->start();
		mcc->run();
	}
	catch (exception &e)
	{
		LOG(LogLvl::ERROR) << "Completed with error: " << e.what();
		return 1;
	}
	LOG(LogLvl::INFO) << "Completed app.";
	mcc->stop();
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
