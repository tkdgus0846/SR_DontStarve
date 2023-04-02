#pragma once

enum LOADINGID { LOADING_STAGE, LOADING_BOSS, LOADING_END };
enum WINMODE { MODE_FULL, MODE_WIN };

enum LAYERID { LAYER_ENVIRONMENT, LAYER_PLAYER, LAYER_MONSTER, LAYER_BULLET, LAYER_SKILL, LAYER_UI, LAYER_OBSTACLE, LAYER_CAMERA, LAYER_BOSS, LAYER_NPC, LAYER_ITEM, LAYER_END};

enum ANIMSTATE { IDLE, WALK, RUN, };


namespace Engine
{
	// ID_DYNAMIC : 매 프레임마다 갱신을 해야하는 컴포넌트 집단
	enum COMPONENTID{ID_DYNAMIC, ID_STATIC, ID_END };

	enum INFO {INFO_RIGHT, INFO_UP, INFO_LOOK, INFO_POS, INFO_END };
	enum ROTATION { ROT_X, ROT_Y, ROT_Z, ROT_END };
	enum TEXTYPE { TEX_NORMAL, TEX_CUBE, TEX_END };
	enum RENDERID { RENDER_PRIORITY, RENDER_ALPHA, RENDER_NONALPHA, RENDER_UI, RENDER_END };

	enum MOUSEKEYSTATE { DIM_LB, DIM_RB, DIM_MB, DIM_END };
	enum MOUSEMOVESTATE { DIMS_X, DIMS_Y, DIMS_Z, DIMS_END };
}
