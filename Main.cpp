// ============================================================================
//
// This file contains the actions, conditions and expressions your object uses
// 
// ============================================================================

#include "Common.h"
#include "ParamHelp.h"

// ============================================================================
//
// CONDITIONS
// 
// ============================================================================

CONDITION(
	/* ID */			0,
	/* Name */			"%o: On Function %0",
	/* Flags */			EVFLAGS_NOTABLE,
	/* Params */		(1,PARAM_STRING,"Function Name")
) {
	return(rdPtr->Funcs.top().Name == StrParam());
}

CONDITION(
	/* ID */			1,
	/* Name */			"%o: Function %0",
	/* Flags */			EVFLAGS_ALWAYS|EVFLAGS_NOTABLE,
	/* Params */		(2,PARAM_STRING,"Function Name",PARAM_NUMBER,"Clear Parameters after Function? 0 = yes, anything else = no")
) {
	rdPtr->Temps.top().Name = StrParam();
	rdPtr->Funcs.push(rdPtr->Temps.top());
	rdPtr->rRd->GenerateEvent(0);
	rdPtr->Temps.top() = rdPtr->Funcs.top();
	rdPtr->Funcs.pop();
	if(!lParam())
	{
		rdPtr->Temps.top().IntParams.clear();
		rdPtr->Temps.top().FloatParams.clear();
		rdPtr->Temps.top().StringParams.clear();
	}
	return(rdPtr->Temps.top().IntReturn);
}

// ============================================================================
//
// ACTIONS
// 
// ============================================================================

ACTION(
	/* ID */			0,
	/* Name */			"Set String Parameter %0 to %1",
	/* Flags */			0,
	/* Params */		(2,PARAM_STRING,"String Parameter Name",PARAM_STRING,"String Parameter")
) {
	string ParamName = StrParam();
	string Param = StrParam();
	rdPtr->Temps.top().StringParams[ParamName] = Param;
}

ACTION(
	/* ID */			1,
	/* Name */			"Set Integer Parameter %0 to %1",
	/* Flags */			0,
	/* Params */		(2,PARAM_STRING,"Integer Parameter Name",PARAM_NUMBER,"Integer Parameter")
) {
	string ParamName = StrParam();
	signed int Param = lParam();
	rdPtr->Temps.top().IntParams[ParamName] = Param;
}

ACTION(
	/* ID */			2,
	/* Name */			"Set Float Parameter %0 to %1",
	/* Flags */			0,
	/* Params */		(2,PARAM_STRING,"Float Parameter Name",PARAM_NUMBER,"Float Parameter")
) {
	string ParamName = StrParam();
	float Param = fParam();
	rdPtr->Temps.top().FloatParams[ParamName] = Param;
}

ACTION(
	/* ID */			3,
	/* Name */			"Call Function %0 (Don't Clear Params = %1)",
	/* Flags */			0,
	/* Params */		(2,PARAM_STRING,"Function Name",PARAM_NUMBER,"Clear Parameters after Function? 0 = yes, anything else = no")
) {
	rdPtr->Temps.top().Name = StrParam();
	rdPtr->Funcs.push(rdPtr->Temps.top());
	rdPtr->Temps.push(Function());
	rdPtr->rRd->GenerateEvent(0);
	Function Temp = rdPtr->Funcs.top();
	rdPtr->Funcs.pop();
	rdPtr->Temps.pop();
	rdPtr->Temps.top() = Temp;
	if(!lParam())
	{
		rdPtr->Temps.top().IntParams.clear();
		rdPtr->Temps.top().FloatParams.clear();
		rdPtr->Temps.top().StringParams.clear();
	}
}

ACTION(
	/* ID */			4,
	/* Name */			"Set Integer Return to %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_NUMBER,"Integer Return Value")
) {
	int Return = lParam();
	if(!rdPtr->Funcs.empty())
	{
		rdPtr->Funcs.top().IntReturn = Return;
	}
}

ACTION(
	/* ID */			5,
	/* Name */			"Set Float Return to %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_NUMBER,"Float Return Value")
) {
	float Return = fParam();
	if(!rdPtr->Funcs.empty())
	{
		rdPtr->Funcs.top().FloatReturn = Return;
	}
}

ACTION(
	/* ID */			6,
	/* Name */			"Set String Return to %0",
	/* Flags */			0,
	/* Params */		(1,PARAM_STRING,"String Return Value")
) {
	string Return = StrParam();
	if(!rdPtr->Funcs.empty())
	{
		rdPtr->Funcs.top().StringReturn = Return;
	}
}

// ============================================================================
//
// EXPRESSIONS
// 
// ============================================================================

EXPRESSION(
	/* ID */			0,
	/* Name */			"Current Function$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(0)
) {
	if(!rdPtr->Funcs.empty())
	{
		ReturnStringSafe(rdPtr->Funcs.top().Name.c_str());
	}
	ReturnString("");
}

EXPRESSION(
	/* ID */			1,
	/* Name */			"Integer Params(",
	/* Flags */			0,
	/* Params */		(0)
) {
	if(!rdPtr->Funcs.empty())
	{
		return(rdPtr->Funcs.top().IntParams.size());
	}
	return(0);
}

EXPRESSION(
	/* ID */			2,
	/* Name */			"Float Params(",
	/* Flags */			0,
	/* Params */		(0)
) {
	if(!rdPtr->Funcs.empty())
	{
		return(rdPtr->Funcs.top().FloatParams.size());
	}
	return(0);
}

EXPRESSION(
	/* ID */			3,
	/* Name */			"String Params(",
	/* Flags */			0,
	/* Params */		(0)
) {
	if(!rdPtr->Funcs.empty())
	{
		return(rdPtr->Funcs.top().StringParams.size());
	}
	return(0);
}

EXPRESSION(
	/* ID */			4,
	/* Name */			"Integer Function(",
	/* Flags */			0,
	/* Params */		(2,EXPPARAM_STRING,"Function Name",EXPPARAM_NUMBER,"Clear Parameters after Function? 0 = yes, anything else = no")
) {
	rdPtr->Temps.top().Name = EStrParam();
	rdPtr->Funcs.push(rdPtr->Temps.top());
	rdPtr->Temps.push(Function());
	rdPtr->rRd->GenerateEvent(0);
	Function Temp = rdPtr->Funcs.top();
	rdPtr->Funcs.pop();
	rdPtr->Temps.pop();
	rdPtr->Temps.top() = Temp;
	if(!xlParam())
	{
		rdPtr->Temps.top().IntParams.clear();
		rdPtr->Temps.top().FloatParams.clear();
		rdPtr->Temps.top().StringParams.clear();
	}
	return(rdPtr->Temps.top().IntReturn);
}

EXPRESSION(
	/* ID */			5,
	/* Name */			"Float Function(",
	/* Flags */			EXPFLAG_DOUBLE,
	/* Params */		(2,EXPPARAM_STRING,"Function Name",EXPPARAM_NUMBER,"Clear Parameters after Function? 0 = yes, anything else = no")
) {
	rdPtr->Temps.top().Name = EStrParam();
	rdPtr->Funcs.push(rdPtr->Temps.top());
	rdPtr->Temps.push(Function());
	rdPtr->rRd->GenerateEvent(0);
	Function Temp = rdPtr->Funcs.top();
	rdPtr->Funcs.pop();
	rdPtr->Temps.pop();
	rdPtr->Temps.top() = Temp;
	if(!xlParam())
	{
		rdPtr->Temps.top().IntParams.clear();
		rdPtr->Temps.top().FloatParams.clear();
		rdPtr->Temps.top().StringParams.clear();
	}
	ReturnFloat(rdPtr->Temps.top().FloatReturn);
}

EXPRESSION(
	/* ID */			6,
	/* Name */			"String Function$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(2,EXPPARAM_STRING,"Function Name",EXPPARAM_NUMBER,"Clear Parameters after Function? 0 = yes, anything else = no")
) {
	rdPtr->Temps.top().Name = EStrParam();
	rdPtr->Funcs.push(rdPtr->Temps.top());
	rdPtr->Temps.push(Function());
	rdPtr->rRd->GenerateEvent(0);
	Function Temp = rdPtr->Funcs.top();
	rdPtr->Funcs.pop();
	rdPtr->Temps.pop();
	rdPtr->Temps.top() = Temp;
	if(!xlParam())
	{
		rdPtr->Temps.top().IntParams.clear();
		rdPtr->Temps.top().FloatParams.clear();
		rdPtr->Temps.top().StringParams.clear();
	}
	ReturnStringSafe(rdPtr->Temps.top().StringReturn.c_str());
}

EXPRESSION(
	/* ID */			7,
	/* Name */			"Integer Parameter(",
	/* Flags */			0,
	/* Params */		(1,EXPPARAM_STRING,"Parameter Name")
) {
	if(!rdPtr->Funcs.empty())
	{
		return(rdPtr->Funcs.top().IntParams[EStrParam()]);
	}
	EStrParam();
	return(0);
}

EXPRESSION(
	/* ID */			8,
	/* Name */			"Float Parameter(",
	/* Flags */			EXPFLAG_DOUBLE,
	/* Params */		(1,EXPPARAM_STRING,"Parameter Name")
) {
	if(!rdPtr->Funcs.empty())
	{
		ReturnFloat(rdPtr->Funcs.top().FloatParams[EStrParam()]);
	}
	EStrParam();
	ReturnFloat(0.0);
}

EXPRESSION(
	/* ID */			9,
	/* Name */			"String Parameter$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(1,EXPPARAM_STRING,"Parameter Name")
) {
	string ParamName = EStrParam();
	if(!rdPtr->Funcs.empty())
	{
		ReturnStringSafe(rdPtr->Funcs.top().StringParams[ParamName].c_str());
	}
	ReturnString("");
}

EXPRESSION(
	/* ID */			10,
	/* Name */			"Integer Return(",
	/* Flags */			0,
	/* Params */		(0)
) {
	return(rdPtr->Temps.top().IntReturn);
}

EXPRESSION(
	/* ID */			11,
	/* Name */			"Float Return(",
	/* Flags */			EXPFLAG_DOUBLE,
	/* Params */		(0)
) {
	ReturnFloat(rdPtr->Temps.top().FloatReturn);
}

EXPRESSION(
	/* ID */			12,
	/* Name */			"String Return$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(0)
) {
	ReturnStringSafe(rdPtr->Temps.top().StringReturn.c_str());
}

EXPRESSION(
	/* ID */			13,
	/* Name */			"Set Integer Parameter(",
	/* Flags */			0,
	/* Params */		(2,EXPPARAM_STRING,"Integer Parameter Name",EXPPARAM_NUMBER,"Integer Parameter")
) {
	string ParamName = EStrParam();
	signed int Param = xlParam();
	rdPtr->Temps.top().IntParams[ParamName] = Param;
	return(0);
}

EXPRESSION(
	/* ID */			14,
	/* Name */			"Set Integer Parameter$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(2,EXPPARAM_STRING,"Integer Parameter Name",EXPPARAM_NUMBER,"Integer Parameter")
) {
	string ParamName = EStrParam();
	signed int Param = xlParam();
	rdPtr->Temps.top().IntParams[ParamName] = Param;
	ReturnString("");
}

EXPRESSION(
	/* ID */			15,
	/* Name */			"Set Float Parameter(",
	/* Flags */			0,
	/* Params */		(2,EXPPARAM_STRING,"Float Parameter Name",EXPPARAM_NUMBER,"Float Parameter")
) {
	string ParamName = EStrParam();
	float Param = xfParam();
	rdPtr->Temps.top().FloatParams[ParamName] = Param;
	return(0);
}

EXPRESSION(
	/* ID */			16,
	/* Name */			"Set Float Parameter$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(2,EXPPARAM_STRING,"Float Parameter Name",EXPPARAM_NUMBER,"Float Parameter")
) {
	string ParamName = EStrParam();
	float Param = xfParam();
	rdPtr->Temps.top().FloatParams[ParamName] = Param;
	ReturnString("");
}

EXPRESSION(
	/* ID */			17,
	/* Name */			"Set String Parameter(",
	/* Flags */			0,
	/* Params */		(2,EXPPARAM_STRING,"String Parameter Name",EXPPARAM_STRING,"String Parameter")
) {
	string ParamName = EStrParam();
	string Param = EStrParam();
	rdPtr->Temps.top().StringParams[ParamName] = Param;
	return(0);
}

EXPRESSION(
	/* ID */			18,
	/* Name */			"Set String Parameter$(",
	/* Flags */			EXPFLAG_STRING,
	/* Params */		(2,EXPPARAM_STRING,"String Parameter Name",EXPPARAM_STRING,"String Parameter")
) {
	string ParamName = EStrParam();
	string Param = EStrParam();
	rdPtr->Temps.top().StringParams[ParamName] = Param;
	ReturnString("");
}