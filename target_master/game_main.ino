void game_main(){
  switch(game){
    case 1:
      sequencial_game();
      break;
    case 0:
    default:
      if(network.available()){
        RF24NetworkHeader header;
        network.peek(header);
        Serial.println(header.toString());
        check_address(header);
        network.read(header,0,0);
      }// end if
      return;
  } 
}
