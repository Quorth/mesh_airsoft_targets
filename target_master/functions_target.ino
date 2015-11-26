void lc_to_string(led_command* lc_tmp){
  Serial.print("| LED ID: ");
  Serial.print(lc_tmp->led_id);
  Serial.print("| Red: ");
  Serial.print(lc_tmp->R);
  Serial.print("| Green: ");
  Serial.print(lc_tmp->G);
  Serial.print("| Blue: ");
  Serial.print(lc_tmp->B);
  Serial.print("| Pattern: ");
  Serial.println(lc_tmp->pattern);
}

#ifdef TARGET_NODE

/**************************************
* Sets a received led command 
**************************************/
boolean set_led_command(led_command* lc_tmp){
  if (lc_tmp->pattern > NUM_ANIMATIONS - 1) {
    Serial.println("Pattern out of bounds. Corrupted data?");
    return false;
  }
  //If led_id from incoming led command is 0, result is applied to
  //every LED on the board
  Serial.println("Setting new configuration");
  if(lc_tmp->led_id == 0){
    for(int i=0; i<NUM_LEDS; i++){
      memcpy(&lc[i],&lc_tmp,sizeof(lc_tmp));
    }
  } else {
    memcpy(&lc[lc_tmp->led_id - 1],&lc_tmp,sizeof(lc_tmp));
  }
  Serial.println("New configuration:");
  //Command received to string:
  lc_to_string(lc_tmp);
  free(lc_tmp);
  return 1;
}
/**************************************
* Quick function to turn all leds off 
**************************************/
boolean turn_off_all(){
   for(int i=0; i<NUM_LEDS; i++){
       lc[i].pattern = 0;
   }
   return 0;
}
/**************************************
* Post requested led_command to master
* NOTE: if led_id = 0, post led count
*************************************/
boolean post_led_command(uint8_t led_id){
   if(led_id == 0){
      return mesh.write(NUM_LEDS,'C',sizeof(int));
   } else {
      return mesh.write(lc[led_id],'G',sizeof(led_command));
   }
   return 0;
}
/**************************************
* Post node version to master 
**************************************/
boolean post_version(){
  //TO_DO
  return 0;
}

void update_leds(){
  frame = frame % 24;
  for(int i=0; i<NUM_LEDS; i++){ //for each led
    uint8_t shift_frame = mask_frame[lc[i].pattern][frame];
    analogWrite(led_pinout[i][0],lc[i].R >> shift_frame);
    analogWrite(led_pinout[i][1],lc[i].G >> shift_frame);
    analogWrite(led_pinout[i][2],lc[i].B >> shift_frame);
  }
  //Serial.print("Frame ");
  //Serial.println(frame++);  
}
#endif

#ifdef TARGET_MASTER
/**************************************
* Sends same led command to every target
* on Address List
**************************************/
boolean broadcast_led_command(led_command lc){
  boolean success = true;
  for (int i=0; i < mesh.addrListTop; i++){
    success &= mesh.write(mesh.addrList[i].address,&lc,'C',sizeof(led_command));
  }
  return success;
}

/**************************************
* Turns off every target on Address List 
**************************************/
boolean broadcast_off(){
  boolean success = true;
  for (int i=0; i < mesh.addrListTop; i++){
    success &= mesh.write(mesh.addrList[i].address,0,'O',0);
  }
  return success;
}

/**************************************
* Checks if sender is on Address List
**************************************/
boolean check_address(RF24NetworkHeader header){
    if(mesh.getNodeID(header.from_node) == -1){
      Serial.print("Packet received with no address assigned. Requesting address renew...");
      mesh.write(header.from_node,0,'R',0);
      mesh.DHCP();
      Serial.println("[OK]");
      return false;
    }
    return true;
}


#endif
