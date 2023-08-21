# include <iostream>
# include <vector>
# include <stack>
# include <fstream> 
# include <string>
# include <sstream>
# include <stdlib.h>
# include <queue>
#include <time.h>


using namespace std ;

struct Data {
	int OID ;
	int Arrival ;
	int Duration ;
	int TimeOut ;
	Data *next ;
};

class List {
	
	struct list {
		int OID ;
		int time ;
		int delay ;
	};
	
	vector<list> abort ;
	vector<list> done ;
	int av_delay = 0 ;
	
	int abindex = 0 ;
	int doindex = 0 ;
	
	public :
		
		void pushabort( int OID, int Arrival, int Duration, int TimeOut, int &time, int overdue ) {		
			list tmp ;
			if ( overdue == 0 ) { // 如果不是逾期 
				tmp.OID = OID ;
				tmp.time = Arrival ; // 到達時刻直接取消 
				tmp.delay = 0 ; // delay直接為0 
				abort.push_back( tmp ) ;
			}
			
			else if ( overdue == 1 ) { // 如果是到cpu裡發現逾期 已在cpu執行 
				tmp.OID = OID ;
				tmp.time = TimeOut ; 
				tmp.delay = tmp.time - Arrival ;
				abort.push_back( tmp ) ;
				time = tmp.time ; // 將現在時間改成drop的時間 				
			} // else if()
				
			else if ( overdue == 2 ) { // 佇列拿到cpu發現逾期 
				tmp.OID = OID ;
				tmp.time = time ; 
				tmp.delay = tmp.time - Arrival ;				
				abort.push_back( tmp ) ;
			}
			
			av_delay = av_delay + tmp.delay ;
			abindex ++ ;
		}
		
		void pushdone( int OID, int Arrival, int Duration, int TimeOut, int &time ) {
			list tmp ;
			tmp.OID = OID ;
			tmp.time = time + Duration ;
			if ( time > Arrival ) {
				tmp.time = time + Duration ;
				tmp.delay = time - Arrival ;
				time = tmp.time ;
			}			
			
			else {
				tmp.time = Arrival + Duration ;
				tmp.delay = 0 ;
				time = tmp.time ;
			}
			
			done.push_back( tmp ) ;
			av_delay = av_delay + tmp.delay ;
			doindex ++ ;
		}

		void pushdonef( int OID, int Arrival, int Duration, int TimeOut, int &time ) {
			list tmp ;
			tmp.OID = OID ;
			tmp.time = Arrival + Duration ;
			tmp.delay = 0 ;
			time = tmp.time ;
			done.push_back( tmp ) ;
			doindex ++ ;
		} // pushdonef() 
		
		void clear() {
			abort.clear() ;
			done.clear() ;
		}
		
		void write_txt( string s ) {
			fstream newfile ;
			s = "output" + s + ".txt" ;
			newfile.open( s.c_str(), ios::out ) ;
			newfile << "	[Abort Jobs]	" << endl ;
			newfile << "	OID	Abort	Delay" << endl ;
			for ( int i = 0; i < abort.size(); i++ ) {
				newfile << "[" << i << "]	" << abort[i].OID << "	" ;
				newfile << abort[i].time << "	" << abort[i].delay << endl ;
			}
			
			newfile << "	[Jobs Done]	" << endl ;
			newfile << "	OID	Departure	Delay" << endl ;
			
			for ( int i = 0; i < done.size(); i++ ) {
				newfile << "[" << i << "]	" << done[i].OID << "	" ;
				newfile << done[i].time << "	" << done[i].delay << endl ;
			}
			
			newfile << endl << "[Average Delay]	" ;
			newfile << (av_delay / ( abort.size() + done.size() ) + av_delay % ( abort.size() + done.size() ) ) << " ms" ;
			newfile << endl << "[Success Rate]	" ;
			newfile << done.size() / ( abort.size() + done.size() ) + done.size() % ( abort.size() + done.size() ) << "	%" ;
			newfile.close() ;
		}

		
};

class Queue {
	
	Data *head = NULL ;
	Data *tail = NULL ;
	
	public :		 
		
		void enqueue( Data a ) { // 把資料放進Queue 
			Data *temp = NULL ;
			temp = new Data ;
			temp -> next = NULL ;
			temp -> OID = a.OID ;
			temp -> Arrival = a.Arrival ;
			temp -> Duration = a.Duration ;
			temp -> TimeOut = a.TimeOut ;
			if ( head == NULL ) {
				head = temp ;
				tail = temp ;
			}
			
			else {
				tail -> next = temp ;
				tail = tail -> next ;
			}
		}
		
		void dequeue() {
			Data *temp = head ;
			head = head -> next ;
			delete temp ;
			temp = NULL ;
		}	
			
		void front( int &OID, int &Arrival, int &Duration, int &TimeOut ) {
			OID = head -> OID ;
			Arrival = head -> Arrival ;
			Duration = head -> Duration ;
			TimeOut = head -> TimeOut ;
			dequeue() ;
		}

		bool isEmpty() {
			if ( head == NULL ) return true ;
			else return false ;
		}
		
		bool isFull() {
			Data *walk = head ;
			int i = 0 ;
			while ( walk != NULL ) {
				walk = walk -> next ;
				i ++ ;
			}
			
			if ( i == 3 ) return true ;
			else return false ;
		}

};

class CPU {
	vector<Data> data ;
	Queue a ;
	List l ;
	int time = 0 ;
	
	public :
		
		void cpu( int OID, int Arrival, int Duration, int TimeOut, int &time ) {
			if ( time + Duration > TimeOut ) // 是逾期 
				l.pushabort( OID, Arrival, Duration, TimeOut, time, 1 ) ;  
			else l.pushdone( OID, Arrival, Duration, TimeOut, time ) ; // done 
		}
		
		void distri( string s ) {
			int index, OID, Arrival, Duration, TimeOut ;
			int n = 0 ;
			l.pushdonef( data[index].OID, data[index].Arrival, data[index].Duration, data[index].TimeOut, time ) ;
			// 第一筆資料直接放進done 
			index ++ ;
			while ( index < data.size() ) { //跑所有的資料 
				if ( data[index].Arrival < time ) { // 如果現在到達的時間小於現在時刻 就要排隊 
					if ( a.isFull() ) // 如果滿了就直接取消 
						l.pushabort( data[index].OID, data[index].Arrival,data[index].Duration,
									 data[index].TimeOut, time, 0 ) ;
						//放進取消清單 且非逾期 
					else a.enqueue( data[index] ) ; // 如果沒滿 加進去佇列 
					index ++ ; // 找下一個 
				}
				
				else if ( data[index].Arrival > time ) { // 如果下一個的到達時間比現在時間大 
					while ( ! a.isEmpty() ) { // 佇列不是空的 
						a.front( OID, Arrival, Duration, TimeOut ) ; // 拿佇列第一個的資料出來 
						if ( time >= TimeOut ) l.pushabort( OID, Arrival, Duration, TimeOut, time, 2 ) ;
						else cpu( OID, Arrival, Duration, TimeOut, time ) ; // 放進cpu裡判斷 
					}
					
					a.enqueue( data[index] ) ; // 放新的進去 
					index ++ ;					
				}
				
				else if ( data[index].Arrival == time ) { // 如果等於 
					a.front( OID, Arrival, Duration, TimeOut ) ; // 先拿佇列第一個放進cpu處裡 
					if ( time >= TimeOut ) l.pushabort( OID, Arrival, Duration, TimeOut, time, 2 ) ;
					else cpu( OID, Arrival, Duration, TimeOut, time ) ; // 放進cpu裡判斷 
					a.enqueue( data[index] ) ; // 再把新的放進佇列 
					index ++ ;
				}
			}
			
			while ( ! a.isEmpty() ) {
				a.front( OID, Arrival, Duration, TimeOut ) ;
				if ( time >= TimeOut ) l.pushabort( OID, Arrival, Duration, TimeOut, time, 2 ) ;
				else cpu( OID, Arrival, Duration, TimeOut, time ) ; // 放進cpu裡判斷 
			}
				
			l.write_txt( s ) ;
		}
	
		bool Read_txt( string &name, float &r_time, int type ) {
			float start = clock() ;		
			data.clear() ;
			fstream file ;
			string line ;
			string namef ;
			Data a ;
			int num ; 
			int det = 0 ;
			if ( type == 1 ) namef = "input" + name + ".txt" ;
			else if ( type == 2 ) namef = "sorted" + name + ".txt" ; 
			file.open( namef.c_str(), ios::in ) ;
			getline( file, line ) ;
			if ( file.is_open() ) {
				while ( file >> num ) {
					
					a.OID = num ;
					file >> a.Arrival ; 
					file >> a.Duration ;
					file >> a.TimeOut ;			
					data.push_back( a ) ;
					det = 0 ;
				} // while ()
				
				file.close() ;
				float end = clock() ;
				r_time = end - start ;
				return true ;
			}
	
			else {
				cout << endl << file << " does not exist!" << endl ;
				return false ;
			}
		}
		
		void shellsort( float &t ) {
			float start = clock() ;
			int index = 0 ;
			int gap = data.size() / 2 ; // 間隔 
			for (; gap > 0; gap = gap / 2 ) {
		        for ( int i = gap; i < data.size(); ++i ) {
		        	int j = i ;
					while ( j >= gap && data[j].Arrival <= data[j-gap].Arrival ) {
						if ( data[j].Arrival < data[j-gap].Arrival ) {
							Data tmp = data[j] ;
							data[j] = data[j-gap] ;
							data[j-gap] = tmp ;
						}
						
						else if ( data[j].Arrival == data[j-gap].Arrival ) {
							if ( data[j].OID < data[j-gap].OID ) {
								Data tmp = data[j] ;
								data[j] = data[j-gap] ;	
								data[j-gap] = tmp ;
							}
						}
						
						j = j - gap ;
					}
	    		}
			}
			
			float end = clock() ;
			t = end - start ;
		}
		
		void s_write_txt( string s, float &t ) {
			float start = clock() ;
			fstream newfile ;
			s = "sorted" + s + ".txt" ;
			newfile.open( s.c_str(), ios::out ) ;
			newfile << "OID	" << "Arrival	" << "Duration	" << "TimeOut	" << endl ;

			for ( int i; i < data.size(); i++ ) {
				newfile << data[i].OID << "	" ;
				newfile << data[i].Arrival << "	" << data[i].Duration <<"	" << data[i].TimeOut << endl ;
			}
			
			data.clear() ;
			newfile.close() ;
			float end = clock() ;
			t = end - start ;
		}
		
		void printdata() {
			cout << "	OID	" << "Arrival	" << "Duration	" << "TimeOut	" << endl ;
			for ( int i = 0; i < data.size(); i ++ ) {
				cout << "(" << i << ")	" << data[i].OID << "	" << data[i].Arrival << "	" ;
				cout << data[i].Duration << "	" << data[i].TimeOut << endl ;
			}
		}
	
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
 	
 	int command ;
 	bool test = true ;
 	// SQF sqf ;
 	CPU a ;
 	List l ;
 	float time_r, time_s, time_w ;
 	string s ;
 	bool docommand1 = false ;
 	
 	do {
 		Preface() ;
 		cin >> command ;
 		if ( command == 0 ) test = false ;
 		else if ( command == 1 )	{
 			cout << endl << "Input a file number (e.g., 401, 402, 403, ...):" ;
 			cin >> s ;
 			if ( a.Read_txt( s, time_r , 1 ) ) {
 				a.printdata() ;
	 			a.shellsort( time_s ) ;
	 			a.s_write_txt( s, time_w ) ;
	 			cout << endl << "Reading data:	" << time_r << " clocks (" << time_r << "	ms)";
	 			cout << endl << "Sorting data:	" << time_s << " clocks (" << time_s << "	ms)";
	 			cout << endl << "Writing data:	" << time_w << " clocks (" << time_w << "	ms)" << endl ;
	 			cout << endl << "See sorted" + s + ".txt" << endl ;
	 			docommand1 = true ;
			}			
		}
		
		else if ( command == 2 ) {
			if ( ! docommand1 ) {
				cout << endl << "Input a file number (e.g., 401, 402, 403, ...):" ;
				cin >> s ;
			}
				
			if ( a.Read_txt( s, time_r, 2 ) ) {
				a.distri( s ) ;
				cout << endl << "The simulation is running..." << endl << "See output" << s << ".txt" << endl ;
			} //if()
		}

		else cout << endl << "Command does not exist !" << endl ;
 		
	 } while ( test ) ;
 	
} // main()























