#include "stdafx.h"
#include "Boss.h"
#include "Player.h"

//#include "Boss_State.h"

HRESULT Boss::init()
{
    //_BossState = new Boss_State;
    _ShadowImg = IMAGEMANAGER->addImage("Shadow", "image/Boss/Shadow.bmp", 200, 59, true, RGB(255, 0, 255));

    IMAGEMANAGER->addImage("redDC", "image/Boss/redDC.bmp", 5000, 5000, false, NULL);

    IMAGEMANAGER->addFrameImage("IDLE", "image/Boss/idle.bmp",0,0, 2772, 566, 12, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("WALK", "image/Boss/walk.bmp",0,0, 1557, 526, 9, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ATTACK", "image/Boss/attack.bmp",0,0, 2430, 582, 10, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("HIT", "image/Boss/hit.bmp",0,0, 2295, 528, 9, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("KNOCK", "image/Boss/knock.bmp",0,0, 2340, 520, 10, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("SIT", "image/Boss/sit.bmp",0,0, 876, 392, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("WAKE", "image/Boss/wake.bmp",0,0, 4731, 538, 19, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("TAUNT", "image/Boss/taunt.bmp",0,0, 4899, 668, 23, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("ROAR", "image/Boss/roar.bmp",0,0, 2520, 520, 12, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("IDLE_RUSH", "image/Boss/idle_rush.bmp",0,0, 1040, 508, 5, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("RUSH", "image/Boss/rush.bmp",0,0, 1752, 498, 8, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("RUSHTURN", "image/Boss/rushturn.bmp",0,0, 540, 496, 3, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("JUMP", "image/Boss/jump.bmp",0,0, 1368, 594, 6, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("UP", "image/Boss/up.bmp",0,0, 912, 594, 4, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("DOWN", "image/Boss/down.bmp",0,0, 684, 570, 3, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("LANDHIT", "image/Boss/landhit.bmp",0,0, 2052, 570, 9, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("DEAD", "image/Boss/dead.bmp",0,0, 2772, 566, 9, 2, true, RGB(255, 0, 255));
    IMAGEMANAGER->addFrameImage("CRY", "image/Boss/cry.bmp",0,0, 1232, 566, 4, 2, true, RGB(255, 0, 255));
    
    _Bs = BOSS_STATE::IDLE;
    _ExBs = BOSS_STATE::IDLE;
    _Pz = PHAZE::FIRST;

    _Center.x = 100;
    _Center.y = WINSIZEY*0.5;

    _Hit = { 100,100,200,200 };
    _Rc = { _Center.x - 50,_Center.y - 50,_Center.x + 50,_Center.y + 50 };
    _Shadow = { _Center.x - 50,_Center.y - 50,_Center.x + 50,_Center.y + 50 };
    _Attack = { 0,0,0,0 };
    _Angle = 0;
    _Speed = 2.0f;
    _Hp = 9;
    _Time = 0;
    _HitNum = 0;
    _IsLookLeft = false;

    int Right_Idle[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
    KEYANIMANAGER->addArrayFrameAnimation("RightIdle", "IDLE", Right_Idle, 12, 10, true);

    int Left_Idle[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftIdle", "IDLE", Left_Idle, 12, 10, true);

    int Right_Move[] = { 0,1,2,3,4,5,6,7,8 };
    KEYANIMANAGER->addArrayFrameAnimation("RightMove", "WALK", Right_Move, 9, 10, true);

    int Left_Move[] = { 17,16,15,14,13,12,11,10,9 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftMove", "WALK", Left_Move, 9, 10, true);

    int Right_Attack[] = { 0,1,2,3,4,5,6,7,8,9 };
    KEYANIMANAGER->addArrayFrameAnimation("RightAttack", "ATTACK", Right_Attack, 10, 10, false, RightIDLE,this);
    
    int Left_Attack[] = { 19,18,17,16,15,14,13,12,11,10 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftAttack", "ATTACK", Left_Attack, 10, 10, false, LeftIDLE, this);
    //��Ʈ 1
    int Right_Hit1[] = { 0,1,2};
    KEYANIMANAGER->addArrayFrameAnimation("RightHit1", "HIT", Right_Hit1, 3, 7, false, RightIDLE, this);

    int Left_Hit1[] = { 11,10,9 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftHit1", "HIT", Left_Hit1, 3, 7, false, LeftIDLE, this);
    //��Ʈ 2
    int Right_Hit2[] = { 3,4,5 };
    KEYANIMANAGER->addArrayFrameAnimation("RightHit2", "HIT", Right_Hit2, 3, 7, false, RightIDLE, this);

    int Left_Hit2[] = { 14,13,12 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftHit2", "HIT", Left_Hit2, 3, 7, false, LeftIDLE, this);
    //��Ʈ 3
    int Right_Hit3[] = { 6,7,8 };
    KEYANIMANAGER->addArrayFrameAnimation("RightHit3", "HIT", Right_Hit3, 3, 7, false, RightIDLE, this);

    int Left_Hit3[] = { 17,16,15  };
    KEYANIMANAGER->addArrayFrameAnimation("LeftHit3", "HIT", Left_Hit3, 3, 7, false, LeftIDLE, this);
    //
    int Right_Knock[] = { 9,8,7,6,5,4,3,2,1,0 };
    KEYANIMANAGER->addArrayFrameAnimation("RightKnock", "KNOCK", Right_Knock, 10, 7, false, RightSIT, this);

    int Left_Knock[] = { 10,11,12,13,14,15,16,17,18,19 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftKnock", "KNOCK", Left_Knock, 10, 7, false, LeftSIT, this);

    int Right_Sit[] = { 0,1,2,3 };
    KEYANIMANAGER->addArrayFrameAnimation("RightSit", "SIT", Right_Sit, 4, 5, true);

    int Left_Sit[] = { 7,6,5,4 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftSit", "SIT", Left_Sit, 4, 5, true);

    int Right_Taunt[] = { 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22 };
    KEYANIMANAGER->addArrayFrameAnimation("RightTaunt", "TAUNT", Right_Taunt, 23, 10, false,RightRUSH,this);

    int Left_Taunt[] = { 45,44,43,42,41,40,39,38,37,36,35,34,33,32,31,30,29,28,27,26,25,24,23 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftTaunt", "TAUNT", Left_Taunt, 23, 10, false,LeftRUSH,this);

    int Right_Roar[] = { 0,1,2,3,4,5,6,7,8,9,10,11 };
    KEYANIMANAGER->addArrayFrameAnimation("RightRoar", "ROAR", Right_Roar, 12, 8, false,RightTAUNT,this);

    int Left_Roar[] = { 23,22,21,20,19,18,17,16,15,14,13,12 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftRoar", "ROAR", Left_Roar, 12, 8, false, LeftTAUNT, this);

    int Right_Idle_Rush[] = { 0,1,2,3,4 };
    KEYANIMANAGER->addArrayFrameAnimation("Right_Idle_Rush", "IDLE_RUSH", Right_Idle_Rush, 5, 10, false, RightRUSH,this);

    int Left_Idle_Rush[] = { 9,8,7,6,5 };
    KEYANIMANAGER->addArrayFrameAnimation("Left_Idle_Rush", "IDLE_RUSH", Left_Idle_Rush, 5, 10, false, LeftRUSH, this);

    int Right_Rush[] = { 0,1,2,3,4,5,6,7 };
    KEYANIMANAGER->addArrayFrameAnimation("RightRush", "RUSH", Right_Rush, 8, 10, true);

    int Left_Rush[] = { 15,14,13,12,11,10,9,8 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftRush", "RUSH", Left_Rush, 8, 10, true);
    
    int Right_Turn[] = { 0,1,2 };
    KEYANIMANAGER->addArrayFrameAnimation("RightTurn", "RUSHTURN", Right_Turn, 3, 8, false, LeftRUSH, this);

    int Left_Turn[] = { 5,4,3 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftTurn", "RUSHTURN", Left_Turn, 3, 8, false, RightRUSH, this);

    int Right_Jump[] = {0,1,2,3,4,5};
    KEYANIMANAGER->addArrayFrameAnimation("RightJump", "JUMP", Right_Jump, 6, 10, false,RightJUMP,this);

    int Left_Jump[] = { 11,10,9,8,7,6 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftJump", "JUMP", Left_Jump, 6, 10, false,LeftTJUMP,this);

    int Right_Up[] = { 0,1,2,3 };
    KEYANIMANAGER->addArrayFrameAnimation("RightUp", "UP", Right_Up, 4, 10, true);

    int Left_Up[] = { 7,6,5,4 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftUp", "UP", Left_Up, 4, 10, true);

    int Right_Down[] = { 0,1,2 };
    KEYANIMANAGER->addArrayFrameAnimation("RightDown", "DOWN", Right_Down, 3, 10, true);

    int Left_Down[] = { 5,4,3 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftDown", "DOWN", Left_Down, 3, 10, true);

    int Right_Land_Hit[] = { 0,1,2,3,4,5,6,7,8 };
    KEYANIMANAGER->addArrayFrameAnimation("RightLandHit", "LANDHIT", Right_Land_Hit, 9, 10, false,RightIDLE,this);

    int Left_Land_Hit[] = { 17,16,15,14,13,12,11,10,9 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftLandHit", "LANDHIT", Left_Land_Hit, 9, 10, false,LeftIDLE,this);

    int Right_Dead[] = { 0,1,2,3,4,5,6,7,8 };
    KEYANIMANAGER->addArrayFrameAnimation("RightDead", "DEAD", Right_Dead, 9, 10, false, RightCRY, this);

    int Left_Dead[] = { 17,16,15,14,13,12,11,10,9 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftDead", "DEAD", Left_Dead, 9, 10, false, LeftCRY, this);

    int Right_Cry[] = { 0,1,2,3 };
    KEYANIMANAGER->addArrayFrameAnimation("RightCry", "CRY", Right_Cry, 4, 10, true);

    int Left_Cry[] = { 7,6,5,4 };
    KEYANIMANAGER->addArrayFrameAnimation("LeftCry", "CRY", Left_Cry, 4, 10, true);


    SetAni(KEYANIMANAGER->findAnimation("RightIdle"));
    _Ani->start();

    return S_OK;
}

void Boss::release()
{
}

void Boss::update()
{
    _Angle = getAngle(_Center.x, _Center.y, _Player->GetShadowCenterPoint().x, _Player->GetShadowCenterPoint().y);
   
    _Time++;

    if (KEYMANAGER->isOnceKeyDown('1')) _Bs = BOSS_STATE::IDLE;
    if (KEYMANAGER->isOnceKeyDown('2')) _Bs = BOSS_STATE::WALK;
    if (KEYMANAGER->isOnceKeyDown('3')) _Bs = BOSS_STATE::JUMP;
    if (KEYMANAGER->isOnceKeyDown('4')) _Bs = BOSS_STATE::ROAR;
    if (KEYMANAGER->isOnceKeyDown('5'))
    {
        _Bs = BOSS_STATE::HIT;
        if (_HitNum == 3 ) _HitNum = 1;
        _HitNum++;
    }
    if (KEYMANAGER->isOnceKeyDown('6')) _Bs = BOSS_STATE::KNOCK;
    if (KEYMANAGER->isOnceKeyDown('7')) _Bs = BOSS_STATE::DEAD;

    if (KEYMANAGER->isOnceKeyDown('Z')) _Ani->start();
    if (KEYMANAGER->isOnceKeyDown('Q')) _Hp--;

    if (_Bs != BOSS_STATE::IDLE && _Bs != BOSS_STATE::DOWN)
    {
        _Time = 100;
    }
    if (_Bs == BOSS_STATE::WALK || _Bs==BOSS_STATE::DOWN)
    {
        if (_Center.x > _Player->GetShadowCenterPoint().x)
        {
            _IsLookLeft = true;
        }
        else
        {
            _IsLookLeft = false;
        }
    }
    if (_Bs != BOSS_STATE::UP && _Bs != BOSS_STATE::DOWN && _Bs != BOSS_STATE::KNOCK)
    {
        _Jump = 0;
    }
    if ((_Hp<=6)&&(_Hp>3))
    {
        if (_Pz == PHAZE::FIRST)
        {
            _Bs = BOSS_STATE::ROAR;
        }
        _Pz = PHAZE::SECOND;
    }
    else if((_Hp <=3)&&(_Hp>0))
    {
        if (_Pz == PHAZE::SECOND)
        {
            _Bs = BOSS_STATE::ROAR;
        }
        _Pz = PHAZE::THIRD;
    }
    else if (_Hp <= 0)
    {
        _Bs = BOSS_STATE::DEAD;
    }

    // ���� �� �÷��̾� HP �پ��
    if (isCollision(_Player->GetPlayerRect(), _Attack))
    {
       // _Player->SetHp(_Player->GetHp() - 1);
    }


    switch (_Bs)
    {
    case BOSS_STATE::IDLE:
        _Img = IMAGEMANAGER->findImage("IDLE");
        if (_Time > 200)
        {
            _Bs = BOSS_STATE::WALK;
        }
        break;
    case BOSS_STATE::WALK:
        _Img = IMAGEMANAGER->findImage("WALK");
        if (!_Ani->isPlay())
        {
            _Ani->start();
        }

        if (!_IsLookLeft)
        {
            if (getDistance(_Center.x, _Center.y, _Player->GetShadowCenterPoint().x, _Player->GetShadowCenterPoint().y) < 150)
            {
                _Bs = BOSS_STATE::ATTACK;
                _Time = 100;
            }
        }
        else
        {
            if (getDistance(_Center.x, _Center.y, _Player->GetShadowCenterPoint().x, _Player->GetShadowCenterPoint().y) < 150)
            {
                _Bs = BOSS_STATE::ATTACK;
                _Time = 100;
            }
        }
        break;
    case BOSS_STATE::ATTACK:
        _Img = IMAGEMANAGER->findImage("ATTACK");

        if (!_Ani->isPlay())
        {
            _Ani->start();
        }

        break;
    case BOSS_STATE::SLAP:

        break;
    case BOSS_STATE::GUARD:
        break;
    case BOSS_STATE::PUNCH:
        break;
    case BOSS_STATE::ROAR:
        if (!_Ani->isPlay())
        {
            _Ani->start();
        }
        _Img = IMAGEMANAGER->findImage("ROAR");
        _ExBs = BOSS_STATE::ROAR;
        break;
    case BOSS_STATE::IDLE_RUSH:

        _Img = IMAGEMANAGER->findImage("IDLE_RUSH");
        _ExBs = BOSS_STATE::IDLE_RUSH;
        break;

    case BOSS_STATE::RIGHTRUSH:
        _Img = IMAGEMANAGER->findImage("RUSH");

        if (isCollision(_Rc, _Player->GetPlayerRect()))
        {
            _ExBs = BOSS_STATE::RIGHTRUSH;
            _Ani->stop();
            RightTAUNT(this);
        }
    case BOSS_STATE::LEFTRUSH:
        _Img = IMAGEMANAGER->findImage("RUSH");

        if (isCollision(_Rc, _Player->GetPlayerRect()))
        {
            _ExBs = BOSS_STATE::LEFTRUSH;
            _Ani->stop();
            LeftTAUNT(this);
        }
        break;
    case BOSS_STATE::RUSHTURN:

        _Img = IMAGEMANAGER->findImage("RUSHTURN");
        if (!_Ani->isPlay())
        {
            _Ani->start();
        }
        _ExBs = BOSS_STATE::RUSHTURN;

        break;
    case BOSS_STATE::JUMP:
        if (!_Ani->isPlay())
        {
            _Ani->start();
        }
        _Img = IMAGEMANAGER->findImage("JUMP");
        break;
    case BOSS_STATE::UP:
        _Img = IMAGEMANAGER->findImage("UP");
        break;
    case BOSS_STATE::DOWN:
        _Img = IMAGEMANAGER->findImage("DOWN");
        break;
    case BOSS_STATE::LANDHIT:
        _Img = IMAGEMANAGER->findImage("LANDHIT");
        if (_Ani->getNowAniIndex() == 4)
        {
            _Attack = { _Center.x-400, _Center.y - 200, _Center.x + 400, _Center.y + 200 };
        }
        else
        {
            _Attack = { 0,0,0,0 };
        }
        break;
    case BOSS_STATE::HIT:
        _Img = IMAGEMANAGER->findImage("HIT");
        break;
    case BOSS_STATE::GROUNDHIT:
        break;
    case BOSS_STATE::KNOCK:
        _Img = IMAGEMANAGER->findImage("KNOCK");
        break;
    case BOSS_STATE::SIT:
        _Img = IMAGEMANAGER->findImage("SIT");
        break;
    case BOSS_STATE::WAKE:
        break;
    case BOSS_STATE::TAUNT:
        if (!_Ani->isPlay())
        {
            _Ani->start();
        }
        _Img = IMAGEMANAGER->findImage("TAUNT");

        break;
    case BOSS_STATE::DEAD:
        _Img = IMAGEMANAGER->findImage("DEAD");

        break;

    case BOSS_STATE::CRY:
        _Img = IMAGEMANAGER->findImage("CRY");

        break;
    }

    /// <summary>
    /// ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /// </summary>

    switch (_Bs)
    {
    case BOSS_STATE::IDLE:
        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("RightIdle");
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("LeftIdle");
        }
        break;
    case BOSS_STATE::WALK:
        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("RightMove");
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("LeftMove");
        }

        if ((_Center.x > _Player->GetShadowCenterPoint().x + 50) || (_Center.x < _Player->GetShadowCenterPoint().x - 50))
        {
            _Center.x += cosf(_Angle) * _Speed;
        }
        if ((_Center.y > _Player->GetShadowCenterPoint().y + 5) || (_Center.y < _Player->GetShadowCenterPoint().y - 5))
        {
            _Center.y += -sinf(_Angle) * _Speed;
        }
        break;
    case BOSS_STATE::ATTACK:
        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("RightAttack");
            if (_Ani->getNowAniIndex() == 5)
            {
                _Attack = { _Center.x, _Center.y - 30, _Center.x + 200, _Center.y + 30 };
            }
            else
            {
                _Attack = { 0,0,0,0 };
            }
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("LeftAttack");
            if (_Ani->getNowAniIndex() == 5)
            {
                _Attack = { _Center.x, _Center.y - 30, _Center.x - 200, _Center.y + 30 };
            }
            else
            {
                _Attack = { 0,0,0,0 };
            }
        }
        break;
    case BOSS_STATE::SLAP:
        break;
    case BOSS_STATE::GUARD:
        break;
    case BOSS_STATE::PUNCH:
        break;
    case BOSS_STATE::ROAR:

        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("RightRoar");
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("LeftRoar");
        }

        break;
    case BOSS_STATE::IDLE_RUSH:
        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("Right_Idle_Rush");
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("Left_Idle_Rush");
        }
        break;
    case BOSS_STATE::RIGHTRUSH:

        if (_IsLookLeft)
        {
            _IsLookLeft = false;
        }

        _Ani = KEYANIMANAGER->findAnimation("RightRush");
        _Center.x += _Speed * 2;

        if ((_Center.y > _Player->GetShadowCenterPoint().y + 5) || (_Center.y < _Player->GetShadowCenterPoint().y - 5))
        {
            _Center.y += -sinf(_Angle) * 4;
        }

        if (_Center.x - 500 > _Player->GetShadowCenterPoint().x)
        {
            _Bs = BOSS_STATE::RUSHTURN;
        }
        break;
    case BOSS_STATE::LEFTRUSH:
        if (!_IsLookLeft)
        {
            _IsLookLeft = true;
        }
        _Ani = KEYANIMANAGER->findAnimation("LeftRush");
        _Center.x -= _Speed * 2;

        if ((_Center.y > _Player->GetShadowCenterPoint().y + 5) || (_Center.y < _Player->GetShadowCenterPoint().y - 5))
        {
            _Center.y += -sinf(_Angle) * 4;
        }

        if (_Center.x + 700 < _Player->GetShadowCenterPoint().x)
        {
            _Bs = BOSS_STATE::RUSHTURN;
        }
        break;
    case BOSS_STATE::RUSHTURN:
        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("RightTurn");

            _Center.x += 1;
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("LeftTurn");

            _Center.x -= 1;
        }
        break;
    case BOSS_STATE::JUMP:
        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("RightJump");
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("LeftJump");
        }
        break;
    case BOSS_STATE::UP:
        if (_Center.y - 240 - _Jump > -1000)
        {
            _Jump += 40;
        }

        if (_Center.y - 240 - _Jump < -600)
        {
            float X = _Player->GetShadowCenterPoint().x;
            float Y = _Player->GetShadowCenterPoint().y;
            _Center.x = X;
            _Center.y = Y;
            _Bs = BOSS_STATE::DOWN;
        }

        break;
    case BOSS_STATE::DOWN:
        if (_Jump > 0 && (_Time > 150))
        {
            _Jump -= 60;
            if (!_IsLookLeft)
            {
                _Ani = KEYANIMANAGER->findAnimation("RightDown");
            }
            else
            {
                _Ani = KEYANIMANAGER->findAnimation("LeftDown");
            }
        }
        if (_Jump <= 0)
        {
            _Bs = BOSS_STATE::LANDHIT;
        }
        break;
    case BOSS_STATE::LANDHIT:
        if (!_Ani->isPlay())
        {
            _Ani->start();
        }
        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("RightLandHit");
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("LeftLandHit");
        }
        break;
    case BOSS_STATE::HIT:
        if (!_Ani->isPlay())
        {
            _Ani->start();
        }
        switch (_HitNum)
        {
        case 1:
            if (!_IsLookLeft)
            {
                _Ani = KEYANIMANAGER->findAnimation("RightHit1");
                _Center.x -= 1;
            }
            else
            {
                _Ani = KEYANIMANAGER->findAnimation("LeftHit1");
                _Center.x += 1;
            }
        break;
        case 2:
            if (!_IsLookLeft)
            {
                _Ani = KEYANIMANAGER->findAnimation("RightHit2");
                _Center.x -= 1;
            }
            else
            {
                _Ani = KEYANIMANAGER->findAnimation("LeftHit2");
                _Center.x += 1;
            }
            break;
        case 3:
            if (!_IsLookLeft)
            {
                _Ani = KEYANIMANAGER->findAnimation("RightHit3");
                _Center.x -= 1;
            }
            else
            {
                _Ani = KEYANIMANAGER->findAnimation("LeftHit3");
                _Center.x += 1;
            }
            break;
        }
        break;
    case BOSS_STATE::GROUNDHIT:
        break;
    case BOSS_STATE::KNOCK:
        if (!_Ani->isPlay())
        {
            _Ani->start();
        }
        if (_Ani->getNowAniIndex() < 5)
        {
            _Jump += 1;
        }
        else if (_Ani->getNowAniIndex() > 4)
        {
            _Jump -= 2;
        }
        
        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("RightKnock");
            _Center.x -= 2;
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("LeftKnock");
            _Center.x += 2;
        }
        break;
    case BOSS_STATE::SIT:
        break;
    case BOSS_STATE::WAKE:
        break;
    case BOSS_STATE::TAUNT:
        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("RightTaunt");
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("LeftTaunt");
        }
        break;
    case BOSS_STATE::DEAD:
        if (!_Ani->isPlay())
        {
            _Ani->start();
        }
        if (!_IsLookLeft)
        {
            _Ani = KEYANIMANAGER->findAnimation("RightDead");
        }
        else
        {
            _Ani = KEYANIMANAGER->findAnimation("LeftDead");
        }
        break;
    case BOSS_STATE::CRY:
        break;
    }

    _Rc = { _Center.x - 120 , _Center.y - 30, _Center.x + 120, _Center.y + 60 };

    if (_Bs == BOSS_STATE::ATTACK)
    {
    }
    KEYANIMANAGER->update();
}

void Boss::render()
{
    if (_Bs == BOSS_STATE::ATTACK)
    {
        if (!_IsLookLeft && (_Ani->getNowAniIndex() == 5)) Rectangle(getMemDC(), _Center.x, _Center.y - 30, _Center.x + 200, _Center.y + 30);
        if ( _IsLookLeft && (_Ani->getNowAniIndex() == 5)) Rectangle(getMemDC(), _Center.x, _Center.y - 30, _Center.x - 200, _Center.y + 30);
    }
    if (_Bs == BOSS_STATE::LANDHIT && _Ani->getNowAniIndex() == 1)
    {
        Rectangle(getMemDC(),_Center.x - 300, _Center.y - 200, _Center.x + 300, _Center.y + 200 );
    }

    Rectangle(getMemDC(), _Center.x - (IMAGEMANAGER->findImage("IDLE")->getFrameWidth() * 0.5) + 10, _Center.y - 30, _Center.x + 95, _Center.y + 60);
    _ShadowImg->alphaRender(getMemDC(), _Center.x - (IMAGEMANAGER->findImage("IDLE")->getFrameWidth() * 0.5)+10, _Center.y, 100);

    if (_Pz != PHAZE::THIRD)
    {
        switch (_Bs)
        {
        case BOSS_STATE::IDLE:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani);

            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani);

            }
            break;
        case BOSS_STATE::WALK:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x + 10 - (_Img->getFrameWidth() * 0.5), _Center.y - 220, _Ani);

            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x + 10 - (_Img->getFrameWidth() * 0.5), _Center.y - 220, _Ani);

            }
            break;
        case BOSS_STATE::ATTACK:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x + 10 - (_Img->getFrameWidth() * 0.5), _Center.y - 250, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - 30 - (_Img->getFrameWidth() * 0.5), _Center.y - 250, _Ani);
            }
            break;
        case BOSS_STATE::SLAP:
            break;
        case BOSS_STATE::GUARD:
            break;
        case BOSS_STATE::PUNCH:
            break;
        case BOSS_STATE::ROAR:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 210, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 210, _Ani);
            }
            break;
        case BOSS_STATE::IDLE_RUSH:

            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani);
            }
            break;
        case BOSS_STATE::RIGHTRUSH:
            _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani);

            break;
        case BOSS_STATE::LEFTRUSH:
            _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani);

            break;
        case BOSS_STATE::RUSHTURN:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani);
            }
            break;
        case BOSS_STATE::JUMP:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 250, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 250, _Ani);
            }
            break;
        case BOSS_STATE::UP:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), (_Center.y - 240 - _Jump), _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), (_Center.y - 240 - _Jump), _Ani);
            }
            break;
        case BOSS_STATE::DOWN:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), (_Center.y - 240 - _Jump), _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), (_Center.y - 240 - _Jump), _Ani);
            }
            break;
        case BOSS_STATE::LANDHIT:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani);
            }
            break;
        case BOSS_STATE::HIT:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 230, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 230, _Ani);
            }
            break;
        case BOSS_STATE::GROUNDHIT:
            break;
        case BOSS_STATE::KNOCK:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 230 - _Jump, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 230 - _Jump, _Ani);
            }
            break;
        case BOSS_STATE::SIT:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 150, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 150, _Ani);
            }
            break;
        case BOSS_STATE::WAKE:
            break;
        case BOSS_STATE::TAUNT:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 285, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 285, _Ani);
            }
            break;
        case BOSS_STATE::DEAD:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5) - 50, _Center.y - 240, _Ani);
            }
            break;
        case BOSS_STATE::CRY:

            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5) - 50, _Center.y - 240, _Ani);
            }
            break;
        }
    }
    else
    {
        // �̰� 3������ ������ �ٲ�� ��
        /*switch (_Bs)
        {
        case BOSS_STATE::IDLE:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani,200);

            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani, 200);

            }
            break;
        case BOSS_STATE::WALK:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x + 10 - (_Img->getFrameWidth() * 0.5), _Center.y - 220, _Ani,200);

            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x + 10 - (_Img->getFrameWidth() * 0.5), _Center.y - 220, _Ani, 200);

            }
            break;
        case BOSS_STATE::ATTACK:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x + 10 - (_Img->getFrameWidth() * 0.5), _Center.y - 250, _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - 30 - (_Img->getFrameWidth() * 0.5), _Center.y - 250, _Ani, 200);
            }
            break;
        case BOSS_STATE::SLAP:
            break;
        case BOSS_STATE::GUARD:
            break;
        case BOSS_STATE::PUNCH:
            break;
        case BOSS_STATE::ROAR:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 210, _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 210, _Ani, 200);
            }
            break;
        case BOSS_STATE::IDLE_RUSH:

            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani, 200);
            }
            break;
        case BOSS_STATE::RIGHTRUSH:
            _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani, 200);

            break;
        case BOSS_STATE::LEFTRUSH:
            _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani, 200);

            break;
        case BOSS_STATE::RUSHTURN:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 200, _Ani, 200);
            }
            break;
        case BOSS_STATE::JUMP:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 250, _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 250, _Ani, 200);
            }
            break;
        case BOSS_STATE::UP:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), (_Center.y - 240 - _Jump), _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), (_Center.y - 240 - _Jump), _Ani, 200);
            }
            break;
        case BOSS_STATE::DOWN:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), (_Center.y - 240 - _Jump), _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), (_Center.y - 240 - _Jump), _Ani, 200);
            }
            break;
        case BOSS_STATE::LANDHIT:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani, 200);
            }
            break;
        case BOSS_STATE::HIT:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 230, _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 230, _Ani, 200);
            }
            break;
        case BOSS_STATE::GROUNDHIT:
            break;
        case BOSS_STATE::KNOCK:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 230 - _Jump, _Ani,200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 230 - _Jump, _Ani, 200);
            }
            break;
        case BOSS_STATE::SIT:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 150, _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 150, _Ani, 200);
            }
            break;
        case BOSS_STATE::WAKE:
            break;
        case BOSS_STATE::TAUNT:
            if (!_IsLookLeft)
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 285, _Ani, 200);
            }
            else
            {
                _Img->alphaAniRedRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 285, _Ani, 200);
            }
            break;
        case BOSS_STATE::DEAD:
            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5) - 50, _Center.y - 240, _Ani);
            }
            break;
        case BOSS_STATE::CRY:

            if (!_IsLookLeft)
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5), _Center.y - 240, _Ani);
            }
            else
            {
                _Img->aniRender(getMemDC(), _Center.x - (_Img->getFrameWidth() * 0.5) - 50, _Center.y - 240, _Ani);
            }
            break;
        }*/
    }
}

void Boss::RightIDLE(void* obj)
{
    Boss* b = (Boss*)obj;

    b->SetState(BOSS_STATE::IDLE);
    b->SetAni(KEYANIMANAGER->findAnimation("RightIdle"));
    b->GetAni()->start();
}

void Boss::LeftIDLE(void* obj)
{
    Boss* b = (Boss*)obj;

    b->SetState(BOSS_STATE::IDLE);
    b->SetAni(KEYANIMANAGER->findAnimation("LeftIdle"));
    b->GetAni()->start();
}

void Boss::RightRUSH(void* obj)
{
    Boss* b = (Boss*)obj;
    
    if (b->GetExState()== BOSS_STATE::ROAR)
    {
        b->SetState(BOSS_STATE::IDLE_RUSH);
        b->SetAni(KEYANIMANAGER->findAnimation("Right_Idle_Rush"));
        b->GetAni()->start();
    }
    else if (b->GetExState() == BOSS_STATE::IDLE_RUSH ||
             b->GetExState() == BOSS_STATE::RUSHTURN)
    {
        b->SetState(BOSS_STATE::RIGHTRUSH);
        b->SetAni(KEYANIMANAGER->findAnimation("RightRush"));
        b->GetAni()->start();
    }
    else
    {
        b->SetState(BOSS_STATE::IDLE);
        b->SetAni(KEYANIMANAGER->findAnimation("RightIdle"));
        b->GetAni()->start();
    }
}


void Boss::LeftRUSH(void* obj)
{
    Boss* b = (Boss*)obj;
    if (b->GetExState() == BOSS_STATE::ROAR)
    {
        b->SetState(BOSS_STATE::IDLE_RUSH);
        b->SetAni(KEYANIMANAGER->findAnimation("Left_Idle_Rush"));
        b->GetAni()->start();
    }
    else if (b->GetExState() == BOSS_STATE::IDLE_RUSH ||
             b->GetExState() == BOSS_STATE::RUSHTURN)
    {
        b->SetState(BOSS_STATE::LEFTRUSH);
        b->SetAni(KEYANIMANAGER->findAnimation("LeftRush"));
        b->GetAni()->start();
    }
    else
    {
        b->SetState(BOSS_STATE::IDLE);
        b->SetAni(KEYANIMANAGER->findAnimation("LeftIdle"));
        b->GetAni()->start();
    }
}

void Boss::RightTAUNT(void* obj)
{
    Boss* b = (Boss*)obj;

    b->SetState(BOSS_STATE::TAUNT);
    b->SetAni(KEYANIMANAGER->findAnimation("RightTaunt"));
    b->GetAni()->start();
}

void Boss::LeftTAUNT(void* obj)
{
    Boss* b = (Boss*)obj;

    b->SetState(BOSS_STATE::TAUNT);
    b->SetAni(KEYANIMANAGER->findAnimation("LeftTaunt"));
    b->GetAni()->start();
}

void Boss::RightJUMP(void* obj)
{
    Boss* b = (Boss*)obj;

    b->SetState(BOSS_STATE::UP);
    b->SetAni(KEYANIMANAGER->findAnimation("RightUp"));
    b->GetAni()->start();
}

void Boss::LeftTJUMP(void* obj)
{
    Boss* b = (Boss*)obj;

    b->SetState(BOSS_STATE::UP);
    b->SetAni(KEYANIMANAGER->findAnimation("LeftUp"));
    b->GetAni()->start();
}

void Boss::RightCRY(void* obj)
{
    Boss* b = (Boss*)obj;

    b->SetState(BOSS_STATE::CRY);
    b->SetAni(KEYANIMANAGER->findAnimation("RightCry"));
    b->GetAni()->start();
}

void Boss::LeftCRY(void* obj)
{
    Boss* b = (Boss*)obj;

    b->SetState(BOSS_STATE::CRY);
    b->SetAni(KEYANIMANAGER->findAnimation("LeftCry"));
    b->GetAni()->start();
}

void Boss::RightSIT(void* obj)
{
    Boss* b = (Boss*)obj;

    b->SetState(BOSS_STATE::SIT);
    b->SetAni(KEYANIMANAGER->findAnimation("RightSit"));
    b->GetAni()->start();
}

void Boss::LeftSIT(void* obj)
{
    Boss* b = (Boss*)obj;

    b->SetState(BOSS_STATE::SIT);
    b->SetAni(KEYANIMANAGER->findAnimation("LeftSit"));
    b->GetAni()->start();
}