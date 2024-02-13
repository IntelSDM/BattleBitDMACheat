#include "Pch.h"
#include "PlayerEsp.h"
#include "globals.h"
#include "CheatFunction.h"
#include "Drawing.h"

std::shared_ptr<CheatFunction> UpdatePlayers = std::make_shared<CheatFunction>(1, [] {
	auto handle = TargetProcess.CreateScatterHandle();
	for (auto player : BasePlayer->PlayerList)
	{
		if(player == CurrentLocalPlayer)
			continue;
		if (player->GetPlayerNettworkState()->GetHealth() <= 0)
			continue;
		if (player->GetPlayerNettworkState()->GetFriendly() == true)
			continue;
		player->GetPlayerNettworkState()->UpdatePosition(handle);
		
	}
	TargetProcess.ExecuteReadScatter(handle);
	TargetProcess.CloseScatterHandle(handle);
	

});



std::shared_ptr<CheatFunction> DrawPlayers = std::make_shared<CheatFunction>(0, [] {

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
		if(screenpos == Vector2::Zero())
			continue;


		//printf("Position: %f %f %f\n", player->GetPlayerNettworkState()->GetPosition().x, player->GetPlayerNettworkState()->GetPosition().y, player->GetPlayerNettworkState()->GetPosition().z);
		//printf("Health: %f\n", player->GetPlayerNettworkState()->GetHealth());
		DrawText(screenpos.x, screenpos.y, LIT(L"Player"), "Verdana", 11, Colour(255, 255, 255, 255), FontAlignment::Centre);
	}

	});