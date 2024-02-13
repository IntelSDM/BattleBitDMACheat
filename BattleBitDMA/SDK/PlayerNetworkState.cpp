#include "Pch.h"
#include "PlayerNetworkState.h"
#include "CheatFunction.h"

PlayerNetworkState::PlayerNetworkState(uint64_t address, VMMDLL_SCATTER_HANDLE handle)
{
	Class = address;
	UpdateConnected(handle);
	UpdateHealth(handle);
	UpdateFriendly(handle);
	UpdatePosition(handle);
}

void PlayerNetworkState::UpdateConnected(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle,Class + Connected,reinterpret_cast<void*>(&IsConnected),sizeof(bool));
}

void PlayerNetworkState::UpdateHealth(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle, Class + Health, reinterpret_cast<void*>(&CurrentHealth), sizeof(float));
}

void PlayerNetworkState::UpdateFriendly(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle, Class + Friendly, reinterpret_cast<void*>(&IsFriendly), sizeof(bool));
}

void PlayerNetworkState::UpdatePosition(VMMDLL_SCATTER_HANDLE handle)
{
	TargetProcess.AddScatterReadRequest(handle, Class + PositionOffset, reinterpret_cast<void*>(&Position), sizeof(Vector3));
}

float PlayerNetworkState::GetHealth()
{
	return CurrentHealth;
}

bool PlayerNetworkState::GetConnected()
{
	return IsConnected;
}

bool PlayerNetworkState::GetFriendly()
{
	return IsFriendly;
}

Vector3 PlayerNetworkState::GetPosition()
{
	return Position;
}