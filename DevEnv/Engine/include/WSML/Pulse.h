#ifndef PULSE_H
#define PULSE_H

#include<WSML/WSML.h>

#ifdef __cplusplus
extern "C" {
#endif

	enum Start_Up_Properties
	{
		DPI_AWARENESS_TRUE,
		DPI_AWARENESS_FALSE
	};

	enum DWM
	{
		ENABLE_DWM_EDIT,
		DISABLE_DWM_EDIT
	};

	WSML_API void Init_Program(enum Start_Up_Properties Option, enum DWM Edit_Option);

	WSML_API bool System_Queue();

#ifdef __cplusplus
} // extern "C"
#endif



#endif // !PULSE_H
