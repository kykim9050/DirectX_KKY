#pragma once
#include "WorldPlayer.h"

// ���� :
class UContentsFunction
{
public:

	inline static std::shared_ptr<AWorldPlayer> GetWorldPlayer()
	{
		return AWorldPlayer::GetMainPlayer();
	}

protected:

private:
	// constrcuter destructer
	UContentsFunction();
	~UContentsFunction();
};

