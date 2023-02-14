#pragma once
#include <iostream>
using namespace std;


int pixelvalue(RGBApixel a) {
	if (a.Blue == 0)
		return 0;
	else
		return 1;
}


class Node
{
public:
	int data;
	Node* next;

	Node()
	{
		data = -1;
		next = 0;
	}

	Node(int d, Node* n)
	{
		data = d;
		next = n;
	}

	Node(int d)
	{
		data = d;
		next = 0;
	}

};

class IMGData {

public:

	Node* head;


	IMGData()
	{
		head = 0;
	}

	void insert(int d) {
		Node* point;
		point = head;
		Node* ptr = new Node(d);

		if (head == 0) {
			head = ptr;
			return;
		}

		while (point->next != 0) {
			point = point->next;
		}
		point->next = ptr;
	}




	void print() {
		Node* point = head;
		while (point->next != 0) {
			cout << point->data << endl;
			point = point->next;
		}
	}



	void Task4(BMP& Image) {
		cout << "\n\nWorking on Task4....\n";
		system("PAUSE");
		int height = Image.TellWidth();
		int width = Image.TellHeight();


		RGBApixel Pixel;

		int** img;
		allocate(img, width, height);
		for (int x = 0; x < height; x++) {
			for (int y = 0; y < width; y++) {
				Pixel = Image.GetPixel(x, y);
				if (Pixel.Blue == 0)
					img[x][y] = 0;
				else img[x][y] = 1;
			}
		}

		IMGData* Data = new IMGData[height + 1];
		Data[0].insert(height);
		Data[0].insert(width);

		bool flag = 1;

		for (int x = 0; x < height; x++) {
			flag = 1;

			for (int y = 0; y < width; y++) {
				if (img[x][y] == 1) {
					flag = 0;
				}
			}
			if (flag == 1) {
					Data[x+1].insert(-1);
			}
			else
			{
				for (int y = 0; y < width; y++) {
					if (img[x][y] == 1 && img[x][y - 1] == 0) {
						Data[x + 1].insert(y);
					}
					if (img[x][y] == 1 && img[x][y + 1] == 0) {
						Data[x + 1].insert(y);
					}
				}
				Data[x + 1].insert(-1);
			}
		}




		IMGData Task4;
		

		Node* point;
		for (int x = 0; x < height + 1; x++) {

			Node* point=Data[x].head;

			while (point!=NULL) {
				Task4.insert(point->data);
				point = point->next;
			}
		}


		point = Task4.head;
		cout << point->data << "  ";
		point = point->next;
		cout<<point->data << endl;
		point = point->next;
		while (point != NULL) {
			cout << point->data << ' ';
			if (point->data == -1)cout << endl;
			point = point->next;
		}

	}
};
