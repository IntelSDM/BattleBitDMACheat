#include "Pch.h"
#include "PlayerNetworkState.h"
#include "CheatFunction.h"

PlayerNetworkState::PlayerNetworkState(uint64_t address)
{
	Class = address;
}

void PlayerNetworkState::UpdateConnected(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle,Class + Connected,reinterpret_cast<void*>(&IsConnected),sizeof(bool));
}

void PlayerNetworkState::UpdateHealth(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle, Class + Health, reinterpret_cast<void*>(&CurrentHealth), sizeof(float));
}

float PlayerNetworkState::GetHealth()
{
	return CurrentHealth;
}

bool PlayerNetworkState::GetConnected()
{
	return IsConnected;
}