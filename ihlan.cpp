#define _USE_MATH_DEFINES 
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

int main() {
	int n=5;
	double r=5, h=10, x, y;
	double krok = 2 * M_PI / n;

	std::ofstream file("ihlan.vtk");

	if (file.is_open()) {
		file << "# vtk DataFile Version 3.0" << std::endl;
		file << "ihlan\n";
		file << "ASCII\n";
		file << "DATASET POLYDATA\n";
		file << "POINTS " << n + 1 << " FLOAT\n";
		
		for (size_t i = 0; i < n; i++)
		{
			x = r * cos(i * krok);
			y = r * sin(i * krok);
			file << x << " " << y << " 0\n";
		}
		file << "0 0 " << h << "\n";

		/*file << "LINES " << 2 * n << " " << 2 * n * 3 << "\n";
		for (size_t i = 0; i < n-1; i++)
		{
			file << "2 " << i << " " << i + 1 << "\n";
			file << "2 " << i << " " << n << "\n";
		}
		file << "2 " << n - 1 << " 0\n";
		file << "2 " << n - 1 << " " << n << "\n";*/

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

		file << "CELL_DATA " << n+1 << "\n";
		file << "SCALARS cell_scalars int 1\n";
		file << "LOOKUP_TABLE default\n";
		for (size_t i = 0; i < n+1; i++)
		{
			file << i << "\n";
		}
		file << "NORMALS cell_vectors float\n";
		for (size_t i = 0; i < n+1; i++)
		{
			file <<"1 0 0\n";
		}

		file << "POINT_DATA " << n + 1 << "\n";
		file << "SCALARS sample_scalars \nfloat 1\n";
		file << "LOOKUP_TABLE my_table\n";
		for (float i = 0; i < n + 1; i++)
		{
			file << i << ".0\n";
		}
		file << "LOOKUP_TABLE my_table\n9\n";
		for (float i = 0.1; i <= 1; i=i+0.1)
		{
			//file << i << " 0.0 0.0 1.0\n";
			file << "0.0 " << i << " 0.0 1.0\n";
		}
		

		file.close();
	}
	else {
		std::cout << "Subor sa nepodarilo otvorit!" << std::endl;
	}

	return 0;
}