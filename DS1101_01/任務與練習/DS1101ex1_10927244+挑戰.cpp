// 10927244 ���X�F
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <iomanip>
#include <new>
#include <string>
#include <cstdlib>
#include <cmath>
#include <sstream>
#include <vector>
#include <algorithm>
#include <time.h>
using namespace std;
unsigned long long int N[92] ; // �s��O���ƦC�ƭȪ��}�C
unsigned long long int Factor1[92] ; // �s��p���]��
unsigned long long int Factor2[92] ; // �s��j���]��


void openingremark( int &i ) { // �}����
	while ( i != 0 && i != 1 && i != 2 && i != 3 ) { // i��0�B1�B2���X�j��
		cout << endl << "** Fibonacci Series Generator **" << endl ; // �}����
		cout << "* 0. Quit                      *" << endl ;
		cout << "* 1. Iterative generation      *" << endl ;
		cout << "* 2. Recursive generation      *" << endl ;
		cout << "* 3. Permutation generaton     *" << endl ;
		cout << "********************************" << endl ;
		cout << "Input a command(0, 1, 2, 3):" ;
		cin >> i ; // Ū�J�Ʀr
		if ( i != 0 && i != 1 && i != 2 && i != 3 ) { // �p�Gi���O 0�B1�B2
			cout << endl << "Command does not exist!" << endl ; //  �i�D�ϥΪ̦����O���s�b
		} // if()

	} // while()

} // openingremark()

void getM( unsigned long long int &number ) { // Ū�J�æ^�ǼƦr
	cout << endl << "Input a number:(1~92)";
	cin >> number ;
	while ( number > 92 || number <= 0 ) {
		if ( number > 92 && number <= 999999 ) number= 92 ;
		else {
			cout << endl << "### The number must be in [1,999999] ###" << endl ;
			cout << endl << "Input a number:(1~92)";
			cin >> number ;
		}
	} // while()

} // getM()

void iterativeFib( int number ) { // �ΰj���X�O���ƦC

	unsigned long long int previous = 1 ; // i = 0 ��
	unsigned long long int current = 1 ; // i = 1 ��
	for( int index = 0; index <= number; index ++ ) {
		if ( index < 2 ) N[index] = 1 ; // i = 0 or i = 1
		else {
			N[index] = previous + current ; // �N�e�@���P�ثe�o���ۥ[�s�JN�}�C����index��
			previous = current ; // �e�@���ܬ��{�b�o������
			current = N[index] ; // �o�������ܬ�N[index]����(�ۥ[����)
		}

	} // for()

} // iterativeFib()


void iterativeFindFactor( int index, unsigned long long int &inner_loop ) { // ��]�Ƭۭ��զX (��J�ĴX�Ӫ�index)
	unsigned long long int divisor = sqrt( N[index] ) ; //  �N���Ƴ]��N[index]�}�ڸ� (�]���̱��񪺦]�ƲզX�|�q�}�ڸ��}�l)
	while( divisor > 0 ) {
		inner_loop ++ ;
		if ( N[index] % divisor == 0 ) { // �㰣�ɦs�i�}�C
			Factor1[index] = divisor ;
			Factor2[index] = N[index] / divisor ;
			break ;// ���X�j��
		} // if()

		divisor -- ; //
	} // while()


} // iterativeFindFactor()

void iterativePrint( int number, unsigned long long int inner_loop, int outer_loop ) { // �j��L
	int index = 1 ;
	while( index <= number ) {
		if ( index <= 9 ) cout << "[  " << index << "] " ; // �ƪ���
		else cout << "[ " << index << "] " ; // �ƪ���
    	iterativeFindFactor( index, inner_loop ) ; // �I�s��]�ƪ��j��
    	cout << N[index] << " = " << Factor1[index] << " * " << Factor2[index] << "	";
    	cout << "(Inner loop:	   " << inner_loop << " times)" << endl ;
    	inner_loop = 0 ; // ���s��]�Ƭۭ��զX���j��
    	outer_loop ++ ; // ���j��count
		index++ ;
	} // while()

	cout << "<Outer loop:	" << outer_loop << "times>" << endl ;

} // iterativePrint()

void newFindFactor( int index, unsigned long long int divisor, unsigned long long int inner_recursion ) { // ���j��]�ƲզX�åB�L�X��
	if ( divisor == 0 ) { // �@�}�l���N���ƪ�l��N�}�C����index��
		divisor = sqrt(N[index]) ;
		inner_recursion = 1 ; // �]�t�������I�s
	}

	if ( inner_recursion > 10000000 ) { // �W�L10000000�����j�N����(���j�L�k�Ӧh�h)
		if ( index <= 9 ) cout << "[  " << index << "] " ; // �ƪ���
		else if ( index >= 9 ) cout << "[ " << index << "] " ;
		cout << N[index] << " = (Inner recursion: more than   10000000 times)" << endl;
	}

	else if ( N[index] % divisor == 0 ) { // ��N�}�C����index���i�H�Qdivisor�㰣
		if ( index <= 9 ) cout << "[  " << index << "] " ; // �ƪ���
		else if ( index >= 9 ) cout << "[ " << index << "] " ;
		cout << N[index] << " = " << divisor << " * " << N[index]/divisor ; // �L�X��
    	cout << "	(Inner recursion:  	" << inner_recursion << " times)" << endl ;
    	//return newFindFactor( index, number, 0, 0 ) ;
	} // else

	else { // �p�G�S���㰣
		return newFindFactor( index, divisor-1, inner_recursion + 1 ) ; // ��divisor��@�~���
	} // if()

} // newFindFactor()


unsigned long long int recursiveFib_FindFactor_Print( unsigned long long int pre, unsigned long long int cur, int index,
								unsigned long long int number, unsigned long long int outer_recursion ) { // "��X�O���ƦC"�éI�snewFindFactor�h��X�]�ƲզX
	if ( index == number ) { // base case���j���̫�@���N���U��
		N[index] = cur ;
		newFindFactor( index, 0, 0 ) ; // ��]�Ƭۭ��զX
		cout << "<Outer recursion:	" << outer_recursion << "times>" << endl ;
		return index ;	// Ĳ���ϼu
	}

	N[index] = cur ;
	if( index > 0 ) newFindFactor( index, 0, 0 ) ; // ��]�Ƭۭ��զX
	return recursiveFib_FindFactor_Print( cur, pre+cur, index + 1, number, outer_recursion+1 ) ; // index< number �~���U�@��index+1���O���ƦC

} // recursiveFib_FindFactor_Print


void backtrack( int index, int size, vector<int> group, int &inner_times ) { 
	if ( index == size ) { // �������J���Ʀr�@�˪��j�p�� 
		cout << "[" << inner_times << "]" ; // �L�ǦC 
		for( int i = 0; i < size; i ++ ) {
			cout << group[i] << " " ; // �C�@�ձq��0���L��� ��J���Ʀr�@�˪��j�p �� 
		}

		inner_times ++ ; // ���ƥ[�@ 
		cout << endl ;  

		return ; // �^�� 
	}

	group[index] = 0 ; // �]�w�q0�}�l 
	while( group[index] <= 9 ) { // �@�Ӥ@�Ӷ]����9 
		if( count( group.begin(), group.begin() + index, group[index] ) != 0 ) { // �V�w�L�X���Ʀr�h��>>>>�p�G�@�� 
			group[index] ++ ; // ���ƥ[�@�h���L�@�˪��� 
			continue ; // ���L�᭱�B�J�^��while 
		}
		
		backtrack( index+1, size, group, inner_times ) ; // ���j��U�@�Ӽ� 
		group[index] ++ ; 
	}

}

int main() {
	int model = -1 ; // ����(0 or 1 or 2 )
	openingremark( model ) ; // �}����
	unsigned long long int number = 0 ; // �ϥΪ̿�J�Ʀr
	int index = 1 ;
	unsigned long long int inner_loop = 0 ; // �j�馸��
	int outer_loop = 0 ; // �~���j�馸��
	unsigned long long int inner_recursion = 0 ; // ���j����
	int outer_recursion	= 0 ; // �����j�馸��
	unsigned long long int divisor = 0 ; // recursive������
	int size = 0 ;
	while ( model != 0 ) { // ��model = 1 or model = 2
		if ( model == 1 ) { // Iterative generation
			getM( number ) ;  // �o��ϥΪ̿�J�Ʀr
			iterativeFib( number ) ; // ��O���ƦC
			iterativePrint( number, inner_loop, outer_loop ) ; // �L�O���ƦC
		} // if()

		else if ( model == 2 ) {
			getM( number ) ;  // �o��ϥΪ̿�J�Ʀr
			recursiveFib_FindFactor_Print( 0, 1, 0, number, outer_recursion ) ; // recursive generation
		}

		else if( model == 3 ) {
			cout << endl << "Input a number:(2~10)";
			cin >> number ;
			while ( number > 10 || number < 2 ) {
				cout << endl << "### The number must be in [2,10] ###" << endl ;
				cout << endl << "Input a number:(2~10)";
				cin >> number ;
			} // while()

			clock_t star = clock(); // �@�}�l���ɶ� 
			int inner_times = 1 ;
			vector<int> group(9) ; // ��lgroup��9(�d��2-10) 
			backtrack( 0, number, group, inner_times ) ;
			clock_t end = clock(); // �̫᪺�ɶ� 
			cout << "Recursion: " <<  end - star << "ms" << endl ;

		}

		model = -1 ;
		outer_recursion = 0 ;
		openingremark( model ) ;
	} // while()

} // main()




