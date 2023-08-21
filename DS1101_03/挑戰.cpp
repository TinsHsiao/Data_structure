// 10927248 連翊安 10927244 蕭合亭 

# include <iostream>
# include <stack>
# include <algorithm>
# include <string>
# include <stdio.h> 
# include <ctype.h>

using namespace std ;
class LinkerList {
public:
	struct list {
		char ch ;
		list *next ;
	}; 
	
	struct listint {
		int a = 0 ;
		listint *next ;
	};

	list *store_list = NULL ;
	list *tail = NULL ;
	listint *store_int = NULL ;
	
	bool isEmpty() {
		if ( store_list == NULL ) return true ;
		else return false ;
	}
	
	void set_tail() {
		tail = store_list ;
		if ( store_list == NULL ) {
			tail = NULL ;
		}
		
		else {
			while ( tail -> next != NULL ) {
				tail = tail -> next ;
			}
		}
	} 	
	
	void add ( char c ) {
		if ( store_list == NULL ) {
			store_list = new list ;
			store_list -> next = NULL ;
			store_list -> ch = c ;
			tail = store_list ; 
		}
		
		else {
			tail -> next = new list ;
			tail -> next -> next = NULL ;
			tail = tail -> next ;
			tail -> ch = c ; 
		}
	}
	
	void print_and_delete() {
		list *temp = store_list ;
			
		while ( store_list != NULL ) {
			cout << store_list -> ch ;
			store_list = store_list -> next ;
			delete temp ;
			temp = store_list ; 
		}
		
		cout << endl ;
	}
	
	void print_list() {
		list *temp = store_list ;	
		while ( temp != NULL ) {
			cout << temp -> ch ;
			temp = temp -> next ; 
		}
		
		temp = NULL ;
		cout << endl ;
	}
	
	void delete_head() {
		if ( store_list != NULL ) {
			list *temp ;
			temp = store_list ;
			store_list = store_list -> next ;
			delete temp ;
			temp = NULL ;
		}
	}
	
	void delete_tail() {
		if ( store_list != NULL ) {
			list *temp ;
			temp = store_list ;
			
			while ( temp -> next != tail ) {
				temp = temp -> next ;	
			}
			
			temp -> next = tail -> next ;
			delete tail ;
			tail = temp ; 
		}
	}
	
	void chartoint() { // trouble 
		int tempint = 0 ;
		list *temp = store_list ; 
		listint *i = store_int ;

			if ( isdigit( temp -> ch ) ) {
				while ( isdigit( temp -> ch ) ) {
					tempint = tempint*10 + int( temp->ch ) -'0' ;
					temp = temp -> next ;
				}
				
				i = new listint ;
				i -> next = NULL ; 
				i -> a = tempint ;
				tempint = 0 ; 
			}
			
			else if ( temp -> ch == '+' || temp -> ch == '-' ||
				temp -> ch == '*' || temp -> ch == '/' ) {
				i = new listint ;
				i -> next = NULL ; 
				i -> a = temp -> ch ;
			}
			
			temp = temp -> next ;
			temp = temp -> next ;



	}
	
	void calculate() {
		int temp = 0 ;
		listint *i = store_int ;

		while ( store_int != NULL ) {

			if ( i -> a == int('*') || i -> a == int('/') ||
				 i -> a == int('-') || i -> a == int('+') ) {
				listint *prev = store_int ;
				listint *cur = store_int ;
				while ( cur -> next != i ) {
					prev = cur ;
					cur = cur -> next ;

				}
				
				if ( i -> a == '+' ) 
					prev -> a = prev -> a + cur -> a ;
				else if ( i -> a == '*' )
					prev -> a = prev -> a * cur -> a ;
				else if ( i -> a == '/' ) 
					prev -> a = prev -> a / cur -> a ;
				else if ( i -> a == '-' )
					prev -> a = prev -> a - cur -> a ;
				cout << prev -> a ;  
				prev -> next = i ;
				delete cur ;
				prev = NULL ;
				cur = NULL ;
				i = store_int ;
			}
			
			i = i -> next ;
		} 
		cout << store_int ;
	}
	
	void print_listint() {
		listint *tmp = NULL ;
		while ( tmp != NULL ) {
			cout << tmp -> a << endl ;
			tmp = tmp -> next ; 
		}
		
		cout << endl ;
	}
	
};

class Stack {
public:
	struct stack {
		char ch ;
		stack *next ;
	};
	
	stack *store_stack = NULL ;
	stack *tail = NULL ;

	void set_tail() { // set tail 
		tail = store_stack ;
		if ( store_stack == NULL ) {
			tail = store_stack ;
		}
		
		else {
			while ( tail -> next != NULL ) {
				tail = tail -> next ;
			}
		}
	}

	bool isEmpty() { // determine store_stack is empty
		if ( store_stack == NULL ) return true ;
		else return false ;	;
	}
	
	void pop() { // 刪除最後一個 
		if ( ! isEmpty() ) {
			if ( store_stack -> next == NULL ) {
				store_stack = NULL ;
				delete tail ;
				tail = store_stack ;
			}
			
			else {
				stack *temp = store_stack ;
				while ( temp -> next != tail ) {
					temp = temp -> next ;
				}
				
				temp -> next = NULL ;
				delete tail ;
				tail = temp ;
				temp = NULL ;
			}
		}
	}
	
	char top() { // 回傳最上面的值 
		return tail -> ch ;
	}
	
	void push( char c ) { // 把變數存到最上層 
		if ( store_stack == NULL ) {
			store_stack = new stack ;
			store_stack -> next = NULL ;
			store_stack -> ch = c ; 
			set_tail() ;
		}
		
		else {
			tail -> next = new stack ;
			tail = tail -> next ;
			tail -> ch = c ;
			tail -> next = NULL ; 
		}
	}
	
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
	
	stack<char> t ;
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
	
	if ( isLegalchar( store ) && BracketMatch( store ) && isInfix( store ) ) {
		
		cout << "It is a legitimate infix expression." << endl ;
		return true ;
				
	} // if ()
	
	else return false ;
	
} // CheckError

int Priority( char a ) {   	// the priority of out the stack 
	 
	if ( a == '(' ) return 0 ;   // '(' must stay until touch the ')'
	
	if ( a == '*'|| a == '/' ) return 2 ;  
	
	else return 1 ; // '+', '-'
	
} // Priority()

void InfixToPostfix( string s, LinkerList &post ) {
	
	//LinkerList post ;
	int len = s.length() ;
	Stack oper ;
	
	for ( int i = 0 ; i < len ; i ++ ) {
				
		if ( isdigit( s[i] ) ) {  
			
			while ( i < len && isdigit( s[i] ) ) { // ex 33
				post.add( s[i] ) ;
				i ++ ;
			} // while() 
			
			post.add( ',' ) ;
			post.add( ' ' ) ;
			
			if ( i == len ) break ;  // all were searched
			
		} // if()
		
		if ( s[i] == '(' )  oper.push( s[i] ) ;  // forced into stack 

		if ( isOperator( s[i] ) ) { 
			
			if ( oper.isEmpty() || Priority( s[i] ) > Priority( oper.top() ) ) 
				oper.push( s[i] ) ;
			
			else {
			
				while ( ! oper.isEmpty() && Priority( s[i] ) <= Priority( oper.top() ) && oper.top() != '(' ) {   
				
					post.add( oper.top() ) ;
					post.add( ',' ) ;
					post.add( ' ' ) ;					
					oper.pop() ;
				
				} // while
				
				oper.push( s[i] ) ;  // put now operator into stack 
								
			} // else 				
			
		} //else if()
				
		if ( s[i] == ')' )  {
			
			while ( oper.top() != '(' ) {	// clear the operator which in the bracket 
				
				post.add( oper.top() ) ;
				post.add( ',' ) ;
				post.add( ' ' ) ;				
				oper.pop() ;
				
			} // while 
			
			oper.pop() ;  					// pop the '('
			
		} // else if()
		
	} // for()
	
	while ( ! oper.isEmpty() ) { 	 		// clear the stack 

		post.add( oper.top() ) ;
		post.add( ',' ) ;
		post.add( ' ' ) ;
		oper.pop() ;
		
	} // while 
	
	post.delete_tail() ;  // remove the last two char ", "
	post.delete_tail() ;
	
	cout << "Postfix expression: " ;
	post.print_list() ;
} // InfixtoPostfix

void doCommand() {
	
	string exp = "" ;
	LinkerList post ;
	cout << endl << "Input an infix expression: " ;
	
 	while (	! Read( exp ) ) 
 		cout << endl << "Input an infix expression: " ;

 	if ( CheckError( exp ) ) {
 		InfixToPostfix( exp, post ) ;
	 	post.chartoint() ;
		post.calculate() ;
	} // ()
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
		getline( cin, temp ) ;

 		if ( command == 0 ) break ;
 		
 		else if ( command == 1 ) 
			doCommand() ;
 		
 		else cout << endl << "Command does not exist!" << endl ;
 		
	 } while ( true ) ;
 	
}



/*
class Stack {
	
	struct stack {
		char data ;
		stack * next ; 
	};
	
	stack * head = NULL ;
	stack * tail = NULL ;

	public :
		
		void push( char a ) {
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
		
		int length() {
			stack * walk = head ;
			int len = 0 ;
			while ( walk != NULL ) {
				len ++ ; 
				walk = walk->next ;
			} // while()
			
			return len ;
			
		} // length()
		
		void pop() {
			
			if ( length() == 1 ) {
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
			
		char top() {
			return tail->data ;
		} // top()
		
};

class List {
	
	struct list { 
		char data ;
		list * next ;
	};
	
	public :

	list * head = NULL ;
	list * tail = NULL ;
	
		
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
			
			while ( head != NULL ) {
				cout << head->data ;
				deleHead() ;
			} // while 
			
			cout << endl ;
			
		} // PrintList()		
		
};
*/

