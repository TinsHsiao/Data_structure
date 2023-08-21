// 10927248 10927244 

# include <iostream>
# include <vector>
# include <stack>
# include <fstream> 
# include <string>
# include <sstream>
# include <stdlib.h>

using namespace std ;

class LinkerList {
public:
	struct list {
		char ch ;
		list *next ;
	}; 
 
	list *store_list = NULL ;
	list *tail = NULL ;
	
	void set_tail() {
		tail = store_list ;
		if ( store_list == NULL ) {
			tail = NULL ;
		}
		
		else {
			while ( tail -> next != NULL ) {
				 ;
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
			tail = tail -> next ;
			tail -> next = NULL ;
			tail -> ch = c ; 
		}
	}
	
	void print_and_delete() {
		list *temp ;
		temp = store_list ;
			
		while ( store_list != NULL ) {
			cout << store_list -> ch ;
			store_list = store_list -> next ;
			delete temp ;
			temp = store_list ; 
		}
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
			tail = NULL ;
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
	
	void pop() { // 埃程 
		if ( ! isEmpty() ) {
			if ( store_stack -> next == NULL ) {
				store_stack = NULL ;
				delete tail ;
				tail = NULL ;
			}
			
			else {
				stack *temp = store_stack ;
				while ( temp -> next != tail ) {
					temp = temp -> next ;
				}
				
				temp -> next = NULL ;
				delete tail ;
				tail = temp ;
				//delete temp ;
				temp = NULL ;
			}
		}
	}
	
	char top() { // 肚程 
		return tail -> ch ;
	}
	
	void push( char c ) { // р跑计程糷 
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


int main() {
	/*char a ;
	LinkerList p ;
	scanf( "%c", & a ) ;
	
	while ( a != '\n' ) {
	 p.add( a ) ;
	 p.add( ',' ) ;
	 p.add( ' ' ) ;
	 scanf( "%c", & a ) ;
	} // while
	
	p.delete_tail() ;
	p.delete_tail() ;
	p.print_and_delete() ;*/


	Stack t;
	char a ;
	scanf( "%c", & a ) ;
	while( a != '\n' ) {
	 t.push( a ) ;
	 scanf( "%c", & a ) ;
	} // while()
	 
	while ( ! t.isEmpty() ) {
	 cout << t.top() ;
	 t.pop() ;
	} // while()

}

/*class Node {
public: 
	int oprends ;
	char operators ;
	Node *next ;
};

class expStack {
	typedef struct Node {
		int oprends ;
		char operators ;
		Node *next ;
	};
	
	bool isEmpty() {
		
	}
}; 



class Arithmetic {
	
public :
	
	stack<int> store_oprend ;
	stack<char> store_operator ;
	int num_leftparenthese = 0 ;
	int num_rightparenthese = 0 ;
	
	typedef struct Node {
		int oprends ;
		char operators = '\0';
		Node *next ;
	};
	
	Node *store ;
	
	void data_to_pointer() {
		string s ;
		cin >> s ;
		int i = 0 ;
		int count_node = 0 ;
		int total = 0 ;
		while ( s[i] != '\0') {
			if ( isNumber_isOperator( s[i] ) && s[i] >= '0' && s[i] <= '9' ) {
				while ( isNumber_isOperator( s[i] ) && s[i] >= '0' && s[i] <= '9' ) {
					total = total * 10 + s[i] - '0' ;
					i ++ ;
				}
				
				store[count_node].oprends = total ;
				count_node ++ ;
			}
			
			else if ( isNumber_isOperator( s[i] ) && ( s[i] == '/' || s[i] == '(' || s[i] == ')' ||
			s[i] == '+' || s[i] == '=' || s[i] == '-' || s[i] == '*' ) ){
				store[count_node].operators = s[i] ;
				count_node ++ ;
			}
			
			i ++ ;
		}		
	}	

    bool isNumber_isOperator( char s ) {
        if ( s != '\0' ) {
            if( ! ( (s <= '9' && s >= '0' ) || s == '/' || s == '(' || s == ')' ||
               	s == '+' || s == '=' || s == '-' || s == '*') ) return false ;
        }

        return true ;
    }
    
    bool parenthese_is_inpair( string s ) {
    	for ( int i; s[i] != '\0'; i++ ) {
    		if ( s[i] == '(' ) num_leftparenthese ++ ;
    		else if ( s[i] == ')' ) num_rightparenthese ++ ;
    	}
    	
    	if ( num_leftparenthese == num_rightparenthese ) return true ;
    	else return false ;
	}
	
	
    
} ;

int main() {
    Arithmetic arithmetic ;
    string s ;
    cin >> s ;
    // arithmetic.isNumber_isOperator(s) ;
    cout << arithmetic.parenthese_is_inpair(s) << endl ;
    

}*/
