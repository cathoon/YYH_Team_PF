#pragma once
#include "gameNode.h"
#include "Player.h"

enum SMSTATE
{
	SmBegging,
	SmBlownback,
	SmDazed,
	SmGethit,
	SmHoldhit,
	SmHoldrelrase,
	SmIdle,
	SmJumpPunch,
	SmKick,
	SmKnockdown,
	SmRun,
	SmSideKick,
	SmStPunch,
	SmTaunt,
	SmUpercut,
	SmWalk,
	SmWeaponSwing
};

class EnemySchoolMan : public gameNode
{
private:
	SMSTATE _SmState;
	animation* _SmAni;
	Player* _ply;

	image* _SmShadowImage;
	image* _SmImage;

	MYRECT _SmShadow;				//적 그림자
	MYRECT _SmHit;				    //적 캐릭터 및 충돌처리용 사각형
	MYRECT _SmAttackExploration;	//플레이어 들어올시 공격하는 영역
	MYRECT _SmAttack;				//적이 공격시 충돌처리용

	float _SmCenterX, _SmCenterY;

	float _SmShadowX, _SmShadowY; //그림자의 중점 (EnemyCore에 사용)

	float _EnemyX, _EnemyY; //캐릭터의 중점

	float _ChaseAngle;
	float _Distance;

	int _Time;

	float _Speed;
	int _Hp;

	bool _IsRight; //왼쪽오른쪽
	bool _IsLeft;

public:
	virtual HRESULT init();
	virtual HRESULT Init(POINTFLOAT pt);

	void SmAniInit();
	void SmAniSet(SMSTATE state);

	void SmState();

	virtual void Release();
	virtual void Update();
	virtual void Render();

	float GetSmCenterX() { return _SmCenterX;  }
	float GetSmCenterY() { return _SmCenterY; }
	MYRECT GetSchoolManHit() { return _SmHit; } //피격영역
	MYRECT GetSchoolManAttackExploration() { return _SmAttackExploration; }
	MYRECT GetSchoolManAttack() { return _SmAttack; }


	SMSTATE GetSmState() { return _SmState; }

	POINTFLOAT GetSmPt() { POINTFLOAT temp; temp.x = _SmCenterX; temp.y = _SmCenterY; return temp; }

	int GetHP() { return _Hp; }
	void SmHitHP(float damge);

	void SetSmCenterX(float x);
	void SetSmCenterY(float y);

	void SetPlayer(Player* _p) { _ply = _p; }
};