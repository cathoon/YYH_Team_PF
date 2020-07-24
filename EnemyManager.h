#pragma once
#include "gameNode.h"
#include "EnemyCheerLeader.h"
#include "EnemySchoolGirl.h"
#include "EnemySchoolMan.h"
#include <vector>

class Player;

enum ENEMYTYPE
{
	CheerLeader,
	SchoolMan,
	SchoolGirl
};

struct TagEnemySpawn
{
	ENEMYTYPE EmType;
	POINTFLOAT XY;
};


class EnemyManager : public gameNode
{
private:
	typedef vector<EnemyCheerLeader*> vCheerLeader;
	typedef vector<EnemySchoolMan*>   vSchoolMan;
	typedef vector<EnemySchoolGirl*>  vSchoolGirl;



	vCheerLeader _vCheerLeader;
	vSchoolMan	 _vSchoolMan;
	vSchoolGirl  _vSchoolGirl;

	Player* _Player;

	float _CLAngle;
	float _CLDistance;

	float _SgAngle;
	float _SgDistance;

	float _SmAngle;
	float _SmDistance;


public:
	EnemyManager() {};
	~EnemyManager() {};
	HRESULT init();
	HRESULT Init(vector<TagEnemySpawn> Spawn);
	void Release();
	void Updata();
	void Render();

	void Collision();

	void SpawnEnemyTest(vector<TagEnemySpawn> spawn);
	vector<EnemyCheerLeader*> GetEnemyCheerLeader() { return _vCheerLeader; }
	vector<EnemySchoolMan*>   GetEnemySchoolMan() { return _vSchoolMan; }
	vector<EnemySchoolGirl*>  GetEnemySchoolGirl() { return _vSchoolGirl; }

	void SetPlayerLink(Player* p) { _Player = p; }
	bool isAllDeath();
};