/*
 * 
 */

void ConnectDisplay(){
    int i;
    lcd.clear();
    lcd.home();
    for(int j=0; j<64; j++){
      lcd.print("*");
    }
    lcd.setCursor(0,3);
    lcd.print("*  Kerbal Sim  *");
    lcd.setCursor(8,1);
    lcd.print("*  V:20170527  *");
    delay(2000);
    lcd.clear();
    return 0;
}

void ClearLine(int COL, int ROW){
  lcd.setCursor(COL,ROW);
  lcd.print("              ");
}


void Spacing(long int Number){
  if (Number/100 < 1){
        lcd.print(" ");
           if (Number/10 < 1)
               lcd.print(" ");
        }
}

void Zeros(long int Number){
  if (Number/100 < 1){
        lcd.print("0");
           if (Number/10 < 1)
               lcd.print("0");
        }
}


void DigitPrint(long int info, int COL, int ROW){
  
   long int hundreds;
   long int thousands;
   long int millions;

    //lcd.setCursor(COL,ROW);
    
    if (info < 0){
        info=-1*info;
        lcd.setCursor(COL,ROW);
        lcd.print(" -");
    }
    
    hundreds = info%1000;
    thousands = (info/1000)%1000;
    millions = info/1000000;
    
    if (millions > 0){
        lcd.setCursor(COL+1,ROW);
        Spacing(millions);        
        lcd.print(millions);
        lcd.print(",");
        Zeros(thousands);
        lcd.print(thousands);
        lcd.print(",");
        Zeros(hundreds);
        lcd.print(hundreds);

    }
    else if (thousands > 0){
        lcd.setCursor(COL+3,ROW);
        Spacing(thousands);
        lcd.print(thousands);
        lcd.print(",");
        Zeros(hundreds);
        lcd.print(hundreds);
    }
    else if (hundreds >= 0){
        lcd.setCursor(COL+5,ROW);
        Spacing(hundreds);
        lcd.print(hundreds);
    }
}

void TimePrint(long int info, int COL, int ROW){
  
   long int secs= info%60;
   long int mins = (info/60)%60;
   long int hrs = (info/3600)%24;
   long int days = info/86400;
       
   //lcd.setCursor(COL,ROW);
   
     if (days > 0){
        lcd.setCursor(COL,ROW);
        Spacing(days);        
        lcd.print(days);
        lcd.print(": ");
        lcd.print(hrs);
        lcd.print(": ");
        lcd.print(mins);
        lcd.print(": ");
        lcd.print(secs);
   
    }
    else if (hrs > 0){
       lcd.setCursor(COL+2,ROW);
       Spacing(hrs);
        lcd.print(hrs);
        lcd.print(": ");
        lcd.print(mins);
        lcd.print(": ");
        lcd.print(secs);
    }
    else if (mins > 0){
        lcd.setCursor(COL+4,ROW);
        Spacing(mins);
        lcd.print(mins);
        lcd.print(": ");
        lcd.print(secs);
    }
    else if (secs >= 0){
        lcd.setCursor(COL+6,ROW);
        Spacing(secs);
        lcd.print(secs);
    }
}




void DisplayScreen(int Screen){
 lcd.setCursor(0,0);

  switch(Screen){
    case 1: 
       lcd.print("Apoapsis:     ");
       break;
    case 2:
       lcd.print("Altitude:     ");
       break;
    case 3:
       lcd.print("Acceleration: ");
       break;
    case 4:
       lcd.print("Time to Ap:   ");
       break;
    case 5:
       lcd.print("Orbit Period: ");
       break;
    case 6:
       lcd.print("SOI:          ");
       break;
    case 7:
       lcd.print("Liquid Fuel:  ");
       break;
    case 8:
       lcd.print("MonoProp:     ");
       break;
    case 9:
       lcd.print("Mission Time: ");
       break;
    case 10:
       lcd.print("Next Node:    ");
       break;
    case 11:
       lcd.print("Target Dist:  ");
       break;
    default:
       lcd.print("No");
       break;
  }

 lcd.setCursor(8,1);

  switch(Screen){
    case 1: 
       lcd.print("Periapsis:    ");
       break;
    case 2:
       lcd.print("Velocity:     ");
       break;
    case 3:
       lcd.print("Vert Vel:     ");
       break;
    case 4:
       lcd.print("Time to Pe:   ");
       break;
    case 5:
       lcd.print("Inclination:  ");
       break;
    case 6:
       lcd.print("Density:      ");
       break;
    case 7:
       lcd.print("Oxidizer:     ");
       break;
    case 8:
       lcd.print("Elec Charge:  ");
       break;
    case 9:
       lcd.print("Stage:        ");
       break;
    case 10:
       lcd.print("Node DV:      ");
       break;
    case 11:
       lcd.print("Relative Vel: ");
       break;
    default:
       lcd.print("No");
       break;
  }
  return;

}

void DisplayInfo(int Screen){
   
    ClearLine(0,2);
    lcd.setCursor(0,2); 
 switch(Screen){
    case 1: // Apoapsis:
       DigitPrint(VData.AP, 0,2);
       lcd.print("m");
       break;
    case 2: // Altitude
       DigitPrint(VData.RAlt, 0,2);
       lcd.print("m");
       break;
    case 3: // Acceleration
       lcd.print("          ");
       lcd.print(VData.G);
       lcd.print("G");
       break;
    case 4: // Time to AP
       TimePrint(VData.TAp, 0,2);
       break;
    case 5: // Orbit Period
       TimePrint(VData.period, 0,2);
       break;
    case 6: // SOI
       for(int i = 0; i<8; i++)
           PrintSOI(VData.SOINumber);
       break;
    case 7: // Liquid Fuel %
       lcd.print("        ");
       lcd.print(Calc.Liq);
       lcd.print("%");
       break;
    case 8: // MonoProp %
       lcd.print("        ");
       lcd.print(Calc.Mono);
       lcd.print("%");
       break;
    case 9: // Mission Time
       TimePrint(VData.MissionTime, 0,2);
       break;
    case 10: // Next Node
       TimePrint(VData.MNTime, 0,2);
       break;
    case 11: // Target Dist
       DigitPrint(VData.TargetDist, 0,2);
       lcd.print("m");
       break;
    default:
       lcd.print("NaN");
       break;
  }
  ClearLine(8,3);
  lcd.setCursor(8,3);  
switch(Screen){
    case 1: // Periapsis
       DigitPrint(VData.PE, 8,3);
       lcd.print("m");
       break;
    case 2: // Velocity 
       DigitPrint(Calc.Vel, 8,3);
       lcd.print("m/s");
       break;
    case 3: // Vert Vel
       DigitPrint(VData.VVI, 8,3);
       lcd.print("m/s");
       break;
    case 4: // Time to Pe
       TimePrint(VData.TPe, 8,3);
       break;
    case 5: // Inclination
       lcd.print("         ");
       lcd.print(VData.inc);
       lcd.print("*");
       break;
    case 6: // Density
       lcd.print("      ");
       lcd.print(VData.Density);
       lcd.print("kg/m^2");
       break;
    case 7: // Oxidizer %
       lcd.print("        ");
       lcd.print(Calc.Oxi);
       lcd.print("%");
       break;
    case 8: // Elec Charge %
       lcd.print("        ");
       lcd.print(Calc.Elec);
       lcd.print("%");
       break;
    case 9:  // Stage
       lcd.print("             ");
       lcd.print(VData.CurrentStage);
       break;
    case 10: // Node DV
       DigitPrint(VData.MNDeltaV,8,3);
       lcd.print("m/s");
       break;
    case 11: // Relative Vel
       DigitPrint(VData.TargetV, 8,3);
       lcd.print("m/s");
       break;
    default:
       lcd.print("           NaN");
       break;
  }
}

void MakeCalc(){
  
  Calc.Liq=100*VData.LiquidFuelS/VData.LiquidFuelTotS;
  Calc.Oxi=100*VData.OxidizerS/VData.OxidizerTotS;
  Calc.Mono=100*VData.MonoProp/VData.MonoPropTot;
  Calc.Elec=100*VData.ECharge/VData.EChargeTot;


 Calc.Secs = VData.MissionTime%60;
 Calc.Mins = (VData.MissionTime/60)%60;
 Calc.Hrs = (VData.MissionTime/3600)%24;
 Calc.Days = VData.MissionTime/86,400;

int Mode = VData.NavballSASMode;
int State;
int Previous;
Mode=Mode/16;

  if(Mode==2)
     State = 1;
  else if (Mode==1)
     State = 0;

if (State == 0)
   Calc.Vel = VData.VOrbit;
else
   Calc.Vel = VData.Vsurf;
   
Previous = State;

if (Calc.Liq < 25)
   Warn.Liq=1;
else
   Warn.Liq=0;

if (Calc.Mono < 25)
   Warn.Mono=1;
else
   Warn.Mono=0;

if (Calc.Elec < 25)
   Warn.Elec=1;
else
   Warn.Elec=0;

if (VData.G > 4)
   Warn.Gee=1;
else
   Warn.Gee=0;

if (VData.RAlt < 2000)
   Warn.Alt=1;
else
   Warn.Alt=0;

if (VData.MaxOverHeat > 70)
   Warn.Heat=1;
else
   Warn.Heat=0;

if (VData.PE > 0)
   Warn.Orbit=1;
else
   Warn.Orbit=0;

if (VData.Density > 0)
   Warn.Atmo=1;
else
   Warn.Atmo=0;

}

void PrintSOI(int SOI){
lcd.setCursor(3,2);
switch(SOI){
  case 100:
     lcd.print("Kerbol        ");
     break;
  case 110:
     lcd.print("Moho          ");
     break;
  case 120:
     lcd.print("Eve");
     break;
  case 121:
     lcd.print("Gilly");
     break;
  case 130:
     lcd.print("Kerbin");
     break;
  case 131:
     lcd.print("Mun");
     break;
  case 132:
     lcd.print("Minmus");
     break;
  case 140:
     lcd.print("Duna");
     break;
  case 141:
     lcd.print("Ike");
     break;
  case 150:
     lcd.print("Dres");
     break;
  case 160:
     lcd.print("Jool");
     break; 
  case 161:
     lcd.print("Laythe");
     break;
  case 162:
     lcd.print("Vall");
     break;
  case 163:
     lcd.print("Tylo");
     break;
  case 164:
     lcd.print("Bop");
     break;
  case 165:
     lcd.print("Pol");
     break;
  case 170:
     lcd.print("Eeloo");
     break;
  default:
     lcd.print("NaN");
     break;
}
}







