#pragma once

#include <string>

namespace SLangDR
{
	struct FSDRConfig
	{
		std::string AppName = "SLang Differentiable Renderer Demo";
		bool bEnableValidation = true;
	};

	class FSDR
	{
	public:

		FSDR() = default;
		~FSDR();

		FSDR(const FSDR&) = delete;
		FSDR& operator=(const FSDR&) = delete;
		FSDR(FSDR&&) = delete;
		FSDR& operator=(FSDR&&) = delete;

		int Run(const FSDRConfig& InConfig, int ArgC, char** ArgV);

	private:

		void Initialize(const FSDRConfig& InConfig, int ArgC, char** ArgV);
		void Execute();
		void Shutdown();

		FSDRConfig Config;
		bool bInitialized = false;
	};
}
