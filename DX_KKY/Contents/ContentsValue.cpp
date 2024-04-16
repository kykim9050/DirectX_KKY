#include "PreCompile.h"
#include "ContentsValue.h"


const float UContentsValue::CameraInitZValue = -100.0f;
const float UContentsValue::WorldMapPlayerXInitValue = 832.0f;
const float UContentsValue::WorldMapPlayerYInitValue = -768.0f;
const FVector UContentsValue::WorldMapCameraInitValue = FVector(UContentsValue::WorldMapPlayerXInitValue, 
	UContentsValue::WorldMapPlayerYInitValue, 
	UContentsValue::CameraInitZValue);

const float UContentsValue::ContentsCameraInitXPos = 640.0f;
const float UContentsValue::ContentsCameraInitYPos = -360.0f;
const float4 UContentsValue::ContentsCameraInitPos = float4(UContentsValue::ContentsCameraInitXPos, UContentsValue::ContentsCameraInitYPos, UContentsValue::CameraInitZValue);

const float UContentsValue::PlayerCheckPosOffSet = 32.0f;


std::shared_ptr<UEngineTexture> UContentsValue::ColMapTexture = std::shared_ptr<UEngineTexture>();