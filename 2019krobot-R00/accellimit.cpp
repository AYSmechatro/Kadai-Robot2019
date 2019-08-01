#include "accellimit.h"

void Accellimit::set(int a){
  limitval=a;
}

void Accellimit::reset(){
  val=0;
}

int Accellimit::alimit(int inval){
  static unsigned long lasttime=0;
  if(millis()-lasttime>=limitval){
    if(val>inval){
      val--;
    }else if(val<inval){
      val++;
    }
    lasttime=millis();
  }
  return val;
}

