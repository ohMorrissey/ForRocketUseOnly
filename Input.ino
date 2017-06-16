/*
 * Removed LED status indicators and replaced with LCD text feedback
 */


int input() {
  int returnValue = -1;
  now = millis();

  if (KSPBoardReceiveData()){
    deadtimeOld = now;
    returnValue = id;
    switch(id) {
    case 0: //Handshake packet
      Handshake();
      break;
    case 1:
      lcd.setCursor(7,0);
      lcd.print(" *"); // Displays Connected instead of Connected LED
      break;
    }


  }
  else
  { //if no message received for a while, go idle
    deadtime = now - deadtimeOld; 
    if (deadtime > IDLETIMER)
    {
      deadtimeOld = now;
      Connected = false;
      lcd.setCursor(7,0);
      lcd.print(" ?");   // Opposite of above
 
    }    
  }

  return returnValue;
}

byte ControlStatus(byte n)
{
  return ((VData.ActionGroups >> n) & 1) == 1;
}

