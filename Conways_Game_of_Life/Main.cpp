#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <ctime>
using namespace std;

HWND myconsole = GetConsoleWindow();
HDC mydc = GetDC(myconsole);

int main() {
	const int size = 301;
	int main_arr[size][size];
	int updated_arr[size][size];

	//Randomized map generation
	srand(time(0));
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			int chance = rand() % 2;
			main_arr[i][j] = chance;
			updated_arr[i][j] = chance;
		}
	}

	//Map generation
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (i == j || size - 1 - i == j) {
				main_arr[i][j] = 1;
				updated_arr[i][j] = 1;
			}
		}
	}

	//Initial print
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (main_arr[i][j] == 1) {
				SetPixel(mydc, 1 + j, 17 + i, RGB(255, 255, 255));
			}
			else {
				SetPixel(mydc, 1 + j, 17 + i, RGB(0, 0, 0));
			}
		}
	}

	//Border
	for (int i = 0; i < size + 2; i++) {
		for (int j = 0; j < size + 2; j++) {
			if (i == 0 || i == size + 1 || j == 0 || j == size + 1) {
				SetPixel(mydc, i, 16 + j, RGB(255, 90, 0));
			}
		}
	}

	//Game loop
	while (true) {
		//Look at all the nodes
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				int count = 0;
				//Look at all the neighbours
				if (i > 0) {
					count += main_arr[i - 1][j];
					if (j > 0) {
						count += main_arr[i - 1][j - 1];
					}
					else {
						count += main_arr[i - 1][size - 1];
					}
					if (j < size - 1) {
						count += main_arr[i - 1][j + 1];
					}
					else {
						count += main_arr[i - 1][0];
					}
				}
				else {
					count += main_arr[size - 1][j];
					if (j > 0) {
						count += main_arr[size - 1][j - 1];
					}
					else {
						count += main_arr[size - 1][size - 1];
					}
					if (j < size - 1) {
						count += main_arr[size - 1][j + 1];
					}
					else {
						count += main_arr[size - 1][0];
					}
				}
				if (j > 0) {
					count += main_arr[i][j - 1];
				}
				else {
					count += main_arr[i][size - 1];
				}
				if (j < size - 1) {
					count += main_arr[i][j + 1];
				}
				else {
					count += main_arr[i][0];
				}
				if (i < size - 1) {
					count += main_arr[i + 1][j];
					if (j > 0) {
						count += main_arr[i + 1][j - 1];
					}
					else {
						count += main_arr[i + 1][size - 1];
					}
					if (j < size - 1) {
						count += main_arr[i + 1][j + 1];
					}
					else {
						count += main_arr[i + 1][0];
					}
				}
				else {
					count += main_arr[0][j];
					if (j > 0) {
						count += main_arr[0][j - 1];
					}
					else {
						count += main_arr[0][size - 1];
					}
					if (j < size - 1) {
						count += main_arr[0][j + 1];
					}
					else {
						count += main_arr[0][0];
					}
				}

				//Change the state of the node
				if (main_arr[i][j] == 1 && (count < 2 || count > 3)) {
					updated_arr[i][j] = 0;
				}
				else if (main_arr[i][j] == 0 && count == 3) {
					updated_arr[i][j] = 1;
				}
			}
		}

		//Draw the new changes of the map
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				if (main_arr[i][j] != updated_arr[i][j]) {
					if (updated_arr[i][j] == 1) {
						SetPixel(mydc, 1 + j, 17 + i, RGB(255, 255, 255));
					}
					else {
						SetPixel(mydc, 1 + j, 17 + i, RGB(0, 0, 0));
					}
				}
			}
		}

		//Update the main_map
		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size; j++) {
				main_arr[i][j] = updated_arr[i][j];
			}
		}

		//Sleep(38);
	}

	cin.ignore();
	return 0;
}