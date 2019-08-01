#ifndef _INC_UIDATA_H
#define _INC_UIDATA_H

//各項目の最後は"END"にしてください。

//全体項目
const char *UIMENUTOP[10] = {
  "ｲﾝﾌｫ", "ﾊﾞｯﾃﾘ", "ｺﾝﾄﾛｰﾗ", "ｾﾝｻ", "ﾊﾟﾗﾒｰﾀ", "ﾓｰﾀ",
  "END"
};

//インフォ
const char *UIMENUINFO[10] = {
  "ﾛｯｸ/ｱﾝﾛｯｸ",
  "END"
};

//バッテリ
const char *UIMENUBATT[10] = {
  "COM/ｻｰﾎﾞ", "ﾓｰﾀ1", "ﾓｰﾀ2", "ﾃﾞﾝｱﾂｱﾗｰﾑ",
  "END"
};

//コントローラ
const char *UIMENUCTL[10] = {
  "ｼﾞｮｳﾀｲ", "ｷｰﾆｭｳﾘｮｸ", "ｽﾃｨｯｸﾆｭｳﾘｮｸ", "ｽﾃｨｯｸﾆｭｰﾄﾗﾙ", "ｽﾃｨｯｸﾎﾞﾀﾝ", "ｱﾅﾛｸﾞﾑｺｳｶ",
  "END"
};

//センサ
const char *UIMENUSENS[14] = {
  "S1", "S2", "S3",
  "END"
};

//パラメータ
const char *UIMENUPARAM[10] = {
  "ﾀｲﾔｽﾋﾟｰﾄﾞH", "ﾀｲﾔｽﾋﾟｰﾄﾞM", "ﾀｲﾔｽﾋﾟｰﾄﾞL",
  "END"
};

//モータ
const char *UIMENUMOTOR[13] = {
  "ﾀｲﾔL", "ﾀｲﾔR", "ｱｰﾑ", "ｱｰﾑ",
  "ｺｷ ﾘﾌﾄ", "", "", "",
  "", "", "", "",
  "END"
};

//インデックスポインタ
//全体項目を変更、追加したら変数名をここに書いてください。
const char **UIMENUINDEX[10] = {
  UIMENUINFO, UIMENUBATT, UIMENUCTL,
  UIMENUSENS, UIMENUPARAM, UIMENUMOTOR
};

#endif
