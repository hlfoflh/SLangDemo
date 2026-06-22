#include "SDR.h"

#include <exception>
#include <iostream>

int main(int ArgC, char** ArgV)
{
	try
	{
		SLangDR::FSDRConfig Config;
		Config.AppName = "SLang Differentiable Renderer Demo";

		SLangDR::FSDR App;
		return App.Run(Config, ArgC, ArgV);
	}
	catch (const std::exception& Error)
	{
		std::cerr << "Fatal error: " << Error.what() << '\n';
		return 1;
	}
}
