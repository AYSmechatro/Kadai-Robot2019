//config data process

//保存用構造体の構造を変えたり、データを初期化する場合は、以下の数値を変更してください。
const int ROM_ADDRES_OFFSET = 210;  //データの格納先の先頭アドレス
const byte ROM_SUMCODE = 0x1C;      //保存データの正誤比較用パラメータ

/************************************************/

//保存データの正誤比較
void checkRom() {
  if (EEPROM.read(ROM_ADDRES_OFFSET) == ROM_SUMCODE) {
    loadRom();
#ifdef DEBUG_ROM
    Serial.println("Load from EEPROM.");
#endif
  } else {
#ifdef DEBUG_ROM
    Serial.println("Invalid EEPROM checksum.");
#endif
  }
}

//データ読み出し
void loadRom() {
  EEPROM.get(ROM_ADDRES_OFFSET + 1, value);
}

//保存
void writeRom() {
  EEPROM.update(ROM_ADDRES_OFFSET, ROM_SUMCODE);
  EEPROM.put(ROM_ADDRES_OFFSET + 1, value);
}
