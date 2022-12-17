#include "pch.hpp"
#include "MidiClient.hpp"
#include "MidiClockClient.hpp"
#include "lib/log.hpp"

using namespace std;

void help(std::string app_name);

int main(int argc, char *argv[])
{

	const char *clientName = nullptr;
	const char *dstName = nullptr;
	const char *bar_time = nullptr;
	bool exactTime = false;

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
		else if (strcmp(argv[i], "-e") == 0)
		{
			exactTime = true;
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
			help(argv[0]);
			return 0;
		}
	}

	if (clientName == nullptr)
	{
		clientName = "pimidiclock";
	}
	if (bar_time == nullptr)
	{
		help(argv[0]);
		return 1;
	}
	LOG(LogLvl::INFO) << "MIDI clock client name: " << clientName;
	MidiClockClient *mcc = nullptr;

	try
	{
		mcc = new MidiClockClient(clientName, dstName);
		float fbt = std::stof(std::string(bar_time));
		fbt = max(fbt, 0.05F);
		fbt = min(fbt, 10000.0F);
		mcc->setBarTime(fbt);
		LOG(LogLvl::INFO) << "Starting MIDI clock, bar time: " << mcc->getBarTime()
						  << ",  BPM: " << mcc->getBpm() << " exact time: " << exactTime;
		mcc->run(exactTime);
	}
	catch (exception &e)
	{
		LOG(LogLvl::ERROR) << "Completed with error: " << e.what();
		help(argv[0]);
		return 1;
	}
	LOG(LogLvl::INFO) << "Completed app.";
	mcc->stop();
}

void help(std::string app_name)
{
	cout << "\nUsage: " << app_name << " -b <bar_length_seconds> [options]\n"
		 << "  -n [name] name of created MIDI port, optional\n"
		 << "  -d [dstName] destination port to connect, optional\n"
		 << "  -v verbose output\n"
		 << "  -vv more verbose\n"
		 << "  -vvv even more verbose\n"
		 << "  -h displays this info\n";
}
