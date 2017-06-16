/* 
 * Original: Zitronen
 * http://forum.kerbalspaceprogram.com/index.php?/topic/60281-hardware-plugin-arduino-based-physical-display-serial-port-io-tutorial-23-04-17/&
 * Modified: ohMorrissey
 * For Rocket Use only
 * http://forum.kerbalspaceprogram.com/index.php?/topic/159865-for-rocket-use-only-a-kerbal-simpit-build-log/
 * Kerbal Space Program LCD HUD Display
 * V:20170527
 * 
 */

//macro
#define details(name) (uint8_t*)&name,sizeof(name)

//if no message received from KSP for more than 2s, go idle
#define IDLETIMER 2000
#define CONTROLREFRESH 25

unsigned long deadtime, deadtimeOld, controlTime, controlTimeOld;
unsigned long now;

boolean Connected = false;

byte caution = 0, warning = 0, id;

struct VesselData
{
    byte id;                //1
    float AP;               //2
    float PE;               //3
    float SemiMajorAxis;    //4
    float SemiMinorAxis;    //5
    float VVI;              //6
    float e;                //7
    float inc;              //8
    float G;                //9
    long TAp;               //10
    long TPe;               //11
    float TrueAnomaly;      //12
    float Density;          //13
    long period;            //14
    float RAlt;             //15
    float Alt;              //16
    float Vsurf;            //17
    float Lat;              //18
    float Lon;              //19
    float LiquidFuelTot;    //20
    float LiquidFuel;       //21
    float OxidizerTot;      //22
    float Oxidizer;         //23
    float EChargeTot;       //24
    float ECharge;          //25
    float MonoPropTot;      //26
    float MonoProp;         //27
    float IntakeAirTot;     //28
    float IntakeAir;        //29
    float SolidFuelTot;     //30
    float SolidFuel;        //31
    float XenonGasTot;      //32
    float XenonGas;         //33
    float LiquidFuelTotS;   //34
    float LiquidFuelS;      //35
    float OxidizerTotS;     //36
    float OxidizerS;        //37
    uint32_t MissionTime;   //38
    float deltaTime;        //39
    float VOrbit;           //40
    uint32_t MNTime;        //41
    float MNDeltaV;         //42
    float Pitch;            //43
    float Roll;             //44
    float Heading;          //45
    uint16_t ActionGroups;  //46  status bit order:SAS, RCS, Light, Gear, Brakes, Abort, Custom01 - 10
    byte SOINumber;         //47  SOI Number (decimal format: sun-planet-moon e.g. 130 = kerbin, 131 = mun)
    byte MaxOverHeat;       //48  Max part overheat (% percent)
    float MachNumber;       //49
    float IAS;              //50  Indicated Air Speed
    byte CurrentStage;      //51  Current stage number
    byte TotalStage;        //52  TotalNumber of stages
    float TargetDist;       //53  Distance to targeted vessel (m)
    float TargetV;          //54  Target vessel relative velocity
    byte NavballSASMode;    //55  Combined byte for navball target mode and SAS mode
                                    // First four bits indicate AutoPilot mode:
                                    // 0 SAS is off  //1 = Regular Stability Assist //2 = Prograde
                                    // 3 = RetroGrade //4 = Normal //5 = Antinormal //6 = Radial In
                                    // 7 = Radial Out //8 = Target //9 = Anti-Target //10 = Maneuver node
                                    // Last 4 bits set navball mode. (0=ignore,1=ORBIT,2=SURFACE,3=TARGET)
};

struct HandShakePacket
{
  byte id;
  byte M1;
  byte M2;
  byte M3;
};

struct Calculations
{
   float Liq;
   float Oxi;
   float Mono;
   float Elec;
   float Secs;
   float Mins;
   float Hrs;
   float Days;
   //char SOI[7];
   float Vel;
};

struct Warnings 
{
  bool Liq;
  bool Mono;
  bool Elec;
  bool Gee; 
  bool Alt;
  bool Heat;
  bool Orbit;
  bool Atmo;
};

byte delta[8] = {
  B00100,
  B00100,
  B01010,
  B01010,
  B01010,
  B10001,
  B11111,
};


/*struct ControlPacket {
  byte id;
  byte MainControls;                  //SAS RCS Lights Gear Brakes Precision Abort Stage
  byte Mode;                          //0 = stage, 1 = docking, 2 = map
  unsigned int ControlGroup;          //control groups 1-10 in 2 bytes
  byte NavballSASMode;                //AutoPilot mode
  byte AdditionalControlByte1;
  int Pitch;                          //-1000 -> 1000
  int Roll;                           //-1000 -> 1000
  int Yaw;                            //-1000 -> 1000
  int TX;                             //-1000 -> 1000
  int TY;                             //-1000 -> 1000
  int TZ;                             //-1000 -> 1000
  int WheelSteer;                     //-1000 -> 1000
  int Throttle;                       //    0 -> 1000
  int WheelThrottle;                  //    0 -> 1000
};
*/
#include <LiquidCrystal.h>


// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 9, 8, 7, 6, 5, 4, 3, 2);

   int Display=1;
   int DispPrev=0;
   int DispPin = 13;
   bool DispPinPrev = 0;
   int timer = 0;

HandShakePacket HPacket;
VesselData VData;
//ControlPacket CPacket;
Calculations Calc;
Warnings Warn;

void setup() {
  Serial.begin(38400);
  pinMode(DispPin, INPUT_PULLUP);
  

  InitTxPackets();
  Display = 1;
  DispPrev = 0;

 
    lcd.begin(16, 4);
    ConnectDisplay();
    lcd.createChar(0, delta); 
    
}

void loop()
{
  input();
  
if(timer==100){
  
  MakeCalc();
  
   if(digitalRead(DispPin)!=DispPinPrev){
        if(digitalRead(DispPin)==HIGH){
           lcd.clear();
           Display++;
        }
        DispPinPrev= digitalRead(DispPin);
  }
  
  if (Display > 11){
        Display = 1;
  } 
  
  if(Display==DispPrev){
        DisplayScreen(Display);
  }
  
  DisplayInfo(Display);  
 
  DispPrev = Display;
  }
  
timer++;

if (timer > 100)
timer=0;
delay(1);




}


