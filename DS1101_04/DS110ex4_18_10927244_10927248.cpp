//10927248 �s���w 10927244 ���X�F 

# include <iostream>
# include <vector>
# include <string>
# include <fstream>
# include <iomanip> // ����p�ƿ�X
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
	int no ; 	// �����O�q���Ӧ�C����
} ;

struct Cancel {
	int OID ;
	int Abort ;
	int Delay ;
	int no ;	// �����O�q���Ӧ�C����
} ;

vector<Cancel> cancel ;
vector<Done> done ;
vector<Data> list ;
int DataSize ;
double START, END ;
string text ;
int cpunum ;

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
			if ( head == NULL ) {
				size = 0 ;
			} // if()

			return size ;
		} // Size()

		
		bool empty() {
			return head == NULL ;
		} // empty()
			
		T top() {
			return head->data ;
		} // top()

		void Print() {
			queue * walk = head ;
			while( walk != NULL ) {
				cout << walk->data.OID ;
				cout << endl ;
				walk = walk->next ;
			} // while()
		} // Print()
		
};



void Print() {

	cout << endl << "\tOID" << "\tArrival" << "\tDuration" << "\tTimeout" ;

	for ( int i = 0 ; i < DataSize ; i ++ ) {
		cout << endl << '(' << i + 1 << ")\t" ;
		cout << list[i].OID << '\t' << list[i].Arri << '\t' ;
		cout << list[i].Dura << '\t' << list[i].TimeOut ; 
	} // for()

	cout << endl ;

} // Print()

void ShellSort() {

	int loc = 0 ;

	for ( int gap = DataSize / 2 ; gap > 0 ; gap = gap / 2 ) {
		for ( int i = gap ; i < DataSize ; i ++ ) {
			for ( loc = i ; loc >= gap && list[loc].Arri <= list[loc-gap].Arri ; loc = loc - gap ) {
	
				if ( list[loc].Arri < list[loc-gap].Arri ) {
					swap( list[loc], list[loc-gap] ) ;
				} // if()

				else if ( list[loc].Arri == list[loc-gap].Arri && list[loc].OID < list[loc-gap].OID ) {
					swap( list[loc], list[loc-gap] ) ;
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

	for ( int i = 0 ; i < DataSize ; i ++ ) {
		newfile << list[i].OID << '\t' << list[i].Arri << '\t' ;
		newfile << list[i].Dura << '\t' << list[i].TimeOut <<endl ;  
	} // for()

	newfile.close() ;

} // WriteSort() 

class CPU {

	Queue<Data> wait ;
	int time ;
	int work ; 	// ����cpu�O�_�����b�B�z���u�@ 

	public :

		CPU() {
			time = 0 ;
			work = 0 ;
		} // CPU()

		int Time() {
			return time ;
		} // Time()

		int WaitNum() {			
			// �^�ǲ{�b���h�֭Ӥu�@�b���ݩΰ���
			return wait.Size() + work ;
		} // WaitNum()

		bool isFull() {
			return wait.Size() == 3 ;
		} // ifFull() 

		void PushIn( Data t ) {
			wait.push( t ) ;
		} // PushIn()

		void Judge( Data t, int no ) {
			// �B�z��C�̪��u�@ 
			Done tempD ;
			Cancel tempC ;
			if ( time + t.Dura <= t.TimeOut ) {
				// �btimeout�e�i�H���槹
				tempD.OID = t.OID, tempD.Depart = time + t.Dura, tempD.Delay = time - t.Arri ;
				tempD.no = no + 1 ;
				if ( tempD.Depart > time ) time = tempD.Depart ;
				done.push_back( tempD ) ;
			} // if()

			else if ( time >= t.TimeOut ) {
				// ���X�ɤw�W�Ltimeout
				tempC.OID = t.OID, tempC.Abort = time, tempC.Delay = time - t.Arri ;
				tempC.no = no + 1 ;
				cancel.push_back( tempC ) ;
			} // else if

			else if ( time + t.Dura > t.TimeOut ) {
				// ���X��b����L�{��timeout 
				tempC.OID = t.OID, tempC.Abort = t.TimeOut, tempC.Delay = t.TimeOut - t.Arri ;
				tempC.no = no + 1 ;
				time = t.TimeOut ;
				cancel.push_back( tempC ) ;
			} // else if 

		} // Judge()

		void DealArri( int Arri, int no ) {
			// �u�@��F�ɶ� >= �ثe�u�@�������ɶ� 
			bool update = false ;
			Data t ;

			if ( time > Arri ) {
				// �]���bsimulation�̭��|�h�ˬd�C�@��cpu
				// �����@�w�C��cpu���u�@�����ɶ��� <= ��F�ɶ�
				// �ҥH�����ˬd 
				update = true ;
			} // if()

			while ( ! wait.empty() && ! update ) {
				// �ˬd��C�̪��u�@���p
				// �@����ثe�u�@�ɶ� > Arri �Φ�C�u�@���w���� 
				t = wait.top() ;
				Judge( t, no ) ;
				wait.pop() ;

				if ( time > Arri ) {
					update = true ;
					
					// time > Arri ��ܲ{�b�o��cpu�����b���檺�u�@
					// �ҥHwork = 1 
					work = 1 ;
				} // if()

			} // while()

			if ( time <= Arri ) {
				// cpu�b�ثe�n�i�Ӫ��u�@��F���ɭԬO���m�� 
				// �ҥHwork  = 0  
				work = 0 ;
			} // if()

		} // DealArri()

		void Donework( Data t, int no ) {

			Done tempD ;
			tempD.OID = t.OID, tempD.Depart = t.Arri + t.Dura, tempD.Delay = 0 ;
			tempD.no = no + 1 ;
			time = tempD.Depart ;
			done.push_back( tempD ) ;
			work = 1 ;

		} // Done()

		void ClearWait( int no ) {
			Data t ;

			while ( ! wait.empty() ) {
				t = wait.top() ;
				Judge( t, no ) ;
				wait.pop() ;
			} // while()

		} // ClearWait()

		void Print() {
			wait.Print() ;
		} // Print

};

int Path( vector<CPU> cpu ) {
	// ��ֵ̤��ݤu�@��cpu�s�� 
	int exe = 0 ;
	for ( int i = 1 ; i < cpu.size() ; i ++ ) {

		if ( cpu[exe].WaitNum() > cpu[i].WaitNum() ) {
			exe = i ;
		} // if()

	} // for()

	return exe ;

} // Path()

bool AllFull( vector<CPU> cpu ) {
	// �ˬd�C��cpu����C�O�_�����F 
	for ( int i = 0 ; i < cpu.size() ; i ++ ) {
		if ( ! cpu[i].isFull() ) {
			return false ;
		} // if()
	} // for()

	return true ;

} // AllFull()

int TimeFast( vector<CPU> cpu, int & mintime ) {
	// ���ְ̧��浲���ثe�u�@��cpu�ɶ� 
	int exe = 0 ;
	mintime = cpu[0].Time() ;

	for ( int i = 1 ; i < cpunum ; i ++ ) {
		if ( cpu[i].WaitNum() != 0 && cpu[i].Time() < mintime ) {
			mintime = cpu[i].Time() ;
			exe = i ;
		} // if()
	} // for()

	return exe ;

} // TimeFast()

void Simulation() {
	vector<CPU> cpu(cpunum) ;
	int mintime ;

	cpu[0].Donework( list[0], 0 ) ;
	mintime = cpu[0].Time() ;		// �]�w�ثe�ַ̧|�����mcpu�X�{���ɶ� 

	int exe = 0 ;  // �����ֵ̤��ݤu�@��cpu�s�� 
	Cancel tempC ;
	
	exe = Path( cpu ) ;		// ��s�ثe�ֵ̤��ݤu�@��cpu�s�� 

	for ( int i = 1 ; i < DataSize ; i ++ ) {

		exe = Path( cpu ) ;

		if ( list[i].Arri >= mintime ) {
			// ���u�@��F�ɶ� > �ثe�ֵ̧����u�@���ɶ� 

			for ( int j = 0 ; j < cpunum ; j ++ ) {
				// �ˬd�C��cpu����C���p 
				cpu[j].DealArri( list[i].Arri, j ) ;
			} // for()

			exe = Path( cpu ) ;		// ��s�ثe�ֵ̤��ݤu�@��cpu�s�� 

			if ( cpu[exe].WaitNum() == 0 ) {
				// �p�G��cpu�b���u�@��F���ɭ�
				// �w�g�����쥻���u�@
				// ��C�]�S�����ݤu�@, �N����{�b�i�Ӫ��u�@ 
				cpu[exe].Donework( list[i], exe ) ;
			} // if()

			else {
				// �p�G�s��exe��cpu�����b���檺�u�@
				// �⦹�u�@��i�s��exe����C���� 
				cpu[exe].PushIn( list[i] ) ;
			} // else 

		} // if()

		else if ( AllFull( cpu ) ) {
			// ��C�����F
			tempC.OID = list[i].OID, tempC.Abort = list[i].Arri, tempC.Delay = 0 ;
			tempC.no = 0 ;
			cancel.push_back( tempC ) ;
		} // if()

		else if ( cpu[exe].WaitNum() == 0 ) {
			// �p�G�{�b���ݤH�Ƴ̤֪�cpu�O���m���p
			// �⦹�u�@���s��exe��cpu���� 
			cpu[exe].Donework( list[i], exe ) ;
		} // else if 

		else {
			// ���u�@�b����
			// ��icpu����C���� 
			cpu[exe].PushIn( list[i] ) ;
		} // else

		// ��s�{�b�ֵ̧�������u�@��cpu�ɶ� 
		TimeFast( cpu, mintime ) ;

	} // for()

	for ( int i = 0 ; i < cpunum ; i ++ ) {
		// �M�ŨC��cpu����C
		cpu[i].ClearWait( i ) ;
	} // for()


} // Simulation()

bool Read( int command ) {
	string temp ;  
	cout << endl << "Input a file number (e.g., 401, 402, ...):" ;
	cin >> text ;

	if ( command == 1 ) {
		temp = "input" + text + ".txt" ;  // set file name
	} // if 

	else if ( command == 2 ) {
		temp = "sorted" + text + ".txt" ;
		cpunum = 1 ;
	} // else if() 	

	else if ( command == 3 ) {
		temp = "sorted" + text + ".txt" ;
		cpunum = 2 ;
	} // if() 

	fstream file ;
	file.open( temp.c_str(), ios:: in ) ;     // open the file

	START = clock() ;

	if ( ! file.is_open() ) {         // check the file can be opened 
		cout << "### " << temp << " does not exist ! ###" << endl ;
		return false ;
	} // if()

	else {

		Data t ;
		getline( file, temp ) ;				// read the title 

		if ( file.eof() ) {
			cout << "### Get nothing from the file" << temp << " ! ###" << endl ;
			return false ;
		} // if()

		while ( file >> t.OID ) {			// Read the data and push into vector 
			file >> t.Arri >> t.Dura >> t.TimeOut ;
			list.push_back( t ) ;
		} // while()

		DataSize = list.size() ;	// set size

	} // else 
	
	file.close() ;
	END = clock() ; 
	return true ;
} // Read()

void WriteSim( int command ) {
	
	fstream newfile ;
	string temp ;
	float delay = 0.0 ;

	if ( command == 2 ) {
		temp = "output" + text + ".txt" ;
	} // if()

	else if ( command = 3 ) {
		temp = "double" + text + ".txt" ;
	} // else if ()

	newfile.open( temp.c_str(), ios :: out ) ;

	newfile << "\t[Abort Jobs]" << endl << "\tOID" ;

	if ( command == 3 ) {
		newfile << "\tCID" ;
	} // if()

	newfile << "\tAbort" << "\tDelay" << endl ;
 
	for ( int i = 0 ; i < cancel.size() ; i ++ ) {
		newfile << "[" << i + 1 << "]\t" << cancel[i].OID << '\t' ;

		if ( command == 3 ) {
			newfile << cancel[i].no << '\t' ;
		} // if()

		newfile << cancel[i].Abort << '\t' << cancel[i].Delay << endl ;
		delay += cancel[i].Delay ;
	} // for()

	newfile << "\t[Jobs Done]" << endl << "\tOID" ;

	if ( command == 3 ) {
		newfile << "\tCID" ;
	} // if()

	newfile << "\tDeparture" << "\tDelay" << endl ;

	for ( int i = 0 ; i < done.size() ; i ++ ) {
		newfile << "[" << i + 1 << "]\t" << done[i].OID << '\t' ;

		if ( command == 3 ) {
			newfile << done[i].no << '\t' ;
		} // if()

		newfile << done[i].Depart << '\t' << done[i].Delay << endl ; 
		delay += done[i].Delay ;
	} // for()

	delay = delay / DataSize ; 
	double success = ( (double)done.size() / (double)DataSize ) * 100 ;
	
	newfile << "[Average Delay]\t" << fixed << setprecision(2) << delay << " ms" << endl ;
	newfile << "[Success Rate]\t" << fixed << setprecision(2) << success << " %" << endl ;

	newfile.close() ;
	
} // WriteSim() 

void initial() {
	cancel.clear() ;
	done.clear() ;
	list.clear() ;
} // initial()

void doCommand( int command ) {

	if ( ! Read( command ) ) return ; 

	if ( command == 1 ) {

		Print() ;
		cout << endl << "Reading data: " << END - START / CLOCKS_PER_SEC * 1000 << " ms" << endl ;

		START = clock() ;
		ShellSort() ;
		END = clock() ;
		cout << "Sorting data: " << END - START / CLOCKS_PER_SEC * 1000 << " ms" << endl ;  

		START = clock() ;
		WriteSort() ;
		END = clock() ;
		cout << "Writing data: " << END - START / CLOCKS_PER_SEC * 1000 << " ms" << endl ; 

		cout << endl << "See sorted" << text << ".txt" << endl ;

	} // if ()

	else if ( command == 2 ) {
		cout << endl << "The Simulation is running..." << endl ;
		cpunum = 1 ;
		Simulation() ;
		WriteSim( 2 ) ;
		cout << "See output" << text << ".txt" << endl ;
	} // else if()

	else if ( command == 3 ) {
		cout << endl << "The Simulation is running..." << endl ;
		cpunum = 2 ;
		Simulation() ;
		WriteSim( 3 ) ;
		cout << "See double" << text << ".txt" << endl ;
	} // else if ()

} // doCommand()

void Preface() {
	
	cout << endl << "**** Simulate FIFO Queues by SQF *****" ;
	cout << endl << "* 0. Quit                            *" ;
	cout << endl << "* 1. Sort a file                     *" ;
	cout << endl << "* 2. Simulate one FIFO queue         *" ;
	cout << endl << "* 3. Simulate two queues by SQF      *" ;
	cout << endl << "**************************************" ;
	cout << endl << "Input a choice(0, 1, 2, 3): " ;

} // Preface()

bool Check( string temp, int & command ) {
	command = 0 ;
	for ( int i = 0 ; i < temp.size() ; i ++ ) {
		if ( temp[i] < '0' || temp[i] > '9' ) {
			return false ;
		} //if()

		command = command + temp[i] - '0' ;

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
		initial() ;
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


