#include "PreCompile.h"
#include "ContentsValue.h"


const float UContentsValue::CameraInitZValue = -100.0f;
const float UContentsValue::WorldMapPlayerXInitValue = 832.0f;
const float UContentsValue::WorldMapPlayerYInitValue = -768.0f;
const float4 UContentsValue::WorldMapCameraInitValue = float4(UContentsValue::WorldMapPlayerXInitValue,
	UContentsValue::WorldMapPlayerYInitValue, 
	UContentsValue::CameraInitZValue);

const float UContentsValue::ContentsCameraInitXPos = 640.0f;
const float UContentsValue::ContentsCameraInitYPos = -360.0f;
const float4 UContentsValue::ContentsCameraInitPos = float4(UContentsValue::ContentsCameraInitXPos, UContentsValue::ContentsCameraInitYPos, UContentsValue::CameraInitZValue);

const float UContentsValue::PlayerCheckPosOffSet = 32.0f;

const float4 UContentsValue::Up_BulletInitPos = float4(0.0f, 166.0f, 0.0f);
const float4 UContentsValue::RightUp_BulletInitPos = float4(26.0f, 166.0f, 0.0f);
const float4 UContentsValue::DiagUp_BulletInitPos = float4(64.0f, 116.0f, 0.0f);
const float4 UContentsValue::Straight_BulletInitPos = float4(72.0f, 80.0f, 0.0f);
const float4 UContentsValue::DiagDown_BulletInitPos = float4(64.0f, 36.0f, 0.0f);
const float4 UContentsValue::Down_BulletInitPos = float4(0.0f, 0.0f, 0.0f);
const float4 UContentsValue::RightDown_BulletInitPos = float4(28.0f, 0.0f, 0.0f);;
const float4 UContentsValue::Duck_BulletInitPos = float4(80.0f, 40.0f, 0.0f);


std::shared_ptr<UEngineTexture> UContentsValue::ColMapTexture = std::shared_ptr<UEngineTexture>();

const float4 UContentsValue::PlayerBulletColSize = float4(16.0f, 16.0f, 0.0f);
const float4 UContentsValue::PlayerSSBulletColSize = float4(64.0f, 64.0f, 0.0f);
