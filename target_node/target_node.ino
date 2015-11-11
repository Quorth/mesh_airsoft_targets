/** Airsoft Target - Target Node 
 *
 * The nodes will refresh their network address as soon as a single write fails. This allows the
 * nodes to change position in relation to each other and the master node.
 */
#include "RF24.h"
#include "RF24Network.h"
#include "RF24Mesh.h"

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
  mesh.setNodeID(nodeID);
  // Connect to the mesh
  Serial.println(F("Connecting to the mesh..."));
  mesh.begin();
  Serial.println(F("Connected to the mesh!"));
}
void loop() {
  mesh.update();
  
  // If interruption triggered, flag is set
  // so notify the master
  if (int_flag) {
    // Send an 'H' type message to notify a hit
    Serial.print("Hit received! Notifying to master... ");
    while (!mesh.write(0,'H',0)) {
      // If a write fails, check connectivity to the mesh network
      if (!mesh.checkConnection()) {
        //refresh the network address
        Serial.println("[FAILED]");
        Serial.print("Renewing Address... ");
        mesh.renewAddress();
        Serial.print("[OK]");
      } else {
        Serial.println("[FAIL]");
        Serial.println("Resending... ");
      }
    }
    Serial.println("[OK]"); 
    int_flag = 0;
  }
  
  while (network.available()) {
    RF24NetworkHeader header;
  }
}
void toggle(){
    int_flag = !int_flag;   
}
