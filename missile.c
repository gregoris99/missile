#include <stdio.h>
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//BUILDS CITY OR BASE.
void buildCityOrBase(int x1, int x2, char* what)
{   
   if(what=="city")
    for(int x=x1; x<=x2; x++)
      for(int J=26; J<=28; J++)     
        mvprintw(J,x,"o");   

   if(what=="base")
    for(int x=x1; x<=x2; x++)
     for(int J=26; J<=28; J++)    
      mvprintw(J,x,"@");    

}

//BUILDS THE WHOLE CITY
void BuildWholeCity( int loc[])
{
    buildCityOrBase(2,7,"city");
    loc[0]=2;
    buildCityOrBase(10,15,"city");
    loc[1]=10;
    buildCityOrBase(18,23,"city");
    loc[2]=18;

    buildCityOrBase(28,35,"base");
     
    buildCityOrBase(40,45,"city");
    loc[3]=40;
    buildCityOrBase(48,53,"city");
    loc[4]=48;
    buildCityOrBase(56,61,"city");
    loc[5]=56;      
}

//initialising an array with the location of the incoming missiles.
int incomingMissile(int loc3[])
{
   int n = rand() % 63 + 2;
   
   for(int i=0; i<23; i++)
    loc3[i]=i+3;

   return n;
}
//function to destroy a city if hit by missile.
bool destroyOrNot(int x)
{
  if((x>1) && (x<8) )
  {
    for(int i=2; i<8; i++)
     for(int j=26; j<28; j++)
        mvprintw(j,i," ");  

        return true; 
  }

  if((x>9) && (x<16) )
  {
    for(int i=10; i<16; i++)
     for(int j=26; j<28; j++)
        mvprintw(j,i," ");

        return true;    
  }

  else if((x>17) && (x<24))
  {
    for(int i=18; i<24; i++)
     for(int j=26; j<28; j++)
        mvprintw(j,i," ");   

        return true; 
  }

  else if((x>39) && (x<46))
  {
    for(int i=40; i<46; i++)
     for(int j=26; j<28; j++)
        mvprintw(j,i," ");  

        return true;  
  }

  else if((x>47) && (x<54))
  {
    for(int i=48; i<54; i++)
     for(int j=26; j<28; j++)
        mvprintw(j,x," ");  

        return true;  
  }

  else if((x>55) && (x<62))
  {
    for(int i=56; i<62; i++)
     for(int j=26; j<28; j++)
        mvprintw(j,x," ");

        return true;    
  }
  
  else return false;
}


//RULES:
//NAVIGATE USING ARROW KEYS.
//LAUNCH MISSILE USING DELETE KEY.
//YOU GET 10 POINTS IF YOU DESTROY A MISSILE.
//YOU LOSE 2 POINTS IF A CITY IS DESTROYED.
//GAME WILL RESET IF YOU RUN OUT OF CITIES OR IF YOU HAVE NO MISSILES LEFT.
//GAME WILL FROZE FOR 2 SECOND BEFORE RESET.
//COUNTER MISSILES ARE LAUNCHED BUT ARE NOT VISIBLE AS THEY ARE DELETED VERY QUICKLY (DONT KNOW HOW TO FIX IT).
//INCOMING MISSILES CAN NOT DESTROY THE BASE

int main()
{    
    initscr();    
    keypad(stdscr, TRUE);
    WINDOW *win1=newwin(30,65,0,0);      
    refresh();  

    int start=0;

    while(start==0)
    {
    

    mvprintw(1,10,"MISSILES LEFT: ");
    mvprintw(2,10,"REMAINING CITIES: "); 
    mvprintw(0,10,"SCORE: ");

    int missiles=10;
    int score=0;
    int cities=6;

    //array to store tha starting X index on map for every city
    //THIS WILL HELP TO KNOW IF A MISSILE HIT THE CITY OR THE GROUND.
    int loc[6];
    
    mvprintw(1,27,"%d",missiles);     
    mvprintw(0,17,"%d",score);  
    mvprintw(2,28,"%d",cities);  

    BuildWholeCity(loc);        
    
    //used to track and update cursos movement
    int moveX=31;
    int moveY=14;    

    //giving the starting position for the cursos
    mvprintw(moveY,moveX,"+");    
    wrefresh(win1);     
    
    //array used to store locations of incoming missile1
    //WILL HELP TO VALIDATE WHEATHER OR NOT A OUR MISSILE DESTOYED AN INCOMING MISSILE
    
    int incomingLoc1[23];
    int incomingLoc2[23];
    
    //X index for incoming missiles
    int incoming1=incomingMissile(incomingLoc1);
    int incoming11=incoming1;
    int incoming2=incomingMissile(incomingLoc2);
    int incoming22=incoming2;
    
    
    //used for WHILE loop
    int cont=1;

    //USED FOR KEYBOARD INPUT
    int ch;
    
    //used for printing the incoming missiles part by part on every execution of loop
    int Y=0;
    int X=0;

    nodelay(stdscr, TRUE);
    
    while(cont==1)
    {
      //the clock will help to show the incoming missiles gradually.
      clock_t begin = clock();             

      ch=getch();

     if((moveX>2) && (moveX<62) && (moveY>5) && (moveY<21)) 
     { 
      ch=getch();

      //WHEN AN ARROW KEY IS PRESSED THE CURSOS MOVES TO THAT DIRECTION INDICATED BY ARROW.

      if(ch == KEY_LEFT)
      {        
        mvprintw(moveY,moveX," "); //DELETE PREVIOUS CURSOS
        wrefresh(win1);
        moveX=moveX-2;              //UPDATE LOCATION FOR NEW CURSOS
        mvprintw(moveY,moveX,"+");  //PRINT NEW CURSOS    
        wrefresh(win1);             
      }

      if(ch == KEY_RIGHT)
      {
        mvprintw(moveY,moveX," ");
        wrefresh(win1);
        moveX=moveX+2;
        mvprintw(moveY,moveX,"+");     
        wrefresh(win1);            
      }

      if(ch == KEY_UP)
      {
        mvprintw(moveY,moveX," ");
        wrefresh(win1);
        moveY=moveY-2;
        mvprintw(moveY,moveX,"+");     
        wrefresh(win1);             
      }

      if(ch == KEY_DOWN)
      {
        mvprintw(moveY,moveX," ");
        wrefresh(win1);
        moveY=moveY+2;
        mvprintw(moveY,moveX,"+");     
        wrefresh(win1);             
      }      

     }

    else
     {

       //THIS IS USED TO PREVENT THE CURSOS FROM GOING OUTSIDE THE BOARDERS OF THE WINDOW.
       mvprintw(moveY,moveX," ");
       wrefresh(win1);

       move(moveY,moveX);

       if (moveX<2)
        moveX=moveX+2;
       if (moveX>62)
        moveX=moveX-2; 
       if (moveY<5)
        moveY=moveY+2;
       if (moveY>21)
        moveY=moveY-2;    

        move(moveY,moveX);   
      }
      //DEL key used to launch missiles, MISSILES ARE LAUNCHED BUT THEY ARE NOT VISIBLE AS THEY ARE DELETED TOO QUICK :(
      if(ch == KEY_DC)
      {       
         missiles--; //update missiles number
         mvprintw(1,27," ");
         move(moveY,moveX); 
         mvprintw(1,28," ");
         move(moveY,moveX); 
         mvprintw(1,27,"%d",missiles); //print how many missiles are left
         wrefresh(win1);
         move(moveX,moveY);            //move cursos back to its previous location so as cursos movement is not interapted by printing

        if(moveX>31)  //USED TO LAUNCH A CURSOS WHEN THE TARGET IS ON THE RIGHT HALF OF WINDOW.
        {
          for(int i=31; i<moveX; i++)
          {
           mvprintw(23,i,"#");     
           wrefresh(win1);
          }

          for(int j=23; j>moveY; j--)
          {
           mvprintw(j,moveX,"#");     
           wrefresh(win1);
          }          
          
          //CHECKS IF THE LAUNCHED MISSILE IS NEAR AN INCOMING MISSILE
          // IF YES THEN THE INCOMING MISSILE IS DELETED AND SCORE UPDATED

          if(((moveX==incoming1) || (moveX+1==incoming1) || (moveX+2==incoming1) || (moveX-1==incoming1) ||  (moveX-2==incoming1)) 
           &&  ((moveY==incomingLoc1[Y]) || (moveY+1==incomingLoc1[Y]) ||   (moveY+2==incomingLoc1[Y]) || (moveY+3==incomingLoc1[Y]) ||(moveY+4==incomingLoc1[Y]) || (moveY+5==incomingLoc1[Y]) ||   
           (moveY-1==incomingLoc1[Y]) ||(moveY-2==incomingLoc1[Y]) ||(moveY-3==incomingLoc1[Y]) ||(moveY-4==incomingLoc1[Y]) ||(moveY-5==incomingLoc1[Y])))       
            {
              Y=22;//USED GENERATE A NEW MISSILE AS THIS ONE IS GOING TO BE DELETED (USED ON LINE: 419 )
              incoming1=0; //UPDATE NUMBER OF MISSILES LEFT AND PRINT IT.
              score=score+10;
              mvprintw(0,17,"%d",score);
              move(moveY,moveX);  
              wrefresh(win1);
               
              for(int d=0; d<24; d++)        //DELETES THE INCOMING MISSILE    
                mvprintw(incomingLoc1[d],incoming1," ");              
            
            }
          //SAME THING FOR THE SECOND INCOMING MISSILE

          if(((moveX==incoming2) || (moveX+1==incoming2) || (moveX+2==incoming2) || (moveX-1==incoming2) ||  (moveX-2==incoming2)) 
           &&  ((moveY==incomingLoc2[X]) || (moveY+1==incomingLoc2[X]) || (moveY+2==incomingLoc2[X]) || (moveY+3==incomingLoc2[X]) || (moveY+4==incomingLoc2[X]) || (moveY+5==incomingLoc2[X]) ||   
           (moveY-1==incomingLoc2[X]) ||(moveY-2==incomingLoc2[X]) ||(moveY-3==incomingLoc2[X]) ||(moveY-4==incomingLoc2[X]) || (moveY-5==incomingLoc2[X])))       
            {
              X=22;
              incoming2=0;
              score=score+10;
              mvprintw(0,17,"%d",score);
              move(moveY,moveX); 
              wrefresh(win1);                

              for(int d=0; d<24; d++)
                mvprintw(incomingLoc2[d],incoming2," "); 
              
            }           

          move(moveY,moveX);   

          //DELETES THE LINE CREATED FROM THE LAUNCHED MISSILE, HAPPENS OO QUICK SO LINE OF LAUNCHED MISSILE IS INVISIBLE.     

           for(int i=31; i<moveX; i++)
          {
           mvprintw(23,i," ");     
           wrefresh(win1);
          }

          for(int j=23; j>moveY; j--)
          {
           mvprintw(j,moveX," ");     
           wrefresh(win1);
          }                   

          move(moveY,moveX);  
           
        }//
       
        //SAME THING, PROGRAM USES THIS BLOCK OF CODE TO DETECT WHEATHER AN INCOMING MISSILE IS DESTROYED BY A LAUNCHED MISSILE WHEN THE TARHET IS ON THE 
        //LEFT HALF OF SCREEN
        if(moveX<31)
        {
          for(int i=31; i>moveX; i--)
          {
           mvprintw(23,i,"#");     
           wrefresh(win1);
          }

          for(int j=23; j>moveY; j--)
          {
           mvprintw(j,moveX,"#");     
           wrefresh(win1);
          }          

          if(((moveX==incoming1) || (moveX+1==incoming1) || (moveX+2==incoming1) || (moveX-1==incoming1) || (moveX-2==incoming1)) 
           &&  ((moveY==incomingLoc1[Y]) || (moveY+1==incomingLoc1[Y]) || (moveY+2==incomingLoc1[Y]) || (moveY+3==incomingLoc1[Y]) || (moveY+4==incomingLoc1[Y]) || (moveY+5==incomingLoc1[Y]) ||   
           (moveY-1==incomingLoc1[Y]) ||(moveY-2==incomingLoc1[Y]) ||(moveY-3==incomingLoc1[Y]) ||(moveY-4==incomingLoc1[Y]) ||(moveY-5==incomingLoc1[Y])))       
            {
              Y=22;
              incoming1=0;
              score=score+10;
              mvprintw(0,17,"%d",score);
              move(moveY,moveX); 
              wrefresh(win1);
                
              for(int d=0; d<24; d++)            
                mvprintw(incomingLoc1[d],incoming1," ");              
            
            }

           move(moveY,moveX);    

          if(((moveX==incoming2) || (moveX+1==incoming2) || (moveX+2==incoming2) || (moveX-1==incoming2) ||  (moveX-2==incoming2)) 
           &&  ((moveY==incomingLoc2[X]) || (moveY+1==incomingLoc2[X]) || (moveY+2==incomingLoc2[X]) || (moveY+3==incomingLoc2[X]) || (moveY+4==incomingLoc2[X]) || (moveY+5==incomingLoc2[X]) ||   
           (moveY-1==incomingLoc2[X]) ||(moveY-2==incomingLoc2[X]) ||(moveY-3==incomingLoc2[X]) ||(moveY-4==incomingLoc2[X]) ||(moveY-5==incomingLoc2[X]))  )       
             {

              X=22;
              incoming2=0;
              score=score+10;
              mvprintw(0,17,"%d",score);
              move(moveY,moveX);
              wrefresh(win1);                 

              for(int d=0; d<24; d++)
               mvprintw(incomingLoc2[d],incoming2," "); 
              
            }           

          move(moveY,moveX);          

          for(int i=31; i>moveX; i--)
          {
           mvprintw(23,i," ");     
           wrefresh(win1);
          }

          for(int j=23; j>moveY; j--)
          {
           mvprintw(j,moveX," ");     
           wrefresh(win1);
          }                  

          move(moveY,moveX);         

        }//
                    
      } //shoot if

      //THE CLOCK IS USED TO PRINT THE INOMING MISSILES PART BY PART GRADUALLY.
      if (begin%110000==0)
      {
       
       //CONTINUES PRINTING MISSILES IF IT HAS NOT REACHED THE GROUND OR IT IS STILL NOT DESTROYED.
       if(Y<22) 
       {
        mvprintw(incomingLoc1[Y],incoming1,"$");
        wrefresh(win1);
        move(moveY,moveX);  
        wrefresh(win1);
        Y++; 
       }              
      
       //Y BECOMES 22 WHEN A MISSILES REACHED THE GROUND OR WHEN A MISSILES IS DESTROYED BY A LAUNCHED MISSILE 
        if(Y==22)
        {
          //DESTROYORNOT FUNCTION IS CALLED TO CHECK WHEATHER THE MISSILES HIT A CITY OR JUST THE GROUND.
          
          bool del=destroyOrNot(incoming1);
          move(moveY,moveX);  
          wrefresh(win1);

          //IF MISSILES HIT A CITY THEN UPDATE REMAINING CITIES, UPDATE SCORE.
          if(del)
          {
            cities=cities-1;
            mvprintw(2,28,"%d",cities);  
            move(moveY,moveX);
            wrefresh(win1);
            if(score>2)
            score=score-2;
            else score=0;
            mvprintw(0,17,"%d",score);
            move(moveY,moveX);  
            wrefresh(win1);
          }

          incoming1=incoming11; //used to preserve the X index of the incoming missiles in order to delete it

          //DELETES THE INCOMING MISSILES          
          for(int d=0; d<24; d++)
            mvprintw(incomingLoc1[d],incoming1," ");

          //GENERATED A NEW INCOMING MISSILE  

          incoming1=incomingMissile(incomingLoc1);  
          incoming11=incoming1;

          Y=0;

          move(moveY,moveX);  
          wrefresh(win1); 
          
        }       
      }
      
      //SAME THING FOR THE SECOND INCOMING MISSILES.
      if (begin%100000==0)
      {       

       if(X<22)
       { 
        mvprintw(incomingLoc2[X],incoming2,"$");  
        wrefresh(win1);
        move(moveY,moveX);    
        wrefresh(win1);
        X++;      
       }

        if(X==22)
        {
        
          bool del=destroyOrNot(incoming2);
          move(moveY,moveX);  
          wrefresh(win1);

          if(del)
          {
            cities=cities-1;
            mvprintw(2,28,"%d",cities);  
            move(moveY,moveX);
            wrefresh(win1);
            if(score>2)
            score=score-2;
            else score=0;
            mvprintw(0,17,"%d",score);
            move(moveY,moveX);  
            wrefresh(win1);
          }

          incoming2=incoming22;

          for(int d=0; d<24; d++)
            mvprintw(incomingLoc2[d],incoming2," ");

          incoming2=incomingMissile(incomingLoc2);
          incoming22=incoming2; 
          X=0; 

          move(moveY,moveX);  
          wrefresh(win1);  
        }
          
      }

      //IF CITIES=0 OR IS MISSILES LEFT=0 THEN RESET THE GAME AND START AGAIN.
      if((cities==0) || (missiles==0))
      {
         mvprintw(0,17,"%d",score);  
         mvprintw(2,28,"%d",cities);

        wclear(win1);
        
        sleep(2);        
        wclear(win1);        

        cont=0; //USED TO STOP THE INNER LOOP

      }

    } //while loop

  }//first while 

    getch();
    endwin();

} //main