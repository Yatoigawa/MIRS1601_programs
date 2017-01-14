#ifndef _USS_H
#define _USS_H

class USS
{
  public:
    USS(int pin);

    long getCM() {
      pinMode(this->pin, OUTPUT);
      digitalWriteDirect(this->pin, LOW);
      delayMicroseconds(2);
      digitalWriteDirect(this->pin, HIGH);
      delayMicroseconds(5);
      digitalWriteDirect(this->pin, LOW);

      pinMode(this->pin, INPUT);
      this->duration = pulseIn(this->pin, HIGH);
      return microsecondsToCentimeters(this->duration);
    }
  private:
    int pin;
    long duration;

    long microsecondsToCentimeters(long microseconds) {
      //return microseconds / 29 / 2
      return microseconds * 0.03448275862069 * 0.5;
    }

    void digitalWriteDirect(int pin, boolean val)
    {
      if (val)
      { // digitalWriteDirect
        g_APinDescription[pin].pPort->PIO_SODR = g_APinDescription[pin].ulPin;
      }
      else
      {
        g_APinDescription[pin].pPort->PIO_CODR = g_APinDescription[pin].ulPin;
      }
    }

    int digitalReadDirect(int pin)
    {
      // digitalReadDirect
      return !!(g_APinDescription[pin].pPort->PIO_PDSR & g_APinDescription[pin].ulPin);
    }
};

#endif
