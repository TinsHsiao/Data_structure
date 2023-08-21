// 10927244 Ëï≠Âêà‰∫≠ 10927248 ÈÄ£ÁøäÂÆâ

# include <iostream>
# include <vector>
# include <fstream>
# include <string>

using namespace std ;

struct SchoolInfo {
    string Sname ;
    string Dname ;
    string Type ;
    string Level ;
    int nStud ;
    int nProf ;
    int nGrad ;
} ;

vector<SchoolInfo> Data ;

struct Tree {
    SchoolInfo data ;
    Tree * left ;
    Tree * right ;
} ;

Tree * shead = NULL ;
Tree * ghead = NULL ;

int num ;
bool found = false ;        

typedef Tree * TreeList ;

void Add( TreeList & head, SchoolInfo temp, int gn ) {

    if ( head == NULL ) {

        Tree * t = new Tree ;
        t->right = NULL ;
        t->left = NULL ;
        t->data = temp ;
        head = t ;
        
    } // if()

    else if ( gn == 1 ) {               // the key value is nGrad

        if ( head->data.nGrad > temp.nGrad ) {
            Add( head->left, temp, 1 ) ; 
        } // if()

        else {
            Add( head->right, temp, 1 ) ; 
        } // else

    } // else if

    else if ( gn == 2 ) {               // the key value is Sname

        if ( head->data.Sname.compare( temp.Sname ) > 0 ) {
            Add( head->left, temp, 2 ) ; 
        } // if()

        else {
            Add( head->right, temp, 2 ) ; 
        } // else

    } // else if ()

} // Add()

int Height( TreeList head ) {

    if ( head == NULL ) return 0 ;
    
    int right = Height( head->right ) ;
    int left = Height( head->left ) ;
    
    if ( right > left ) return right + 1 ;
    else return left + 1 ; 

} // Height()

void Sort() {

    for ( int i = 0 ; i < Data.size() ; i ++ ) {
        
        Add( ghead, Data[i], 1 ) ;
        Add( shead, Data[i], 2 ) ;

    } // for()

} // Sort()

void preOrderPrint( TreeList head ) {
    if ( head != NULL ) {

        cout << '[' << num + 1 << "]\t" << head->data.Sname << '\t' << head->data.Dname << '\t' ;
        cout << head->data.Type << '\t' << head->data.Level << '\t' << head->data.nStud << '\t' ;
        cout << head->data.nProf << '\t' << head->data.nGrad << '\t' << endl ;
        num ++ ;
        
        preOrderPrint( head->left ) ;
        preOrderPrint( head->right ) ;
    } // if()
} // inOrderPrint()

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

        SearchByG( head->left, test ) ;
        preOrderPrint( head->right ) ; 

    } // else if 

    else {
        SearchByG( head->right, test ) ;
    } // else

} // SearchBy

vector<SchoolInfo> del ;

void DeleteNode( TreeList & head, TreeList pre ) { // ßR∞£∏`¬I 

    if ( head->left == NULL && head->right == NULL ) { // ¶p™G¶π∏`¬I®S¶≥§¿§‰ 
        if ( pre->right == head ) pre->right = NULL ; // ¶p™G´e§@≠”∏`¬I™∫•k√‰§¿§‰¨O≤{¶b™∫head (•ÁßY¶π∏`¬I¨∞´e§@•k§¿§‰) 
        else if ( pre->left == head ) pre->left = NULL ; // ¶p™G´e§@≠”∏`¬I™∫•™√‰§¿§‰¨O≤{¶b™∫head (•ÁßY¶π∏`¬I¨∞´e§@•™§¿§‰) 
        delete head ; // ßR∞£¶π∏`¬I 
        head = NULL ; // ≥]©whead¨∞NULL 
    } // if()

    else if ( head->right != NULL ) { // ¶π∏`¬I™∫•k∏`¬I§£¨∞NULL 
        Tree * walk = head->right ; // •˝≥]©wwalk´¸¶V¶π∏`¬I™∫•k§¿§‰ 
        Tree * prew = head ; // ≥]©wprew¨∞´e§@≠”™∫head 

        while ( walk->left != NULL ) { // ß‰®Ï•™√‰®S¶≥§¿§‰™∫∏`¬I 
            prew = walk ;
            walk = walk->left ;
        } // while()

        head->data = walk->data ;  
        DeleteNode( walk, prew ) ;

    } // else 

    else if ( head->right == NULL ) {
        
        Tree * temp = head ;
        if ( head == ghead ) {
            ghead = head->left ;
        } // if()

        else if ( head == shead ) {
            shead = head->left ;
        } // else if()

        else if ( pre->right == head ) {
            pre->right = head->left ;
        } // if()

        else if ( pre->left == head ) {
            pre->left = head->left ;
        } // else if()
        
        delete temp ;
        temp = NULL ;    
        /*
        Tree * walk = head->left ;
        Tree * prew = head ;

        while ( walk->right != NULL ) {
            prew = walk ;
            walk = walk->right ;
        } // while()

        head->data = walk->data ;
        DeleteNode( walk, prew ) ;
       */
    } // else if()

} // DeleteNode()

void DeleteG( TreeList & head, int test, TreeList pre ) {

    if ( head == NULL ) {
        if ( ! found ) cout << "There is no match!" << endl ;
    } // if()

    else if ( head->data.nGrad <= test ) {
        found = true ;
        cout << '[' << num + 1 << "]\t" << head->data.Sname << '\t' << head->data.Dname << '\t' ;
        cout << head->data.Type << '\t' << head->data.Level << '\t' << head->data.nStud << '\t' ;
        cout << head->data.nProf << '\t' << head->data.nGrad << endl ;
        num ++ ;  
        del.push_back( head->data ) ;

        DeleteG( head->right, test, head ) ;
        DeleteG( head->left, test, head ) ;

        DeleteNode( head, pre ) ;

    } // else if()

    else {
        DeleteG( head->left, test, head ) ;
    } // else 

} // DeleteG()

void DeleteData( int test ) {
    for ( int i = Data.size() - 1 ; i >= 0 ; i-- ) {
        if ( Data[i].nGrad <= test ) {
            Data.erase( Data.begin() + i ) ;
        } // if()
    } // for()
} // DeleteData()

void DeleteName( TreeList & head, TreeList & pre ) {
    if ( head == NULL ) {
        return ;
    } // if()

    if ( head->data.Sname.compare( del[0].Sname ) == 0 ) {
        if ( head->data.nGrad == del[0].nGrad ) {
            DeleteNode( head, pre ) ;
        } // if()

        else {
            DeleteName( head->right, head ) ;
        } // else
    } // if

    else if( head->data.Sname.compare( del[0].Sname ) < 0 ) {
        DeleteName( head->right, head ) ;
    } // else if()

    else {
        DeleteName( head->left, head ) ;
    } // else 
} // DeleteName()

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

bool Read() {

    string text ;  
	cout << endl << "Input a file number (e.g., 501, 502, ...): " ;
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
		SchoolInfo t ;

		getline( file, temp ) ;				// read the title 
        getline( file, temp ) ;				// read the title 
		getline( file, temp ) ;				// read the title  
		
		if ( file.eof() ) {
			cout << "### Get nothing from the file" << text << " ! ###" << endl ;
			cout << endl << "There is no data!" << endl ;
			return false ;
		} // if()

        while ( getline( file, temp, '\t' ) ) {

            getline( file, t.Sname, '\t' ) ;
            getline( file, temp, '\t' ) ;               // read Department ID
            getline( file, t.Dname, '\t' ) ;
            getline( file, t.Type, '\t' ) ;
            getline( file, t.Level, '\t' ) ;

            file >> t.nStud >> t.nProf >> t.nGrad ;

            getline( file, temp ) ;                     // read the rest of the line

            Data.push_back( t ) ;

        } // while()

    } // else

    file.close() ;
    return true ;

} // Read()

void Print() {
    for ( int i = 0 ; i < Data.size() ; i ++ ) {
        cout << '[' << i + 1 << "]\t" << Data[i].Sname << '\t' << Data[i].Dname << '\t' ;
        cout << Data[i].Type << '\t' << Data[i].Level << '\t' << Data[i].nStud << '\t' ;
        cout << Data[i].nProf << '\t' << Data[i].nGrad << endl ;
    } // for 
} // Print()

void Clear( TreeList & head ) {
    if ( head != NULL ) {
        Clear( head->right ) ;
        Clear( head->left ) ;
        delete head ;
        head = NULL ;
    } // if()
} // Clear()

void Initial() {
    Data.clear() ;
    Clear( ghead ) ;
    ghead = NULL ;
    Clear( shead ) ;
    shead = NULL ;
    del.clear() ;
} // Initial()

void doCommand( int command ) {
    int test ;
    string temp ;
    found = false ;
    num = 0 ;

    if ( command == 1 ) {
        Initial() ;
        if ( Read() ) {
            Print() ;
            Sort() ;
            cout << endl << "Tree height {School name} = " << Height( shead ) << endl ;
            cout << "Tree height {Number of graduates} = " << Height( ghead ) << endl ;
        } // if()

    } // if()

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

    else if ( command == 4 ) {

        if ( ghead == NULL ) {
            cout << endl << "Please choose command 1 first!" << endl ;
        } // if()

        else {
            cout << "Input the number of graduates: " ;
            cin >> test ;
            DeleteG( ghead, test, ghead ) ;
            num = 0 ;
            DeleteData( test ) ;
            while( ! del.empty() ) {
                num = 0 ;
                DeleteName( shead, shead ) ;
               // preOrderPrint( shead ) ;
                //cout << del[0].Sname << endl ;
                del.erase( del.begin() ) ;
               // cout << "aaa" << endl ;
            } // while()
            //cout << endl ;
            // num = 0 ;
            // Print() ;

            //num = 0 ;
            // cout << endl ;
            // preOrderPrint( shead ) ;
            cout << endl << "Tree height {School name} = " << Height( shead ) << endl ;
            cout << "Tree height {Number of graduates} = " << Height( ghead ) << endl ;

        } // else

    } // else if ()

} // doCommand()

void Preface() {
	
	cout << endl << "*** University Graduate Information System ***" ;
    cout << endl << "* 0. Quit                                    *" ;
    cout << endl << "* 1. Create Two Binary Search Trees          *" ;
    cout << endl << "* 2. Search by Number of Graduates           *" ;
    cout << endl << "* 3. Search by School Name                   *" ;
    cout << endl << "* 4. Removal by Number of Graduates          *" ;
    cout << endl << "**********************************************" ;
    cout << endl << "Input a command(0, 1-4): " ;

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
 		
 		else if ( command == 1 || command == 2 || command == 3 || command == 4 ) {
            doCommand( command ) ;
		} // else if()

 		else cout << endl << "Command does not exist!" << endl ;
 		
	 } while ( test ) ;

     system( "pause" ) ;
 	
} // main()




/*

void Add( TreeList & head, SchoolInfo temp, int gs ) {

    Tree * walk = head ;
    Tree * pre = NULL ;
    int gh = 0, sh = 0 ;

    while ( walk != NULL ) {
        pre = walk ;
        if ( gs == 1 ) {
            gh ++ ;
            if ( walk->data.nGrad > temp.nGrad ) {
                walk = walk->left ;
            } // if()

            else {
                walk = walk->right ; 
            } // else
        } // if()

        else if ( gs == 2 ) {
            sh ++ ;
            if ( walk->data.Sname.compare( temp.Sname ) > 0 ) {
                walk = walk->left ;
            } // if()

            else {
                walk = walk->right ; 
            } // else
        } // else if()
    } // while()

    if ( gs == 1 ) gh ++ ;
    else sh ++ ;

    if ( gh > gHeight ) gHeight = gh ; 
    if ( sh > sHeight ) sHeight = sh ;

    Tree * t = new Tree ;
    t->right = NULL ;
    t->left = NULL ;
    t->data = temp ;

    if ( head == NULL ) {
        head = t ;
    } // if()

    else if ( gs == 1 ) {
        if ( pre->data.nGrad > temp.nGrad ) {
            pre->left = t ;
        } // if

        else {
            pre->right = t ;
        } // else 
    } // if ()

    else if ( gs == 2 ) {
        if ( pre->data.Sname.compare( temp.Sname ) > 0 ) {
            pre->left = t ;
        } // if()

        else {
            pre->right = t ;
        } // else
    } // else if()

} // Add()

*/
