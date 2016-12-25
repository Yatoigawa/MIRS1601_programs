
			Remadme  USART_ver1_328P

 この文章はUSART_ver1.hの使い方を記してあるものです。また、この
文書はAtmelStudioを使用して読むことを推奨いたします。

対応マイコン:ATmega48A,ATmega88A,ATmega168A,ATmega328及びこれら
			 マイコンの派生



関数の一覧と役割、数値

uint8_t Usart_Init(uint8_t baudratemode,uint16_t baudrate)
	・Usartに使用するポートと通信速度の指定・初期化
		引数	uint8_t  baudratemode …通信モード(2倍速or通常)
				uint16_t baudrate	  …ボーレート値(UBRR値)
		戻り値	0		通常終了
				0xFF	baudratemode値のエラー
				0xFE	baudrate値のエラー
	※baudratemode,baudrateの値は下記に従ってください。


void Usart_Begin(void)
	・Usart通信の開始


void Usart_End(void)
	・Usart通信の終了
	※ポートの方向レジスタに出力が依存するので、短絡しないよう
	  ご注意下さい。そのため、使用しないことを推奨します。


void Usart_Write(uint8_t writedata)
	・Usart通信によるデータ送信(1Byte)
	　　引数	uint8_t writedata	…送信データ
	送信データは1Byteのuint8_t型(unsigned char型)であること。
	前回の送信が終わっていない場合、終わるまで待機する。


uint8_t Usart_Read (uint8_t *_readdata)
	・Usart受信データの読み取り
	　　引数	uint8_t *_readdata   …受信データ
		戻り値…受信データバッファに格納されているデータ数
				(受信したデータを含んだ数)
		※戻り値が0の場合、受信データがないことを意味します。
		　そのとき、引数の中のデータは0(0x00)になります。


uint8_t Usart_ReadDataBaff(uint8_t *_readdata,uint8_t _mode)
	・ReadDataバッファの制御
	※関数内でのみ使用します。基本的に外部から呼び出しをしないで
	ください。




注意事項・留意事項
	・受信データをバッファに移す際に割り込みを使用しています。
	　受信する際は全割り込み許可を与えてください。
	・F_CPU値を与えてください。
	・受信データバッファの大きさをUsartReadMax(マクロ)で与えて
	  ください。バッファが大きいほどオーバーフローする可能性は
	  減りますが、メモリを多く使います。ただし、200が最大値です。
	  また、指定されない場合・デフォルト値は10です。
	・Usart_Readの受信データは'uint8_t *'型です。ポインタを参照
	　しているので注意してください。
	・オーバーフローした場合、古いデータが消され新しいデータが入ります。


baudratemode,baudrateの値について
	baudratemode値、baudrate値は通信速度を設定する為の値です。
	baudratemode値…倍速モードの設定
					通常(U2X=0)…0
					倍速(U2X=1)…1
	baudrate値…UBRR値(CPUクロックの分周値)
		※uint16_t型(unsigned short int)です。ご注意ください。

	数値の求め方
	1.下記の表から求める
		 	 表1:代表的なクロックのボーレート値
   +-----------+------------+---------------+-----------+
   |  スピード | CPUクロック| baudratemode値| baudrate値|
   +-----------+------------+---------------+-----------+
   |  LowSpeed |      20MHz |          0    |      129  |
   |  (9600bps)|      16MHz |          0    |      103  |
   |           |       8MHz |          0    |       51  |
   |           |       1MHz |          1    |       42  |
   +-----------+------------+---------------+-----------+
   |MiddleSpeed|      20MHz |          1    |       64  |
   | (38400bps)|      16MHz |          0    |       25  |
   |           |       8MHz |          0    |       12  |
   +-----------+------------+---------------+-----------+
   | HighSpeed |      20MHz |          1    |        4  |
   |  (500kbps)|      16MHz |          0    |        1  |
   |           |       8MHz |          0    |        0  |
   +-----------+------------+---------------+-----------+

	2.データシートを読む
	テータシートには代表的なCPUクロックと通信速度の対応表が載って
	います。また、計算式がかいてあるのでそこから求めてください。
	表には通常と倍速の２種類の数値が書いてありますが、誤差の小さい方
	を採用してください。誤差が赤色の場合、信頼性がありません。

	3.付属のC言語のソースプログラムを使用する。
	付属してあるプログラムソースコードをコンパイルし、動作させてください。
	誤差の計算もした上で数値を返します。



サンプルプログラム
動作内容:受信したデータを送信する

/************************
 CPUクロック…20MHz
 通信速度…LowSpeed
 受信バッファ…10(Byte)
 ************************/

#define F_CPU 20000000UL		//CPU…20MHz
#define UsartReadMax 10			//バッファの大きさを10に設定
#include <avr/io.h>
#include <util/delay.h>
#include "USART_ver1.h"

int main(void){
	uint8_t a;
	uint8_t readdata;
	/*ポート初期化*/
	DDRB=0x00;
	DDRC=0x00;
	DDRD=0x00;
	Usart_Init(0,129);			//USART初期化・ボーレート値設定　
	_delay_ms(100);
	Usart_Begin();				//USART通信の許可
	sei();						//全割り込み許可
	Usart_Write(0xAA);			//0xAAを送信(接続確認用)
	while(1){
		a=Usart_Read(&readdata);	//データ読み取り
		if(a>0){					//a>0→受信データがある場合
			Usart_Write(readdata);	//受信データを送信
		}
	}
	return 0;
}