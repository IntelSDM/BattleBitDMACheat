#include "pch.h"
#include "Memory.h"
#include "CheatFunction.h"
#include "PlayerNetwork.h"
std::shared_ptr<PlayerNetwork> playernetwork = std::make_shared<PlayerNetwork>(0);
std::shared_ptr<CheatFunction> cheatfunction = std::make_shared<CheatFunction>(1000, [] {
	playernetwork->CachePlayers();
	
	});
void main()
{
	if (!TargetProcess.Init("BattleBit.exe"))
	{
		printf("Failed to initialize process\n");
		return;
	}
	TargetProcess.GetBaseAddress("GameAssembly.dll");

	playernetwork->InitializePlayerList();
	while (true)
	{
		cheatfunction->Execute();
	}

}
	