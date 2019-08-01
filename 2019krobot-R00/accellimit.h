//加速度制限処理クラス

//author : Sato Masamune
//date : 2019/07/06

//description :
//モーターの出力の急激な変化を防ぐ関数です。
//加速度制限値はPWM出力値を1あげるのに何msかかるかで指定します。
//example)0~255(停止から全開まで)を5秒でする場合
//  加速度制限値=5*1000/256=だいたい20
//加速度制限値の指定はset()関数で指定します。
//非常停止などで急激に停止するには、reset()関数を呼び出します。

//使用例 : motorpower[1]=fan1.accellimit(button*256);

#ifndef _INC_ACCELLIMIT
#define _INC_ACCELLIMIT

#include <Arduino.h>

//typedef accel byte;

class Accellimit {
  private:
    int limitval = 0; //[ms/val]
    int val = 0;

  public:
    void set(int a);
    void reset();
    int alimit(int inval);
};

#endif
