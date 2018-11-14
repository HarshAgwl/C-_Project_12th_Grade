#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>

struct song{
 char songName[100];
 char artistName[100];
 char releaseYear[10];
 char biography[3000];
 char lyrics[3000];
};

char line[100];
char ch;


void main(){
clrscr();
ifstream sf;
fstream sf2;
sf.open("songs.txt",ios::in);
sf2.open("final.dat",ios::binary|ios::out|ios::trunc|ios::app);
//while(!sourceFile.eof()){
song s1;
for(int i=0;i<7;i++){
  strcpy(s1.biography,"");
  strcpy(s1.lyrics,"");
  //Get Song Name
  sf.getline(s1.songName,100);
  //Get Artist's Name
  sf.getline(s1.artistName,100);
  //Get Release year
  sf.getline(s1.releaseYear,10);

  //Get Biography
  while(1){
   sf.getline(line,100);
   if(line[0]=='^' || line[0]=='~'){
    break;
   }
   strcat(s1.biography,line);
   if(strlen(line)<99){
    strcat(s1.biography,"\n");
   }
  }

  //Get lyrics
  while(1){
   sf.getline(line,100);
   if(line[0]=='^' || line[0]=='~'){
    break;
   }
   strcat(s1.lyrics,line);
   if(strlen(line)<99){
    strcat(s1.lyrics,"\n");
   }
  }
  cout<<s1.biography<<endl;
  sf2.write((char*)&s1,sizeof(s1));
}

sf2.close();
sf.close();
getch();
}