#define _USE_MATH_DEFINES
#include <iostream>
#include<fstream>
#include<cmath>

int main()
{
    int r=1,n=10;
    double krok1 = M_PI / (n+1);
    double krok2 = 2* M_PI / n;
    int pocet = 0;
    //double a1, a2;
    //double krok = 360 / n;
    std::cout << "krok1=" << krok1 << " krok2=" << krok2 << "\n";
    std::ofstream file("sfera.vtk");
    if (file.is_open()) {
        file << "# vtk DataFile Version 3.0" << std::endl;
        file << "sfera\n";
        file << "ASCII\n";
        file << "DATASET POLYDATA\n";
        file << "POINTS " << n*n+2<< " FLOAT\n";
        //generovanie bodov
        file << "0 0 " << r << "\n";       
        for (float j = krok1; j < M_PI-0.005; j+=krok1)
        {
            for (float i = 0; i < 2*M_PI-0.005; i+=krok2)
            {
                file << r * cos(i) * sin(j) << " " << r * sin(i) * sin(j) << " " << r * cos(j) << "\n";
                pocet++;
                std::cout << i << " " << j << "\n";
            }
        }
        file << "0 0 " << -r << "\n";
        
        file << "POLYGONS " << 2*n*(n-1)+2*n << " " << (2*n*(n-1)+2*n) * 4 << "\n";//polygony

        for (size_t i = 1; i < n; i++)//horny ihlan
        {
            file << "3 " << i << " " << i + 1 << " " << 0 << "\n";
        }
        file << "3 " << n <<" 1 0 \n";

        for (size_t j = 0; j < n-1; j++)
        {
            for (size_t i = 1; i < n; i++)
            {
                file << "3 " << j * n + i << " " << j * n + i + n << " " << j * n + i + 1 << "\n";
                file << "3 " << j * n + i + 1 << " " << j * n + i + n << " " << j * n + i + n + 1 << "\n";
            }
            file << "3 " << j * n + n << " " << j * n + n + n << " " << j * n + 1 << "\n";
            file << "3 " << j * n + 1 << " " << j * n + n + n << " " << j * n + n + 1 << "\n";
        }
               
        for (size_t i = n*n-n+1; i < n*n ; i++)//spodny ihlan
        {
            file << "3 " << i << " " << i + 1 << " " << n * n + 1 << "\n";
        }
        file << "3 " << n*n << " " << n * n -n+1<< " " << n * n + 1 << "\n";

        std::cout << pocet;
        file.close();
    }

    return 0;
}