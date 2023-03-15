/******************************************************************************/
/*!
\file		GateState_List.h
\brief		List of gate states available for the gate state machines
\author 	Ng Yuwen Felicia, 100%%


Copyright (C) 2021 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the
prior written consent of DigiPen Institute of Technology is prohibited.
 */
 /******************************************************************************/

#ifndef GATESTATELIST_H
#define GATESTATELIST_H
enum GATE_STATE
{
	STATE_NONE,
	STATE_GOING_UP,
	STATE_GOING_DOWN,
	STATE_TRIGGERED,
	STATE_PRESSED,
};
enum GATE_INNER_STATE
{
	GATE_INNER_STATE_ON_ENTER,
	GATE_INNER_STATE_ON_UPDATE,
	GATE_INNER_STATE_ON_EXIT
};

#endif

