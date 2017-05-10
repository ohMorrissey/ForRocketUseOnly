/* Leaving for Now as my output is a keyobard emulator on a seperate board
 *  
 *  
 *  

  void output() {
  now = millis();
  controlTime = now - controlTimeOld;
  if (controlTime > CONTROLREFRESH) {
    controlTimeOld = now;
    controls();
  }
}

void controls() {
  if (Connected) {

    if (digitalRead(SASPIN)) { //--------- This is how you do main controls
      MainControls(SAS, HIGH);
      setSASMode(SMSAS); //setting SAS mode
      //setNavballMode(NAVBallSURFACE); //setting navball mode
    }
    else {
      //setNavballMode(NAVBallTARGET);
      MainControls(SAS, LOW);
    }

    if (digitalRead(RCSPIN))
      MainControls(RCS, HIGH);
    else
      MainControls(RCS, LOW);

    if (digitalRead(CG1PIN))   //--------- This is how you do control groups
      ControlGroups(1, HIGH);
    else
      ControlGroups(1, LOW);
      
    /*
       if (getSASMode() == SMPrograde) { //--------- This is how you read SAS modes
         //Blink LED, do stuff, etc.
       }

       if (getNavballMode() == NAVBallTARGET) { //--------- This is how you read navball modes
         //Blink LED, do stuff, etc.
       }
   


    //This is an example of reading analog inputs to an axis, with deadband and limits
    CPacket.Throttle = constrain(map(analogRead(THROTTLEPIN), THROTTLEDB, 1024 - THROTTLEDB, 0, 1000), 0, 1000);

    //This is an example of reading analog inputs to an axis, with deadband and limits
    //CPacket.Pitch = constrain(map(analogRead(THROTTLEPIN),0,1024,-1000,1000),-1000, 1000);

    KSPBoardSendData(details(CPacket));
  }
}

void controlsInit() {
  pinMode(SASPIN, INPUT_PULLUP);
  pinMode(RCSPIN, INPUT_PULLUP);
  pinMode(CG1PIN, INPUT_PULLUP);
}

byte getSASMode() {
  return VData.NavballSASMode & B00001111; // leaves alone the lower 4 bits of; all higher bits set to 0.
}

byte getNavballMode() {
  return VData.NavballSASMode >> 4; // leaves alone the higher 4 bits of; all lower bits set to 0.
}

void setSASMode(byte m) {
  CPacket.NavballSASMode &= B11110000;
  CPacket.NavballSASMode += m;
}

void setNavballMode(byte m) {
  CPacket.NavballSASMode &= B00001111;
  CPacket.NavballSASMode += m << 4;
}

void MainControls(byte n, boolean s) {
  if (s)
    CPacket.MainControls |= (1 << n);       // forces nth bit of x to be 1.  all other bits left alone.
  else
    CPacket.MainControls &= ~(1 << n);      // forces nth bit of x to be 0.  all other bits left alone.
}

void ControlGroups(byte n, boolean s) {
  if (s)
    CPacket.ControlGroup |= (1 << n);       // forces nth bit of x to be 1.  all other bits left alone.
  else
    CPacket.ControlGroup &= ~(1 << n);      // forces nth bit of x to be 0.  all other bits left alone.
}


 */
