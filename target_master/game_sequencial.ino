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
  
void sequencial_game(){
  Serial.print("Sequential Game Enabled. Game State ");
  Serial.println(game_state);
  switch(game_state){
      // Case 1 - Setup node targets and start chronometer
      case 1:
        broadcast_off();
        time = millis();
        current = 0;
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
          check_address(header);
          Serial.println(header.toString());
          network.read(header,0,0);
          
          if(header.from_node == mesh.addrList[current].address && header.type == 'H'){
            mesh.write(header.from_node,0,'O',0);
            current++;
            game_state = current < mesh.addrListTop ? 2 : 4;
          } //end if(mesh.getNodeID...)
          
        }// end if(network.available())
        break;
       case 4:
         time = millis() - time;
         game_state = 5;
         break;
       case 5:
         Serial.print(time);
         break;
       case 0:
       default:
         game_state = 1;
         break;
    }
}
