

//  ███████╗███╗   ██╗ ██████╗  ██████╗ ██████╗ ██╗   ██╗██╗███╗   ██╗ ██████╗ 
//  ██╔════╝████╗  ██║██╔═══██╗██╔═══██╗██╔══██╗╚██╗ ██╔╝██║████╗  ██║██╔═══██╗
//  ███████╗██╔██╗ ██║██║   ██║██║   ██║██████╔╝ ╚████╔╝ ██║██╔██╗ ██║██║   ██║
//  ╚════██║██║╚██╗██║██║   ██║██║   ██║██╔═══╝   ╚██╔╝  ██║██║╚██╗██║██║   ██║
//  ███████║██║ ╚████║╚██████╔╝╚██████╔╝██║        ██║██╗██║██║ ╚████║╚██████╔╝
//  ╚══════╝╚═╝  ╚═══╝ ╚═════╝  ╚═════╝ ╚═╝        ╚═╝╚═╝╚═╝╚═╝  ╚═══╝ ╚═════╝ 
//                                           
// Read a servo pulse width and activates LEDs according to 
//   |            LEDs ON               |             LEDs OFF             |   LED1 & LED2 ON, LED3 Blink    |       
//   |----------------------------------|-----------------|----------------|---------------------------------|
//  1 ms                        ON_PULSE_WIDTH          1,5 ms     BLINK_PULSE_WIDTH                        2 ms
// 
// In blink, LED 3 is flashing while LED1 and LED2 are ON
// Flash duration is ajusted by the pulse lenght : The more close to 2ms, the longer the LED is ON

// This code is published under the GNU General Public License v3.0
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
// THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.



#define CHANNEL_INPUT 2

#define LED1 9
#define LED2 10
#define LED3 11

#define ON_PULSE_WIDTH 1400
#define BLINK_PULSE_WIDTH 1600
#define BLINK_OFF_INTERVAL 1000

unsigned long pulseWidth;
unsigned long flashDuration;
unsigned long nextMillis = 0;

enum Mode { off, on, blink_11};
Mode currentMode;
Mode previousMode;

// Activate or deactivate all LEDs accroding to mode passed as argument
void SetAllLEDsTo( Mode aMode)
{
  switch(aMode) {
    case on:
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
      digitalWrite(LED3, HIGH);
      break;
    case off:
      digitalWrite(LED1, LOW);
      digitalWrite(LED2, LOW);
      digitalWrite(LED3, LOW);
      break;
  }
}

void setup() {
    // Set inputs...
  pinMode(CHANNEL_INPUT, INPUT);
  
  // Set outputs...
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  currentMode = off;
  previousMode = off;
  SetAllLEDsTo(currentMode);
}

void loop() {
  //Read pulse width...
  pulseWidth = pulseIn( CHANNEL_INPUT, HIGH);

  //Do we have a "On" Pulse width  
  if (pulseWidth <= ON_PULSE_WIDTH)   {
     currentMode = on; 
  } // Do we have a blink pulse width ?
  else if (pulseWidth >= BLINK_PULSE_WIDTH) {
     currentMode = blink_11;
     // Compute LED3 flash duration
     flashDuration = max( 80, (pulseWidth - BLINK_PULSE_WIDTH) );
  }
  else {                                            // We are inbetween, in OFF mode
    currentMode = off; 
  }
 
  //Update LEDs state according to currentMode... 
  switch( currentMode)
  {
    case off:
      if (previousMode != currentMode) {SetAllLEDsTo( off );}
        break;

    case on:
      if (previousMode != currentMode) {SetAllLEDsTo( on );}
        break;

    case blink_11:  
    if (previousMode != currentMode) {              // Do we have to activate LED1 and LED2 ?
      digitalWrite(LED1, HIGH);
      digitalWrite(LED2, HIGH);
    }

    // If current time is over the next event time...
    if (millis() > nextMillis ) {
    
      if (digitalRead( LED3) == LOW) {              // If LED3 is Off
        digitalWrite(LED3, HIGH);                   // Set it ON
        nextMillis = millis() + flashDuration;      // Compute next event time...
      }
      else {
        digitalWrite(LED3, LOW);                    // Otherwise, set LED3 Off
        nextMillis = millis() + BLINK_OFF_INTERVAL; // Compute next event time...
      }
    }
    break;    
  }
  previousMode = currentMode;  // Save current mode for next iteration

}
