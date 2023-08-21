// 10927248 ³sÖö¦w 10927244 ¿½¦X«F

# include <iostream>
# include <iomanip>
# include <fstream>
# include <string>
# include <vector>
# include <math.h>

using namespace std ;

struct Info {
    int No ;
    string Name ;
    string Type1 ;
    int HP ;
    int Attack ;
    int Defense ;
} ;

vector<Info> Data ;

struct Node {
        int index ;
        int HP ;
        Node * right ;
        Node * left ;
};

typedef Node * BST ;

class Tree {
        
    Node * root = NULL ;

    public :

        void Add( BST & tree, Info temp, int i ) {
            
            if ( tree == NULL ) {
                Node * t = new Node ;
                t->index = i ;
                t->HP = temp.HP ;
                t->left = NULL ;
                t->right = NULL ;
                tree = t ;
            } // if()

            else if ( tree->HP <= temp.HP ) {
                Add( tree->right, temp, i ) ;
            } // else if ()

            else {
                Add( tree->left, temp, i ) ;
            } // else
            
        } // Add()


        int getBoder( BST tree, BST pre, char lr ) {

            if ( tree == NULL ) {
                return pre->index ;
            } // if()

            else if ( lr == 'l' ) {
                return getBoder( tree->left, tree, lr ) ;
            } // else

            else {
                return getBoder( tree->right, tree, lr ) ;
            } // else if
        } // getleft

        int Height( BST head ) {

            if ( head == NULL ) return 0 ;
            
            int right = Height( head->right ) ;
            int left = Height( head->left ) ;
            
            if ( right > left ) return right + 1 ;
            else return left + 1 ; 

        } // Height()

        BST getRoot() {
            return root ;
        } // getRoot()


        void Plant( vector<Info> data ) {
            for ( int i = 0 ; i < data.size() ; i ++ ) {
                Add( root, data[i], i ) ;
            } // for()
        } // Plant

        void PreOrderPrint( BST head ) {
            if ( head != NULL ) {
                cout << head->index << head->HP << endl ;
                PreOrderPrint( head->left ) ;
                PreOrderPrint( head->right ) ;
            } // if()
        } // PreOrderPrint()
} ;

class Heap {
    vector<Info> heap ;
    int size ;

    public :

        void Rebuild( vector<Info> data ) {
            heap.assign( data.begin(), data.end() ) ;
            size = heap.size() ;
            for ( int i = ( size - 2 ) / 2 ; i >= 0 ; i -- ) {
                Heapify( i ) ;
            } // for() 
			 
        } // Rebuild 

        void Heapify( int parent ) {
            int Lkid = parent * 2 + 1, Rkid = parent * 2 + 2 ;
            int Gkid ;
            bool test = true ;
            
            while( parent <= ( size - 2 ) / 2 && test ) {
                if ( Rkid < size && heap[Lkid].HP < heap[Rkid].HP ) {
					Gkid = Rkid ;
                } // if

                else if ( Rkid >= size || heap[Lkid].HP >= heap[Rkid].HP ) {
                	Gkid = Lkid ;
				} // else if() 
				
                if ( heap[parent].HP < heap[Gkid].HP ) {
                    swap( heap[parent], heap[Gkid] ) ;
                    parent = Gkid ;
                } // if()

                else if ( heap[parent].HP >= heap[Gkid].HP ) {
                    test = false ;
                } // else 

                Lkid = parent * 2 + 1, Rkid = parent * 2 + 2 ;

            } // while()

        } // Heapify()

        void DeleteRoot() {
            int i = size - 1 ;
            swap( heap[0], heap[i] ) ;
            heap.pop_back() ;
            size = heap.size() ;
            Heapify( 0 ) ;
        } // DeleteRoot()

        bool isEmpty() {
            return heap.empty() ;
        } // isEmpty()

        int Size() {
            return heap.size() ;
        } // Size()

        Info get( int i ) {
            return heap[i] ;
        } // get

        int Bottom() {
            return size - 1 ;
        } // Bottom()

        int Leftest() {
            int index = Height() ;
            index = pow( 2, index - 1 )  - 1 ;
            return index ;
        } // Boder()

        int Height() { 
            return log2( size ) + 1 ;
        } // Height()

        void Clear() {
            heap.clear() ;
        } // Clear()

} ;


int StoI( string temp ) {
    int num = 0 ; 
	for ( int i = 0 ; i < temp.size() ; i ++ ) {
		if ( temp[i] >='0' && temp[i] <= '9' ) {
			num = num * 10 + temp[i] - '0' ;
		} //if()
	} // for()
    return num ;
} // StoI

bool Read() {

    string text ;  
	cout << endl << "Input a file number (e.g., 601, 602, ...): " ;
	cin >> text ;
	text = "input" + text + ".txt" ;  // set file name

    fstream file ;
	file.open( text.c_str(), ios:: in ) ; 

	if ( ! file.is_open() ) {         // check the file can be opened 
		cout << endl << "### " << text << " does not exist ! ###" << endl ;
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

        while ( getline( file, temp, '\t' ) ) {
            
            t.No = StoI( temp ) ;
            getline( file, t.Name, '\t' ) ;
            getline( file, t.Type1, '\t' ) ;
            getline( file, temp, '\t' ) ;       // Read Type2 
            getline( file, temp, '\t' ) ;       // read total 

            getline( file, temp, '\t' ) ;   
            t.HP = StoI( temp ) ;
            getline( file, temp, '\t' ) ;
            t.Attack = StoI( temp ) ;
            getline( file, temp, '\t' ) ;
            t.Defense = StoI( temp ) ;

            getline( file, temp ) ;                     // read the rest of the line

            Data.push_back( t ) ;

        } // while()

    } // else

    file.close() ;
    return true ;

} // Read()

void PrintTitle() {
    cout << "\t   #" << "\t\t" << left << setw( 32 ) << "Name" ;
    cout << left << setw( 16 ) << "Type1" << left << setw( 12 ) ;
    cout << "HP" << left << setw( 12 ) << "Attack" << "Defense" << endl ;
} // PrintTitle()

void Print( Info a, int i ) {

    cout << '[' << i + 1 << "]\t   " << a.No << "\t\t" << left << setw( 32 ) << a.Name  ;
    cout << left << setw( 16 ) << a.Type1 << left << setw( 12 ) << a.HP ;
    cout << left << setw( 12 ) << a.Attack << a.Defense << endl ;

} // Print()

Heap gheap ;

void doCommand( int command ) {
    Tree bst ;
    int index ;

    
    if ( command == 1 ) {
        Data.clear() ;
        gheap.Clear() ;
        if ( Read() ) {

            PrintTitle() ;
            for ( int i = 0 ; i < Data.size() ; i ++ ) {
                Print( Data[i], i ) ;
            } // for()

            bst.Plant( Data ) ;
            cout << "HP tree height = " << bst.Height( bst.getRoot() ) << endl ;

            cout << "Leftmost Node :" << endl ;
            index = bst.getBoder( bst.getRoot(), bst.getRoot(), 'l' ) ;
            PrintTitle() ;
            Print( Data[index], index ) ;

            cout << "Rightmost Node :" << endl ;
            index = bst.getBoder( bst.getRoot(), bst.getRoot(), 'r' ) ;
            PrintTitle() ;
            Print( Data[index], index ) ;
        } // if()

    } // if()

    else if ( command == 2 ) {
        if ( Data.empty() ) {
            cout << endl << "### Please choose command 1 first! ###" << endl ;
            return ; 
        } // if()

        gheap.Rebuild( Data ) ;
        PrintTitle() ;
        for ( int i = 0 ; i < Data.size() ; i ++ ) {
            Print( gheap.get( i ), i - 1 ) ;
        } // for()
        cout << "HP heap height = " << gheap.Height() << endl ;

        cout << "Leftmost Node :" << endl ;
        index = gheap.Leftest() ;
        PrintTitle() ;
        Print( gheap.get( index ), index - 1 ) ;

        cout << "Bottom :" << endl ;
        index = gheap.Bottom() ;
        PrintTitle() ;
        Print( gheap.get( index ), index - 1 ) ;

    } // else if()

    else if ( command == 3 ) {

        if ( gheap.isEmpty() ) {
            cout << endl << "----- Execute Mission 2 first! -----" << endl ;
        } // if()
        
        else {
            cout << "The remove root:" << endl ;
            PrintTitle() ;
            Info t = gheap.get( 0 ) ;
            cout << "\t   " << t.No << "\t\t" << left << setw( 32 ) << t.Name  ;
            cout << left << setw( 16 ) << t.Type1 << left << setw( 12 ) << t.HP ;
            cout << left << setw( 12 ) << t.Attack << t.Defense << endl << endl ;
			
            gheap.DeleteRoot() ;
            
            if ( ! gheap.isEmpty() ) {
                PrintTitle() ;
                for ( int i = 0 ; i < gheap.Size() ; i ++ ) {
                    Print( gheap.get( i ), i - 1 ) ;
                } // for()
                cout << "HP heap height = " << gheap.Height() << endl ;

                cout << "Leftmost Node :" << endl ;
                index = gheap.Leftest() ;
                PrintTitle() ;
                Print( gheap.get( index ), index - 1 ) ;

                cout << "Bottom :" << endl ;
                index = gheap.Bottom() ;
                PrintTitle() ;
                Print( gheap.get( index ), index - 1 ) ;
            } // if()

        } // else 

    } // else if

} // doCommand() 

void Preface() {
	
    cout << endl << "****** Pokemon Tree and Heap ******" ;
    cout << endl << "*0. QUIT                          *" ;
    cout << endl << "*1. Read a file to build BST      *" ;
    cout << endl << "*2. Transform it into Max Heap    *" ;
    cout << endl << "*3. Delete max from Max Heap     *" ;
    cout << endl << "***********************************" ;
    cout << endl << "Input a choice(0, 1, 2, 3):" ;

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
