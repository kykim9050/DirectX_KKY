#pragma once


// Ό³Έν :
class UContentsValue
{
public:

	static const float WorldMapPlayerXInitValue;
	static const float WorldMapPlayerYInitValue;

	static const float CameraInitZValue;
	static const float4 WorldMapCameraInitValue;

	static const float4 ContentsCameraInitPos;
	static const float ContentsCameraInitXPos;
	static const float ContentsCameraInitYPos;

	static const float PlayerCheckPosOffSet;

	static std::shared_ptr<UEngineTexture> ColMapTexture;

	static const float4 Up_BulletInitPos;
	static const float4 RightUp_BulletInitPos;
	static const float4 DiagUp_BulletInitPos;
	static const float4 Straight_BulletInitPos;
	static const float4 DiagDown_BulletInitPos;
	static const float4 Down_BulletInitPos;
	static const float4 RightDown_BulletInitPos;
	static const float4 Duck_BulletInitPos;

	static const float4 PlayerBulletColSize;
	static const float4 PlayerSSBulletColSize;

protected:

private:
	UContentsValue();
	~UContentsValue();
};

