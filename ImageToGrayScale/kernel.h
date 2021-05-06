#pragma once

void rgba_to_greyscale(unsigned char* dev_R, unsigned char* dev_G, unsigned char* dev_B, unsigned char* dev_OUT);
void rgba_to_greyscale_cpp(unsigned char* R, unsigned char* G, unsigned char* B, unsigned char* OUT, int numRows, int numCols);