/*************************************************************************
	> File Name: calcultor.cpp
	> Author: leon
	> Mail: sjzlyl406@163.com 
	> Created Time: 2015年06月28日 星期日 12时31分34秒
 ************************************************************************/

#include"calcultor.h"
#include<iostream>

/* PreTreatment
 * skip space
 * judge '(' & ')'*/
void Calcultor::PreTreatment()
{
	size_t i = 0;
	std::stack<char> ParenStack;

	for(;i != program_.size();++i){
		// skip space;
		if(isspace(program_[i]))
			program_.erase(i--, 1);

		//judge '(' and ')'
		if((i>0 && !isdigit(program_[i-1]) || i == 0) && 
				program_[i] == '(' && 
				(i<program_.size() && isdigit(program_[i+1])))
			ParenStack.push('(');
		if(program_[i] == ')')
			if(ParenStack.empty())
				throw std::runtime_error("Incorrect Expression!");
			else
				ParenStack.pop();
	}
	if(!ParenStack.empty())
		throw std::runtime_error("Incorrect Expression!");
	// judge "abs"/"sin"/"cos"...
	for(i = 0; i < program_.size(); ++i) {
		if(isalpha(program_[i])) {
			if((program_[i] == 'e' || program_[i] == 'E') &&
					isdigit(program_[i-1]) && 
					(isdigit(program_[i+1]) || program_[i+1] == '-' || program_[i+1] == '+'))
				continue;
			throw std::runtime_error("Incorrect Expression!");
		}	
	}
}
/* return the result */
const double Calcultor::Evaluate(std::string program )
{
	program_ = program;

	return Evaluate();
}
const double Calcultor::Evaluate()
{
	PreTreatment();

	return Expression(program_);
}

/* analytic forms of the Expression */
const double Calcultor::Expression(std::string program)
{
	if(FindChar(program, '(')) {
		CalParen(program);			// ()
	}
	if(FindChar(program, '*') || FindChar(program, '/'))
		CalMulAndDiv(program);		// * /
	if(FindChar(program, '+') || FindChar(program, '-'))
		CalPluAndMin(program);		// + -

	double result;
	std::istringstream s;
	s.str(program);
	s >> result;
	return result;
}

/* if there is a c in program */
bool Calcultor::FindChar(const std::string &program, const char c)
{
	if(find(program.begin(), program.end(), c) != program.end())
		return true;
	else
		return false;
}

/* recursively compute the expression in parenthesis*/
void Calcultor::CalParen(std::string &program)
{
	while(FindChar(program, ')')) {
		double result;
		size_t i = 0, left = 0, right = 0;
		size_t length = program.size();
		std::stack<size_t> indexStack;
		while(left <length && program[left] != '(')
			left++;
		i = left;
		if(i != length)
			indexStack.push(i);

		i++;
		while(i < length) {
			if(program[i] == '(')
				indexStack.push(i);
			if(program[i] == ')') {
				indexStack.pop();
				if(indexStack.size() == 0) {
					right = i;
					break;
				}
			}
			i++;
		}
		result = Expression(program.substr(left+1, right - left - 1));
		WriteDouble(program, left, right, result);
	}
}
/* * & / */
void Calcultor::CalMulAndDiv(std::string &program)
{
	while(FindChar(program,'*') || FindChar(program,'/'))
	{
		size_t left = 0, right = 0;
		double left_n, right_n, result;
		size_t i = program.find('*');
		size_t j = program.find('/');

		i = i < j ? i : j;

		left = ExtractNum(program, i, left_n, false);
		right = ExtractNum(program, i, right_n, true);

		if(program[i] == '*')
			result = left_n * right_n;
		else
			if(right_n > -ERRORRANGE && right_n < ERRORRANGE)
				throw std::runtime_error("divid by zero!");
			else
				result = left_n * 1.0 / right_n;
		WriteDouble(program, left, right, result);
	}
}

/* + & - */
void Calcultor::CalPluAndMin(std::string &program)
{
	while(FindChar(program.substr(1),'+') || FindChar(program.substr(1),'-'))
	{
		size_t left = 0, right = 0;
		double left_n,right_n, result;
		size_t i = program.find('+');
		size_t j = program.find('-');
		if(i == 0)
			i = program.substr(1).find('+') + 1;
		if(j == 0)
			j = program.substr(1).find('-') + 1;

		i = i < j ? i : j;

		left = ExtractNum(program, i, left_n, false);
		right = ExtractNum(program, i, right_n, true);

		if(program[i] == '+')
			result = left_n + right_n;
		else
			result = left_n - right_n;
		WriteDouble(program, left, right, result);
	}
}

size_t Calcultor::ExtractNum(const std::string &program, size_t i, double &result, bool right_)
{
	result = 0.0;
	size_t length = program.size();
	if(right_) {  // 右边查找
		size_t right = i+1;
		if(program[right] == '+' || program[right]=='-')
			right++;
		while(right < length && 
			(isdigit(program[right]) || program[right] == '.'))
			++right;
		if(right < length && (program[right] == 'e' || program[right] == 'E')) {
			right++;
			if(right < length && (program[right]== '+' || program[right] == '-'))
				right++;
			while(right < length && isdigit(program[right]))
				right++;
		}

		right--;
		std::string Num = program.substr(i+1, right - i);
		std::stringstream os(Num);
		os >> result;
		
		return right;
	}
	else {  //左边查找 
		size_t left = i-1;
		while(left >= 0 && isdigit(program[left]))
			left--;
		if(left > 1 && (program[left]=='+' || program[left] == '-') &&
				(program[left-1] == 'e' || program[left-1] == 'E'))
			left-=2;
		else if(left > 0 &&( program[left] == 'e' || program[left] == 'E'))
			left--;
		while(left >= 0 && isdigit(program[left]))
			left--;
		if(left > 0 && program[left] == '.')
			left--;
		while(left > 0 && isdigit(program[left]))
			left--;
		if(left > 1 && (program[left] == '+' || program[left] == '-')
				&& (!isdigit(program[left-1])));
		else if(left == 0 && 
			(program[left] == '+' || program[left] == '-'));
		else
			left++;
		
		std::string Num = program.substr(left, i-left);
		std::stringstream os(Num);
		os >> result;

		return left;
	}
}

void Calcultor::WriteDouble(std::string &program, size_t left, size_t right, double result)
{
	std::stringstream os;
	os << program.substr(0, left) << result << program.substr(right+1);

	program.clear();
	program = os.str();
}

int main(void)
{
	try{
		std::string str;
		getline(std::cin,str);

		Calcultor c(str);
		double result;
		result = c.Evaluate(str);

		std::cout<< c.program_ << "="<< result<< std::endl;
	}
	catch(const std::exception &e)
	{
		std::cout<< e.what() <<std::endl;
	}
	return 0;
}

