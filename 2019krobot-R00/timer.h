//タイマークラス

//author : Sato Masamune
//date : 2019/06/07

//description :
//Arduinoのmillis()関数を利用して時間処理を簡単に実装できます。
//delay()と違い、待ち時間中ほかの処理ができます。

//参考links :
// https://qiita.com/codai-04/items/990e2684937b3d207e14
// http://wisdom.sakura.ne.jp/programming/c/c54.html
// http://www.asahi-net.or.jp/~wv7y-kmr/memo/old/cpp_cls.html

#ifndef _INC_TIMER
#define _INC_TIMER

#include <Arduino.h>

class Timer {
  private:
    bool defined = false;
    unsigned long settime;
    unsigned long lasttime;

  public:
    void set(unsigned long t);
    bool check();
};

#endif
