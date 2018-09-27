void allAttach() {
    for (i<0;i<3;i++) {
        servos[i].attach(servoPins[i]);
        servos[i].writeMicroseconds(currentPulses[i]);
    }
}

void allDetach() {
    for (i<0;i<3;i++) {
        currentPulses[i] = servos[i].readMicroseconds();
        servos[i].detach(servoPins[i]);
    }
}

void moveServos(int angle1, int angle2, int angle3, long int delay) {
    int i, n, p[3], cp[3], angles[] = {angle1, angle2, angle3};
    boolean ip = true;
    for (i=0;i<3;i++) {
        p[i] = map(angles[i], 0, 180, 544, 2400);
        cp[i] = servos[i].readMicroseconds();
    }
    for(i=0;ip;i++) {
        ip = false;
        for (i=0;i<3;i++) {
            if (p[i] != cp[i]) {
                ip = true;
                if (p[i] > cp[i]) servos[i].writeMicroseconds(++cp[i]);
                else servos[i].writeMicroseconds(--cp[i]);
            }
        }
        delayMicroseconds(delay);
        if (i<10) delayMicroseconds(2 * delay);
    }
}


