#ifdef TARGET_NODE

/**************************************
* Sets a received led command 
**************************************/
boolean set_led_command(led_command* lc_tmp){
  //If led_id from incoming led command is 0, result is applied to
  //every LED on the board
  if(lc_tmp->led_id == 0){
    for(int i=0; i<NUM_LEDS; i++){
      memcpy(&lc[i],&lc_tmp,sizeof(lc_tmp));
    }
  } else {
    memcpy(&lc[lc_tmp->led_id - 1],&lc_tmp,sizeof(lc_tmp));
  }
  free(lc_tmp);
  return 1;
}
/**************************************
* Quick function to turn all leds off 
**************************************/
boolean turn_off_all(){
  //TO_DO
  return 0;
}
/**************************************
* Post requested led_command to master
* NOTE: if led_id = 0, post led count
*************************************/
boolean post_led_command(uint8_t led_id){
  //TO_DO
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
  //TO_DO
}
#endif
