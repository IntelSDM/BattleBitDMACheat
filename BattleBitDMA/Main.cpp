#include "pch.h"
#include "Memory.h"
#include "CheatFunction.h"
#include "PlayerNetwork.h"
#include "Globals.h"
#include "MainCamera.h"
std::shared_ptr<PlayerNetwork> Player ;
std::shared_ptr<MainCamera> Camera ;
std::shared_ptr<CheatFunction> Cache = std::make_shared<CheatFunction>(1000, [] {
	Player->CachePlayers();
	
	});
std::shared_ptr<CheatFunction> UpdateCamera = std::make_shared<CheatFunction>(100, [] {
	Camera->UpdateViewMatrix();

	});
std::shared_ptr<PlayerNetwork> CurrentLocalPlayer;
void InitialiseClasses()
{
	Player = std::make_shared<PlayerNetwork>(0);
	Camera = std::make_shared<MainCamera>();
}
void main()
{
	if (!TargetProcess.Init("BattleBit.exe"))
	{
		printf("Failed to initialize process\n");
		return;
	}
	TargetProcess.GetBaseAddress("GameAssembly.dll");
	InitialiseClasses();
	Player->InitializePlayerList();
	while (true)
	{
		Cache->Execute();
		UpdateCamera->Execute();
	}

}
	