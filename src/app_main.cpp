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
	const char *barSeconds = nullptr;
	const char *busyPct = nullptr;

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
		else if (strcmp(argv[i], "-s") == 0 && i + 1 < argc)
		{
			barSeconds = argv[i + 1];
		}
		else if (strcmp(argv[i], "-b") == 0)
		{
			busyPct = argv[i + 1];
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
	if (barSeconds == nullptr)
	{
		help(argv[0]);
		return 1;
	}
	if (busyPct == nullptr)
	{
		busyPct = "0";
	}

	LOG(LogLvl::INFO) << "MIDI clock client name: " << clientName;
	MidiClockClient *mcc = nullptr;

	try
	{
		mcc = new MidiClockClient(clientName, dstName);
		uint busyPctInt = std::stoi(busyPct);
		mcc->setWaitBusyPct(busyPctInt);

		double barSecondsDbl = std::stod(std::string(barSeconds));
		mcc->setBarSeconds(barSecondsDbl);

		LOG(LogLvl::INFO) << "Starting MIDI clock, bar time seconds: " << mcc->getBarSeconds()
						  << ",  BPM: " << mcc->getBpm() << " busy wait time %: " << mcc->getWaitBusyPct();

		mcc->run();
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
	cout << "\nUsage: " << app_name << " -s <seconds_per_bar> [options]\n"
		 << "  -b [busyPercent] percent of busy wait, optional\n"
		 << "  -n [name] name of created MIDI port, optional\n"
		 << "  -d [dstName] destination port to connect, optional\n"
		 << "  -v verbose output\n"
		 << "  -vv more verbose\n"
		 << "  -vvv even more verbose\n"
		 << "  -h displays this info\n";
}
