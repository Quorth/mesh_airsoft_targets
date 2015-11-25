void game_sm(){
  if(game == 0) return;
  
  /**************************************
  * Game 1: Sequencial shoot
  * 
  * Target nodes start all off, then
  * turn one on and keep it until shot,
  * after shot turn it off and turn on
  * next target.
  *
  * Game ends when all targets have been shot
  * and displays how much time has passed.
  **************************************/

  if(game == 1){
    switch(game_state){
      // Case 1 - Setup node targets and start chronometer
      case 1:
        broadcast_off();
        time = millis();
        game_state = 2;
        break;
      // Case 2 - Turn on current led
      case 2:
        mesh.write(mesh.addrList[current].address,&lc_on,'C',sizeof(led_command));
        game_state = 3;
        break;
      case 3:
        if(network.available()){
          RF24NetworkHeader header;
          network.peek(header);
          if(mesh.getNodeID(header.from_node) == current){
            mesh.write(header.from_node,0,'O',0);
            current++;
          } //end if
        }// end if
        game_state = current < mesh.addrListTop ? 2 : 4; 
        break;
       case 4:
         time = millis() - time;
         game_state = 5;
         break;
       case 5:
         Serial.print(time);
         break;
    } // end switch
  } //end game
}//end function
