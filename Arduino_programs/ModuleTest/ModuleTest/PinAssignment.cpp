/*
�s���̏�����������t�@�C��
*/
#include "PinAssignment.h"
#include "Arduino.h"

//�ϐ���`
//�s������z��ɓ����(�������֐��Ŏg������)
//TODO:�S�Ẵs����K�؂Ȕz��ɓ����(�ʓ|)
const int outputPins[5] = { 8, 9 ,TL_0, TL_1, TL_2};
const int inputPins[1] = { 2 };

//�������֐���`
void initPinAssiment(const int Pins[], byte io) {
	for (int i = 0; i < sizeof(Pins) / sizeof(Pins[0]); i++)
	{
		pinMode(Pins[i], io);
	}
}