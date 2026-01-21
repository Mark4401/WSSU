#include <cstdio>
#include <cuda_runtime.h>
#include <chrono>

#define THREADS 256
#define BLOCKS 256

__device__ double bbp_term(int k) {
    double k_d = (double)k;
    double term = (4.0 / (8.0 * k_d + 1.0))
        - (2.0 / (8.0 * k_d + 4.0))
        - (1.0 / (8.0 * k_d + 5.0))
        - (1.0 / (8.0 * k_d + 6.0));
    return term;
}

__global__ void bbp_pi_kernel(double* output, int start_k) {
    int idx = blockIdx.x * blockDim.x + threadIdx.x;
    int k = start_k + idx;
    output[idx] = bbp_term(k);
}

extern "C" void CUDA_demo() {
    const int total_threads = THREADS * BLOCKS;
    double* d_output;
    cudaMalloc(&d_output, total_threads * sizeof(double));

    auto start = std::chrono::high_resolution_clock::now();
    const auto duration = std::chrono::minutes(2);
    auto last_print = start;

    int k_offset = 0;
    long long hexDigits = 0;

    while (std::chrono::high_resolution_clock::now() - start < duration) {
        bbp_pi_kernel << <BLOCKS, THREADS >> > (d_output, k_offset);
        cudaDeviceSynchronize();

        k_offset += total_threads;
        hexDigits += total_threads;

        auto now = std::chrono::high_resolution_clock::now();
        if (now - last_print >= std::chrono::seconds(1)) {
            last_print = now;

            printf("Elapsed: %lld sec | Hex digits computed: %lld\n",
                std::chrono::duration_cast<std::chrono::seconds>(now - start).count(),
                hexDigits);
        }
    }

    cudaFree(d_output);
    printf("Done. APP CALL\n");
}