// ConsoleApplication1.cpp: 定义控制台应用程序的入口点。
//
/*DE_test
*
*/
#include "stdafx.h"
#include <iostream>
#include <cmath>
#include <ctime>
#include <time.h>



//产生随机数，随机数为（0.0，1.0）
#define MC  5//并行数
#define dNUM   10//单数
int srcData0[dNUM][3] = //初始数据行数是单号，第一列是一单有几炉，第二列是一炉多少时间，第三列是洗炉时间
{ { 9,43,122 },
{ 6,43,145 },
{ 8,45,160 },
{ 8,50,135 },
{ 7,41,136 },
{ 7,42,141 },
{ 5,45,158 },
{ 5,48,120 },
{ 10,43,155 },
{ 10,40,180 }
};
int srcData[dNUM] = //初始数据行数
{ 631,403,680,670,559,576,541,480,740,760};
double Rand_Double(void)
{
	return static_cast<double>(rand()) / static_cast<double>(RAND_MAX);
}

//测试函数Hansen
//参数个数为50
int Hansen(int *p_pars)//p_pars指向一套单子的分配方案
{
	int result = 0;//返回的时间数
	
	int mx[MC];//中间值用来统计主机完成所有单子的 时间
	
	for (int i = 0; i < MC; i++)
	{
		mx[i] = 0;

	}
	for (int j = 0; j < dNUM; j++)
	{
		mx[p_pars[j]] += srcData[ j];//

	}

		
				
		
	for (int j = 0; j < MC; j++)//主机中最长的时间
	{
		if (mx[j] > result)
		{
			result = mx[j];
		}

	}

	return result;
}

class CFunction
{
public:
	void *m_p_fun;//指向测试函数的指针
	int m_pars_num;//参数个数
	double m_min;//下限
	double m_max;//上限
	bool m_pos;//求解最小值还是最大值，如果是最小值则m_pos为false，如果是最大值则m_pos为true
public:
	CFunction(void *p_fun, int pars_num, double min, double max, bool pos)
		:m_p_fun(p_fun), m_pars_num(pars_num), m_min(min), m_max(max), m_pos(pos)
	{
	}

	virtual int Compute(int *p_pars) = 0;
};

class CHansen :public CFunction
{
public:
	//注册函数
	CHansen(void)
		:CFunction(Hansen, dNUM, 0,4.0, false)
	{
	}

	int Compute(int *p_pars)
	{
		return Hansen(p_pars);
	}
};

//个体，表示 一套当单炉子分配方案
class CIndividual
{
public:
	int *m_p_DNA;//参数
	int m_f;//适应值
	int m_DNA_length;//DNA的长度
	


public:
	CIndividual(void)
		:m_f(0.0), m_DNA_length(0), m_p_DNA(NULL)
	{
	}

	~CIndividual(void)
	{
		if (m_p_DNA != NULL)
			delete[] m_p_DNA;
	}

	//初始化，分配内存空间
	void Ini(int pars_num)
	{
		m_DNA_length = pars_num;
		m_p_DNA = new int[m_DNA_length];
	}

	//假定两者分配的内存空间的大小一样
	CIndividual& operator=(CIndividual& ind)
	{
		m_f = ind.m_f;
		//m_DNA_length = ind.m_DNA_length;
		for (int i = 0; i<m_DNA_length; ++i)
		{
			m_p_DNA[i] = ind.m_p_DNA[i];
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream& o, CIndividual& ind)
	{
		return o << ind.m_f;
	}
};


int main()
{
   
		//---------------------------设置随机数------------------------------------
		srand((unsigned int)(time(NULL)));

	//获得参数
	int Num=20000, T=100;
	double zoom=0.5, cr=0.8;

	std::cout << "种群大小："<< Num<< std::endl;
	//cin >> Num;

	std::cout << "进化代数：" << T << std::endl;
	//cin >> T;

	std::cout << "缩放因子：" << zoom << std::endl;;
	//cin >> zoom;

	std::cout << "交叉因子：" << cr << std::endl;
//	cin >> cr;

	//----------------------对函数进行操作,注册函数------------------------------
	CHansen fun_Hansen;

	CFunction *p_fun = &fun_Hansen;//为了实现多态
	int pars_num = p_fun->m_pars_num;//参数个数
	double min = p_fun->m_min;//下限
	double max = p_fun->m_max;//上限
	bool pos = p_fun->m_pos;//求最大值还是最小值

							//----------------------注册种群,并分配内存空间-----------------------------
	CIndividual *p_old = new CIndividual[Num];
	CIndividual *p_new = new CIndividual[Num];
	for (int i = 0; i<Num; ++i)
	{
		p_old[i].Ini(pars_num);
		p_new[i].Ini(pars_num);
	}

	//-------------------------产生初始的随机种群--------------------------------
	for (int i = 0; i<Num; ++i)//对种群进行遍历
	{
		for (int j = 0; j<pars_num; ++j)//对参数列表进行遍历
			p_old[i].m_p_DNA[j] = (int)(Rand_Double()*(max - min) + min+0.5);
		p_old[i].m_f = p_fun->Compute(p_old[i].m_p_DNA);
	}

	CIndividual ind_best;
	ind_best.Ini(pars_num);

	for (int t = 0; t<T; ++t)//开始一代一代地进化
	{
		//显示结果
		ind_best = p_old[0];
		int besti = 0;
		for (int i = 1; i<Num; ++i)
		{
			if (pos == true && ind_best.m_f<p_old[i].m_f)//求最大值
				ind_best = p_old[i];
			else if (pos == false && ind_best.m_f > p_old[i].m_f)//求最小值
			{
				ind_best = p_old[i];
				besti = i;
			}
		}
		if (t == T - 1)
		{
			for (int j = 0; j < pars_num; j++)//对参数列表进行遍历
			{
				std::cout << p_old[besti].m_p_DNA[j]<<"\t";
				
			}
			std::cout <<  "\n";
		}
		std::cout<<"T:"<<t<<"Time:"<< ind_best << "\n";

		//差分变异
		for (int i = 0; i<Num; i++)//对种群进行遍历
		{
			//产生三个随机数
			int x1=0, x2=0, x3=0;
			
			while (x1 == i || x2 == i || x3 == i || x1 == x2 || x1 == x3
				|| x2 == x3) {// 取r1,r2,r3  
				x1 = rand() % Num;
				x2 = rand() % Num;
				x3 = rand() % Num;
			};

			for (int j = 0; j<pars_num; j++)//对参数列表进行遍历
			{
				p_new[i].m_p_DNA[j] = (int)(p_old[x1].m_p_DNA[j] + zoom * (p_old[x2].m_p_DNA[j] - p_old[x3].m_p_DNA[j])+0.5);
				if (p_new[i].m_p_DNA[j]<min || p_new[i].m_p_DNA[j]>max)//越界
					p_new[i].m_p_DNA[j] = p_old[i].m_p_DNA[j];

			
			}
		}

		//交叉操作，注意，交叉要对每个实数位进行交叉
		for (int i = 0; i<Num; ++i)//对种群进行遍历
		{
			for (int j = 0; j<pars_num; ++j)
			{
				if (Rand_Double()>cr)//不交叉
					p_new[i].m_p_DNA[j] = p_old[i].m_p_DNA[j];			

			}
			p_new[i].m_f = p_fun->Compute(p_new[i].m_p_DNA);
		}

		//选择操作
		for (int i = 0; i<Num; ++i)//对种群进行遍历
		{
			if (pos == true && p_new[i].m_f < p_old[i].m_f)//求最大值
				p_new[i] = p_old[i];
			else if (pos == false && p_new[i].m_f > p_old[i].m_f)//求最小值
				p_new[i] = p_old[i];
		}

		//交换
		CIndividual *p_tmp;
		p_tmp = p_old;
		p_old = p_new;
		p_new = p_tmp;
		//此时，新种群的值被保存到p_old中
	}
	char name;
	std::cin >> name;
	return 0;
}
