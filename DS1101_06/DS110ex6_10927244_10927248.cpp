// 10927244 ¿½¦X«F 10927248 ³sÖö¦w

# include <iostream>
# include <vector>
# include <fstream>
# include <string>

using namespace std ;

struct Info {
	int num ;
    string name ;
    string Type1 ;
    int hp ;
    string attack ;
    string defense ;
} ;

vector<Info> Data ;

struct Tree {
    Info data ;
    Tree * left ;
    Tree * right ;
} ;

Tree * head = NULL ;
int Height = 0 ;

int num ;
bool found = false ;        

typedef Tree * TreeList ;

void Add( TreeList & head, Info temp ) {

    if ( head == NULL ) {

        Tree * t = new Tree ;
        t->right = NULL ;
        t->left = NULL ;
        t->data = temp ;
        head = t ;
        
    } // if()

    else if ( head->data.hp > temp.hp ) {
        Add( head->left, temp ) ; 
    } // if()

    else {
        Add( head->right, temp ) ; 
    } // else

} // Add()

int height( TreeList head ) {

    if ( head == NULL ) return 0 ;
    
    int right = height( head->right ) ;
    int left = height( head->left ) ;
    
    if ( right > left ) return right + 1 ;
    else return left + 1 ; 

} // height()

void Findleft() {
	num = 0 ;
	int smallest = num ;
	num ++ ;
	while ( num < Data.size() ) {
		if ( Data[num].hp <= Data[smallest].hp ) smallest = num ;
		num ++ ; 
	}
	
	cout << "Leftmost node :" << endl << "\t#\tName\t\tType 1\tHP\tAttack\tDefense" << endl ;
    cout << '[' << smallest + 1 << "]\t" << Data[smallest].num << '\t' << Data[smallest].name << "\t" ;
    cout << Data[smallest].Type1 << '\t' << Data[smallest].hp << '\t' << Data[smallest].attack << '\t' ;
    cout << Data[smallest].defense << endl ;
}

void Findright() {
	num = 0 ;
	int largest = Data[num].hp ;
	num ++ ;
	while ( num < Data.size() ) {
		if ( Data[num].hp >= Data[largest].hp ) largest = num ;
		num ++ ; 
	}
	
	cout << "Rightmost node :" << endl << "\t#\tName\t\tType 1\tHP\tAttack\tDefense" << endl ;
    cout << '[' << largest + 1 << "]\t" << Data[largest].num << '\t' << Data[largest].name << "\t" ;
    cout << Data[largest].Type1 << '\t' << Data[largest].hp << '\t' << Data[largest].attack << '\t' ;
    cout << Data[largest].defense << endl ;
}

void Sort() {

    for ( int i = 0 ; i < Data.size() ; i ++ ) {
        
        Add( head, Data[i] ) ;

    } // for()

} // Sort()

/*
void preOrderPrint( Tree * head ) {
    if ( head != NULL ) {

        cout << '[' << num + 1 << "]\t" << head->data.Sname << '\t' << head->data.Dname << '\t' ;
        cout << head->data.Type << '\t' << head->data.Level << '\t' << head->data.nStud << '\t' ;
        cout << head->data.nProf << '\t' << head->data.nGrad << endl ;
        num ++ ;
        preOrderPrint( head->left ) ;
        preOrderPrint( head->right ) ;

    } // if()
} // preOrderPrint()

void SearchByG( TreeList head, int test ) {

    if ( head == NULL ) {
        if ( ! found ) cout << "There is no match!" << endl ;
    } // if()

    else if ( head->data.nGrad >= test ) {
        found = true ;
        cout << '[' << num + 1 << "]\t" << head->data.Sname << '\t' << head->data.Dname << '\t' ;
        cout << head->data.Type << '\t' << head->data.Level << '\t' << head->data.nStud << '\t' ;
        cout << head->data.nProf << '\t' << head->data.nGrad << endl ;
        num ++ ;

        if ( head->left != NULL ) {
            SearchByG( head->left, test ) ;
        } // if()

        preOrderPrint( head->right ) ; 

    } // else if 

    else {
        SearchByG( head->right, test ) ;
    } // else

} // SearchByG

void SearchByName( TreeList head, string test ) {

    if ( head == NULL ) {
        cout << "There is no match!" << endl ;
    } // if()

    else if ( head->data.Sname.compare( test ) == 0 ) {
        TreeList walk = head ;
        while ( walk != NULL && walk->data.Sname.compare( test ) == 0 ) {
            cout << '[' << num + 1 << "]\t" << walk->data.Sname << '\t' << walk->data.Dname << '\t' ;
            cout << walk->data.Type << '\t' << walk->data.Level << '\t' << walk->data.nStud << '\t' ;
            cout << walk->data.nProf << '\t' << walk->data.nGrad << endl ;
            num ++ ;
            walk = walk->right ;
        } // while()

    } // else if 

    else if ( head->data.Sname.compare( test ) < 0 ){
        SearchByName( head->right, test ) ;
    } // else if()

    else {
        SearchByName( head->left, test ) ;
    } // else

} // SearchByName()
*/

bool Read() {

    string text ;  
	cout << endl << "Input a file number (e.g., 601, 602, ...): " ;
	cin >> text ;
	text = "input" + text + ".txt" ;  // set file name

    fstream file ;
	file.open( text.c_str(), ios:: in ) ; 

	if ( ! file.is_open() ) {         // check the file can be opened 
		cout << "### " << text << " does not exist ! ###" << endl ;
		return false ;
	} // if()

	else {
        
        string temp ;
		Info t ;

		getline( file, temp ) ;				// read the title 
		if ( file.eof() ) {
			cout << "### Get nothing from the file" << text << " ! ###" << endl ;
			cout << endl << "There is no data!" << endl ;
			return false ;
		} // if()

        while ( file >> t.num ) {
        	getline( file, temp, '\t' ) ;
            getline( file, t.name, '\t' ) ;
            getline( file, t.Type1, '\t' ) ;               // read Department ID
            getline( file, temp, '\t' ) ;
            getline( file, temp, '\t' ) ;
            file >> t.hp ;
            file >> t.attack >> t.defense ;

            getline( file, temp ) ;                     // read the rest of the line

            Data.push_back( t ) ;

        } // while()

    } // else

    file.close() ;
    return true ;

} // Read()

void Print() {
	cout << "\t#\tName\t\tType 1\tHP\tAttack\tDefense" << endl ;
    for ( int i = 0 ; i < Data.size() ; i ++ ) {
        cout << '[' << i + 1 << "]\t" << Data[i].num << '\t' << Data[i].name << "\t" ;
        cout << Data[i].Type1 << '\t' << Data[i].hp << '\t' << Data[i].attack << '\t' ;
        cout << Data[i].defense << endl ;
    } // for 
} // Print()

void Initial() {
    Data.clear() ;
    delete head ;
    head = NULL ;
} // Initial()

void doCommand( int command ) {
    int test ;
    string temp ;
    found = false ;
    num = 0 ;

    if ( command == 1 ) {
        Initial() ;
        if ( Read() ) {
        	Info t ;
            Print() ;
            Sort() ;
            cout << endl << "HP tree height = " << height( head ) << endl ;
            Findleft() ;
			Findright() ; 
        } // if()

    } // if()
/*
    else if ( command == 2 ) {

        if ( ghead == NULL ) {
            cout << endl << "Please choose command 1 first!" << endl ;
        } // if()

        else {
            cout << "Input the number of graduates: " ;
            cin >> test ;
            cout << "Search results:" << endl ;
            SearchByG( ghead, test ) ;
        } // else

    } // else if ()

    else if ( command == 3 ) {

        if ( shead == NULL ) {
            cout << endl << "Please choose command 1 first!" << endl ;
        } // if()

        else {
            cout << "Input a school name: " ;
            cin >> temp ;
            cout << "Search results:" << endl ;
            SearchByName( shead, temp ) ;
        } // else

    } // else if 
*/
} // doCommand()

void Preface() {
	
	cout << endl << "*** University Graduate Information System ***" ;
    cout << endl << "* 0. Quit                                    *" ;
    cout << endl << "* 1. Create Two Binary Search Trees          *" ;
    cout << endl << "* 2. Search by Number of Graduates           *" ;
    cout << endl << "* 3. Search by School Name                   *" ;
    cout << endl << "**********************************************" ;
    cout << endl << "Input a command(0, 1-3): " ;

} // Preface()

bool Check( string temp, int & command ) {
    
	command = 0 ;
	for ( int i = 0 ; i < temp.size() ; i ++ ) {
		if ( temp[i] < '0' || temp[i] > '9' ) {
			return false ;
		} //if()

		command = command * 10 + temp[i] - '0' ;

	} // for()

	return true ;
} // Check()

int main() {
 	
	string temp ;
 	int command ;
 	bool test = true ;

 	do {
 		
 		Preface() ;
		cin >> temp ;
		if ( ! Check( temp, command ) ) {
			cout << endl << "Command does not exist!" << endl ;
		} // if()

 		else if ( command == 0 ) test = false ;
 		
 		else if ( command == 1 || command == 2 || command == 3 ) {
            doCommand( command ) ;
		} // else if()

 		else cout << endl << "Command does not exist!" << endl ;
 		
	 } while ( test ) ;
 	
} // main()
