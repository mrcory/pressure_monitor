
//Store X values in the array
int readingArray [arraySize] = {0};
int arrayPos = 0;


//Add pressure reading to the array
void addPressure () {
  readingArray [arrayPos] = analogRead(sensePin); //Write to current array position

  arrayPos++; //Increment the current array position

  if (arrayPos > arraySize - 1) { arrayPos = 0; } //Reset position in array when at the end 
}

int averagePressure () {
  int _reading = 0;
  int _numValues = 0;
  
  for ( int i = 0; i < arraySize - 1; i++) { //Add all non zero values from array together
    if (readingArray != 0) {
      _reading += readingArray[i];
      _numValues++;                          //Increment the number of values to average
    }
  }

  if (_numValues > 0) {
    _reading = _reading / _numValues;       //Average the values together if we have one or more
  }

  return _reading;                          //Return our average value or 0
}

//Average the array and return value
int getPressure () {
  int _value = 0;

  _value = map(averagePressure(), pressureMinVal, pressureMaxVal, pressureMinPSI, pressureMaxPSI);

  return _value;
}
