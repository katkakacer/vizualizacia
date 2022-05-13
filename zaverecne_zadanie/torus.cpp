#define _USE_MATH_DEFINES
#include <iostream>
#include<fstream>
#include<cmath>

int main()
{
    int r = 10, n = 30, R = 15;
    double krok1 = M_PI / (n + 1);
    double krok2 = 2 * M_PI / n;
    int pocet = 0;
    //double a1, a2;
    //double krok = 360 / n;
    //std::cout << "krok1=" << krok1 << " krok2=" << krok2 << "\n";
    std::ofstream file("torus.vtk");
    if (file.is_open()) {
        file << "# vtk DataFile Version 3.0" << std::endl;
        file << "torus\n";
        file << "ASCII\n";
        file << "DATASET POLYDATA\n";
        file << "POINTS " << n * n << " FLOAT\n";
        //generovanie bodov
        for (float j = krok1; j < 2 * M_PI - 0.005; j += krok2)
        {
            for (float i = 0; i < 2 * M_PI - 0.005; i += krok2)
            {
                file << (R+r * cos(i)) * cos(j) << " " << (R+r * cos(i)) * sin(j) << " " << r * sin(i) << "\n";
                //pocet++;
                //std::cout << i << " " << j << "\n";
            }
        }

        file << "POLYGONS " << 2 * n * n << " " << 2 * n * n * 4 << "\n";//polygony

        //for (size_t i = 1; i < n; i++)//horny ihlan
        //{
        //    file << "3 " << i << " " << i + 1 << " " << 0 << "\n";
        //}
        //file << "3 " << n << " 1 0 \n";

        for (size_t j = 0; j < n - 1; j++)
        {
            for (size_t i = 0; i < n - 1; i++)
            {
                file << "3 " << j * n + i << " " << j * n + i + 1 << " " << j * n + i + n << "\n";
                file << "3 " << j * n + i + n << " " << j * n + i + 1 << " " << j * n + i + n + 1 << "\n";
                pocet += 2;
            }
            file << "3 " << j * n + n - 1 << " " << j * n << " " << j * n + n + n - 1 << "\n";
            file << "3 " << j * n + n + n - 1 << " " << j * n << " " << j * n + n << "\n";
            pocet += 2;
        }

        for (size_t i = 0; i < n-1; i++)
        {
            file << "3 " << (n - 1) * n + i << " " << (n - 1) * n + i + 1 << " " << i << "\n";
            file << "3 " << i << " " << (n - 1) * n + i + 1 << " " << i + 1 << "\n";
            pocet += 2;
        }
        file << "3 " << (n - 1) * n + n - 1 << " " << (n - 1) * n << " " << 0 << "\n";
        file << "3 " << 0 << " " << (n - 1) * n + n - 1 << " " << n - 1 << "\n";
        pocet += 2;

        //for (size_t i = n * n - n + 1; i < n * n; i++)//spodny ihlan
        //{
        //    file << "3 " << i + 1 << " " << i << " " << n * n + 1 << "\n";
        //}
        //file << "3 " << n * n - n + 1 << " " << n * n << " " << n * n + 1 << "\n";

        std::cout << pocet;
        file.close();
    }

    return 0;
}