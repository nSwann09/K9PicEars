void SSD1306_ClrAll(int address, char color);
void SSD1306_Out8(int address, char row, char col, char *texto, char color);
void SSD1306_OutMine(int address, int row, int col, int texto, char color);
void SSD1306_Fill(int address, int TopX, int TopY, int BottomX, int BottomY, char color);
void SSD1306_TextFill(int address, int TopX, int TopY, int BottomX, int BottomY, char color, int texto);
void SSD1306_Init(int address);