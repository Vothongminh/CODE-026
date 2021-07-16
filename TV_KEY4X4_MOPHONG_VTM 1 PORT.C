UNSIGNED INT8 HANG,COT,MP,MPT;
VOID TIMHANG ()
{  HANG=0XFF;
   IF(INPUT(PIN_A0)==0)  {HANG=0;}
   ELSE IF (INPUT(PIN_A1)==0) {HANG=1;}
   ELSE IF (INPUT(PIN_A2)==0) {HANG=2;}
   ELSE IF (INPUT(PIN_A3)==0) {HANG=3;}
}
VOID KEYPRESS()
{
   MP=0XFF;
   
   FOR (COT=0;COT<4;COT++)
   {
      SWITCH(COT)
      {  CASE 0:  OUTPUT_LOW(PIN_B0);
                  TIMHANG();
                  OUTPUT_HIGH(PIN_B0);
                  BREAK;
         CASE 1:  OUTPUT_LOW(PIN_B1);
                  TIMHANG();
                  OUTPUT_HIGH(PIN_B1);
                  BREAK;
         CASE 2:  OUTPUT_LOW(PIN_B2);
                  TIMHANG();
                  OUTPUT_HIGH(PIN_B2);
                  BREAK;
         CASE 3:  OUTPUT_LOW(PIN_B3);
                  TIMHANG();
                  OUTPUT_HIGH(PIN_B3);
                  BREAK;
      }
      IF (HANG!=0XFF) {
         IF((HANG == 0) && (COT == 3)) {MP = 1;BREAK;}
         ELSE IF((HANG == 0) && (COT == 2)) {MP = 2;BREAK;}
         ELSE IF((HANG == 0) && (COT == 1)) {MP = 3;BREAK;}
         ELSE IF((HANG == 0) && (COT == 0)) {MP = 10;BREAK;} //A
         ELSE IF((HANG == 1) && (COT == 3)) {MP = 4;BREAK;}
         ELSE IF((HANG == 1) && (COT == 2)) {MP = 5;BREAK;}
         ELSE IF((HANG == 1) && (COT == 1)) {MP = 6;BREAK;}
         ELSE IF((HANG == 1) && (COT == 0)) {MP = 11;BREAK;} //B
         ELSE IF((HANG == 2) && (COT == 3)) {MP = 7;BREAK;}
         ELSE IF((HANG == 2) && (COT == 2)) {MP = 8;BREAK;}
         ELSE IF((HANG == 2) && (COT == 1)) {MP = 9;BREAK;}
         ELSE IF((HANG == 2) && (COT == 0)) {MP = 12;BREAK;} //C
         ELSE IF((HANG == 3) && (COT == 3)) {MP = 14;BREAK;} //*
         ELSE IF((HANG == 3) && (COT == 2)) {MP = 0;BREAK;}
         ELSE IF((HANG == 3) && (COT == 1)) {MP = 15;BREAK;} //#
         ELSE IF((HANG == 3) && (COT == 0)) {MP = 13;BREAK;} //D
      }
   }
   
  
}
VOID KEY_4X4()
{
   KEYPRESS();
   IF (MP!=0XFF)
   {
      DELAY_MS(10);
      KEYPRESS();
      IF(MP!=0XFF)
      {
         MPT=MP;
         
         WHILE(MP!=0XFF) {KEYPRESS();}
         MP=MPT;
      }
   }
}
