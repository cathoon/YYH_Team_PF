#pragma once
#include "singletonBase.h"
#include "image.h"
#include "animation.h"
class cameraManager : public singletonBase<cameraManager>
{
private:
	float _L, _T; // 카메라 LEFT, TOP 절대 좌표이며 이를 기준으로 그려짐
	float _x, _y; // 카메라 중점 좌표
	float _width, _height; // 카메라 너비, 높이 값

	float _minL, _maxL; // Left 좌표의 가능한 범위
	float _minT, _maxT; // Top 좌표의 가능한 범위
	float _minX, _maxX; // x 좌표의 가능한 범위
	float _minY, _maxY; // y 좌표의 가능한 범위

	float _speed;
public:
	cameraManager();
	~cameraManager();

	HRESULT init();
	void release();

	void setConfig(float left, float top, float width, float height, float minL, float minT, float maxL, float maxT);
	void setConfigCenter(float x, float y, float width, float height, float minX, float minY, float maxX, float maxY);
	float getL();
	float getT();
	float getX();
	float getY();
	void setL(float newL);
	void setT(float newT);
	void setX(float newX);
	void setY(float newY);
	void movePivot(float offsetX, float offsetY);

	float getRelativeX(float x);
	float getRelativeY(float y);

	void rectangle(HDC hdc, TTYONE_UTIL::MYRECT rect);
	void ellipse(HDC hdc, TTYONE_UTIL::MYRECT rect);

	void render(HDC hdc, image* img);
	void render(HDC hdc, image* img, float destX, float destY);
	void render(HDC hdc, image* img, float destX, float destY, float sourX, float sourY, float sourWidth, float sourHeight);
	void alpharender(HDC hdc, image* img, float destX, float destY, int alpha);
	void loopRender(HDC hdc, image* img, float destX, float destY);

	void frameRender(HDC hdc, image* img, float destX, float destY);
	void frameRender(HDC hdc, image* img, float destX, float destY, int frameX, int frameY);
	void AniRender(HDC hdc, image* img, float destX, float destY, animation* ani);
	void KeyAniRender(HDC hdc, image* img, string KeyName, float destX, float destY, animation* ani);
	void KeyAnialphaRender(HDC hdc, image* img, float destX, float destY, animation* ani,int alpha);
	float getSpeed() { return _speed; }
	void setSpeed(float s) { _speed = s; }

	void zoom(HDC hdc, float ratio);
};

