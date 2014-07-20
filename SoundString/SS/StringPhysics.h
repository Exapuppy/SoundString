#ifndef _STRINGPHYSICS_H
#define _STRINGPHYSICS_H

# include <stdio.h>
# define _USE_MATH_DEFINES
# include <math.h>
# include <Windows.h>

# define COUNT 256//количество элементов на струне. 

typedef class tagInData
{
public:
	double l;//длина струны
	double Fn;//сила натяжения струны
	double p;//плотность струны
	double Ao;//первоначальное отклонение струны
public:
	tagInData(	double _l, double _Fn, double _p, double _Ao) : 
				l(_l), Fn(_Fn), p(_p), Ao(_Ao) {};
	tagInData(){};
}INDATA, *LPINDATA;

typedef class tagStringParam : public INDATA
{
public:
	float x[COUNT]; //
	float y[COUNT]; //текущие координаты точек

	float w;//циклическая частота
	float v_nyu;//частота(Гц)
	float T;//период

	float t;//текущее время

	float Ek;// кинет. энергия
	float Ep;// потенциальная.

	bool Go;
	int timespeed; // скорость течения времени
private:
	float pw;//Fn/ma
	float step;

	//доп. переменные для оптимизации
	//
	float par1, par2;
	double Ao2sin[COUNT];
	//

	void Standart()//задание стандартного набора параметров для струны(для тестов)
	{
	//Standart Data
		l = 1000;	//mm
		Fn = 40;		//H
		p = 1;	//gramm/mm
		t = 0;
		Ao = 100;	//mm
		timespeed = 1;
	//
	};
	void Calc_param()//расчет всяких штук
	{
		v_nyu = 1000*sqrt(Fn/p)/l;
		T=1/v_nyu;
		w = M_PI * v_nyu;
		step = l/COUNT;
		pw = Fn/(p*l*step*1e-6);//!!---
		Fill_x();
		register double Ao2 = Ao*Ao;
		par1 = ( M_PI - 1) * M_PI * Fn * Ao2 /( l * 1000) ;
		par2 = ( 1 - M_1_PI) * w * w * l * Ao2 * 1E-9 * p;

		register double Ao_2 = 2 * Ao;
		register double pi_l = M_PI/l;
		for(int i = COUNT - 1; i >= 0; i--)
			Ao2sin[i] = Ao_2 * sin(pi_l*x[i]);
	};
	void Fill_x() // просто расстановка точек по длине. каждой точке ставит ее положение на струне
	{
		x[COUNT - 1] = l - step;
		for(int c = COUNT - 2; c >= 0; c--)
			x[c] = c*step;
	};
public:
	tagStringParam(){Go=true;};
	void Create_First_String_Pos()
	{
		Standart();
		Calc_param();
		Fill_x();
		register double Ao_2 = 2 * Ao;
		register double pi_l = M_PI/l;
		for(int i = COUNT - 1; i >= 0; i--)
			y[i] = Ao_2*sin(pi_l*x[i]) * sin(w*t);
	};
	void WaveProcess()
	{
		t += 0.0002;
		//
		register double sin_wt = sin(w*t);
		register double sin_wt_2 = sin_wt * sin_wt;
		register double cos_wt_2 = 1 - sin_wt_2;
		Ek = par2 * cos_wt_2; Ep = par1 * sin_wt_2;
		//
		
		for(int i = COUNT - 1; i >= 0; i--)
			y[i] =  Ao2sin[i] * sin_wt;
	};
	void Ctrl_Reaction(int _value, int _typename)
	{
		switch(_typename)
		{
		case 0/*null*/:
			return;
		case 1/*But_Stop*/:
			Go = !Go;
			break;
		case 2/*But_Std*/:
			Standart();
			break;
		case 3/*L*/:
			l = _value;
			Fill_x();
			break;
		case 4/*L_UP*/:
			l += 1;
			Fill_x();
			break;
		case 5/*L_DOWN*/:
			l -= 1;
			Fill_x();
			break;
		case 9/*p*/:
			p = (float)_value/10;
			break;
		case 10/*p_UP*/:
			p += 1;
			break;
		case 11/*p_DOWN*/:
			p -= 1;
			break;
		case 12/*Fn*/:
			Fn = _value;
			break;
		case 13/*Fn_UP*/:
			Fn += 1;
			break;
		case 14/*Fn_DOWN*/:
			Fn -= 1;
			break;
		case 15/*Ao*/:
			Ao = _value;
			break;
		case 16/*Ao_UP*/:
			Ao += 1;
			break;
		case 17/*Ao_DOWN*/:
			Ao -= 1;
			break;
		case 19:
			timespeed = _value;
		default:
			break;
		}
		this->Calc_param();
	};
}STRINGPARAM, *LPSTRINGPARAM;

#endif