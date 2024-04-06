#pragma once

// Ό³Έν :
class ATutorialMode
{
public:
	// constrcuter destructer
	ATutorialMode();
	~ATutorialMode();

	// delete Function
	ATutorialMode(const ATutorialMode& _Other) = delete;
	ATutorialMode(ATutorialMode&& _Other) noexcept = delete;
	ATutorialMode& operator=(const ATutorialMode& _Other) = delete;
	ATutorialMode& operator=(ATutorialMode&& _Other) noexcept = delete;

protected:

private:

};

