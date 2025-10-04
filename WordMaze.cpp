#include<iostream>
#include<cstdlib>
#include<ctime>
#include<cstring>
#include<windows.h>
#include<iomanip>

using namespace std;

void setColor(int textColor, int bgColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,(bgColor << 4) | textColor);
}

char toLowerChar(char c){
    if(c >= 'A' && c <= 'Z') return c + ('a' - 'A');
    return c;
}
char toUpperChar(char c){
	setColor(0,1);
    if(c >= 'a' && c <= 'z') return c - ('a' - 'A');
    return c;
}


struct GRID {
    int row, col;
    char **grid;

    GRID(int r=7, int c=7) {
        row = r; col = c;
        grid = new char*[row];
        for(int i=0;i<row;i++){
            grid[i] = new char[col];
        }
    }

    void fillRandom() {
        for(int i=0;i<row;i++){
            for(int j=0;j<col;j++){
                grid[i][j] = 'a' + rand() % 26;
            }
        }
    }

    void print() {
    	setColor(14,0);
        for(int i=0;i<row;i++){
            cout<<"\t";
            for(int j=0;j<col;j++){
                cout<<grid[i][j]<<"\t";
            }
            cout<<endl;
        }
        setColor(7,0);
    }

    ~GRID() {
        for(int i=0;i<row;i++) delete [] grid[i];
        delete [] grid;
    }
};

struct Dictionary {
    int wordCount;
    char **words;

    Dictionary(int n=10) {
        wordCount = n;
        words = new char*[wordCount];
        for(int i=0;i<wordCount;i++) words[i] = new char[20];

        strcpy(words[0], "stack");
        strcpy(words[1], "link");
        strcpy(words[2], "tree");
        strcpy(words[3], "book");
        strcpy(words[4], "data");
        strcpy(words[5], "science");
        strcpy(words[6], "input");
        strcpy(words[7], "output");
        strcpy(words[8], "program");
        strcpy(words[9], "error");
    }

    ~Dictionary() {
        for(int i=0;i<wordCount;i++) delete [] words[i];
        delete [] words;
    }
};

int selectWordCount(int size) {
    if(size <= 5) return 3;
    if(size <= 7) return 5;
    if(size <= 10) return 8;
    return 10;
}

bool **createOccupied(int r, int c){
    bool **occ = new bool*[r];
    for(int i=0;i<r;i++){
        occ[i] = new bool[c];
        for(int j=0;j<c;j++) occ[i][j] = false;
    }
    return occ;
}

void deleteOccupied(bool **occ, int r){
    if(!occ) return;
    for(int i=0;i<r;i++) delete [] occ[i];
    delete [] occ;
}


bool placeWordInMaze(GRID *maze, char *word, bool **occupied) {
    int len = strlen(word);
    int tries = 100; 
    int dirX[8] = {0, 0, 1, -1, 1, 1, -1, -1};
    int dirY[8] = {1, -1, 0, 0, 1, -1, 1, -1};

    while(tries--) {
        int d = rand() % 8;
        int r = rand() % maze->row;
        int c = rand() % maze->col;

        int endR = r + (len - 1) * dirX[d];
        int endC = c + (len - 1) * dirY[d];
		if(endR < 0 || endR >= maze->row || endC < 0 || endC >= maze->col) {
            continue;
        }
        
		int nr = r, nc = c;
        bool canPlace = true;

        for(int i=0;i<len;i++){
            if(nr<0 || nr>=maze->row || nc<0 || nc>=maze->col){
                canPlace = false;
                break;
            }
            if(occupied[nr][nc]) {
                if(toLowerChar(maze->grid[nr][nc]) != toLowerChar(word[i])){
                    canPlace = false;
                    break;
                }
            }
            nr += dirX[d];
            nc += dirY[d];
        }

        if(canPlace){
            nr = r; nc = c;
            for(int i=0;i<len;i++){
                maze->grid[nr][nc] = word[i]; 
                occupied[nr][nc] = true;
                nr += dirX[d];
                nc += dirY[d];
            }
            return true;
        }
    }
    return false; 
}

void showProgress(char **selectedWords, bool *found, int wordCountToPlace){
	
    cout<<"\nWords to Find: ";
    
    for(int i=0;i<wordCountToPlace;i++){
        
		if(!found[i]) 
		cout<<selectedWords[i]<<", ";
		
    }
    
    cout<<"\nWords Found: ";
    for(int i=0;i<wordCountToPlace;i++){
        
		if(found[i]) 
		cout<<selectedWords[i]<<", ";
    }
    
    cout<<"\nTotal Words: "<<wordCountToPlace<<endl;
}

void strToLower(char *s){
    for(int i=0;s[i];i++)
        if(s[i]>='A' && s[i]<='Z') s[i] += 'a'-'A';
}

bool checkWordAt(GRID *maze, char *word, int r, int c){
    
	int len = strlen(word);
    int dirX[8] = {0,0,1,-1,1,1,-1,-1};
    int dirY[8] = {1,-1,0,0,1,-1,1,-1};

    for(int d=0;d<8;d++){
        
		int nr=r, nc=c;
        int i;
        
        for(i=0;i<len;i++){
        	
            if(nr<0 || nr>=maze->row || nc<0 || nc>=maze->col) 
			break;
            if(toLowerChar(maze->grid[nr][nc]) != toLowerChar(word[i])) 
			break;
			
            nr += dirX[d];
            nc += dirY[d];
        }
        
        if(i==len){
		 
            nr=r; nc=c;
            for(i=0;i<len;i++){
                maze->grid[nr][nc] = toUpperChar(maze->grid[nr][nc]);
                nr += dirX[d];
                nc += dirY[d];
                setColor(7,0);
            }
            return true;
        }
    }
    return false;
}

void giveHint(GRID *maze, char **words, bool *found, int wordCount){
    
	int unfound[50], count=0;
    for(int i=0;i<wordCount;i++){
    	
        if(!found[i]) {
        	
        	unfound[count++]=i;
		}
    }
    
    if(count==0){	
        cout<<"All words already found!\n"; 
		return;
    }
    
    int pick = unfound[rand()%count];
    char *w = words[pick];
    char first = toLowerChar(w[0]);

    for(int r=0;r<maze->row;r++){
    	
        for(int c=0;c<maze->col;c++){
        	
            if(toLowerChar(maze->grid[r][c])==first){
            	
                cout<<"Hint: Word \""<<w<<"\" starts near ("<<r<<","<<c<<")"<<endl;
                return;
            }
        }
    }
    cout<<"No hint available"<<endl;
}

int main(){
	
	bool hintUsed = false;
	int attempts = 0;
	time_t startTime, endTime;
	srand(time(0));
	Dictionary dict(10);
	
	int choose, row = 7, col =7;
	GRID *maze = new GRID(row,col);
    maze->fillRandom();
    
    bool **occupied = createOccupied(row, col);
	int wordCountToPlace = selectWordCount(row);
    char **selectedWords = new char*[wordCountToPlace];
    bool *found = new bool[wordCountToPlace];
    
        
    for(int i=0;i<wordCountToPlace;i++) 
	found[i]=false;
    
    for(int i=0;i<wordCountToPlace;i++){
        selectedWords[i] = new char[20];
        int idx; bool unique;
        do{
            unique = true;
            idx = rand() % dict.wordCount;
            for(int j=0;j<i;j++){
                if(strcmp(dict.words[idx], selectedWords[j])==0){
                    unique=false; 
					break;
                }
            }
        }while(!unique);

        strcpy(selectedWords[i], dict.words[idx]);

        bool placed = placeWordInMaze(maze, selectedWords[i], occupied);
        if(!placed){
            int more = 0;
            while(!placed && more++ < 5) placed = placeWordInMaze(maze, selectedWords[i], occupied);
            if(!placed){
                cout<<"Warning: couldn't place word \\"<<selectedWords[i]<<"\\ after many attempts"<<endl;
            }
        }
    }

	while(true){
		
		setColor(11, 0);
   		cout<<"\t\t\t\tMAZE GAME"<<endl<<endl;
   		setColor(7, 0);
		
       	cout<<"1. Play Game"<<endl;
    	cout<<"2. Exit"<<endl;
    	cin>>choose;
    	
    	switch(choose){
    		case 1:{
    			int select;
    			cout<<"Enter MAZE SIZE"<<endl;
    			cout<<"1. 5x5 GRID"<<endl;
    			cout<<"2. 7x7 GRID (default)"<<endl;
    			cout<<"3. 10x10 GRID "<<endl;
    			cout<<"4. Greater then 10"<<endl;
    			cout<<"Select: ";
    			cin>>select;
    			while(select > 4 || select < 1){
                    setColor(4, 0);
                    cout<<"ERROR. Select within the range"<<endl;
                    setColor(7, 0);
                    cout<<"Select : ";
                    cin>>select;
                }
                delete maze;
                deleteOccupied(occupied, row);
                
                for(int i=0;i<wordCountToPlace;i++) 
				delete [] selectedWords[i];
				
                delete [] selectedWords;
                delete [] found;

                if(select == 1){
					row = 5; 
					col = 5; 
				}
                else if(select == 2){
					row = 7; 
					col = 7; 
				}
                else if(select == 3){ 
					row = 10; 
					col = 10; 
				}
                else{ 
					row = 11 + rand() % 5; 
					col = row; 
				}
				
				maze = new GRID(row,col);
              	maze->fillRandom();
               	occupied = createOccupied(row,col);
               	
               	wordCountToPlace = selectWordCount(row);
                selectedWords = new char*[wordCountToPlace];
                found = new bool[wordCountToPlace];
                
                for(int i=0;i<wordCountToPlace;i++) 
				found[i]=false;
               	
               	for(int i=0;i<wordCountToPlace;i++){
			        selectedWords[i] = new char[20];
			        int idx; bool unique;
  				    do{
  			          	unique = true;
     			    	idx = rand() % dict.wordCount;
   			         	for(int j=0;j<i;j++){
   			         		
                			if(strcmp(dict.words[idx], selectedWords[j])==0){
                    		unique=false; 
							break;
                			}
           				}
        			}while(!unique);

       			strcpy(selectedWords[i], dict.words[idx]);

    		    bool placed = placeWordInMaze(maze, selectedWords[i], occupied);
        		if(!placed){
            		int more = 0;
            		while(!placed && more++ < 5) 
					placed = placeWordInMaze(maze, selectedWords[i], occupied);
            		if(!placed){
                		cout<<"Warning: couldn't place word \\"<<selectedWords[i]<<"\\ after many attempts"<<endl;
            			}
        			}
   				}
    
                while(true){
                	system("cls");
                	maze->print();
                	bool allDone=true;
        			for(int i=0;i<wordCountToPlace;i++){
            			if(!found[i]){ 
							allDone=false; 
							break; 
						}
       				}
        			if(allDone){
        				time(&endTime);
						setColor(6,0);
 					    cout<<"\nFinal Puzzle with Found Words Highlighted"<<endl;
 					    time(&endTime);
					    cout<<"\nGame Over! Stats:"<<endl;
						cout<<"Attempts: "<<attempts<<endl;
						cout<<"Time taken: "<<difftime(endTime, startTime)<<" seconds"<<endl;
						setColor(7,0);
						return 0;
					}
        			setColor(10,0);
        			cout<<"\nAttempts: "<<attempts<<endl;
        			setColor(7,0);
        			
        			cout<<"Options:"<<endl;
					cout<<"1. Guess a word"<<endl;
					cout<<"2. Use Hint"<<endl;
					cout<<"3. Print Board"<<endl;
					cout<<"4. Progress"<<endl;
					cout<<"5. Exit"<<endl;
					cout<<"Choice: ";
        			int choice; 
					cin>>choice;
					while (choice > 5 || choice <1){
						setColor(4, 0);
                    	cout<<"ERROR. Select within the range"<<endl;
                    	setColor(7, 0);
                    	cout<<"Select : ";
                    	cin>>choice;
					}
					if(choice == 1){
						attempts ++;
						char guess[20];
                		int gr,gc;
                		cout<<"\nEnter your guess (word) and starting row and col (0-indexed): ";
                		cin>>guess>>gr>>gc;

                		strToLower(guess);
               			bool validWord=false;
                		int idx=-1;
                		for(int i=0;i<wordCountToPlace;i++){
                    		char temp[20]; strcpy(temp,selectedWords[i]);
                    		strToLower(temp);
                    		if(strcmp(temp,guess)==0){ 
							validWord=true; idx=i; 
							break;
							}
                		}

               			if(!validWord) 
						{ 
							cout<<"Word not in selected words!\n"; 
							continue;
						}
                		if(found[idx]) 
						{ 
							cout<<"Word already found!\n"; 
							continue;
						}

                		if(checkWordAt(maze, guess, gr, gc)){
                    	cout<<"Correct! Word found.\n";
                    	found[idx]=true;
                		} else {
                    		cout<<"Incorrect position or word not starting there.\n";
                		}
					}
					else if(choice == 2){
						if(!hintUsed){
        					giveHint(maze, selectedWords, found, wordCountToPlace);
        					hintUsed = true;
    					} else {
        					setColor(4,0);
        					cout<<"Hint already used!"<<endl;
        					setColor(7,0);
  						 }
					}
					else if(choice == 3){
						maze->print();
					}
					else if(choice == 4){
						showProgress(selectedWords,found,wordCountToPlace);
					}
					else{
						return 0;
					}
					Sleep(2000);
				}
				
				break;
			}
			case 2:{
				cout<<"Exiting...."<<endl;
				return 0;
				break;
			}
			default:{
				setColor(4,0);
				cout<<"Invalid Option"<<endl;
				setColor(7,0);
				break;
			}
		}
		system("cls");
	}
    
	return 0;
}
