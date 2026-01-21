#ifndef CUDA_DEFS_H
#define CUDA_DEFS_H

extern "C" void library_Cuda_demo();

#define __CUDA__ extern "C"

__CUDA__ void Test_CU();

#endif // !CUDA_DEFS_H
