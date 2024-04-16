#pragma once


// ���� :
class UContentsValue
{
public:

	static const float WorldMapPlayerXInitValue;
	static const float WorldMapPlayerYInitValue;

	static const float CameraInitZValue;
	static const FVector WorldMapCameraInitValue;

	static const float4 ContentsCameraInitPos;
	static const float ContentsCameraInitXPos;
	static const float ContentsCameraInitYPos;

	static const float PlayerCheckPosOffSet;

	static std::shared_ptr<UEngineTexture> ColMapTexture;



protected:

private:
	UContentsValue();
	~UContentsValue();
};

