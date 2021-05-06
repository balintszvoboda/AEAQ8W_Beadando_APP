
#include "cuda_runtime.h"
#include "device_launch_parameters.h"

#include <stdio.h>

__global__
void rgba_to_greyscale(unsigned char* dev_R, unsigned char* dev_G, unsigned char* dev_B, unsigned char* dev_OUT)
{
	int globalIdx = blockIdx.x * blockDim.x + threadIdx.x;

	dev_OUT[globalIdx] = .299f * (float)dev_R[globalIdx] + .587f * (float)dev_G[globalIdx] + .114f * (float)dev_B[globalIdx];
}

void rgba_to_greyscale_cpp(unsigned char* R, unsigned char* G, unsigned char* B, unsigned char* OUT,
	int numRows, int numCols) {

	unsigned char* dev_R;
	unsigned char* dev_G;
	unsigned char* dev_B;
	unsigned char* dev_OUT;

	int imageSize = numRows * numCols * sizeof(unsigned char);
	
	cudaMalloc((void**)&dev_R, imageSize);
	cudaMalloc((void**)&dev_G, imageSize);
	cudaMalloc((void**)&dev_B, imageSize);
	cudaMalloc((void**)&dev_OUT, imageSize);

	cudaMemcpy(dev_R, R, imageSize, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_G, G, imageSize, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_B, B, imageSize, cudaMemcpyHostToDevice);
	cudaMemcpy(dev_OUT, OUT, imageSize, cudaMemcpyHostToDevice);

	int gridSize = (numRows * numCols / 1024) + 1;
	int blockSize = numRows * numCols < 1024 ? numRows * numCols : 1024;

	rgba_to_greyscale << <gridSize, blockSize >> > (dev_R, dev_G, dev_B, dev_OUT);

	cudaMemcpy(OUT, dev_OUT, imageSize, cudaMemcpyDeviceToHost);

	cudaFree(dev_R);
	cudaFree(dev_G);
	cudaFree(dev_B);
	cudaFree(dev_OUT);
}
