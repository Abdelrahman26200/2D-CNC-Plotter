#define DIR_1  2
#define STEP_1 3
#define ENA_1  4
#define DIR_2  5
#define STEP_2 6
#define ENA_2  7
#define PEN_up  8
#define PEN_down 9
#define y_limit  10
#define x_limit 11
#define forward LOW
#define backward HIGH

char x=0,y=0;

void setup() {
pinMode(DIR_1,OUTPUT);
pinMode(STEP_1,OUTPUT);
pinMode(ENA_1,OUTPUT);
pinMode(DIR_2,OUTPUT);
pinMode(STEP_2,OUTPUT);
pinMode(ENA_2,OUTPUT);
pinMode(PEN_up,OUTPUT);
pinMode(PEN_down,OUTPUT);
pinMode(y_limit,INPUT);
pinMode(x_limit,INPUT);

digitalWrite(ENA_1,LOW);
digitalWrite(ENA_2,LOW);

Home(); 
}

void move_x(char ch_x,char ch_direction) /* x in mm , dirction forward or backward*/
{
  int int_rev=0,limit=0,c=0;
  int_rev = 0.8 *200*ch_x ;
   digitalWrite(DIR_2,ch_direction);
   limit = digitalRead(x_limit);
 
  while(limit != 1 && c < int_rev)
  {
    limit = digitalRead(x_limit);
    digitalWrite(STEP_2,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_2,LOW);
    delayMicroseconds(500);
     c++;
  }
  
  if (limit !=1 )
{
  if(ch_direction==forward)
  {
      x=x+ch_x;
  }
  else if(ch_direction==backward)
  {
    x=x-ch_x;
  }
}
else
{
  digitalWrite(DIR_2,forward);
  while(limit ==1)
  {
    limit = digitalRead(x_limit);
    digitalWrite(STEP_2,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_2,LOW);
    delayMicroseconds(500);
  }
  x=0;
}

}
void move_y(char ch_y,char ch_direction) /* y in mm , dirction forward or backward*/
{
  int int_rev=0,limit=0,c=0;
  int_rev = 0.8 *200*ch_y ;
   digitalWrite(DIR_1,ch_direction);
   limit = digitalRead(y_limit);
 
  while(limit != 1 && c < int_rev)
  {
    limit = digitalRead(y_limit);
    digitalWrite(STEP_1,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_1,LOW);
    delayMicroseconds(500);
     c++;
  }
  
  if (limit !=1 )
{
  if(ch_direction==forward)
  {
      y=y+ch_y;
  }
  else if(ch_direction==backward)
  {
    y=y-ch_y;
  }
}
else
{
  digitalWrite(DIR_1,forward);
  while(limit ==1)
  {
    limit = digitalRead(y_limit);
    digitalWrite(STEP_1,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_1,LOW);
    delayMicroseconds(500);
  }
  y=0;
}

}

void move_xy(int int_x ,int x_dir, int int_y,int y_dir)
{
    int int_rev_x=0,int_rev_y=0,limit_x=0,limit_y=0,cx=0,cy=0;
  int_rev_x = 0.8 *200*int_x ;
  int_rev_y = 0.8 *200*int_y ;

   digitalWrite(DIR_1,y_dir);
   digitalWrite(DIR_2,x_dir);
  while(cx < int_rev_x || cy < int_rev_y)
  {
    limit_x = digitalRead(x_limit);
    if(limit_x != 1)
    {
    digitalWrite(STEP_2,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_2,LOW);
    delayMicroseconds(500);
     cx++;
    }
    limit_y = digitalRead(y_limit);
    if(limit_y != 1)
    {
    digitalWrite(STEP_1,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_1,LOW);
    delayMicroseconds(500);
     cy++;
    }
    
  }
  
  if (limit_x !=1 )
{
  if(x_dir==forward)
  {
     x=x+int_x;
  }
  else if(x_dir==backward)
  {
    x=x-int_x;
  }
}
else
{
  digitalWrite(DIR_2,forward);
  while(limit_x ==1)
  {
    limit_x = digitalRead(x_limit);
    digitalWrite(STEP_2,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_2,LOW);
    delayMicroseconds(500);
  }
}
   if (limit_y !=1 )
{
  if(y_dir==forward)
  {
     y=y+int_y;
  }
  else if(y_dir==backward)
  {
    y=y-int_y;
  }
}
else
{
  digitalWrite(DIR_1,forward);
  while(limit_y ==1)
  {
    limit_y = digitalRead(y_limit);
    digitalWrite(STEP_1,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_1,LOW);
    delayMicroseconds(500);
  }
 x=0;
 y=0;
}
}

void Home()
{
   char limit_y=0,limit_x=0;
  limit_y = digitalRead(y_limit);
  limit_x = digitalRead(x_limit);
  digitalWrite(DIR_1,backward);
  digitalWrite(DIR_2,backward);
  digitalWrite(PEN_up,HIGH);
  delay(1000);
  digitalWrite(PEN_up,LOW);

  while(limit_y==0 || limit_x==0)
  {
    limit_y = digitalRead(y_limit);
    limit_x = digitalRead(x_limit);
    if(limit_y==0)
    {
      digitalWrite(STEP_1,HIGH);
      delayMicroseconds(500);
      digitalWrite(STEP_1,LOW);
      delayMicroseconds(500);
    }
    if(limit_x==0)
    {
      digitalWrite(STEP_2,HIGH);
      delayMicroseconds(500);
      digitalWrite(STEP_2,LOW);
      delayMicroseconds(500);
    }
  }
  digitalWrite(DIR_1,forward);
  digitalWrite(DIR_2,forward);
  while(limit_y==1 || limit_x==1)
  {
    limit_y = digitalRead(y_limit);
    limit_x = digitalRead(x_limit);
    if(limit_y==1)
    {
    digitalWrite(STEP_1,HIGH);
    delayMicroseconds(500);
    digitalWrite(STEP_1,LOW);
    delayMicroseconds(500);
    }
    if(limit_x==1)
    {
      digitalWrite(STEP_2,HIGH);
      delayMicroseconds(500);
      digitalWrite(STEP_2,LOW);
      delayMicroseconds(500);
    }
  }
  y=0;
  x=0;
}
void squar(int side)
{
  digitalWrite(PEN_down,HIGH);
  move_y(side,forward);
  move_x(side,forward);
  move_y(side,backward);
  move_x(side,backward);
  digitalWrite(PEN_down,LOW);
  digitalWrite(PEN_up,HIGH);
  delay(1000);
  digitalWrite(PEN_up,LOW);
}
void diamond(int radius)
{
  int i2=0,j2=0,i=0,j=0;
  digitalWrite(PEN_down,HIGH);
  for(i=0;i<(2*radius);i++)
  {
      j=sqrt((radius)^2 - (i)^2);

      if(i<radius)
      {
        move_xy(abs(j-j2),forward,abs(i-i2),forward);
      }
      if(i>radius)
      {
        move_xy(abs(j2-j),backward,abs(i-i2),forward);
      }
       i2 = i;
       j2 = j;
  }
  for(i;i>0;i--)
  {
    j=sqrt((radius)^2 - ((i)^2));
    
      if(i>radius)
      {
        move_xy(abs(j-j2),backward,abs(i2-i),backward);
      }
      if(i<radius)
      {
        move_xy(abs(j-j2),forward,abs(i-i2),backward);
      }
      i2 = i;
      j2 = j;
  }
 digitalWrite(PEN_down,LOW);
 digitalWrite(PEN_up,HIGH);
  delay(1000);
  digitalWrite(PEN_up,LOW);
}
void loop() 
{
   move_x(1,forward);
     
//squar();
while(1)
{
}
}
