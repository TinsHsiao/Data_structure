//10927248 連翊安 10927244 蕭合亭 
# include <iostream>
# include <vector>
# include <string>
# include <fstream>
# include <iomanip> // 控制小數輸出
# include <ctime> 

using namespace std ;

struct schoolData {
	string school ;
	string major ;
	string depart ;
	string level ;
	int students ;
	int teachers ;
	int graduates ; 
};

struct Tree {
	schoolData data ;
	Tree *right ;
	Tree *left ;
};

vector<schoolData> data ;

typedef Tree *trees ;
string text ;
int DataSize ;

bool Read() { // command = 1 進來 
	string temp ;  
	cout << endl << "Input a file number (e.g., 401, 402, ...):" ;
	cin >> text ;

	temp = "input" + text + ".txt" ;  // set file name
	
	fstream file ;
	file.open( temp.c_str(), ios:: in ) ;     // open the file

	if ( ! file.is_open() ) {         // check the file can be opened 
		cout << "### " << temp << " does not exist ! ###" << endl ;
		cout << "There is no data! " << endl ;
		return false ;
	} // if()

	else {

		schoolData t ;
		int unuseint ;
		string unusestr ;
		string str1 ;
		string str2 ;
		int i = 0 ;
		getline( file, temp ) ;				// read the title 

		if ( file.eof() ) {
			cout << "### Get nothing from the file" << temp << " ! ###" << endl ;
			return false ;
		} // if()
		
		getline( file, temp ) ;	
		getline( file, temp ) ;	

		while ( file >> unuseint ) {			// Read the data and push into vector 
			file >> t.school >> unusestr >> t.major  >> str1 >> str2  ;
			t.depart = str1 + " " + str2 ;
			file >> str1 >> str2  ;
			t.level = str1 + " " + str2 ;
			file >> t.students >> t.teachers >>t.graduates ;
			getline( file, temp ) ;	
			data.push_back( t ) ;
			
		} // while()

		DataSize = data.size() ;	// set size

	} // else 
	
	file.close() ;
	return true ;
} // Read()

Tree * stree = NULL ;
Tree * gtree = NULL ;

class binaryTree {

	public :
		bool found = false ;
		int index = 0 ;
		void Addgtree( trees & head, schoolData t ) { // graduates
			if ( head == NULL ) {
				
				Tree *temp = new Tree ; 
				temp->data = t ;
				temp->left = NULL ;
				temp->right = NULL ;
				head = temp ; 
			}
			
			else if ( head->data.graduates < t.graduates ) {
				Addgtree( head->right, t ) ;
			}
			
			else {
				Addgtree( head->left, t ) ;
			}
		}
		
		void Addstree( trees &head, schoolData t ) { // schoolname
			
			if ( head == NULL ) {
				Tree *temp = new Tree ; 
				temp->data = t ;
				temp->left = NULL ;
				temp->right = NULL ;
				head = temp ;
			}
			
			else if ( head->data.school.compare( t.school ) > 0 ) {
				Addstree( head->left, t ) ;
			}
			
			else {
				Addstree( head->right, t ) ;
			}
		}
		
		void build() {
			for ( int i = 0; i < data.size(); i++ ) {
				Addgtree( gtree, data[i] ) ;
			}
			
			for ( int i = 0; i < data.size(); i++ ) {
				Addstree( stree, data[i] ) ;
			}
		}
		
		int Height( trees head ) {
			if ( head == NULL ) return 0 ;
			return 1 + max( Height( head->right ), Height( head->left ) ) ;
		}
		
		void printList( schoolData t ) {
			cout << t.school << "\t" << t.major << "\t" << t.depart << "\t";
			cout << t.level << "\t" << t.students << "\t" << t.teachers << "\t" << t.graduates << endl ;
		}
		
		void searchByGraduates( trees head, int number ) {

			if ( head == NULL && !found ) cout << "There is no match!" << endl ;
			
			else if ( head->data.graduates >= number ) {
				found = true ;
				cout << "[" << index << "]\t" ;
				printList( head->data ) ;
				index ++ ;
				if ( head->left != NULL ) searchByGraduates( head->left, number ) ;
			}
			
			else if ( head->right !)searchByGraduates( head->right, number ) ;
			else return ;
		}
	
		void initial() {
			delete gtree ;
			gtree = NULL ;
			delete stree ;
			stree = NULL ;
			data.clear() ; 
		}
};

void PrintData() {
	for ( int i = 0; i < data.size();  i++ ) {
		cout << "[" << i+1 << "]\t" << data[i].school << "\t" << data[i].major << "\t" << data[i].depart << "\t";
		cout << data[i].level << "\t" << data[i].students << "\t" << data[i].teachers << "\t" << data[i].graduates << endl ;
	}
}

void do_command( int i ) {
	binaryTree a ;
	int number ;
	bool dofirststep = false ;
	if ( i == 1 ) {
		a.initial() ;
		Read() ;
		a.build() ;
		PrintData() ;
 		int g = a.Height( gtree ) ;
		int s = a.Height( stree ) ;
		cout << "Tree height {School name} = " << s << endl ;
		cout << "Tree height {Number of graduates} = " << g << endl ;
	}

	else if ( i == 2 ) {
		if ( gtree == NULL ) {
            cout << endl << "Please choose command 1 first!" << endl ;
        } // if()
        
        else {
            cout << "Input the number of graduates: " ;
            cin >> number ;
            cout << "Search results:" << endl ;
            a.searchByGraduates( gtree, number ) ;
        } // else
	}
	
	
}

void Preface() {
	
	cout << endl << "*** University Graduate Information System ***" ;
	cout << endl << "* 0. Quit                            		  *" ;
	cout << endl << "* 1. Create Two Binary Search Trees          *" ;
	cout << endl << "* 2. Search by Number of Graduates           *" ;
	cout << endl << "* 3. Search by School Name                   *" ;
	cout << endl << "**********************************************" ;
	cout << endl << "Input a command(0, 1, 2, 3): " ;

} // Preface()

int main() {
 	
	string temp ;
 	int command ;
 	int gheight, sheight ;
 	bool test = true ;
 	binaryTree t ;
 	do {
 		Preface() ;
		cin >> command ;
		if ( command == 0 ) test = false ;
		else do_command( command ) ;
		
 		
	} while ( test ) ;
 	
} // main()


