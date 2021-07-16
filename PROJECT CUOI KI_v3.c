#INCLUDE <16F887.H>
#INCLUDE <MATH.H>
#FUSES HS
#USE DELAY(CLOCK = 20M)
#INCLUDE <TV_KEY4X4_MOPHONG_VTM 1 PORT.C>
#DEFINE ENA PIN_C7 // CHO PHEP L298
#DEFINE ENB PIN_C5
#DEFINE IN1 PIN_C2
#DEFINE IN2 PIN_C4
#DEFINE IN3 PIN_C1
#DEFINE IN4 PIN_C6
//..............................................
#DEFINE LCD_RS_PIN      PIN_E0 
#DEFINE LCD_RW_PIN      PIN_A5
#DEFINE LCD_ENABLE_PIN  PIN_A4 
#DEFINE LCD_DATA4       PIN_D1 
#DEFINE LCD_DATA5       PIN_D0 
#DEFINE LCD_DATA6       PIN_C3 
#DEFINE LCD_DATA7       PIN_C0
#INCLUDE <LCD.C>

UNSIGNED INT8 CHUOI1[] = {"    "}; //4 KITU
UNSIGNED INT8 CHUOI2[] = {"   "};  //3 KITU
UNSIGNED INT8 CHUOI3[] = {' '};  //3 KITU
UNSIGNED INT8 I, DEM;
UNSIGNED INT8 VALUE, SPEED, DELAY, Q;
//..............................................
VOID TOCDO(){
   IF(SPEED == 1) DELAY = 20;      //15RPM 
   ELSE IF(SPEED == 2) DELAY = 15; //20RPM
   ELSE IF(SPEED == 3) DELAY = 10;  //30RPM
   ELSE IF(SPEED == 4) DELAY = 5;  //60RPM
   ELSE IF(SPEED == 5) DELAY = 2;  //150RPM
}
//..............................................
VOID MAIN(){
   SET_TRIS_A(0);
   SET_TRIS_B(0);
   SET_TRIS_C(0); 
   SET_TRIS_D(0);
   LCD_INIT();
   LCD_GOTOXY(1, 1);
   LCD_PUTC("INTERVAL(r):");
   LCD_GOTOXY(1, 2);
   LCD_PUTC("SPEED(1-5) :");
   VALUE = 0; SPEED = 0;
   OUTPUT_LOW(PIN_D2);
   OUTPUT_LOW(PIN_D3);
   OUTPUT_LOW(PIN_D4);
   OUTPUT_LOW(IN1); 
   OUTPUT_LOW(IN2); 
   OUTPUT_LOW(IN3); 
   OUTPUT_LOW(IN4);
   OUTPUT_LOW(ENA); 
   OUTPUT_LOW(ENB);
   WHILE(1){
      STEP1:
      DEM = 1; 
      LCD_GOTOXY(12, 1);
      LCD_PUTC(13+0X30);
      WHILE(CHUOI1[3] != ' '){
         KEY_4X4();
         IF(MP != 0XFF){
            IF(MP == 13) GOTO STEP2;
            ELSE IF (MP == 12){
               VALUE = 0;
               FOR(INT J = 0; J < 4; J++){
                  CHUOI1[J] = ' ';
               }
               LCD_GOTOXY(13, 1);
               FOR(I = 0; I < 4; I++){
                  LCD_PUTC(CHUOI1[I]);
               }
            }
         }
      }
      WHILE((CHUOI1[3] == ' ') || (MP != 13)){
         KEY_4X4();
         IF((MP != 0XFF) && (MP <= 9) && (DEM < 5)){
            FOR(I = 0; I < 3; I++){
               CHUOI1[I] = CHUOI1[I+1];
            }
            CHUOI1[3] = MP+0X30;
            LCD_GOTOXY(13, 1);
            FOR(I = 0; I < 4; I++){
               LCD_PUTC(CHUOI1[I]);
            }
            VALUE = VALUE + MP*POW(10, DEM-1);
            //IF(VALUE == 11) OUTPUT_HIGH(PIN_D4);
            DEM++;
         }
         IF(MP == 12){
            VALUE = 0;
            FOR(INT J = 0; J < 4; J++){
               CHUOI1[J] = ' ';
            }
            LCD_GOTOXY(13, 1);
            FOR(I = 0; I < 4; I++){
               LCD_PUTC(CHUOI1[I]);
            }
            DEM = 1;
         }
      }
      STEP2:
      LCD_GOTOXY(12, 1);
      LCD_PUTC(':');
      LCD_GOTOXY(12, 2);
      LCD_PUTC(13+0X30);
      DEM = 1;
      WHILE(CHUOI2[2] != ' '){
         KEY_4X4();
         IF(MP != 0XFF){
            IF(MP == 13) GOTO STEP3;
            ELSE IF (MP == 12){
               SPEED = 0;
               FOR(INT J = 0; J < 3; J++){
                  CHUOI2[J] = ' ';
               }
               LCD_GOTOXY(14, 2);
               FOR(I = 0; I < 3; I++){
                  LCD_PUTC(CHUOI2[I]);
               }
            }
         }
      }
      WHILE((CHUOI2[2] == ' ') || (MP != 13)){
         KEY_4X4();
         IF((MP != 0XFF) && (MP <= 9) && (DEM < 4)){
            FOR(I = 0; I < 2; I++){
               CHUOI2[I] = CHUOI2[I+1];
            }
            CHUOI2[2] = MP+0X30;
            LCD_GOTOXY(14, 2);
            FOR(I = 0; I < 3; I++){
               LCD_PUTC(CHUOI2[I]);
            }
            SPEED = SPEED + MP*POW(10, DEM-1);
            DEM++;
         }
         IF(MP == 12){
            SPEED = 0;
            FOR(INT J = 0; J < 3; J++){
               CHUOI2[J] = ' ';
            }
            LCD_GOTOXY(14, 2);
            FOR(I = 0; I < 3; I++){
               LCD_PUTC(CHUOI2[I]);
            }
            DEM = 1;
         }
      }
      STEP3:
      LCD_GOTOXY(12, 2);
      LCD_PUTC(':');
      UNSIGNED INT8 VALUE1;
      IF(VALUE < 10) VALUE1 = VALUE;
      ELSE IF(VALUE>9) VALUE1 = VALUE%10*10 + VALUE/10;
      WHILE(1){
         OUTPUT_HIGH(PIN_D2);
         KEY_4X4();
         IF((MP == 10) && (CHUOI1[3] != ' ') && (CHUOI2[2] != ' ')){
            OUTPUT_HIGH(PIN_D3);
            TOCDO();
            LCD_GOTOXY(12, 1);
            LCD_PUTC('>');
            FOR(INT16 N = 1; N <= VALUE1; N++){
            FOR(INT M = 0; M < 50; M++){
               OUTPUT_HIGH(IN1); OUTPUT_LOW(IN2); OUTPUT_HIGH(IN3); OUTPUT_LOW(IN4);
               OUTPUT_HIGH(ENA); OUTPUT_LOW(ENB);
               DELAY_MS(DELAY);
               OUTPUT_LOW(ENA); OUTPUT_HIGH(ENB);
               DELAY_MS(DELAY);
               OUTPUT_HIGH(IN2); OUTPUT_LOW(IN1); OUTPUT_HIGH(IN4); OUTPUT_LOW(IN3);
               OUTPUT_HIGH(ENA); OUTPUT_LOW(ENB);
               DELAY_MS(DELAY);
               OUTPUT_LOW(ENA); OUTPUT_HIGH(ENB);
               DELAY_MS(DELAY);
               KEY_4X4();
               IF(MP == 12) {
                  WHILE(1){
                     DO{ KEY_4X4();} WHILE (MP == 12);
                     DO{ KEY_4X4();} WHILE (MP != 12);
                     DO{ KEY_4X4();} WHILE (MP != 0XFF);
                     GOTO OK1;
                  }
               }
               OK1:;
            }
            LCD_GOTOXY(15, 1);
            IF(N > 9) LCD_PUTC(N/10+0X30);
            ELSE IF (N < 10) LCD_PUTC(' ');
            LCD_PUTC(N%10+0X30);
            }
            DELAY_MS(200);
            LCD_GOTOXY(12, 1);
            LCD_PUTC(":  ");
            OUTPUT_LOW(PIN_D3);
         }
         ELSE IF((MP == 11) && (CHUOI1[3] != ' ') && (CHUOI2[2] != ' ')){
            OUTPUT_HIGH(PIN_D4);
            TOCDO();
            CHUOI3[0] = ' ';
            LCD_GOTOXY(12, 1);
            LCD_PUTC('<');
            FOR(UNSIGNED INT8 Q = 1; Q <= VALUE1; Q++){
            FOR(INT M = 0; M < 50; M++){
               OUTPUT_HIGH(IN2); OUTPUT_LOW(IN1); OUTPUT_HIGH(IN4); OUTPUT_LOW(IN3);
               OUTPUT_LOW(ENA); OUTPUT_HIGH(ENB);
               DELAY_MS(DELAY);
               OUTPUT_HIGH(ENA); OUTPUT_LOW(ENB);
               DELAY_MS(DELAY);
               OUTPUT_HIGH(IN1); OUTPUT_LOW(IN2); OUTPUT_HIGH(IN3); OUTPUT_LOW(IN4);
               OUTPUT_LOW(ENA); OUTPUT_HIGH(ENB);
               DELAY_MS(DELAY);
               OUTPUT_HIGH(ENA); OUTPUT_LOW(ENB);
               DELAY_MS(DELAY);
               KEY_4X4();
               IF(MP == 12) {
                  WHILE(1){
                     DO{ KEY_4X4();} WHILE (MP == 12);
                     DO{ KEY_4X4();} WHILE (MP != 12);
                     DO{ KEY_4X4();} WHILE (MP != 0XFF);
                     GOTO OK2;
                  }
               }
               OK2:;
            }
            LCD_GOTOXY(15, 1);
            IF(Q > 9) LCD_PUTC(Q/10+0X30);
            ELSE IF (Q < 10) LCD_PUTC(' ');
            LCD_PUTC(Q%10+0X30);
            }
            DELAY_MS(200);
            LCD_GOTOXY(12, 1);
            LCD_PUTC(':');
            OUTPUT_LOW(PIN_D4);
         }
         ELSE IF(MP == 13){
            OUTPUT_LOW(PIN_D2);
            OUTPUT_LOW(PIN_D3);
            OUTPUT_LOW(PIN_D4);
            GOTO STEP1;
         }
      }
   }
}
