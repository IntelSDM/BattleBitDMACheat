#pragma once
class PlayerNetworkState
{
private:
	uint64_t Class = 0;
	uint64_t Connected = 0x10; // public bool \u0307\u0307\u0303\u0308\u0305\u0306\u0302\u0308\u0305\u0303\u0301\u0305\u0308\u0306\u0306;
	uint64_t Health = 0x14; // public float \u0302\u0305\u0305\u0308\u0308\u0301\u0303\u0306\u0305\u0303\u0308\u0302\u0306\u0305\u0307;
	uint64_t Seated = 0x40;
	uint64_t Friendly = 0xC8;
	/*
	[Token(Token = "0x40017EE")]
	[FieldOffset(Offset = "0x11C")]
	public Vector3 \u0304\u0306\u0304\u0306\u0301\u0301\u0304\u0302\u0307\u0304\u0306\u0305\u0305\u0306\u0308;

	// Token: 0x040017EF RID: 6127
	[Token(Token = "0x40017EF")]
	[FieldOffset(Offset = "0x128")]
	public Vector3 \u0305\u0301\u0304\u0305\u0303\u0302\u0308\u0302\u0306\u0304\u0303\u0308\u0307\u0306\u0302;

	// Token: 0x040017F0 RID: 6128
	[Token(Token = "0x40017F0")]
	[FieldOffset(Offset = "0x134")]
	public Vector3 \u0307\u0303\u0307\u0304\u0302\u0308\u0305\u0304\u0306\u0305\u0304\u0302\u0306\u0308\u0304;
	Looking for 3 vectors in a row
	*/
	uint64_t PositionOffset = 0x128; // 0x11C

	bool IsConnected = false;
	float CurrentHealth = 0;
	bool IsSeated = false;
	bool IsFriendly = false;
	Vector3 Position;
public:
	PlayerNetworkState(uint64_t address, VMMDLL_SCATTER_HANDLE handle);
	void UpdateConnected(VMMDLL_SCATTER_HANDLE handle );
	void UpdateHealth(VMMDLL_SCATTER_HANDLE handle);
	void UpdateFriendly(VMMDLL_SCATTER_HANDLE handle);
	void UpdatePosition(VMMDLL_SCATTER_HANDLE handle);
	float GetHealth();
	bool GetConnected();
	bool GetFriendly();
	Vector3 GetPosition();

};