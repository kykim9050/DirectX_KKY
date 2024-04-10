#include "PreCompile.h"
#include "ContentsValue.h"


const float UContentsValue::CameraInitZValue = -100.0f;
const float UContentsValue::WorldMapPlayerXInitValue = 832.0f;
const float UContentsValue::WorldMapPlayerYInitValue = -768.0f;
const FVector UContentsValue::WorldMapCameraInitValue = FVector(UContentsValue::WorldMapPlayerXInitValue, 
	UContentsValue::WorldMapPlayerYInitValue, 
	UContentsValue::CameraInitZValue);



std::shared_ptr<UEngineTexture> UContentsValue::ColMapTexture = std::shared_ptr<UEngineTexture>();