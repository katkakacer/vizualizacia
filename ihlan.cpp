#define _USE_MATH_DEFINES 
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

void ihlan(int n) {

}

int main() {
	int n=3;
	double r=5, alfa=0, h=10, x, y;
	double krok = 2 * M_PI / n;

	std::ofstream file("ihlan.vtk");

	if (file.is_open()) {
		file << "# vtk DataFile Version 3.0" << std::endl;
		file << "ihlan\n";
		file << "ASCII\n";
		file << "DATASET POLYDATA\n";
		file << "POINTS " << n + 1 << " FLOAT\n";
		
		//x = r * cos(alfa);
		//y = r * sin(alfa);
		//file << x << " " << y << " 0\n";
		for (size_t i = 0; i < n; i++)
		{
			x = r * cos(alfa + i * krok);
			y = r * sin(alfa + i * krok);
			file << x << " " << y << " 0\n";
		}
		file << "0 0 " << h << "\n";

		file << "LINES " << 2 * n << " " << 2 * n * 3 << "\n";
		for (size_t i = 0; i < n-1; i++)
		{
			file << "2 " << i << " " << i + 1 << "\n";
			file << "2 " << i << " " << n << "\n";
		}
		file << "2 " << n - 1 << " 0\n";
		file << "2 " << n - 1 << " " << n << "\n";

		file << "POLYGONS " << n + 1 << " " << (n + 1) * 4 + n - 3 << "\n";
		for (size_t i = 0; i < n-1; i++)
		{
			file << "3 " << i << " " << i + 1 << " " << n << "\n";
		}
		file << "3 " << n - 1 << " 0 " << n << "\n";
		file << n << " ";
		for (size_t i = 0; i < n; i++)
		{
			file << i << " ";
		}
		file << "\n";
		/*file << "5\nsluchadla\ngbl\n10\n80\n";
		file << "6\nklavesnica\ngenius\n10\n20\n";
		file << "7\nmys\nbloody\n10\n45\n";
		file << "8\nhodinky\nxiaomi\n10\n50\n";
		file << "9\nhodinky\napple\n10\n250\n";
		file << "10\nmobil\nxiaomi\n10\n200\n";
		file << "11\nmobil\napple\n10\n350\n";*/
		file.close();
	}
	else {
		std::cout << "Subor sa nepodarilo otvorit!" << std::endl;
	}
}