#include "pch.h"
#include "Memory.h"
#include "CheatFunction.h"
#include "PlayerNetwork.h"
void main()
{
	if (!TargetProcess.Init("BattleBit.exe"))
	{
		printf("Failed to initialize process\n");
		return;
	}
	TargetProcess.GetBaseAddress("GameAssembly.dll");
	std::shared_ptr<PlayerNetwork> playernetwork = std::make_shared<PlayerNetwork>();
	playernetwork->ItteratePlayers();

}
	