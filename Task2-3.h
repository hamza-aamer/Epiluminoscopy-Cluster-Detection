#pragma once
#include <iostream>
#include "EasyBMP.h"
#include <time.h>
using namespace std;



int difference(int a,int b) {
	if (a > b) {
		return a - b;
	}
	else return b - a;
}





BMP Task23(BMP& Image, BMP& Image2, BMP& Image3) {
	cout << "Working on Task2....\n";


	int height = Image.TellWidth();
	int width = Image.TellHeight();


	srand(time(0));

	int rand1 = 0;
	int rand2 = 255;



	RGBApixel Pixel;
	RGBApixel Black;
	Black.Blue = 0;
	Black.Green = 0;
	Black.Red = 0;
	Black.Alpha = 0;
	RGBApixel White;
	White.Alpha = 255;
	White.Blue = 255;
	White.Green = 255;
	White.Red = 255;

	int mean1=rand1, mean2=rand2;
back:
	int** img;
	int** region;
	allocate(img, width, height);
	allocate(region, width, height);
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			Pixel=Image.GetPixel(x, y);
			img[x][y] = (Pixel.Red + Pixel.Blue + Pixel.Green) / 3;
			if (difference(img[x][y],mean1) < difference(img[x][y], mean2))
			{
				Image.SetPixel(x, y, White);
				region[x][y] = 1;
			}
			else
			{
				Image.SetPixel(x, y, Black);
				region[x][y] = 2;
			}
		}
	}


	int region1count=0, region2count=0;
	int region1total=0, region2total=0;

	
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if (region[x][y]==1) {
				region1count++;
				region1total += img[x][y];
			}
			if (region[x][y] == 2) {
				region2count++;
				region2total += img[x][y];
			}
		}
	}
	bool flag = 0;
	if (mean1!= region1total / region1count)
	{
		mean1 = region1total / region1count;
		flag = 1;
	}
	if (mean2 != region2total / region2count)
	{
		flag = 1;
		mean2 = region2total / region2count;
	}
	if (flag == 1)goto back;





	Image.WriteToFile("Result2.bmp");

	cout << "\tResult Image Saved!\n\n";



	//TASK3
	cout << "Working on Task3....\n";

	int FP = 0;
	int TP = 0;
	int FN = 0;

	int** q3p1;
	int** q3p2;
	allocate(q3p1, width, height);
	allocate(q3p2, width, height);

	int c1 = 0, c2 = 0, c3 = 0, c4 = 0;
	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			if (region[x][y] == 1)
			{
				q3p1[x][y] = 1;
				c1++;
			}
			else if (region[x][y] == 2)
			{
				q3p1[x][y] = 2;
				c2++;
			}
		}
	}

	RGBApixel get;

	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			get=Image2.GetPixel(x, y);
			if (get.Red == 0)
			{
				q3p2[x][y] = 2;
				c3++;
			}
			else
			{
				q3p2[x][y] = 1;
				c4++;
			}
		}
	}





	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {

			if (q3p1[x][y] == 1 && q3p2[x][y] == 1)
			{
				TP++;
				continue;
			}
			else if (q3p1[x][y] == 1 && q3p2[x][y] == 2)
			{
				FP++;
				continue;
			}
			else if (q3p1[x][y] == 2 && q3p2[x][y] == 1)
			{
				FN++;
				continue;
			}
		}
	}

	

	cout << "\n\nK-Means Cluster Results : \n";
	float dice;
	cout << " False Positive : "<<FP<<endl;
	cout << " False Negative : "<<FN<<endl;
	cout << " True Positive  : "<<TP<<endl;

	dice = (2 * (float)TP) / ((float)FN + (2 * (float)TP) + FP);
	cout << "Dice Coefficient : " << dice << endl;




	FP = 0;
	TP = 0;
	FN = 0;

	allocate(q3p2, width, height);

	RGBApixel temp;


	int amount;


	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			get = Image3.GetPixel(x, y);
			if (get.Red == 0)
			{
				q3p1[x][y] = 2;
			}
			else
			{
				q3p1[x][y] = 1;
			}
		}
	}

	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {
			get = Image2.GetPixel(x, y);
			if (get.Red == 0)
			{
				q3p2[x][y] = 2;
			}
			else
			{
				q3p2[x][y] = 1;
			}
		}
	}





	for (int x = 0; x < height; x++) {
		for (int y = 0; y < width; y++) {

			if (q3p1[x][y] ==1 &&  q3p2[x][y]==1)
			{
				TP++;
				continue;
			}
			else if (q3p1[x][y] == 1 && q3p2[x][y] == 2)
			{
				FP++;
				continue;
			}
			else if (q3p1[x][y]==2 && q3p2[x][y]==1)
			{
				FN++;
				continue;
			}

		}
	}





	cout << "\n\nConnected Labeling Results : \n";
	cout << " False Positive : " << FP << endl;
	cout << " False Negative : " << FN << endl;
	cout << " True Positive  : " << TP << endl;

	dice = (2 * (float)TP) / ((float)FN + (2 * (float)TP) + FP);
	cout << "Dice Coefficient : " << dice << endl;



	return Image;
}