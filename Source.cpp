#include "EasyBMP.h"
#include <iostream>
#include "Task1.h"
#include "Task2-3.h"
#include "Task4.h"

using namespace std;



int main() {
	BMP Image1, Image2, Image3,Image4;
	IMGData IMG;

	Image1.ReadFromFile("Assignment 1/Segmented Outputs/mIMD004.bmp");
	Image2.ReadFromFile("Assignment 1/Original Images/IMD004.bmp");
	Image3.ReadFromFile("Assignment 1/Ground Truths/IMD004_lesion.bmp");
	Image4.ReadFromFile("Assignment 1/Segmented Outputs/mIMD004.bmp");

	Task1(Image1);
	Task23(Image2,Image3,Image1);
	IMG.Task4(Image1);


}

