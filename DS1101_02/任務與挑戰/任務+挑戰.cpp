// 10927248 ³sÖö¦w 10927244 ¿½¦X«F 

# include <iostream>
# include <vector>
# include <stack>
# include <fstream> 
# include <string>
# include <sstream>
# include <stdlib.h>
 
using namespace std ;

bool isNumber( string temp ) {
	for ( int i = 0 ; i < temp.size() ; i ++ ) {
		if ( ! isdigit( temp[i] ) ) {
			return false ;
		}
	}
	
	return true ;
}
 
class Maze {
	
	
	public:
	stack<int> x, y ;					// record the branch's x, y 
	stack<int> dir ;
	int column, row ; 					// straight, horizontal
	vector<vector<char> > maze ; 		// store maze
	bool foundall = false ; 	    	// all num of target 'G' has found 
	bool foundone = false ; 			// has found one of 'G'
	int found_goal = 0, target = 0 ; 	// had found how many goal, how many goal to find ( input )   
	int shortstep = 0 ;
	int shortGx = 0, shortGy = 0 ; 	
	
	
	void PrintMaze() { 
		for ( int i = 0 ; i < row ; i ++ ) {
			for ( int j = 0 ; j < column ; j ++ ) {
				if ( maze[i][j] == 'T' ) maze[i][j] = 'G' ;  // return to 'G'
				if ( maze[i][j] == 'D' ) maze[i][j] = 'V' ;
				cout << maze[i][j] ;
			} // for ()
			
			cout << endl ;
		} // for ()
		
		cout << endl ;
	} // PrintMaze()
	
	void VtoE() {
		for ( int i = 0 ; i < row ; i ++ ) {
			for ( int j = 0 ; j < column ; j ++ ) {
				if ( maze[i][j] == 'V' ) maze[i][j] = 'E' ;  // return to 'G'
				
			}
		}
			
	} // RtoE()
			
			
	void CopyMaze( vector<vector<char> > & b ) {
		vector<char> temp ;
		for ( int i = 0 ; i < row ; i ++ ) {
			for ( int j = 0 ; j < column ; j ++ ) {
				temp.push_back( maze[i][j] ) ;
			} // for()
			
			b.push_back( temp ) ;			
			temp.clear() ;
		} // for()

	} // CopyMaze() 


	bool Judge( int i, int j ) { 			// judge if the next one can go 
		if ( i < 0 || i >= row || j < 0 || j >= column ) return false ;  // out of vetor's range
		
		if ( maze[i][j] == 'G' || maze[i][j] == 'E' || maze[i][j] == 'V' || maze[i][j] == 'T' ) return true ;
		
		return false ;
			
	} // Judge()
		
	bool hasBranch( int i, int j, int direction ) {
		bool right = Judge( i, j + 1 ) ;
		bool down = Judge( i + 1, j ) ;
		bool left = Judge( i, j - 1 ) ;
		bool up = Judge( i - 1, j ) ;
		
		if ( direction == 0 ) {  // direction is right 
			 
			if ( ( right && down ) || ( right && up ) || ( up && down ) ) return true ;
			
			else return false ;
			
		} // if ( direction == 0 ) 
		
		if ( direction == 1 ) {  // direction is down 
			
			if ( ( right && down ) || ( left && down ) || ( left && right ) ) return true ;
			
			else return false ;
			
		} // if ( direction == 1 )
		
		if ( direction == 2 ) {   // direction is left 
			
			if ( ( left && down ) || ( left && up ) || ( up && down ) ) return true ;

			else return false ;
			
		} // if ( direction == 2 ) 
		
		if ( direction == 3 ) {  // direction is up 
			
			if ( ( right && up ) || ( left && up ) || ( left && right ) ) return true ;

			else return false ;
			
		} // if ( direction == 3 ) 
		
		return false ;
		
	} // hasBranch()
	
	bool NearBranch( int i, int j ) {					// judge if the position near the branch  
		if ( x.empty() || y.empty() ) return false ;    // no branch before  
		
		else if ( ( i == y.top() + 1 && j == x.top() ) || ( i == y.top() && j == x.top() + 1 ) ||
				 ( i == y.top() - 1 && j == x.top() ) || ( i == y.top() && j == x.top() - 1 ) ||
				 ( i == y.top() && j == x.top() ) ) {    
				 
				 // if the point now at the branch point's left, right, up, down, or the btanch point self 
				 
				return true ;		  
				
		} // else if()
		
		else return false ;
		
	} // NearBranch()
	
	
	void FindGoal_V( int i, int j, int direction ) { 		// find the path which will be passed by, mission 1
		
		if ( foundall ) return ;  				// all target has been found 
			
		if ( maze[i][j] == 'G' )  { 
			maze[i][j] = 'T' ;  				// record this 'G' has been found  
			found_goal ++ ;
			
			if ( found_goal == target ) {  		// has found the number of target 'G'
				PrintMaze() ;
				foundall = true ;   	
				return ;						// back 
			} // if()
									
		} // if ()
		
		
		if ( maze[i][j] == 'E' || maze[i][j] == 'T' ) {		//  to intercept 'V' which was passed by  
		
			if ( maze[i][j] == 'E' ) maze[i][j] = 'V' ;
		
			if ( direction == 0 ) { 	// right 
				
				if ( Judge( i, j + 1 ) ) FindGoal_V( i, j + 1, 0 ) ; // judge if right has road
			
				if ( Judge( i + 1, j ) ) FindGoal_V( i + 1, j, 1 ) ; // judge down
				
				if ( Judge( i - 1, j ) ) FindGoal_V( i - 1, j, 3 ) ; // judge up
							
			} // if 
		
		
			if ( direction == 1 ) { 	//  down 

				if ( Judge( i + 1, j ) ) FindGoal_V( i + 1, j, 1 ) ; // down
			
				if ( Judge( i, j - 1 ) ) FindGoal_V( i, j - 1, 2 ) ; // left
			
				if ( Judge( i, j + 1 ) ) FindGoal_V( i, j + 1, 0 ) ; // right
				
			} // if ()
		
			if ( direction == 2 ) {     // left

				if ( Judge( i, j - 1 ) ) FindGoal_V( i, j -1, 2 ) ; // left
			
				if ( Judge( i - 1, j ) ) FindGoal_V( i - 1, j, 3 ) ; // up
			
				if ( Judge( i + 1, j ) ) FindGoal_V( i + 1, j, 1 ) ; // down
						
			} // if()
		
			if ( direction == 3 ) {     // up

				if ( Judge( i - 1, j ) ) FindGoal_V( i - 1, j, 3 ) ;  // up
			
				if ( Judge( i, j + 1 ) ) FindGoal_V( i, j + 1, 0 ) ;  // right 
			
				if ( Judge( i, j - 1 ) ) FindGoal_V( i, j -1, 2 ) ;   // left
			}  // if ()
		
			return ;
		
		} // if()
		
	} // FindGoal_V()
	
	void FindGoal_R( int i, int j, int direction ) {		// find the one path that can find all 'G', mission 2 
		if ( foundall ) return ;
			
		if ( maze[i][j] == 'G' ) {
			maze[i][j] = 'T' ; 
			found_goal ++ ;
			foundone = true ;	
			if ( found_goal == target ) {
				PrintMaze() ;
				foundall = true ;
			} // if()
			
		
		} // if ()
		
		
		if ( maze[i][j] == 'V'  || maze[i][j] == 'T' ) { 	// because the maze has been changed from 'E' to 'V'
															// just to check the 'V' 

			if ( NearBranch( i, j ) && foundone ) 			// if has found one of 'G' and the position now near the branch 
															// then foundone = false, because it has returned to the previous branch point  
				foundone = false ;
						
			if ( hasBranch( i, j , direction ) ) {		// position has branch, record the position of the branch point 
			
				x.push( j ) ;
				y.push( i ) ;
				
			} // if 		
			
			if ( maze[i][j] == 'V' ) maze[i][j] = 'R' ;
		
			if ( direction == 0 ) { // right 
			
				if ( Judge( i, j + 1 ) ) FindGoal_R( i, j + 1, 0 ) ;
	
				if( Judge( i + 1, j ) )  FindGoal_R( i + 1, j, 1 ) ;

				if ( Judge( i - 1, j ) ) FindGoal_R( i - 1, j, 3 ) ;
				
			} // if()
			
		
			if ( direction == 1 ) {

				if ( Judge( i + 1, j ) ) FindGoal_R( i + 1, j, 1 ) ;
			
				if ( Judge( i, j - 1 ) ) FindGoal_R( i, j - 1, 2 ) ;
			
				if ( Judge( i, j + 1 ) ) FindGoal_R( i, j + 1, 0 ) ;
			
			} // if()
		
			if ( direction == 2 ) {

				if ( Judge( i, j - 1 ) ) FindGoal_R( i, j - 1, 2 ) ;
			
				if ( Judge( i - 1, j ) ) FindGoal_R( i - 1, j, 3 ) ;
			
				if ( Judge( i + 1, j ) ) FindGoal_R( i + 1, j, 1 ) ;
			
			} // if()
			
			if ( direction == 3 ) {

				if ( Judge( i - 1, j ) ) FindGoal_R( i - 1, j, 3 ) ;
			
				if ( Judge( i, j + 1 ) ) FindGoal_R( i, j + 1, 0 ) ;
			
				if ( Judge( i, j - 1 ) ) FindGoal_R( i, j - 1, 2 ) ; 
				
			} // if()
			
			
			// if have not found one of 'G' and the position is not 'T', then the path which passed by before returned to 'E'		
			if ( ! foundone && maze[i][j] != 'T' ) maze[i][j] = 'E' ;	
			
			if ( maze[i][j] == 'T' ) foundone = true ;  // if the point is 'T' then foundone be true
			
			if ( hasBranch( i, j , direction ) ) {  // if the point has branch and all the branch has been search
													// then pop the branch point 
				x.pop() ;
				y.pop() ;
				
			} // if()
			
		} // if()
		
		return ;
		
	} // SearchOne_R() 	
	
	
	void Shortest_R( int i, int j, int direction, vector<vector<char> > & b, int step ) {
		
		if ( foundone ) return ;
		
		if ( maze[i][j] == 'G' && i == shortGy && j == shortGx ) {
			if ( step == shortstep ) {   // find the shortest one then end 
				foundone = true ;
				CopyMaze( b ) ;
			} // if ()
			
			return ;
		} // if()
		
		
		
		if ( maze[i][j] == 'E'  || maze[i][j] == 'G' ) { 	// because the maze has been changed from 'E' to 'V'
															// just to check the 'V' 
			
			
			if ( maze[i][j] == 'E' ) maze[i][j] = 'R' ;
		
			if ( direction == 0 ) { // right 
			
				if ( Judge( i, j + 1 ) ) Shortest_R( i, j + 1, 0, b, step + 1 ) ;
	
				if( Judge( i + 1, j ) )  Shortest_R( i + 1, j, 1, b, step + 1 ) ;

				if ( Judge( i - 1, j ) ) Shortest_R( i - 1, j, 3, b, step + 1 ) ;
				
			} // if()
			
		
			if ( direction == 1 ) {

				if ( Judge( i + 1, j ) ) Shortest_R( i + 1, j, 1, b, step + 1 ) ;
			
				if ( Judge( i, j - 1 ) ) Shortest_R( i, j - 1, 2, b, step + 1 ) ;
			
				if ( Judge( i, j + 1 ) ) Shortest_R( i, j + 1, 0, b, step + 1 ) ;
			
			} // if()
		
			if ( direction == 2 ) {

				if ( Judge( i, j - 1 ) ) Shortest_R( i, j - 1, 2, b, step + 1 ) ;
			
				if ( Judge( i - 1, j ) ) Shortest_R( i - 1, j, 3, b, step + 1 ) ;
			
				if ( Judge( i + 1, j ) ) Shortest_R( i + 1, j, 1, b, step + 1 ) ;
			
			} // if()
			
			if ( direction == 3 ) {

				if ( Judge( i - 1, j ) ) Shortest_R( i - 1, j, 3, b, step + 1 ) ;
			
				if ( Judge( i, j + 1 ) ) Shortest_R( i, j + 1, 0, b, step + 1 ) ;
			
				if ( Judge( i, j - 1 ) ) Shortest_R( i, j - 1, 2, b, step + 1 ) ; 
				
			} // if()
					
		 	
			if ( maze[i][j] == 'R' )maze[i][j] = 'E' ;	// return to 'E'
			
			
		} // if()
		
		return ;
		
	} // Shortest_R() 
	
	void Shortest_V( int i, int j, int direction, int step ) {
		if ( shortstep != 0 && step > shortstep ) return ;
		
		if ( maze[i][j] == 'G'  ) {  // find one road to 'G' 
		
			foundone = true ;
 			if ( shortstep == 0 ) {  // if  this is the first one 
				shortstep = step ;
				shortGx = j ;
				shortGy = i ;
			}
			
			else if ( step <= shortstep ) { 
				shortstep = step ;
				shortGx = j ;
				shortGy = i ;
			}
			
			return ;
		} // if ()
		
		// if ( ! hasbranch( i, j ) && foundone ) 
		
		if ( maze[i][j] == 'E'  || maze[i][j] == 'T' || maze[i][j] == 'V' ) { 	
															
			
			if ( maze[i][j] == 'E' ) maze[i][j] = 'V' ;
			
			if ( hasBranch( i, j , direction ) ) {		// position has branch, record the position of the branch point 
			
				x.push( j ) ;
				y.push( i ) ;
				
			} // if 
		
			if ( direction == 0 ) { // right 
			
				if ( Judge( i, j + 1 ) ) Shortest_V( i, j + 1, 0, step + 1 ) ;
	
				if( Judge( i + 1, j ) )  Shortest_V( i + 1, j, 1, step + 1  ) ;

				if ( Judge( i - 1, j ) ) Shortest_V( i - 1, j, 3, step + 1 ) ;
				
			} // if()
			
		
			if ( direction == 1 ) {

				if ( Judge( i + 1, j ) ) Shortest_V( i + 1, j, 1, step + 1 ) ;
			
				if ( Judge( i, j - 1 ) ) Shortest_V( i, j - 1, 2, step + 1 ) ;
			
				if ( Judge( i, j + 1 ) ) Shortest_V( i, j + 1, 0, step + 1 ) ;
			
			} // if()
		
			if ( direction == 2 ) {

				if ( Judge( i, j - 1 ) ) Shortest_V( i, j - 1, 2, step + 1 ) ;
			
				if ( Judge( i - 1, j ) ) Shortest_V( i - 1, j, 3, step + 1 ) ;
			
				if ( Judge( i + 1, j ) ) Shortest_V( i + 1, j, 1, step + 1 ) ;
			
			} // if()
			
			if ( direction == 3 ) {

				if ( Judge( i - 1, j ) ) Shortest_V( i - 1, j, 3, step + 1 ) ;
			
				if ( Judge( i, j + 1 ) ) Shortest_V( i, j + 1, 0, step + 1 ) ;
			
				if ( Judge( i, j - 1 ) ) Shortest_V( i, j - 1, 2, step + 1 ) ; 
				
			} // if()
			
		} // if()
		
		return ;
		
	} // Shortest_V() 
	
	void initial() { 
		maze.clear() ;
		found_goal = 0 ;
		foundall = false ;
		foundone= false ;
		row = 0 ;
		column = 0 ;
		shortGx = 0, shortGy = 0 ; 	
		shortstep = 0 ;
		
		while ( ! x.empty() && ! y.empty() ) {
			x.pop() ;
			y.pop() ;
		} // while()
		
		
	} // initial()
	
	bool Read_txt() {
		fstream buffer ;
		string file ;
		cin >> file ;
		file = "input" + file +".txt" ;
		buffer.open( file.c_str(), ios::in ) ;
		if ( buffer.is_open() ) {
			vector<char> buffer_column ;
			char temp[20] = {'\0'} ;
			buffer.getline( temp, 20 ) ;
			int i = 0 ;
			while ( temp[i] == ' ' ) i ++ ;
			while( temp[i] != ' ' ) {
				column = column * 10 + temp[i] - '0' ;
				i ++ ;
			}

			while ( temp[i] == ' ' ) i ++ ;
			while( temp[i] !=  '\0' ) {
				row = row * 10 + temp[i] - '0';
 				i ++ ;
			}
		
			while( ! buffer.eof() ) {
				buffer.getline( temp, 20 ) ;
				for( int i = 0; temp[i] != '\0'; i++ ) {
					buffer_column.push_back(temp[i]) ;
				}
					
				maze.push_back( buffer_column ) ;
				buffer_column.clear() ;
			}
			
			buffer.close() ;
			return true ;
		}
			
		else {
			cout << endl << file << " does not exist!" << endl ;
			return false ;
		}			
	}


	void doCommand( int command ) {
		string temp ;
		if ( command == 1 ) target = 1 ;	// set the target of command 1 
		
		else if ( command == 2 ) {			// get the input target of command 2 
			cout << endl ;
			cout << "Number of G (goal) :" ;
			cin >> temp ;
			cout << endl ; 
			while ( ! isNumber( temp ) ) {
				cout << "Number of G (goal) :" ;
				cin >> temp ;
				cout << endl ;
			} // while ()
			
			target = atoi( temp.c_str() ) ;
						
		} // else if()
		
 		FindGoal_V( 0, 0, 0 ) ;		// start from the maze[0][0] and direction is right 
 		
		if ( foundall ) {			// all the target has been found then reset the found_goal && foundall 
									// FindGoal_R start from maze[0][0] and direction is right 
			found_goal = 0 ;
			foundall = false ;
			FindGoal_R( 0, 0, 0 ) ;
			
		} // if()
		
		else PrintMaze() ;			// not found num of target 'G' then print the current situation of the maze
		
	} // doCommand()
	
	void Command3() {
		vector<vector<char> > storeMaze ; // to store the 
			
		Shortest_V( 0, 0, 0, 1 ) ; 	 
		
		PrintMaze() ;
		VtoE() ;
		
		if ( foundone ) {
			foundone = false ;
			Shortest_R( 0, 0, 0, storeMaze, 1 ) ; 	 			
			for ( int i = 0 ; i < row ; i ++ ) {		// print the shortest path road 
				for ( int j = 0 ; j < column ; j ++ ) {
					cout << storeMaze[i][j] ;
				} // for ()	
			
				cout << endl ;
			} // for()
			
			cout << endl ;
			cout << "Shortest path length = " << shortstep << endl ;
		} // if()
		
		
		
	} // Command3()

	
};
 


void Preface() {
	
	cout << endl << "*** Path Finding ***" ;
	cout << endl << "* 0. Quit          *" ;
	cout << endl << "* 1. One goal      *" ;
	cout << endl << "* 2. More goals    *" ;
	cout << endl << "* 3. Shortest path *" ;
	cout << endl << "********************" ;
	cout << endl << "Input a command(0, 1, 2, 3): " ;
	
} // Preface() 
 
 int main() {
	int command ;
	Maze maze ;
 	do {
 		
 		Preface() ;
 		cin >> command ;
 		
		maze.initial() ;
		
		if ( command == 0 ) break ;
		
 		else if ( command == 1 || command == 2 ) {
 			
 			cout << endl << "Input a file number (e.g., 201, 202, ...):" ;
 			
 			if ( maze.Read_txt() ) {
 				
				maze.doCommand( command ) ;
				
				cout << endl ;
				
			} // if()
			
		} // else if()
		
		else if ( command == 3 ) {
			cout << endl << "Input a file number (e.g., 201, 202, ...):" ;
 			
 			if ( maze.Read_txt() ) 
 				maze.Command3() ;
			
		} // else if 
		
		else cout << endl << "Command does not exist !" << endl ;
			
	 } while ( command != 0 ) ;

}
