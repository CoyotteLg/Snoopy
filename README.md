# Snoopy
Little LEDs controler for a static Snoopy plane

Read a servo pulse width and activates LEDs according to 
```
//   |            LEDs ON               |             LEDs OFF             |   LED1 & LED2 ON, LED3 Blink    |       
//   |----------------------------------|-----------------|----------------|---------------------------------|
//  1 ms                        ON_PULSE_WIDTH          1,5 ms     BLINK_PULSE_WIDTH                        2 ms
```
In blink, LED 3 is flashing while LED1 and LED2 are ON  
Flash duration is ajusted by the pulse lenght : The more close to ms, the longer the LED is ON
 ``` 
  
  
```  
This code is published under the GNU General Public License v3.0
 
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO 
THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE 
OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
