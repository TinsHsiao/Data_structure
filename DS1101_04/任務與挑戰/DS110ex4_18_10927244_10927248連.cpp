//10927248 連翊安 10927244 蕭合亭 

# include <iostream>
# include <vector>
# include <string>
# include <fstream>
# include <iomanip> // 控制小數輸出
# include <ctime> 

using namespace std ;

struct Data{
	int OID ;
	int Arri ;
	int Dura ;
	int TimeOut ;
};

struct Done {
	int OID ;
	int Depart ;
	int Delay ;
} ;

struct Cancel {
	int OID ;
	int Abort ;
	int Delay ;
} ;

template <class T>

class Queue {
	
 	int size ;
 	
	struct queue {
		T data ;
		queue * next ; 
	};
	
	queue * head = NULL ;
	queue * tail = NULL ;

	public :
		
		void push( T a ) {
			queue * temp = new queue ;
			temp->next = NULL ;
			temp->data = a ;
			
			if ( head == NULL ) {
				head = temp ;
				tail = temp ;
				temp = NULL ;
				size = 1 ;
			} // if
			
			else {
				tail->next = temp ;
				tail = tail->next ;
				temp = NULL ;
				size ++ ;
			} // else 

		} // push()
		
		void pop() {
			
			if ( head->next == NULL ) {
				delete head ;
				head = NULL ;
				tail = NULL ;
				size -- ;
				return ;
			} // if ()
			

			queue * temp = NULL ;
			temp = head ;
			head = head->next ;
			temp->next = NULL ;
			delete temp ;
			temp = NULL ;
			size -- ;
			return ;
				
		} // pop()

		
		int Size() {
			return size ;
		} // Size()

		
		bool empty() {
			return head == NULL ;
		} // empty()
			
		T top() {
			return head->data ;
		} // top()
		
};

class CPU {
	vector<Cancel> cancel ;
	vector<Done> done ;
	vector<Data> data ;
	int size ;
	string text ; 	// the file name
	int time ; 		// the previous job finish time  
	double START, END ;


	public :

		bool Read( int command ) {
			string temp ;  
			if ( command == 1 ) {
				cout << endl << "Input a file number (e.g., 401, 402, ...):" ;
				cin >> text ;
				temp = "input" + text + ".txt" ;  // set file name
			} // if 

			else if ( command == 2 ) {
				cout << endl << "Input a file number (e.g., 401, 402, ...):" ;
				cin >> text ;
				temp = "sorted" + text + ".txt" ;
			} // else if() 	

			fstream file ;
			file.open( temp.c_str(), ios :: in ) ;     // open the file

			START = clock() ;

			if ( ! file.is_open() ) {         // check the file can be opened 
				cout << "### " << temp << " does not exist ! ###" << endl ;
				return false ;
			} // if()

			else {

				Data t ;
				getline( file, temp ) ;				// read the title 

				while ( file >> t.OID ) {			// Read the data and push into vector 
					file >> t.Arri >> t.Dura >> t.TimeOut ;
					data.push_back( t ) ;
				} // while()

				size = data.size() ;	// set size

			} // else 
			
			file.close() ;
			END = clock() ; 
			return true ;
		} // Read()
	
		void Print() {

			cout << endl << "\tOID" << "\tArrival" << "\tDuration" << "\tTimeout" ;

			for ( int i = 0 ; i < size ; i ++ ) {
				cout << endl << '(' << i + 1 << ")\t" ;
				cout <<  data[i].OID << '\t' << data[i].Arri << '\t' ;
				cout << data[i].Dura << '\t' << data[i].TimeOut ; 
			} // for()

			cout << endl ;

		} // Print()

		void ShellSort() {

			int loc = 0 ;

			for ( int gap = size / 2 ; gap > 0 ; gap = gap / 2 ) {
				for ( int i = gap ; i < size ; i ++ ) {
					for ( loc = i ; loc >= gap && data[loc].Arri <= data[loc-gap].Arri ; loc = loc - gap ) {
			
						if ( data[loc].Arri < data[loc-gap].Arri ) {
							swap( data[loc], data[loc-gap] ) ;
						} // if()

						else if ( data[loc].Arri == data[loc-gap].Arri && data[loc].OID < data[loc-gap].OID ) {
							swap( data[loc], data[loc-gap] ) ;
						} // else if()

					} // for()
				} // for()
			} // for()

		} // ShellSort()

		void WriteSort() {
			
			fstream newfile ;
			string temp = "sorted" + text + ".txt" ;

			newfile.open( temp.c_str(), ios :: out ) ;

			newfile << "OID\t" << "Arrival\t" << "Duration\t" << "TimeOut" << endl ;

			for ( int i = 0 ; i < size ; i ++ ) {
				newfile << data[i].OID << '\t' << data[i].Arri << '\t' ;
				newfile << data[i].Dura << '\t' << data[i].TimeOut <<endl ;  
			} // for()

			newfile.close() ;

		} // WriteSort() 

		void Simulation() {			 // the data now is sorted 

			Queue<Data> wait ;
			Data t ;
			Done tempD ;
			Cancel tempC ; 	
			bool update = false ;  // 檢查佇列裡的工作

			tempD.OID = data[0].OID, tempD.Depart = data[0].Arri + data[0].Dura, tempD.Delay = 0 ;
			time = tempD.Depart ;		// 第一個工作結束的時間 
			done.push_back( tempD ) ;

			for ( int i = 1 ; i < size ; i ++ ) {
				if ( data[i].Arri >= time ) {
					// 此工作抵達時間 >= 目前工作結束
					while ( ! wait.empty() && ! update ) {
						// 檢查佇列裡是否還有能夠執行完成的工作
						t = wait.top() ;

						if ( time + t.Dura <= t.TimeOut ) {
							// 在timeout前可以執行完
							tempD.OID = t.OID, tempD.Depart = time + t.Dura, tempD.Delay = time - t.Arri ;
							time = tempD.Depart ;
							done.push_back( tempD ) ;
						} // if()

						else if ( time >= t.TimeOut ) {
							// 取出時已超過timeout
							tempC.OID = t.OID, tempC.Abort = time, tempC.Delay = time - t.Arri ;
							cancel.push_back( tempC ) ;
						} // else if

						else if ( time + t.Dura > t.TimeOut ) {
							// 取出後在執行過程中timeout 
							tempC.OID = t.OID, tempC.Abort = t.TimeOut, tempC.Delay = t.TimeOut - t.Arri ;
							time = t.TimeOut ;
							cancel.push_back( tempC ) ;
						} // else if 

						if ( time > data[i].Arri ) {
							// 目前工作進來時
							// 原本在佇列裡的工作已經做到超過此工作進來時間
							// 結束佇列檢查
							update = true ;  
						} // if()

						wait.pop() ;

					} // while()

					if ( update ) {
						// time > data[i].Arrival => 進佇列
						wait.push( data[i] ) ;
					} // if()

					else {
						// 此工作抵達時間 >= time, 此工作要執行
						tempD.OID = data[i].OID, tempD.Depart = data[i].Arri + data[i].Dura, tempD.Delay = 0 ;
						time = tempD.Depart ;
						done.push_back( tempD ) ;
					} // else 

					update = false ;

				} // else if 

				else if ( wait.Size() == 3 ) {	
					// 佇列已滿
					tempC.OID = data[i].OID, tempC.Abort = data[i].Arri, tempC.Delay = 0 ;
					cancel.push_back( tempC ) ;
				} // if()

				else {
					wait.push( data[i] ) ;
				} // else 

			} // for()

			while ( ! wait.empty() ) {
				// 清空佇列
				t = wait.top() ;

				if ( time + t.Dura <= t.TimeOut ) {
					// 在timeout前可以執行完
					tempD.OID = t.OID, tempD.Depart = time + t.Dura, tempD.Delay = time - t.Arri ;
					if ( tempD.Depart > time ) time = tempD.Depart ;
					done.push_back( tempD ) ;
				} // if()

				else if ( time >= t.TimeOut ) {
					// 取出時已超過timeout
					tempC.OID = t.OID, tempC.Abort = time, tempC.Delay = time - t.Arri ;
					cancel.push_back( tempC ) ;
				} // else if

				else if ( time + t.Dura > t.TimeOut ) {
					// 取出後在執行過程中timeout 
					tempC.OID = t.OID, tempC.Abort = t.TimeOut, tempC.Delay = t.TimeOut - t.Arri ;
					time = t.TimeOut ;
					cancel.push_back( tempC ) ;
				} // else if 

				wait.pop() ;
				
			} // while() 

		} // Simulation() 

		void WriteSim() {
			fstream newfile ;
			string temp = "output" + text + ".txt" ;
			float delay = 0.0 ;

			newfile.open( temp.c_str(), ios :: out ) ;

			newfile << "\t[Abort Jobs]" << endl << "\tOID" << "\tAbort" << "\tDelay" << endl ;

			for ( int i = 0 ; i < cancel.size() ; i ++ ) {
				newfile << "[" << i + 1 << "]\t" << cancel[i].OID << '\t' ;
				newfile << cancel[i].Abort << '\t' << cancel[i].Delay << endl ;
				delay += cancel[i].Delay ;
			} // for()

			newfile << "\t[Jobs Done]" << endl << "\tOID" << "\tDeparture" << "\tDelay" << endl ;

			for ( int i = 0 ; i < done.size() ; i ++ ) {
				newfile << "[" << i + 1 << "]\t" << done[i].OID << '\t' ;
				newfile << done[i].Depart << '\t' << done[i].Delay << endl ; 
				delay += done[i].Delay ;
			} // for()

			delay = delay / size ; 
			double success = ( (double)done.size() / (double)size ) * 100 ;
			
			newfile << "[Average Delay]\t" << fixed << setprecision(2) << delay << " ms" << endl ;
			newfile << "[Success Rate]\t" << fixed << setprecision(2) << success << " %" << endl ;

			newfile.close() ;
			
		} // WriteSim() 

		void Inintial() {
			cancel.clear() ;
			done.clear() ;
			data.clear() ;
			time = 0 ;
		} // Inintial()

		void doCommand( int command ) {

			if ( ! Read( command ) ) return ; 

			if ( command == 1 ) {

				Print() ;
				cout << endl << "Reading data: " << END - START << " ms" << endl ;

				START = clock() ;
				ShellSort() ;
				END = clock() ;
				cout << "Sorting data: " << END - START << " ms" << endl ;  

				START = clock() ;
				WriteSort() ;
				END = clock() ;
				cout << "Writing data: " << END - START << " ms" << endl ; 

				cout << endl << "See sorted" << text << ".txt" << endl ;

			} // if ()

			else if ( command == 2 ) {
				cout << endl << "The Simulation is running..." << endl ;
				Simulation() ;
				WriteSim() ;
				cout << "See output" << text << ".txt" << endl ;
			} // else if()
			
		} // doCommand()

};


void Preface() {
	
	cout << endl << "**** Simulate FIFO Queues by SQF *****" ;
	cout << endl << "* 0. Quit                            *" ;
	cout << endl << "* 1. Sort a file                     *" ;
	cout << endl << "* 2. Simulate one FIFO queue         *" ;
	cout << endl << "***********************************" ;
	cout << endl << "Input a choice(0, 1, 2): " ;

} // Preface()


int main() {
 	
	string temp ;
 	int command ;
 	bool test = true ;
 	CPU cpu ;
 	
 	do {
 		
 		Preface() ;
		cin >> command ;
		cpu.Inintial() ;
 		if ( command == 0 ) test = false ;
 		
 		else if ( command == 1 || command == 2 ) {
			 cpu.doCommand( command ) ; 	
		} // else if()

 		else cout << endl << "Command does not exist!" << endl ;
 		
	 } while ( test ) ;
 	
} // main()


