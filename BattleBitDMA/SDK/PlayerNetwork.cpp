#include "Pch.h"
#include "PlayerNetwork.h"

PlayerNetwork::PlayerNetwork(uint64_t address)
{
	Class = address;
}
void PlayerNetwork::InitializePlayerList()
{
	StaticClass = TargetProcess.Read<uint64_t>(TargetProcess.GetBaseAddress("GameAssembly.dll") + StaticClass);
	printf("StaticClass: 0x%llX\n", StaticClass);
	StaticField = TargetProcess.Read<uint64_t>(StaticClass + StaticField);
	FastList = TargetProcess.Read<uint64_t>(StaticField + FastList);
	printf("FastList: 0x%llX\n", FastList);
}
void PlayerNetwork::CachePlayers()
{
	
	auto handle = TargetProcess.CreateScatterHandle();
	uint32_t fastlistsize = 0;
	uint64_t fastlistbuffer = 0;
	TargetProcess.AddScatterReadRequest(handle, FastList + 0x10, reinterpret_cast<void*>(&fastlistbuffer), sizeof(uint64_t));
	TargetProcess.AddScatterReadRequest(handle, FastList + 0x18, reinterpret_cast<void*>(&fastlistsize), sizeof(uint32_t));
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);

	std::vector<uint64_t> players;
	players.resize(fastlistsize);
	handle = TargetProcess.CreateScatterHandle();
	for (int i = 0; i < fastlistsize; i++)
	{
		TargetProcess.AddScatterReadRequest(handle,fastlistbuffer + (0x20 + (i * 0x8)), reinterpret_cast<void*>(&players[i]),sizeof(uint64_t));

	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	for (int i = 0; i < fastlistsize; i++)
	{
		PlayerList[players[i]] = std::make_shared<PlayerNetwork>(players[i]);
	}
	handle = TargetProcess.CreateScatterHandle();
	for (auto pair : PlayerList)
	{
		TargetProcess.AddScatterReadRequest(handle, pair.second->Class + pair.second->NetworkState, reinterpret_cast<void*>(&pair.second->NetworkState), sizeof(uint64_t));
		TargetProcess.AddScatterReadRequest(handle, pair.second->Class + pair.second->LocalPlayer, reinterpret_cast<void*>(&pair.second->IsLocalPlayer), sizeof(bool));
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	handle = TargetProcess.CreateScatterHandle();
	for (auto pair : PlayerList)
	{
		pair.second->PlayerState = std::make_shared<PlayerNetworkState>(pair.second->NetworkState,handle);
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);

	for (auto pair : PlayerList)
	{//print if player is connected and health
	//	if (pair.second->PlayerState->GetConnected())
	//	{
		//	printf("Player: 0x%llX is connected\n", pair.first);
			printf("Player: 0x%llX has health: %f\n", pair.first, pair.second->PlayerState->GetHealth());
			printf("Player: 0x%llX is friendly: %d\n", pair.first, pair.second->PlayerState->GetFriendly());
			printf("Player: 0x%llX is at position: %f %f %f\n", pair.first, pair.second->PlayerState->GetPosition().x, pair.second->PlayerState->GetPosition().y, pair.second->PlayerState->GetPosition().z);
	//	}
	}




}