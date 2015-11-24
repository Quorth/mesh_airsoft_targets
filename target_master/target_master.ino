 /** Airsoft Target - Master Node 
  * 
  * The Master Node is the main node, which makes the control of the game. The rest of the nodes are 
  * essentially dummies.
  *
  * Targets are connected to each other usin a mesh network using the RF24Mesh library.
  *
  * The nodes can change physical or logical position in the network, and reconnect through different
  * routing nodes as required. The master node manages the address assignments for the individual nodes
  * in a manner similar to DHCP.
  *
  */
  
  
#include "RF24Network.h"
#include "RF24.h"
#include "RF24Mesh.h"

#define TARGET_MASTER
#include "lib_target.h"

#include <SPI.h>
//Include eeprom.h for AVR (Uno, Nano) etc. except ATTiny
#include <EEPROM.h>
/***** Configure the chosen CE,CS pins *****/
RF24 radio(14,15);
RF24Network network(radio);
RF24Mesh mesh(radio,network);
uint32_t displayTimer = 0;
void setup() {
  Serial.begin(115200);
  // Set the nodeID to 0 for the master node
  mesh.setNodeID(0);
  //Serial.println(mesh.getNodeID());
  // Connect to the mesh
  mesh.begin();
  lc.led_id = 0;
  lc.pattern = 1;
  lc.R = 255;
  lc.G = 0;
  lc.B = 0;
}
void loop() {    
  // Call mesh.update to keep the network updated
  mesh.update();
  
  // In addition, keep the 'DHCP service' running on the master node so addresses will
  // be assigned to the sensor nodes
  mesh.DHCP();
  
  
  // Check for incoming data from the targets
  if(network.available()){
    RF24NetworkHeader header;
    network.peek(header);
    if(mesh.getNodeID(header.from_node) == -1){
      Serial.print("Packet received with no address assigned. Requesting address renew...");
      mesh.write(header.from_node,0,'R',0);
      mesh.DHCP();
      Serial.println("[OK]");
    }
    uint32_t dat=0;
    switch(header.type){
      // Display the incoming data from the targets
      case 'H': 
	network.read(header,0,0);
	Serial.print("Received hit from node ");
        Serial.println(mesh.getNodeID(header.from_node));
        mesh.write(header.from_node,&lc,'C',sizeof(led_command));
	break;
      default:
        network.read(header,&dat,sizeof(dat));
        Serial.print("Received msg from node ");
        Serial.print(mesh.getNodeID(header.from_node));
        Serial.print(" with content ");
        Serial.println(dat);
	break;
    }
 }
  
  if(millis() - displayTimer > 5000){
    displayTimer = millis();
    Serial.println(" ");
    Serial.println(F("********Assigned Addresses********"));
     for(int i=0; i<mesh.addrListTop; i++){
       Serial.print("NodeID: ");
       Serial.print(mesh.addrList[i].nodeID);
       Serial.print(" RF24Network Address: 0");
       Serial.println(mesh.addrList[i].address,OCT);
     }
    Serial.println(F("**********************************"));
  }
}
