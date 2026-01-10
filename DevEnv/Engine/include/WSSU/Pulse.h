#ifndef PULSE_H
#define PULSE_H

#include<WSSU/WSSU.h>

#ifdef __cplusplus
extern "C" {
#endif

	enum Start_Up_Properties
	{
		DPI_AWARENESS_TRUE,
		DPI_AWARENESS_FALSE
	};

	WSSU_API void Init_Program(enum Start_Up_Properties Option);

	WSSU_API bool System_Queue();

#ifdef __cplusplus
} // extern "C"
#endif



#endif // !PULSE_H
