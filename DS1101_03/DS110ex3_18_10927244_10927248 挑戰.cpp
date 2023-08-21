// 10927248 ³sÖö¦w 10927244 ¿½¦X«F 

# include <iostream>
# include <algorithm>
# include <string>
# include <stdio.h> 
# include <ctype.h>

using namespace std ;
template <class T>

class Stack {
	
	struct stack {
		T data ;
		stack * next ; 
	};
	
	stack * head = NULL ;
	stack * tail = NULL ;

	public :
		
		void push( T a ) {
			stack * temp = new stack ;
			temp->next = NULL ;
			temp->data = a ;
			
			if ( head == NULL ) {
				head = temp ;
				tail = temp ;
				temp = NULL ;
			} // if
			
			else {
				tail->next = temp ;
				tail = tail->next ;
				temp = NULL ;
			} // else 
			
		} // push()
		
		void pop() {
			
			if ( head->next == NULL ) {
				delete head ;
				head = NULL ;
				tail = NULL ;
				return ;
			} // if ()
			
			stack * walk = head ;
			stack * pre = NULL ;
			while ( walk != tail ) {
				pre = walk ;
				walk = walk->next ;
			} // while()
			
			tail = pre ;
			tail->next = NULL ;
			delete walk ;
			walk = NULL ;
			return ;
				
		} // pop()
		
		bool empty() {
			return head == NULL ;
		} // empty()
			
		T top() {
			return tail->data ;
		} // top()
		
};


class List {
	
	struct list { 
		char data ;
		list * next ;
	};
	
	list * head = NULL ;
	list * tail = NULL ;
	
	public :	
		void add( char a ) {
			list * temp = new list ;
			temp->next = NULL ;
			temp->data = a ;
			
			if ( head == NULL ) {
				head = temp ;
				tail = temp ;
				temp = NULL ;
			} // if
		
			else {
				tail->next = temp ;
				tail = tail->next ;
				temp = NULL ;
			} // else 
			
		} // add()
		
		void addComma() {
			add(',') ;
			add(' ') ;
		} // addComma()
		
		void deleTail() {
			
			list * walk = head ;
			list * pre = NULL ;
			while ( walk != tail ) {
				pre = walk ;
				walk = walk->next ;
			} // while()
			
			tail = pre ;
			tail->next = NULL ;
			delete walk ;
			walk = NULL ;
			
		} // deleTail()
		
		void deleHead() {
			
			if ( head->next == NULL ) {
				delete head ;
				head = NULL ;
				tail = NULL ;
				return ;
			} // if()
			
			list * temp = head ;
			head = head->next ;
			temp->next = NULL ;
			delete temp ;
			temp = NULL ;
			
		} // deleteHead()
		
		void PrintList() {
			
			list * walk = head ;
			while ( walk != NULL ) {
				cout << walk->data ;
				walk = walk->next ;
			} // while 
			
			cout << endl ;
			
		} // PrintList()	
		
		char top() {
			return head->data ;
		} // top()
		
		bool empty() {
			return head == NULL ;
		} // empty()
		
};

bool isOperator( char a ) {
	
	if ( a == '+' || a == '-' || a == '*' || a == '/' ) return true ;
	return false ;
	
} // isOperater()

bool isBracket( char a ) {
	
	if ( a == '(' || a == ')' ) return true ;
	return false ;
	
} // isBracket()

bool isWhiteSpace( char a ) {
	
	if ( a == ' ' || a == '\t' || a == '\n' ) return true ;
	return false ;
	
} // isWhiteSpace()

bool isLegalchar( string s ) {
	
	for( int i = 0 ; i < s.length() ; i ++ ) {
		
		if ( ! isdigit( s[i] ) && ! isOperator( s[i] ) && ! isBracket( s[i] ) ) {
			
			cout << "Error 1: " << s[i] << " is not a legitimate character." << endl ;
			return false ;
			
		} // if()
			
	} // for()
	
	return true ;
	
} // Legalchar()

bool Read( string & s ) {
	
	char a ;
	scanf( "%c", & a ) ;
	while ( a != '\n' ) {
		
		if( ! isWhiteSpace( a ) ) s += a ; // skip whitespace 
		scanf( "%c", & a ) ;
		
	} // while ()
	
	if ( s == "" ) return false ;
	return true ;
	
} // Read()

bool BracketMatch( string s ) {  	// if the brackets are perfectly matched
	
	Stack<char> t ;
	int len = s.length() ;
	
	for ( int i = 0 ; i < len ; i ++ ) {
		
		if ( s[i] == '(' ) t.push( s[i] ) ;
		
		if ( s[i] == ')' ) {
			
			if ( t.empty() ) {
				
				cout << "Error 2: there is one extra close parenthesis." << endl ;
				return false ;
				
			} // if ()
			
			if ( t.top() == '(' ) t.pop() ;  // one
			
		} // if ()
		
	} // for()
	
	if ( t.empty() ) return true ;
	
	else { 				// there still have open parenthesis 
	
		cout << "Error 2: there is one extra open parenthesis." << endl ; 
		return false ;
		
	} // else 
	
} // BracketMatch()

bool isInfix( string s ) {
	
	bool record = false ;
	int len = s.length() ;
		
	for ( int i = 0 ; i < len ; i ++ ) {
						
		if ( isdigit( s[i] ) ) {
			
			if ( ( i != 0 && s[i-1] == ')' ) || ( i < len - 1 && s[i+1] == '(' ) || record ) { // 3(2) or (2)2 ,(3+4)(3)
				
				cout << "Error 3: there is one extra operand." << endl ;
				return false ;
				
			} // if()
			
		} // if()
		
		if ( isOperator( s[i] ) && ( i == 0 || isOperator( s[i-1] ) || i == len - 1 ) ) {   //  +, 1--, 1-
			
				cout << "Error 3: there is one extra operator." << endl ;
				return false ;
									
		} // if()
		
		if ( isOperator( s[i] ) && ( s[i-1] == '('  || s[i+1] == ')' ) ) {  // (-), (3+)
			
			cout << "Error 3: it is not infix in the parentheses." << endl ;
			return false ;	
			
		} // else if
		
		if ( s[i] == ')' && s[i-1] == '(' ) {  // ()
			
			cout << "Error 3: it is not infix in the parentheses." << endl ;
			return false ;	
			
		} // if ()
		
		if ( i > 0 && s[i] == '(' && s[i-1] == ')' )		// (3+4)(3)
			record = true ;   
		
	} // for()

	return true ;		
	
} // isInfix()

bool CheckError( string  store ) {
	
	if ( ! isLegalchar( store ) )  return false ;
	
	if ( ! BracketMatch( store ) )  return false ;
	
	if ( ! isInfix( store ) ) return false ;
	
	else {
		
		cout << "It is a legitimate infix expression." << endl ;
		return true ;
		
	} // else
	
} // CheckError

int Priority( char a ) {   	// the priority of out the stack 
	 
	if ( a == '(' ) return 0 ;   // '(' must stay until touch the ')', so its priority is smallest 
	
	if ( a == '*'|| a == '/' ) return 2 ;  
	
	else return 1 ; // '+', '-'
	
} // Priority()

bool Arithmetic( Stack<int> & num, char oper ) {
	int b = num.top() ;
	num.pop() ;
	int a = num.top() ;
	num.pop() ;
	
	if ( oper == '+' ) a = a + b ;
	
	if ( oper == '-' ) a = a - b ;
	
	if ( oper == '*' ) a = a * b ;
	
	if ( oper == '/' ) {
		if ( b != 0 ) 
			a = a / b ;
			
		else {
			cout << "### Error: Divided by ZERO! ###" << endl ;
			return false ;
		} // else 
		
	} // if()
	
	num.push( a ) ;
	return true ;
	
} // Arithmetic()

void Calculate( List post ) {
	Stack<int> num ;
	int operand = 0 ;
	bool test = true ;
	
	while ( ! post.empty() ) {
		
		if ( isdigit( post.top() ) ) {
		
			while( ! post.empty() && isdigit( post.top() ) ) {
			
				operand = operand* 10 + post.top() - '0' ;
				post.deleHead() ;
			
			} // while
		
			num.push( operand ) ;
			operand = 0 ;
			
		} // if()
		
		if ( post.empty() ) break ;
		
		if ( isOperator( post.top() ) )  {
			
			if ( ! Arithmetic( num, post.top() ) ) {
			 	test = false ;
			 	break ;
			} // if()
			
			post.deleHead() ;  
		} // if()
			
		
		post.deleHead() ;  
		
	} // while()
		
	if ( test )cout << "Answer is :" << num.top() << endl ;	
	else cout << "### It cannot be sucessfully evaluted! ###" << endl ;
	
} // Calculate()

void InfixToPostfix( string s ) {
	
	List post ;
	int len = s.length() ;
	Stack<char> oper ;
	
	for ( int i = 0 ; i < len ; i ++ ) {
				
		if ( isdigit( s[i] ) ) {  
			
			while ( i < len && isdigit( s[i] ) ) { // ex 33
				post.add( s[i] ) ;
				i ++ ;
			} // while() 
			
			post.addComma() ;
			
			if ( i == len ) break ;  // all were searched
			
		} // if()
		
		if ( s[i] == '(' )  oper.push( s[i] ) ;  // forced into stack 

		if ( isOperator( s[i] ) ) { 
			
			if ( oper.empty() || Priority( s[i] ) > Priority( oper.top() ) ) 
				oper.push( s[i] ) ;
			
			else {
			
				while ( ! oper.empty() && Priority( s[i] ) <= Priority( oper.top() ) && oper.top() != '(' ) {  
				
					post.add( oper.top() ) ;
					post.addComma() ;
					oper.pop() ;
				
				} // while
				
				oper.push( s[i] ) ;  // put now operator into stack 
								
			} // else 				
			
		} //else if()
				
		if ( s[i] == ')' )  {
			
			while ( oper.top() != '(' ) {	// clear the operator which in the bracket 
				
				post.add( oper.top() ) ;
				post.addComma() ;				
				oper.pop() ;
				
			} // while 
			
			oper.pop() ;  					// pop the '('
			
		} // else if()
		
	} // for()
	
	while ( ! oper.empty() ) { 	 		// clear the stack 

		post.add( oper.top() ) ;
		post.addComma() ;
		oper.pop() ;
		
	} // while 
	
	post.deleTail() ;  // remove the last two char ',' and ' '
	post.deleTail() ;
	
	cout << "Postfix expression: " ;
	post.PrintList() ;
	Calculate( post ) ;
	
} // InfixtoPostfix

void doCommand() {
	
	string exp = "" ;
	cout << endl << "Input an infix expression: " ;
	
 	while (	! Read( exp ) ) 
 		cout << endl << "Input an infix expression: " ;

 	if ( CheckError( exp ) ) 
 		InfixToPostfix( exp ) ;
	
} // doCommand() 

void Preface() {
	
	cout << endl << "* Arithmetic Expression Evaluator *" ;
	cout << endl << "* 0. QUIT                         *" ;
	cout << endl << "* 1. Infix2postfix Evaluation     *" ;
	cout << endl << "***********************************" ;
	cout << endl << "Input a choice(0, 1): " ;

} // Preface()
 
 
int main() {
 	
 	int command ;
 	string temp ;
 	
 	do {
 		
 		Preface() ;
 		cin >> command ;
		getline( cin, temp ) ; // read the current line or read '\n'  

 		if ( command == 0 ) break ;
 		
 		else if ( command == 1 ) 
			doCommand() ;
 		
 		else cout << endl << "Command does not exist!" << endl ;
 		
	 } while ( true ) ;
 	
}
 
