/** Airsoft Target - Target Node 
 *
 * The nodes will refresh their network address as soon as a single write fails. This allows the
 * nodes to change position in relation to each other and the master node.
 */
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"
#include <avr/wdt.h>
#define TARGET_NODE
#include "lib_target.h"

#include <SPI.h>
#include <EEPROM.h>
//#include <printf.h>
/**** Configure the nrf24l01 CE and CS pins ****/
RF24 radio(7, 8);
RF24Network network(radio);
RF24Mesh mesh(radio, network);
/**
 * User Configuration: nodeID - A unique identifier for each radio. Allows addressing
 * to change dynamically with physical changes to the mesh.
 *
 * In this example, configuration takes place below, prior to uploading the sketch to the device
 * A unique value from 1-255 must be configured for each node.
 * This will be stored in EEPROM on AVR devices, so remains persistent between further uploads, loss of power, etc.
 *
 **/

void setup() {
  
  Serial.begin(115200);
  
  attachInterrupt(0,toggle,RISING);
  // Set the nodeID manually
  mesh.setNodeID(NODE_ID);
  // Connect to the mesh
  Serial.println(F("Connecting to the mesh..."));
  mesh.begin();
  Serial.println(F("Connected to the mesh!"));
  lc[0] = {1,0,255,255,255};
  wdt_enable(WDTO_250MS);
  
}
void loop() {
  wdt_reset();
  mesh.update();
  
  // If interruption triggered, flag is set
  // so notify the master
  if (int_flag) {
    int_proc = 1;
    // Send an 'H' type message to notify a hit
    Serial.print("Hit received! Notifying to master... ");
    while (!mesh.write(0,'H',0)) {
      Serial.println("[FAILED]");
      // If a write fails, check connectivity to the mesh network
      if (!mesh.checkConnection()) {
        //refresh the network address
        Serial.print("Renewing Address... ");
        mesh.renewAddress();
        Serial.println("[OK]");
      } else {
        Serial.println("[FAIL]");
        Serial.println("Resending... ");
      }
    }
    Serial.println("[OK]"); 
    int_flag = 0;
    delay(50);
    int_proc = 0;
  }
  
  while (network.available()) {
    RF24NetworkHeader header;
    network.peek(header);
    switch(header.type){
      case 'C':
        Serial.println("Received new LED Command from master:");
        led_command lc_tmp;
        network.read(header,&lc_tmp,sizeof(lc_tmp));
        //Set the led command
        set_led_command(&lc_tmp);
        break;
      case 'G':
	int led_id = 0;
	network.read(header,&led_id,sizeof(led_id));
	Serial.print("Asked for LED command with LED id ");
	Serial.println(led_id);
	Serial.print("Sending data... ");
	while(!post_led_command(led_id)){
	   Serial.println("[FAIL]");
	   Serial.print("Resending... ");
	}
	Serial.println("[OK]");
	break;
      case 'O':	
	Serial.print("Received general OFF status from master. Turning off all leds...");
	turn_off_all();
	Serial.println("[OK]");
	break;
      case 'V':
	Serial.print("Master asking for node version...");
	post_version();
	Serial.println("[OK]");
	break;
      default:
	Serial.println("Received unknown command. Corrupted frame?");
        break;
    }
  }
  if(millis() - display_timer > 40){ //Update LED patterns @25fps
    update_leds();
    display_timer = millis();
  }
}
void toggle(){
    int_flag = int_proc==1 ? 0 : 1;   
}
