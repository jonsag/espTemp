
void drawText(int size, int posX, int posY, String text)
{
    display.setTextSize(size);
    display.setTextColor(WHITE);
    display.setCursor(posX, posY);
    display.println(text);
}