#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>

using namespace std;

int main()
{
	setlocale(LC_ALL, "Russian");
	double x0;
	double y0;
	double x1;
	double y1;
	double x2;
	double y2;
	int m;
	double step;
	double gamma;
	double R;
	double w;
	double tau;
	double taum;
	double eta0;
	double eta1;
	double Rm;
	cout << "¬ведите R:";
	cin >> R;
	cout << "¬ведите w:";
	cin >> w;
	cout << "¬ведите шаг:";
	cin >> step;
	cout << "¬ведите координаты M0:";
	cin >> x0;
	cin >> y0;
	vector <double> x;
	vector <double> y;
	vector <double> Gamma;

	ofstream myfile;
	myfile.open("results.csv");
	
	

	m = 0;
	gamma = step;

	do {
		eta0 = pow((y0*y0 - 2 * (w - 1)*x0), 0.5);
		tau = pow((1 - w), -1)*(y0 + eta0);
		y1 = R * eta0 + (w - 1)*(gamma - tau);
		x1 = (R*eta0 + (w - 1)*(gamma - tau)*0.5)*(gamma - tau);


		if (x1 < 0)
		{
			y1 = y0 + (w - 1)*gamma;
			x1 = x0 + gamma * y0 + (w - 1)*pow(gamma, 2) / 2;
			m = 0;
			if (x1 < 0) goto next_cycle;
		}

		x.push_back(x1);
		y.push_back(y1);
		Gamma.push_back(gamma);
		x2 = x1;
		y2 = x1;

		do
		{
			do
			{
				m++;
				x1 = x2;
				y1 = y2;
				Rm = pow(R, m);
				long double g2;
				g2 = pow((2 - gamma), -1);
				long double bd;
				{
					bd = gamma * (w - 1) + 2;
					bd = pow(bd, -1);
				}
				long double bd1;
				bd1 = pow((R - 1), -1);
				eta1 = (y2*y2 + 2 * (gamma*w*bd1 + 1)*x1);
				eta1 = (eta1, 0.5);
				taum = (2 - gamma)*bd*(y1 + bd1 * eta1*(1 + R - 2 * Rm));
				y2 = Rm * eta1 - (2 - gamma - taum)*(gamma * w * g2 + 1);
				x2 = Rm * eta1 - 0.5*(2 - gamma - taum)*(gamma * w*g2 + 1)*(2 - gamma - taum);
			} while (x2 >= 0);
			x2 = x1 + (2 - gamma)*y1 - 0.5*gamma * (w - 1) + 2 * (2 - gamma);
			y2 = y1 - (w - 1)*gamma - 2;
			x.push_back(x2);
			y.push_back(y2);
			Gamma.push_back(gamma);
		} while ((x2 >= 0) || (m <= 100));
next_cycle:
		gamma = gamma + step;
	} while (gamma < 2);

	
	for (int i = 0; i < x.size(); i++)
	{
		myfile << x[i]<<";"<<y[i]<<";"<<Gamma[i]<<"\n";
	}
	myfile.close();

	


	
		


}