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
	double xOrig;
	double yOrig;
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
	double Eps;
	double taum_p;
	int n;
	int k;
	int ih;
	cout << "Введите R:";
	cin >> R;
	cout << "Введите w:";
	cin >> w;
	cout << "Введите шаг:";
	cin >> step;
	cout << "Введите координаты M0:";
	cin >> x0;
	cin >> y0;
	xOrig = x0;
	yOrig = y0;
	cout << "Введите n:";
	cout << "Введите k:";
	cin >> n;
	cin >> k;
	vector <double> xf4;
	vector <double> xf3;
	vector <double> xf6;
	vector <double> xf5;
	vector <double> yf4;
	vector <double> yf3;
	vector <double> yf6;
	vector <double> yf5;
	vector <double> Gammaf4;
	vector <double> Gammaf3;
	vector <double> Gammaf6;
	vector <double> Gammaf5;
	vector <double> xf6p;
	vector <double> yf6p;
	vector <double> Gammaf6p;
	vector <double> Gammafih;
	vector <double> xfih;
	vector <double> yfih;
	int C1;
	int C2;

	double g2;
	double bd;
	double bd1;

	taum_p = 0;
	Eps = 0.00001;
	m = 0;
	gamma = step;
	ih = 0;

	do {
		for (int ix = 1; ix <= n; ix++)
		{
			eta0 = pow((y0*y0 - 2 * (w - 1)*x0), 0.5);
			if (ih = 0)
			{
				tau = 1 / (1 - w)*(y0 + eta0);
			}
			else
			{
				tau = 0;
			}
			y1 = R * eta0 + (w - 1)*(gamma - tau);
			x1 = (R*eta0 + (w - 1)*(gamma - tau)*0.5)*(gamma - tau);
			if ((x1 >= 0) && (tau < gamma) && (tau >= 0))
			{
				xf4.push_back(x1);
				yf4.push_back(y1);
				Gammaf4.push_back(gamma);
			}

			else
			{
				y1 = y0 + (w - 1)*gamma;
				x1 = x0 + gamma * y0 + (w - 1)*gamma*gamma / 2;
				m = 0;
				if (x1 < 0) goto next_cycle;
				else
				{
					xf3.push_back(x1);
					yf3.push_back(y1);
					Gammaf3.push_back(gamma);
				}
			}


			x2 = x1;
			y2 = y1;

			taum = 0;
			m = 0;
			do
			{
				taum_p = taum;
				m++;
				x1 = x2;
				y1 = y2;
				Rm = pow(R, m);

				g2 = 1 / (2 - gamma);


				bd = 1 / (gamma * (w - 1) + 2);


				bd1 = 1 / (R - 1);
				eta1 = (y2*y2 + 2 * (gamma*w*bd1 + 1)*x1);
				eta1 = pow(eta1, 0.5);
				taum = (2 - gamma)*bd*(y1 + bd1 * eta1*(1 + R - 2 * Rm));
				y2 = Rm * eta1 - (2 - gamma - taum)*(gamma * w * g2 + 1);
				x2 = Rm * eta1 - 0.5*(2 - gamma - taum)*(gamma * w*g2 + 1)*(2 - gamma - taum);
				/*
				if ((m > 1) && (ix > n - k))
				{
					xf6.push_back(x1);
					yf6.push_back(y1);
					Gammaf6.push_back(gamma);
				}
				*/
			} while (((x2 >= 0) || ((taum >= 0) && (taum <= 2 - gamma))) && (abs(taum - taum_p) > Eps));



			if (m == 1)
			{
				x2 = x1 + (2 - gamma)*y1 - 0.5*gamma * (w - 1) + 2 * (2 - gamma);
				if (x2 >= 0)
				{
					y2 = y1 - (w - 1)*gamma - 2;
					if (ix > n - k)
					{
						xf5.push_back(x2);
						yf5.push_back(y2);
						Gammaf5.push_back(gamma);
					}
				}
			}
			else if (abs(taum - taum_p) > Eps)
			{
				C1 = y1 - taum_p + 2 * log(taum_p);
				C2 = x1 - (taum_p*taum_p)*0.5 + 2 * taum_p*log(taum_p);
				y2 = (2 - gamma) - 2 * log(2 - gamma) + C1;
				x2 = 0.5*(2 - gamma)*(2 - gamma) + (2 - gamma)*(C1 + 2) - 2 * (2 - gamma)*log(2 - gamma) + C2;
				if (ix > n - k)
				{
					xf6p.push_back(x2);
					yf6p.push_back(y2);
					Gammaf6p.push_back(gamma);
				}
				else
				{
					if (ix > n - k)
					{
						xfih.push_back(x2);
						yfih.push_back(y2);
						Gammafih.push_back(gamma);
					}
					x2 = 0;
					y2 = 0;
					ih = 1;
				}
			}
			x0 = x2;
			y0 = y2;
		}
	next_cycle:
		x0 = xOrig;
		y0 = yOrig;
		gamma = gamma + step;
	} while (gamma < 2);

	ofstream myfilef4;
	myfilef4.open("resultsf4.csv");

	for (int i = 0; i < xf4.size(); i++)
	{
		myfilef4 << xf4[i] << ";" << yf4[i] << ";" << Gammaf4[i] << "\n";
	}
	myfilef4.close();

	ofstream myfilef3;
	myfilef3.open("resultsf3.csv");

	for (int i = 0; i < xf3.size(); i++)
	{
		myfilef3 << xf3[i] << ";" << yf3[i] << ";" << Gammaf3[i] << "\n";
	}
	myfilef3.close();

	ofstream myfilef6;
	myfilef6.open("resultsf6.csv");

	for (int i = 0; i < xf6.size(); i++)
	{
		myfilef6 << xf6[i] << ";" << yf6[i] << ";" << Gammaf6[i] << "\n";
	}
	myfilef6.close();

	ofstream myfilef5;
	myfilef5.open("resultsf5.csv");

	for (int i = 0; i < xf5.size(); i++)
	{
		myfilef5 << xf5[i] << ";" << yf5[i] << ";" << Gammaf5[i] << "\n";
	}
	myfilef5.close();

	ofstream myfilef6p;
	myfilef6p.open("resultsf6p.csv");

	for (int i = 0; i < xf6p.size(); i++)
	{
		myfilef6p << xf6p[i] << ";" << yf6p[i] << ";" << Gammaf6p[i] << "\n";
	}
	myfilef6p.close();

	ofstream myfilefih;
	myfilefih.open("resultsfih.csv");

	for (int i = 0; i < xfih.size(); i++)
	{
		myfilefih << xfih[i] << ";" << yfih[i] << ";" << Gammafih[i] << "\n";
	}
	myfilefih.close();










}


