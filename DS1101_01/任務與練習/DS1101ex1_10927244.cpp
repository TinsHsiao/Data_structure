// 10927244 蕭合亭
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <new>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
using namespace std;
unsigned long long int N[92] ; // 存放費式數列數值的陣列
unsigned long long int Factor1[92] ; // 存放小的因數
unsigned long long int Factor2[92] ; // 存放大的因數

void openingremark( int &i ) { // 開場白 
	while ( i != 0 && i != 1 && i != 2 ) { // i為0、1、2跳出迴圈 
		cout << endl << "** Fibonacci Series Generator **" << endl ; // 開場白 
		cout << "* 0. Quit                      *" << endl ;
		cout << "* 1. Iterative generation      *" << endl ;
		cout << "* 2. Recursive generation      *" << endl ;
		cout << "********************************" << endl ;
		cout << "Input a command(0, 1, 2):" ;
		cin >> i ; // 讀入數字 
		if ( i != 0 && i != 1 && i != 2 ) { // 如果i不是 0、1、2
			cout << endl << "Command does not exist!" << endl ; //  告訴使用者此指令不存在 
		} // if()

	} // while()

} // openingremark()

void getM( unsigned long long int &number ) { // 讀入並回傳數字
	cout << endl << "Input a number:(1~92)";
	cin >> number ;
	while ( number > 92 || number <= 0 ) {
		cout << endl << "Input a number:(1~92)";
		cin >> number ;
	} // while()

} // getM()

int iterativeFib( int number ) { // 用迴圈找出費式數列

	unsigned long long int previous = 1 ; // i = 0 時
	unsigned long long int current = 1 ; // i = 1 時
	for( int index = 0; index <= number; index ++ ) { 
		if ( index < 2 ) N[index] = 1 ; // i = 0 or i = 1
		else {
			N[index] = previous + current ; // 將前一項與目前這項相加存入N陣列的第index項 
			previous = current ; // 前一項變為現在這項的值 
			current = N[index] ; // 這項的值變為N[index]的值(相加完的) 
		}

	} // for()

	return *N ;
} // iterativeFib()


int iterativeFindFactor( int index, unsigned long long int &inner_loop ) { // 找因數相乘組合 (輸入第幾個的index)
	unsigned long long int divisor = sqrt( N[index] ) ; //  將除數設為N[index]開根號 (因為最接近的因數組合會從開根號開始) 
	while( divisor > 0 ) {
		inner_loop ++ ;
		if ( N[index] % divisor == 0 ) { // 整除時存進陣列 
			Factor1[index] = divisor ;
			Factor2[index] = N[index] / divisor ;
			break ;// 跳出迴圈 
		} // if()

		divisor -- ; //  
	} // while()


} // iterativeFindFactor()

void iterativePrint( int number, unsigned long long int inner_loop, int outer_loop ) { // 迴圈印 
	int index = 1 ;
	while( index <= number ) {
		if ( index <= 9 ) cout << "[  " << index << "] " ; // 排版用 
		else cout << "[ " << index << "] " ; // 排版用 
    	iterativeFindFactor( index, inner_loop ) ; // 呼叫找因數的迴圈 
    	cout << N[index] << " = " << Factor1[index] << " * " << Factor2[index] << "	";
    	cout << "(Inner loop:	   " << inner_loop << " times)" << endl ;
    	inner_loop = 0 ; // 重新算因數相乘組合的迴圈 
    	outer_loop ++ ; // 此迴圈count 
		index++ ;
	} // while()

	cout << "<Outer loop:	" << outer_loop << "times>" << endl ;
	
} // iterativePrint()

void newFindFactor( int index, unsigned long long int divisor, unsigned long long int inner_recursion ) { // 遞迴找因數組合並且印出來 
	if ( divisor == 0 ) { // 一開始先將除數初始為N陣列中第index項 
		divisor = sqrt(N[index]) ;
		inner_recursion = 1 ; // 包含此次的呼叫 
	}
	
	if ( inner_recursion > 10000000 ) { // 超過10000000次遞迴就停止(遞迴無法太多層) 
		if ( index <= 9 ) cout << "[  " << index << "] " ; // 排版用 
		else if ( index >= 9 ) cout << "[ " << index << "] " ;
		cout << N[index] << " = (Inner recursion: more than   10000000 times)" << endl;
	}
		
	else if ( N[index] % divisor == 0 ) { // 當N陣列中第index項可以被divisor整除 
		if ( index <= 9 ) cout << "[  " << index << "] " ; // 排版用 
		else if ( index >= 9 ) cout << "[ " << index << "] " ;
		cout << N[index] << " = " << divisor << " * " << N[index]/divisor ; // 印出來 
    	cout << "	(Inner recursion:  	" << inner_recursion << " times)" << endl ;
    	//return newFindFactor( index, number, 0, 0 ) ;
	} // else 

	else { // 如果沒有整除 
		return newFindFactor( index, divisor-1, inner_recursion + 1 ) ; // 往divisor減一繼續找 
	} // if()
	
} // newFindFactor() 

unsigned long long int recursiveFib_FindFactor_Print( unsigned long long int pre, unsigned long long int cur, int index,
								unsigned long long int number, unsigned long long int outer_recursion ) { // "找出費式數列"並呼叫newFindFactor去找出因數組合 
	if ( index == number ) { // base case當遞迴找到最後一項就停下來 
		N[index] = cur ;  
		newFindFactor( index, 0, 0 ) ; // 找因數相乘組合 
		cout << "<Outer recursion:	" << outer_recursion << "times>" << endl ;
		return index ;	// 觸底反彈 
	}
	
	N[index] = cur ;
	if( index > 0 ) newFindFactor( index, 0, 0 ) ; // 找因數相乘組合  
	return recursiveFib_FindFactor_Print( cur, pre+cur, index + 1, number, outer_recursion+1 ) ; // index< number 繼續找下一個index+1項費式數列 

} // recursiveFib_FindFactor_Print

int main() {
	int model = -1 ; // 類型(0 or 1 or 2 ) 
	openingremark( model ) ; // 開場白 
	unsigned long long int number = 0 ; // 使用者輸入數字 
	int index = 1 ; 
	unsigned long long int inner_loop = 0 ; // 迴圈次數
	int outer_loop = 0 ; // 外部迴圈次數 
	unsigned long long int inner_recursion = 0 ; // 遞迴次數
	int outer_recursion	= 0 ; // 內部迴圈次數 
	unsigned long long int divisor = 0 ; // recursive的除數
	while ( model != 0 ) { // 當model = 1 or model = 2  
		getM( number ) ;  // 得到使用者輸入數字 
		if ( model == 1 ) { // Iterative generation
			iterativeFib( number ) ; // 找費式數列 
			iterativePrint( number, inner_loop, outer_loop ) ; // 印費式數列 
		} // if()

		else if ( model == 2 ) recursiveFib_FindFactor_Print( 0, 1, 0, number, outer_recursion ) ; // recursive generation 

		model = -1 ;  
		outer_recursion = 0 ;
		openingremark( model ) ;
	} // while()

} // main()



