#include "SDR.h"

#include <iostream>

namespace SLangDR
{
	FSDR::~FSDR()
	{
		if (bInitialized)
		{
			Shutdown();
		}
	}

	int FSDR::Run(const FSDRConfig& InConfig, int ArgC, char** ArgV)
	{
		Initialize(InConfig, ArgC, ArgV);
		Execute();
		Shutdown();

		return 0;
	}

	void FSDR::Initialize(const FSDRConfig& InConfig, int ArgC, char** ArgV)
	{
		(void)ArgC;
		(void)ArgV;

		Config = InConfig;
		bInitialized = true;

		std::cout << Config.AppName << '\n';
		std::cout << "Validation: " << (Config.bEnableValidation ? "enabled" : "disabled") << '\n';
	}

	void FSDR::Execute()
	{
		std::cout << "No rendering passes registered yet." << '\n';
	}

	void FSDR::Shutdown()
	{
		bInitialized = false;
	}
}
