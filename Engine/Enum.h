﻿#pragma once

enum LOADINGID { LOADING_STAGE, LOADING_BOSS, LOADING_END };
enum WINMODE { MODE_FULL, MODE_WIN };

enum LAYERID { LAYER_CAMERA, LAYER_ENVIRONMENT, LAYER_PLAYER, LAYER_MONSTER, LAYER_BULLET, LAYER_SKILL, LAYER_UI, LAYER_OBSTACLE, LAYER_BOSS, LAYER_NPC, LAYER_ITEM, LAYER_END};


enum ANIMSTATE {
	// 애니메이션들의 상태들을 최대한 예측해봤음. 여기서 필요한것들만 가져다 쓰면 됨. 다른 경우가 있다면 넣어도 됨. 이 이넘값들을 애니메이션 컴포넌트에 바인딩하면 자동으로 애니메이션 출력함.
	ANIM_IDLE, ANIM_WALK, ANIM_RUN, ANIM_JUMP, ANIM_ATTACK, ANIM_ATTACK2, ANIM_ATTACK3, ANIM_DAMAGED, ANIM_DAMAGED2, ANIM_DAMAGED3, ANIM_FLY, ANIM_SHOT, ANIM_END};

enum COLGROUP
{
	/* 충돌 레이어임. 그룹별로 충돌 검사를 하기위해서 구분하였음. 콜라이더를 넣어줄때 (클론할때) 세번째 매개변수로 넣어도 되고 콜리전 매니져의 Change_ColGroup 함수를 써도 됨.*/
	COL_ENVIRONMENT,
	COL_DETECTION,
	COL_PLAYER,
	COL_ENEMY,
	COL_PLAYERBULLET,
	COL_ENEMYBULLET,
	COL_OBJ,
	COL_END
};



enum COL_DIR
{
	/*	DIR_UP,DOWN: 월드좌표 y값으로 + 방향에서 충돌, - 방향에서 충돌
	DIR_RIGHT,LEFT: 월드좌표 x값으로 + 방향에서 충돌, - 방향에서 충돌
	DIR_FROMT,BACK: 월드좌표 z값으로 + 방향에서 충돌, - 방향에서 충돌 */
	DIR_UP = -1,
	DIR_DOWN = 1,
	DIR_LEFT = -2,
	DIR_RIGHT = 2,
	DIR_FRONT = -3,
	DIR_BACK = 3,
	DIR_END = 4
};

namespace Engine
{
	// ID_UPDATE: 업데이트랑 레이트 업데이트만 함.
	// ID_RENDER: 렌더만 부름.
	// ID_ALL: 둘다 함.
	// ID_STATIC: 아무것도 안함.
	enum COMPONENTID{ID_UPDATE, ID_RENDER, ID_ALL, ID_STATIC, ID_END };

	enum INFO {INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum ROTATION { ROT_X, ROT_Y, ROT_Z, ROT_END };
	enum TEXTYPE { TEX_NORMAL, TEX_CUBE, TEX_END };
	enum RENDERID { RENDER_PRIORITY, RENDER_ALPHA, RENDER_NONALPHA, RENDER_UI, RENDER_ALPHA_UI, RENDER_END };

	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };
	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };
}
