/*************************************************************************
	> File Name: function.cpp
	> Author: leon
	> Mail: sjzlyl406@163.com 
	> Created Time: 2015年07月01日 星期三 14时24分13秒
 ************************************************************************/

#include"function.h"

double Doabs(double arg)
{
	return fabs(arg);
}

typedef double (*OneArgFunction) (double arg);
typedef double (*TwoArgFunction) (double arg1, double arg2);

static std::map<std::string, OneArgFunction> OneArgumentFunc;
static std::map<std::string, TwoArgFunction> TwoArgumentFunc;

static int LoadOneArgFunc()
{
	OneArgumentFunc["abs"]		= Doabs;
	OneArgumentFunc["acos"]		= acos;
	OneArgumentFunc["asin"]		= asin;
	OneArgumentFunc["atan"]		= atan;
	OneArgumentFunc["ceil"]		= ceil;
	OneArgumentFunc["cos"]		= cos;
	OneArgumentFunc["cosh"]		= cosh;
	OneArgumentFunc["exp"]		= exp;
	OneArgumentFunc["floor"]	= floor;
	OneArgumentFunc["log"]		= log;
	OneArgumentFunc["log10"]	= log10;
	OneArgumentFunc["sin"]		= sin;
	OneArgumentFunc["sqrt"]		= sqrt;
	OneArgumentFunc["tan"]		= tan;
	OneArgumentFunc["tanh"]		= tanh;

	return 0;
}
static int LoadTwoArgFunc()
{
	TwoArgumentFunc["pow"]		= pow;

	return 0;
}

static int DoLoadOneArgFunc = LoadOneArgFunc();
static int DoLoadTwoArgFunc = LoadTwoArgFunc();

Function::Function()
{
	program_ = "blanc";
	strFunc = "";
	num1 = num2 = 0.0;
	g_status = false;
}
Function::Function(const std::string &str) : program_(str)
{
	strFunc = "";
	num1 = num2 = 0.0;
	g_status = false;
}

const double Function::Evaluate()
{
	double result = 0.0;
	if(!Check()){
		std::stringstream ss;
		ss << "error : " << program_ << " is uncorrect" <<std::endl;
		throw std::runtime_error(ss.str());
	}
	if(!Explain()) {
		std::stringstream ss;
		ss << "error : " << program_ << " is uncorrect" <<std::endl;
		throw std::runtime_error(ss.str());
	}
	return Expression();
}
const double Function::Evaluate(std::string program)
{
	program_ = program;
	return Evaluate();
}

bool Function::Check()
{
	enum _state {
		alpha,
		LeftPar,
		digit,
		comma,
		pause
	}state = alpha;

	bool RetStatus = true;
	std::string::iterator iter = program_.begin();
	for(; iter != program_.end(); ++iter ) {
		switch(state) {
			case alpha: {
				if(isalpha(*iter))
					state = alpha;
				else if(*iter == '(')
					state = LeftPar;
				else if(*iter == '1' || *iter == '0')
					state = alpha;
				else
					RetStatus = false;
				break;
			}
			case LeftPar: {
				if(*iter == '+' || *iter == '-' || isdigit(*iter))
					state = digit;
				else
					RetStatus = false;
				break;
			}
			case digit: {
				if((isdigit(*iter)) ||
					(*iter == '.' && isdigit(*(iter+1))) || 
					(*iter == 'e' && isdigit(*(iter+1))))
					continue;
				else if(*iter == ',')
					state = comma;
				else if(*iter == ')')
					state = pause;
				else
					RetStatus = false;
				break;
			}
			case comma: {
				if((isdigit(*iter)) ||
					(*iter == '.' && isdigit(*(iter+1))) || 
					(*iter == 'e' && isdigit(*(iter+1))))
					state = digit;
				else
					RetStatus = false;
				break;
			}
			case pause: {
				RetStatus = false;
			}
			default: ;
		}
	}

	return RetStatus;
}

bool Function::Explain()
{
	std::string &program = program_;

	size_t indexWordEnd = program.find('(');
	strFunc = program.substr(0, indexWordEnd);

	size_t indexBegin = indexWordEnd+1;
	size_t indexEnd = program.size() - 1;
	size_t indexMid = program.find(',');

	if(indexMid == std::string::npos) {
		std::stringstream ss(program.substr(indexBegin,indexEnd));
		ss >> num1;
	}
	else {
		std::stringstream ss1(program.substr(indexBegin,indexMid-1));
		ss1 >> num1;
		std::stringstream ss2(program.substr(indexMid+1,indexEnd));
		ss2 >> num2;
	}
	return true;
}
const double Function::Expression()
{
	double result = 0.0;
	bool func1 = false, func2 = false;

	std::map<std::string, OneArgFunction>::iterator iter1;
	iter1 = OneArgumentFunc.find(strFunc);
	if(iter1 != OneArgumentFunc.end() ) {
		result = OneArgumentFunc[strFunc](num1);
		func1 = true;
	}

	std::map<std::string, TwoArgFunction>::iterator iter2;
	iter2 = TwoArgumentFunc.find(strFunc);
	if(iter2 != TwoArgumentFunc.end() ) {
		result = TwoArgumentFunc[strFunc](num1, num2);
		func2 = true;
	}

	g_status = func1 || func2;
	return result;
}

bool Function::GetState()
{
	if(strFunc == "")
		Evaluate();

	return g_status;
}


/**************** test ******************
int main(void)
{
	try{
		std::string str;
		std::cin >> str;

		Function ff(str);
		double ans = ff.Evaluate();

		if(ff.GetState())
			std::cout<< ans << std::endl;
		else
			std::cout<<"error: no return!" << std::endl;
	}
	catch(const std::exception &e){
		std::cout<< e.what() <<std::endl;
	}

	return 0;
}
*/

