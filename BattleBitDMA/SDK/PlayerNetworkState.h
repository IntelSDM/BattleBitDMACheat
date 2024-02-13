#pragma once
class PlayerNetworkState
{
private:
	uint64_t Class = 0;
	uint64_t Connected = 0x10; // public bool \u0307\u0307\u0303\u0308\u0305\u0306\u0302\u0308\u0305\u0303\u0301\u0305\u0308\u0306\u0306;
	uint64_t Health = 0x14; // public float \u0302\u0305\u0305\u0308\u0308\u0301\u0303\u0306\u0305\u0303\u0308\u0302\u0306\u0305\u0307;
	bool IsConnected = false;
	float CurrentHealth = 0;
public:
	PlayerNetworkState(uint64_t address);
	void UpdateConnected(VMMDLL_SCATTER_HANDLE handle );
	void UpdateHealth(VMMDLL_SCATTER_HANDLE handle);
	float GetHealth();
	bool GetConnected();

};