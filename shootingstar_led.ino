

void stream(int datanum ,int data[][8]){
int i,j;

  for(i=0;i<datanum;i++) {

    for(j=0;j<8;j++){

      if(data[i][j] == 1)
      {RGBLED.setPixelColor(j, 255,200,255) ;
      }else{
        RGBLED.setPixelColor(j, 0,0,0);
      }  
    RGBLED.show() ; 
    delay(200);
    }
  }
}
/*
  int datan = 11;
int data[][8]={ {1,0,0,0,0,0,0,0},
                {1,1,0,0,0,0,0,0},
                {1,1,1,0,0,0,0,0},
                {0,1,1,1,0,0,0,0},
                {0,0,1,1,1,0,0,0},
                {0,0,0,1,1,1,0,0},
                {0,0,0,0,1,1,1,0},
                {0,0,0,0,0,1,1,1},
                {0,0,0,0,0,0,1,1},
                {0,0,0,0,0,0,0,1},
                {0,0,0,0,0,0,0,0}
                };
                
  stream(datan,data);

  delay(200);
*/


// 流れ星を流す
void fadestream(int speed){
  int i,b,k;
  int length = 100;
  double ganma = 2;
  
  for(k=0;k<(510+length*9);k++){
    for(i=0;i<8;i++){
      b = 255 - abs(255+i*length - k);
      if(b<0){b=0;}
      
     double a = (double)b/255;
      a = 255 * pow(a,ganma);
      b = a;
      RGBLED.setPixelColor(i, b,b,b);
    }
    RGBLED.show() ;
    delayMicroseconds(speed);
    //  Serial.println(b);
  }

}






