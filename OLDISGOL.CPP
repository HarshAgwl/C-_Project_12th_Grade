#include<iostream.h>
#include<conio.h>
#include<string.h>
#include<dos.h>
#include<fstream.h>
#include<process.h>
#include<ctype.h>

struct song{
 char songName[100];
 char artistName[100];
 char releaseYear[10];
 char biography[3000];
 char lyrics[3000];
};

int selectedOptionNo = 0;
char mainMenuOptions[3][20] = {"O p e n","C r e d i t s","Q u i t"};
int mainMenuLength = 3;
char songMenuOptions[3][40] = {"View Artist\'s Biography","View Lyrics","Go Back"};
char songNames[7][100];
char inp1;
int currentSongNo;

song s1;
fstream sf;

void produceSound(int soundNo){
  sound(soundNo);
  delay(50);
  nosound();
}

void intro(){
  for(int i=0;i<1;i++){
   sound(200);
   delay(700);
   sound(210);
   delay(100);
   sound(200);
   delay(300);
   sound(210);
   delay(100);
   sound(200);
   delay(300);
   nosound();
  }  
  cout<<"         ___  _     ____    ___ ____     ____  ___  _     ____  \n        / _ \\| |   |  _ \\  |_ _/ ___|   / ___|/ _ \\| |   |  _ \\ \n       | | | | |   | | | |  | |\\___ \\  | |  _| | | | |   | | | |\n       | |_| | |___| |_| |  | | ___) | | |_| | |_| | |___| |_| |\n        \\___/|_____|____/  |___|____/   \\____|\\___/|_____|____/ \n                                                               "<<endl;  
  for(int l=0;l<1;l++){
   sound(225);
   delay(700);
   sound(240);
   delay(100);
   sound(225);
   delay(300);
   sound(240);
   delay(100);
   sound(225);
   delay(300);
   nosound();
  } 
   cout<<"                        M U S I C   L I B R A R Y"<<endl<<endl<<endl;
}

void biographyMenu(){
  clrscr();
  cout<<endl;
  cout<<" ";
    for(int s=0;s<strlen(s1.artistName);s++){
      cout<<s1.artistName[s]<<" ";
    }
    cout<<endl<<"----------------------------------------------------------------------------"<<endl;
  cout<<" ";
  for(int z=0;z<strlen(s1.biography);z++){
    cout<<s1.biography[z];
    if(s1.biography[z]=='\n'){
      cout<<" ";
    }
  }

  cout<<endl;
  cout<<" "<<(char)14<<" Go Back";

  inp1 = getch();
}

void lyricsMenu(){
  int noOfLines = 0;
  for(int z=0;z<strlen(s1.lyrics);z++){
      if(s1.lyrics[z]=='\n'){
        noOfLines++;
      }
  }
  int lineOffset = 0;
  int currentLineNo = 0;
  int addSpace = 0;
  while(1){
    clrscr();
    cout<<endl;
    cout<<" ";
    for(int s=0;s<strlen(s1.songName);s++){
      cout<<s1.songName[s]<<" ";
    }
    cout<<endl<<"----------------------------------------------------------------------------"<<endl;
    cout<<" ";
    for(int z=0,currentLineNo=0;z<strlen(s1.lyrics);z++){
      if(currentLineNo>=lineOffset && currentLineNo<lineOffset+20){
        if(addSpace==1 && currentLineNo!=lineOffset){
          addSpace = 0;
          cout<<" ";
        }
        cout<<s1.lyrics[z];
      }
      if(s1.lyrics[z]=='\n'){
        currentLineNo++;
        addSpace = 1;
      }
    }

    cout<<endl;
    cout<<" "<<(char)14<<" Go Back";

    inp1 = getch();
    if(inp1=='\r'){
      break;
    }
    else if(inp1=='w' && lineOffset>0){
      lineOffset--;
    }
    else if(inp1=='s' && lineOffset<noOfLines-1){
      lineOffset++;
    }
  }
}

void generateSongList(){
  for(int i=0;i<7;i++){
    sf.read((char*)&s1,sizeof(song));
    strcpy(songNames[i],s1.songName);
  } 
}

void getAndDisplaySongBasicDetails(){
  sf.seekg(currentSongNo*sizeof(song));
  sf.read((char*)&s1,sizeof(song));
  cout<<endl;
  cout<<" --- S O N G  N A M E ---"<<endl;
  cout<<" "<<s1.songName<<endl<<endl;
  cout<<" --- A R T I S T  N A M E---"<<endl;
  cout<<" "<<s1.artistName<<endl<<endl;
  cout<<" --- R E L E A S E  Y E A R ---"<<endl;
  cout<<" "<<s1.releaseYear<<endl<<endl;
}

void printMainMenu(){

  clrscr();
  cout<<"         ___  _     ____    ___ ____     ____  ___  _     ____  \n        / _ \\| |   |  _ \\  |_ _/ ___|   / ___|/ _ \\| |   |  _ \\ \n       | | | | |   | | | |  | |\\___ \\  | |  _| | | | |   | | | |\n       | |_| | |___| |_| |  | | ___) | | |_| | |_| | |___| |_| |\n        \\___/|_____|____/  |___|____/   \\____|\\___/|_____|____/ \n                                                               "<<endl;
  cout<<"                        M U S I C   L I B R A R Y"<<endl<<endl<<endl;

  for(int i=0;i<mainMenuLength;i++){
    if(i==selectedOptionNo){
    cout<<"\t\t\t   "<<(char)14<<"     ";
    }
    else{
      cout<<"\t\t\t        ";
    }
    cout<<mainMenuOptions[i]<<endl<<endl;
  }

}

void printDirectoryMenu(){
  clrscr();
  cout<<endl<<"            ----- D I R E C T O R Y -----"<<endl<<endl<<endl;
  for(int p=0;p<8;p++){

      if(p==selectedOptionNo){
       cout<<" "<<(char)14<<"  ";
      }
      else{
       cout<<"   ";
      }

      if(p<7){
        for(int a=0;a<strlen(songNames[p]);a++){
              cout<<songNames[p][a];
        }
        cout<<endl<<endl;
      }
      else{
       cout<<"G o  B a c k"<<endl;
      }
   }
}

void printSongMenu(){
  for(int q=0;q<3;q++){
    //Selection Cursor
    if(q==selectedOptionNo){
     cout<<" "<<(char)14<<"  ";
    }
    else{
     cout<<"   ";
    }
    //Print
    cout<<songMenuOptions[q]<<endl<<endl;
  }
}

void initialize(){
  clrscr();
  sf.open("final.dat",ios::binary|ios::in);
  generateSongList();
  intro();
}

void songMenu(){
  currentSongNo = selectedOptionNo;
  selectedOptionNo = 0;

  while(1){

    clrscr();
    getAndDisplaySongBasicDetails();
    printSongMenu();


    //User Menu Input
    inp1 = getch();

    //User Input Response
    if(inp1=='\r'){

      //Biography Option
      if (selectedOptionNo==0){
        biographyMenu();
      }
      //Lyrics Option
      else if(selectedOptionNo==1){
       lyricsMenu();
      }
      //Go Back Option
      else if(selectedOptionNo==2){
        selectedOptionNo = 0;
        break;
      }

    }
    else if(inp1=='w' && selectedOptionNo>0){
      produceSound(1200);
       selectedOptionNo-=1;
    }
    else if(inp1=='s' && selectedOptionNo<2){
      produceSound(1200);
      selectedOptionNo+=1;
    }

  }
}

void directoryMenu(){
  clrscr();
 selectedOptionNo = 0;
 while(1){
  
  printDirectoryMenu();

  inp1 = getch();
  if(inp1=='\r'){

    if(selectedOptionNo==7){
      selectedOptionNo = 0;
      break;
    }
    else{
      songMenu();
   }
  }
  else if(inp1=='w' && selectedOptionNo>0){
    produceSound(1200);
    selectedOptionNo-=1;
  }
  else if(inp1=='s' && selectedOptionNo<7){
    produceSound(1200);
    selectedOptionNo+=1;
  }

 }
}

void credits(){
  while(1){
    clrscr();
    cout<<endl<<endl;
    cout<<"                     H A R S H  A G R A W A L"<<endl<<endl;
    cout<<"                 S O U R A B H  S I N G H"<<endl<<endl;
    cout<<"                       A M A N  F A R I D I"<<endl<<endl;
    cout<<"                     N I T Y A  B O R K A R"<<endl<<endl<<endl;
    cout<<"                           "<<(char)14<<" GO BACK";
    inp1 = getch();
    if(inp1=='\r'){
      break;
    }
  }  
}

void mainMenu(){
  while(1){

   printMainMenu();

   inp1 = getch();

   if(inp1=='\r'){

    if(selectedOptionNo==0){
      directoryMenu();
    }
    else if(selectedOptionNo==1){
      credits();
    }
    else if(selectedOptionNo==2){
    sf.close();
     exit(0);
    }

   }
   else if(inp1=='w' && selectedOptionNo>0){
    produceSound(1200);
    selectedOptionNo-=1;
   }
   else if(inp1=='s' && selectedOptionNo<mainMenuLength-1){
    produceSound(1200);
    selectedOptionNo+=1;
   }
   
  }
}

void main(){
  initialize();
  mainMenu();
}