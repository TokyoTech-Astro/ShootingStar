void fadeStream(int speed) {
    int i, b, k, length = 100;
    double ganma = 2.0;

    for (k=0;k<(510+length*9);k++) {
        for (i=0;i<NUMRGBLED;i++) {
            b = (b=255 - abs(255+i*length-k))?b:0;
            double a = (double) b / 255;
            a = 255 * pow(a, ganma);
            b = a;
            RGBLED.setPixelColor(i,b,b,b);
        }
        RGBLED.show();
        delayMicroseconds(speed);
    }
}
