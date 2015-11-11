#ifdef TARGET_NODE

/**************************************
* Sets a received led command 
**************************************/
boolean set_led_command(led_command* lc){
  //TO_DO
  return 0;
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

#endif
