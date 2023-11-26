#include "Adafruit_GFX.h"
#include "MCUFRIEND_kbv.h"
MCUFRIEND_kbv tft;
uint16_t ox=0,oy=0;
int ave=0, avec=0, avet=0;
////////////////////////////////////////////////////////////////
void aveg(void)
{int z=0;
Serial.println(ave);
Serial.println(avec);
   avet=ave/avec;
   Serial.println(avet);
   avet=avet*32;
   for (int i=0; i<24; i++){
   for (uint16_t a=0; a<3; a++){
   tft.drawLine(avet+a, z, avet+a, z+10, 0xFB21);} // thick
   for (uint16_t a=0; a<2; a++){ tft.drawLine(avet-a, z, avet-a, z+10, 0xFB21);} delay(100); z=z+20; } } 
   ////////////////////////////////////////////////////////////////// 
   //void dchart_10x10(uint16_t nx,uint16_t ny)
   //{ ave+=nx; avec++; nx=nx*32; ny=ny*48; tft.drawCircle(nx, ny, 10, 0x0517); tft.drawCircle(nx, ny, 9, 0x0517); tft.fillCircle(nx, ny, 7, 0x0517); delay (100); ox=nx; oy=ny; } /////////////////////////////////////////////////////////////////////// 
   void dotchart_10x10(float nx,float ny)
   { 
    ave+=nx; 
    avec++;
    nx=nx*30;
    ny=ny*30; 
    int plus=0;
    float fplus=0;
    int sign=0;
    int y=0,x=0; 
    y=oy;
    x=ox;
    float xmines, ymines; 
    xmines=nx-ox;
    ymines=ny-oy; 
    if (ox>nx)
      {
        xmines=ox-nx;
        sign=1;
      }
    else 
    sign=0;
 for (int a=0; a<(ny-oy); a++)
  {
   fplus+=xmines/ymines;
   plus=fplus;
   if (sign==1)
   tft.drawFastHLine(0, y, x-plus, 0xBFDF);
   else
   tft.drawFastHLine(0, y, x+plus, 0xBFDF);
   y++;
   delay(5);
   }  
     for (uint16_t a=0; a<2; a++){
      
    tft.drawLine(ox+a, oy, nx+a, ny, 0x01E8);
    } // thick
    for (uint16_t a=0; a<2; a++)
    {
    tft.drawLine(ox, oy+a, nx, ny+a, 0x01E8);
    }   
   ox=nx;
   oy=ny;
}
////////////////////////////////////////////////////////////////////
void setup() {
 tft.reset();
 Serial.begin(9600);
 uint16_t ID = tft.readID();
 tft.begin(ID);
}
void loop() {
tft.invertDisplay(true);
tft.fillScreen(0xffff);
dotchart_10x10(0, 0); //(Yaxis, Xaxis)
dotchart_10x10(2, 1);
dotchart_10x10(4, 2);
dotchart_10x10(5, 3);
dotchart_10x10(5, 4);
dotchart_10x10(3, 5);
dotchart_10x10(6, 6);
dotchart_10x10(3, 7);
dotchart_10x10(8, 8);
dotchart_10x10(8, 9);
dotchart_10x10(10, 10);
dotchart_10x10(11, 11);
/*dchart_10x10(3, 0);
dchart_10x10(2, 1);
dchart_10x10(4, 2);
dchart_10x10(4, 3);
dchart_10x10(5, 4);
dchart_10x10(3, 5);
dchart_10x10(6, 6);
dchart_10x10(7, 7);
dchart_10x10(9, 8);
dchart_10x10(8, 9);
dchart_10x10(10, 10);*/
tft.setRotation(1);
tft.setTextSize(1);
tft.setTextColor(0x01E8);

tft.setCursor(240, 0);
tft.print("  Xaxis->day");
tft.setCursor(240, 15);
tft.print("  Yaxis->unit");

/*---- Y-axis ------*/
tft.setTextSize(1);
tft.setCursor(0, 0);
tft.print("8");
tft.setCursor(0, 30);
tft.print("7");
tft.setCursor(0, 60);
tft.print("6");
tft.setCursor(0, 90);
tft.print("5");
tft.setCursor(0, 120);
tft.print("4");
tft.setCursor(0, 150);
tft.print("3");
tft.setCursor(0, 180);
tft.print("2");
tft.setCursor(0, 210);
tft.print("1");
tft.setCursor(0, 240);
tft.print("0");

/*----- X-axis -------*/
tft.setCursor(240, 230);
tft.print("8");
tft.setCursor(210, 230);
tft.print("7");
tft.setCursor(180, 230);
tft.print("6");
tft.setCursor(150, 230);
tft.print("5");
tft.setCursor(120, 230);
tft.print("4");
tft.setCursor(90, 230);
tft.print("3");
tft.setCursor(60, 230);
tft.print("2");
tft.setCursor(30, 230);
tft.print("1");

//int dl=20;
//for (int i=0;i<6;i++){            
//for (uint16_t a=0; a<3; a++){
 //  tft.drawLine(dl, 40+a, dl+10, 40+a, 0xFB21);}
 //  dl+=16;}  
//tft.setRotation(0);
 //  aveg();
while(1);
}
