void raspi_open() {
  Serial.begin(115200);

  // バッファのクリア
  while (Serial.available() > 0) {
    Serial.read();
  }
}

int raspi_read(serial_data_t *serial_data) {
  int i;

  while (Serial.available() >= 7) {
    serial_data->val[0] = Serial.read();

    if (serial_data->val[0] >= 0x80) {
      for (i = 1; i < 7; i++) {
        serial_data->val[i] = Serial.read();
      }
      return 0;
    }
  }

  return -1;
}

void raspi_write(serial_data_t serial_data) {
  int i;

  for (i = 0; i < 7; i++) {
    Serial.write(serial_data.val[i]);
  }
}

int raspi_receive(command_data_t *command_data) {
  serial_data_t serial_data;

  if (raspi_read(&serial_data) == 0) {
    *command_data = raspi_decode2(raspi_decode1(serial_data));
    return 0;
  } else {
    return -1;
  }
}

void raspi_send(command_data_t command_data) {
  raspi_write(raspi_encode1(raspi_encode2(command_data)));
}

middle_data_t raspi_decode1(serial_data_t serial_data) {
  middle_data_t middle_data;

  middle_data.val[0] = ((serial_data.val[0] << 1) & 0xfe) | ((serial_data.val[1] >> 6) & 0x01);
  middle_data.val[1] = ((serial_data.val[1] << 2) & 0xfc) | ((serial_data.val[2] >> 5) & 0x03);
  middle_data.val[2] = ((serial_data.val[2] << 3) & 0xf8) | ((serial_data.val[3] >> 4) & 0x07);
  middle_data.val[3] = ((serial_data.val[3] << 4) & 0xf0) | ((serial_data.val[4] >> 3) & 0x0f);
  middle_data.val[4] = ((serial_data.val[4] << 5) & 0xe0) | ((serial_data.val[5] >> 2) & 0x1f);
  middle_data.val[5] = ((serial_data.val[5] << 6) & 0xc0) | ((serial_data.val[6] >> 1) & 0x3f);

  return middle_data;
}

command_data_t raspi_decode2(middle_data_t middle_data) {
  command_data_t command_data;

  command_data.val[0] = ((signed short)middle_data.val[0] << 8) | middle_data.val[1];
  command_data.val[1] = ((signed short)middle_data.val[2] << 8) | middle_data.val[3];
  command_data.val[2] = ((signed short)middle_data.val[4] << 8) | middle_data.val[5];

  return command_data;
}

serial_data_t raspi_encode1(middle_data_t middle_data) {
  serial_data_t serial_data;

  serial_data.val[0] =                              0x80  | ((middle_data.val[0] >> 1) & 0x7f);
  serial_data.val[1] = ((middle_data.val[0] << 6) & 0x40) | ((middle_data.val[1] >> 2) & 0x3f);
  serial_data.val[2] = ((middle_data.val[1] << 5) & 0x60) | ((middle_data.val[2] >> 3) & 0x1f);
  serial_data.val[3] = ((middle_data.val[2] << 4) & 0x70) | ((middle_data.val[3] >> 4) & 0x0f);
  serial_data.val[4] = ((middle_data.val[3] << 3) & 0x78) | ((middle_data.val[4] >> 5) & 0x07);
  serial_data.val[5] = ((middle_data.val[4] << 2) & 0x7c) | ((middle_data.val[5] >> 6) & 0x03);
  serial_data.val[6] = ((middle_data.val[5] << 1) & 0x7e);

  return serial_data;
}

middle_data_t raspi_encode2(command_data_t command_data) {
  middle_data_t middle_data;

  middle_data.val[0] = (command_data.val[0] >> 8) & 0x00ff;
  middle_data.val[1] =  command_data.val[0]       & 0x00ff;
  middle_data.val[2] = (command_data.val[1] >> 8) & 0x00ff;
  middle_data.val[3] =  command_data.val[1]       & 0x00ff;
  middle_data.val[4] = (command_data.val[2] >> 8) & 0x00ff;
  middle_data.val[5] =  command_data.val[2]       & 0x00ff;

  return middle_data;
}
