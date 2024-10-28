#pragma once
#include "WorldPlayer.h"
#include "Player.h"

// ���� :
class UContentsFunction
{
public:

	inline static std::shared_ptr<AWorldPlayer> GetWorldPlayer()
	{
		return AWorldPlayer::GetMainPlayer();
	}

	inline static std::shared_ptr<APlayer> GetStagePlayer()
	{
		return APlayer::GetMainPlayer();
	}

protected:

private:
	// constrcuter destructer
	UContentsFunction();
	~UContentsFunction();
};

