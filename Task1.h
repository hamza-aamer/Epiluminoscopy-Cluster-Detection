#pragma once
#include <iostream>
#include "EasyBMP.h"
using namespace std;
void allocate(int**& array, int cols, int rows)
{
	array = new  int* [rows];
	for (int i = 0; i < rows; i++)
		array[i] = new int[cols]{0};
}



void ComponentReLabel(int **&label,int width,int height,int search, int write) {
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if (label[x][y] == search) {
				label[x][y] = write;
			}
		}
	}
}




RGBApixel makepixel(int alpha, int red, int green, int blue) {
	RGBApixel make;
	make.Alpha = alpha;
	make.Red = red;
	make.Green = green;
	make.Blue = blue;
	return make;
}


BMP Task1(BMP &Image) {
	cout << "Working on Task1....\n";
	int height = Image.TellWidth();
	int width = Image.TellHeight();
	RGBApixel Pixel;
	RGBApixel Black;
	Black.Blue = 0;
	Black.Green = 0;
	Black.Red = 0;
	Black.Alpha = 0;



	int** img;
	allocate(img, width, height);
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			Pixel = Image.GetPixel(x, y);
			img[x][y] = (Pixel.Red + Pixel.Blue + Pixel.Green) / 3;
		}
	}

	int counter=0;
	int** label;
	allocate(label, width, height);
	for (int x = 1; x < height-1; x++) {
		for (int y = 1; y < width-1; y++) {
			if (img[x][y] == 0) {
				label[x][y] = 0;
			}
			else {
				if (img[x][y - 1] == 0 && img[x - 1][y - 1] == 0 && img[x - 1][y] == 0 && img[x - 1][y + 1]==0) {
					counter++;
					label[x][y] = counter;
				}
				else if (img[x][y - 1] != 0) {
					label[x][y] = label[x][y - 1];
				}
				else if (img[x - 1][y - 1] != 0) {
					label[x][y] = label[x - 1][y - 1];
				}
				else if (img[x - 1][y] != 0) {
					label[x][y] = label[x - 1][y];
				}
				else if (img[x - 1][y + 1] != 0) {
					label[x][y] = label[x - 1][y + 1];
				}
			}
		}
	}

	for (int x = 0; x < 100; x++) {
	Recheck:

		for (int x = 1; x < height; x++) {
			for (int y = 1; y < width - 1; y++) {

				if (label[x][y] == 0)
					continue;
				else if (label[x][y - 1] != 0 && label[x][y - 1] != label[x][y]) {
					ComponentReLabel(label, width, height, label[x][y], label[x][y - 1]);
					goto Recheck;
				}
				else if (label[x - 1][y - 1] != 0 && label[x - 1][y - 1] != label[x][y]) {
					ComponentReLabel(label, width, height, label[x][y], label[x - 1][y - 1]);
					goto Recheck;
				}
				else if (label[x - 1][y] != 0 && label[x - 1][y] != label[x][y]) {
					ComponentReLabel(label, width, height, label[x][y], label[x - 1][y]);
					goto Recheck;
				}
				else if (label[x - 1][y + 1] != 0 && label[x - 1][y + 1] != label[x][y]) {
					ComponentReLabel(label, width, height, label[x][y], label[x - 1][y + 1]);
					goto Recheck;
				}

			}
		}

	}



	int* labels = new int[counter]{0};

	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if (label[x][y]>0)
			labels[label[x][y]]++;
		}
	}
	int maxlabel = labels[0];
	for (int x = 0; x < counter; x++) {
		if (labels[x] > maxlabel)
			maxlabel = x;
	}


	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			Image.SetPixel(x, y, Black);
		}
	}



	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if (label[x][y] ==maxlabel )
				Image.SetPixel(x, y, makepixel(255, 255, 255, 255));
		}
	}



	
	Image.WriteToFile("Result1.bmp");
	cout << "\tResult Image Saved!\n\n";

	return Image;
}




