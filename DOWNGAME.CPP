#include<iostream.h>
#include<conio.h>
#include<process.h>
#include<dos.h>
#include<stdlib.h>
#include<string.h>

class humanoidGameObject{
  public:
    char textLines[4][3];
    int leftPos;
    int startingLine;
    void setLine(int line,char first,char second,char third);
};

class blockObstacle{
  public:
    int leftPos;
    int startingLine;
    int length;
};

void humanoidGameObject::setLine(int line,char first,char second,char third){
  textLines[line][0] = first;
  textLines[line][1] = second;
  textLines[line][2] = third;
}

char currentLineCharacters[81];
humanoidGameObject objects[1];
blockObstacle block1;
float timeTracker=0;
float previousTime=22;
int gameOverInt = 0;
char gameOverAsciiText[] = " _____   ___  ___  ___ _____   _____  _   _ ___________ \n|  __ \\ / _ \\ |  \\/  ||  ___| |  _  || | | |  ___| ___ \\\n| |  \\// /_\\ \\| .  . || |__   | | | || | | | |__ | |_/ /\n| | __ |  _  || |\\/| ||  __|  | | | || | | |  __||    / \n| |_\\ \\| | | || |  | || |___  \\ \\_/ /\\ \\_/ / |___| |\\ \\ \n \\____/\\_| |_/\\_|  |_/\\____/   \\___/  \\___/\\____/\\_| \\_|\n                                                        \n                                                        ";
char mainMenuAsciiText[] = "  ______      _      _      _____ _   _  _____ \n |  ____/\\   | |    | |    |_   _| \\ | |/ ____|\n | |__ /  \\  | |    | |      | | |  \\| | |  __ \n |  __/ /\\ \\ | |    | |      | | | . ` | | |_ |\n | | / ____ \\| |____| |____ _| |_| |\\  | |__| |\n |_|/_/    \\_\\______|______|_____|_| \\_|\\_____|\n          |  \\/  |   /\\    \\ \\ / /             \n          | \\  / |  /  \\    \\ V /              \n          | |\\/| | / /\\ \\    > <               \n          | |  | |/ ____ \\  / . \\              \n          |_|  |_/_/    \\_\\/_/ \\_\\             ";
char inp1;
int selectedOptionNo = 0;
char mainMenuOptions[4][40] = {"P l a y","I n s t r u c t i o n s","C r e d i t s","Q u i t"};
int mainMenuLength = 4;
char instructionsText[] = "\n\n\n       Max had gone on an adventure trip\n\n      He found a tunnel and went into it\n\n   Little did he know, it was the gateway to hell\n\n      Help him survive as he falls endlessly\n\n\n               C O N T R O L S\n\n                A - Move Left\n               S - Move Right";
int obstacleType=0;
int direction = 1;

//Funciton to display game over text and show option to go back to main menu
void gameOver(){
  delay(1000);
  clrscr();
  cout<<"     ";
  for(int z=0,currentLineNo=0;z<strlen(gameOverAsciiText);z++){
      cout<<gameOverAsciiText[z];
      if(gameOverAsciiText[z]=='\n'){
        for(int q=0;q<5;q++){
          cout<<" ";
        }
      }
  }
  cout<<"\n\n                        Your score is "<<timeTracker*10<<endl;
  timeTracker = 0;
  cout<<"\n                  Press enter to go back to main menu";
  while(1){
    inp1 = getch();
    if(inp1=='\r'){
      break;
    }
  }
}

void addArray(char word[3],int startingPos){
  for(int r=0;r<3;r++)
    currentLineCharacters[startingPos+r] = word[r];
}

void randomizeObstacle(){
  block1.startingLine=19;
  
  int temp = random(10);

  // Generating different obstacles
  if(temp<=5){
    obstacleType = 0;
    block1.leftPos = random(40);
    block1.length = random(20)+20;
  }
  else if(temp==6 || temp==7){
    obstacleType = 1;
    block1.leftPos = random(5);
  }
  else{
    block1.leftPos = random(40);
    block1.length = random(20)+20;
    obstacleType = 2;
    direction = 1;
  }

}

void drawObstacle(){
  if(obstacleType==0){
    for(int a = block1.leftPos,length = block1.length,track1=0;length>track1;track1++){
      if(currentLineCharacters[a+track1]=='O' || currentLineCharacters[a+track1]=='o' || currentLineCharacters[a+track1]=='H' || currentLineCharacters[a+track1]=='E' || currentLineCharacters[a+track1]=='R'){
        gameOverInt = 1;
        break;
      }
      currentLineCharacters[a+track1] = '0';
    }
  }
  else if(obstacleType==1){
    for(int b = block1.leftPos,length = block1.length,track2=0;length>track2;track2++){
      if(currentLineCharacters[b+track2]=='O' || currentLineCharacters[b+track2]=='o' || currentLineCharacters[b+track2]=='H' || currentLineCharacters[b+track2]=='E' || currentLineCharacters[b+track2]=='R'){
        gameOverInt = 1;
        break;
      }
      currentLineCharacters[b+track2] = '0';
    }
    for(int c = block1.leftPos+block1.length+7,track3=0;80>c;c++){
      if(currentLineCharacters[c+track3]=='O' || currentLineCharacters[c+track3]=='o' || currentLineCharacters[c+track3]=='H' || currentLineCharacters[c+track3]=='E' || currentLineCharacters[c+track3]=='R'){
        gameOverInt = 1;
        break;
      }
      currentLineCharacters[c+track3] = '0';
    }
  }
  else{
    if(direction==1){
      for(int d = block1.leftPos,length = block1.length,track4=0;length>track4;track4++){
        if(currentLineCharacters[d+track4]=='O' || currentLineCharacters[d+track4]=='o' || currentLineCharacters[d+track4]=='H' || currentLineCharacters[d+track4]=='E' || currentLineCharacters[d+track4]=='R'){
          gameOverInt = 1;
          break;
        }
        currentLineCharacters[d+track4] = '0';
      }
      block1.leftPos++;
      if(block1.leftPos+block1.length==79){
        direction = -1;
      }
    }
    else if(direction==-1){
      for(int e = block1.leftPos,length = block1.length,track5=0;length>track5;track5++){
        if(currentLineCharacters[e+track5]=='O' || currentLineCharacters[e+track5]=='o' || currentLineCharacters[e+track5]=='H' || currentLineCharacters[e+track5]=='E' || currentLineCharacters[e+track5]=='R'){
          gameOverInt = 1;
          break;
        }
        currentLineCharacters[e+track5] = '0';
      }
      block1.leftPos--;
      if(block1.leftPos==0){
        direction = 1;
      }
    }
  }
}

void addCharacter(char alphabet,int position){
  currentLineCharacters[position] = alphabet;
}


void SetPlayer(){
  //Player
  objects[0].setLine(0,'H',' ','H');
  objects[0].setLine(1,'E',' ','E');
  objects[0].setLine(2,'R',' ','R');
  objects[0].setLine(3,'O',' ','O');
  objects[0].leftPos=25;
  objects[0].startingLine=0;
}

//Player Move Input 
void Input(){
  if(kbhit()){
    char inputChar;
    inputChar = getch();
    switch (inputChar){
      //Quit
      case 'q': exit(0);
                break;
      case 'a': if(objects[0].leftPos!=0){
                  objects[0].leftPos--;
                }
                break;
      case 'd': if(objects[0].leftPos+3<79){
                objects[0].leftPos++;
                }
                break;
    }
  }
}

void HealthLabelAndLinePrinting(int i){
    for(int z=0,check=1;z<80;z++){
       if(check==1 && i==23){
       cout<<"S C O R E: "<<timeTracker*10<<endl;
       check=0;
       break;
      }
      cout<<currentLineCharacters[z];
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

void gameLoop(){

  randomizeObstacle();
  timeTracker = 0;
  previousTime = 22;
  //Infinite Game Loop
  for(;;){
     //Checking for input
     Input();

    if(gameOverInt){
      gameOverInt=0;
      gameOver();
      break;
    }

     //Adding delay for delaying for redrawing of console
    delay(125);
    timeTracker+=1;

    clrscr();

    //Drawing on the console
    for(int i=0;i<24;i++){

      //Intialising line with blank characters
      for(int p=0;p<80;p++){
        currentLineCharacters[p]=' ';
      }

      if(i==20){
       for(int j=0;j<80;j++)
          addCharacter('-',j);
      }

      if(i>=objects[0].startingLine && i<objects[0].startingLine+4){
        addArray(objects[0].textLines[i-objects[0].startingLine],objects[0].leftPos);
      }

     //Add Obstacle
     if(timeTracker>=20 && i==block1.startingLine){
       drawObstacle();
       if(timeTracker>previousTime){
         previousTime = timeTracker+2;
         block1.startingLine--;
       }
     }

     if(block1.startingLine==-1){
       randomizeObstacle();
     }

     HealthLabelAndLinePrinting(i);

   }

  }
}

void printMainMenu(){
    clrscr();

    cout<<"     ";
    for(int z=0,currentLineNo=0;z<strlen(mainMenuAsciiText);z++){
        cout<<mainMenuAsciiText[z];
        if(mainMenuAsciiText[z]=='\n'){
          for(int q=0;q<5;q++){
            cout<<" ";
          }
        }
    }

    cout<<endl<<endl<<endl;
    for(int i=0;i<mainMenuLength;i++){
    if(i==selectedOptionNo){
    cout<<"\t\t   "<<(char)14<<"     ";
    }
    else{
      cout<<"\t\t        ";
    }
    cout<<mainMenuOptions[i]<<endl<<endl;
  }
}

void showInstructions(){
  clrscr();
  int storyLen = strlen(instructionsText);
  for(int i=0;i<storyLen;i++){
    cout<<instructionsText[i];
    if(i<100){
      if(i%3==0){
        sound(300);
      }
      else if(i%3==1){
        sound(325);
      }
      else{
        sound(350);
      }
    }
    else if(i<200){
      if(i%3==0){
        sound(350);
      }
      else if(i%3==1){
        sound(375);
      }
      else{
        sound(400);
      }
    }
    else{
      if(i%3==0){
        sound(400);
      }
      else if(i%3==1){
        sound(425);
      }
      else{
        sound(450);
      }
    }
    delay(100);
  }
  nosound();
  delay(2000);
  cout<<endl<<endl<<endl;
  cout<<"                "<<(char)14<<" G O  B A C K";
  while(1){
    inp1 = getch();
    if(inp1=='\r'){
      break;
    }
  }
}

void produceSound(int soundNo){
  sound(soundNo);
  delay(50);
  nosound();
}

void main(){
  randomizeObstacle();
  clrscr();
  SetPlayer();

  while(1){

    printMainMenu();

    inp1 = getch();

    if(inp1=='\r'){

    if(selectedOptionNo==0){
      gameLoop();
    }
    else if(selectedOptionNo==1){
      showInstructions();
    }
    else if(selectedOptionNo==2){
      credits();
    }
    else if(selectedOptionNo==3){
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
