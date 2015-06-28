/*************************************************************************
	> File Name: Rand.h
	> Author: leon
	> Mail: sjzlyl406@163.com 
	> Created Time: 2015年06月07日 星期六 20时04分19秒
 ************************************************************************/

#ifndef RAND_H
#define RAND_H

#include<ctime>
#include<cstdlib>

const int getrandom(const int x);
const int roll(const int howmany, const int die);
const bool percent(const int prob);

#endif
