#include "Pch.h"
#include "PlayerEsp.h"
#include "globals.h"
#include "CheatFunction.h"
#include "Drawing.h"

std::shared_ptr<CheatFunction> UpdatePlayers = std::make_shared<CheatFunction>(10, [] {
	auto handle = TargetProcess.CreateScatterHandle();
	for (auto player : BasePlayer->PlayerList)
	{

		if (player->GetPlayerNettworkState()->GetHealth() <= 0)
			continue;
		player->GetPlayerNettworkState()->UpdatePosition(handle);
		
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	

});



void DrawPlayers()
{

	for (auto player : BasePlayer->PlayerList)
	{
		if (player == CurrentLocalPlayer)
			continue;
		if (player->GetPlayerNettworkState()->GetHealth() <= 0)
			continue;
		if (player->GetPlayerNettworkState()->GetFriendly() == true)
			continue;

		Vector3 position = player->GetPlayerNettworkState()->GetPosition();
		Vector2 screenpos = Camera->WorldToScreen(position);
		if (screenpos == Vector2::Zero())
			continue;

		int distance = Vector3::Distance(position, CurrentLocalPlayer->GetPlayerNettworkState()->GetPosition());
		std::wstring distancestr = LIT(L"[") + std::to_wstring(distance) + LIT(L"m]");
		std::wstring primary = player->GetPlayerNettworkState()->GetPrimaryWeaponName();
		std::wstring secondary = player->GetPlayerNettworkState()->GetSecondaryWeaponName();
		DrawText(screenpos.x, screenpos.y, LIT(L"Player") + distancestr, "Verdana", 11, Colour(255, 255, 255, 255), FontAlignment::Centre);
		DrawText(screenpos.x, screenpos.y + 15, primary, "Verdana", 11, Colour(255, 255, 255, 255), FontAlignment::Centre);
		DrawText(screenpos.x, screenpos.y + 30, secondary, "Verdana", 11, Colour(255, 255, 255, 255), FontAlignment::Centre);
	}

}