#include <Arduino.h>
#include <Components.h>

#define MIN_PERC 0
#define MAX_PERC 100
#define INVALID -1

/**
 * @brief The modality of the system
*/
typedef enum {
    AUTOMATIC,
    MANUAL
} modality;

/**
 * @brief Change the modality of the system
*/
void changeModality();
/**
 * @brief Read the serial port and return the value if it is valid
 * @return The value read from the serial port or -1 if it is not valid
*/
int serialRead();
/**
 * @brief Print the status of the system
*/
void printStatus();
/**
 * @brief Convert a char to an int
 * @param c The char to convert
 * @return The int value of the char
*/
int charToInt(char c);

volatile modality currentModality;
volatile int currentAngle;
Components* hw;

void setup() {
    Serial.begin(9600);
    Components* hw = new Components();
    currentModality = AUTOMATIC;
    hw->button->setInterrupt(changeModality, true);
}

void loop() {
    int value = INVALID;
    switch (currentModality) {
        case AUTOMATIC:
            value = serialRead(); 
            break;
        case MANUAL:
            value = hw->pot->detectChange() ? hw->pot->getValue() : INVALID;
            break;
    }
    if (value >= 0) {
        currentAngle = map(value, MIN_PERC, MAX_PERC, hw->gate->getMinAngle(), hw->gate->getMaxAngle());
        hw->gate->setAngle(currentAngle);
        printStatus();
    }
}

void changeModality() {
    if (hw->button->avoidBouncing()) {
        currentModality = (currentModality == AUTOMATIC) ? MANUAL : AUTOMATIC;
    }
}

int serialRead() {
    while (Serial.available() > 0) {
        int perc = charToInt(Serial.read());
        if (perc >= MIN_PERC && perc <= MAX_PERC) {
            return perc;
        }
    }
    return INVALID;
}

void printStatus() {
    char line1[10];
    char line2[10];
    sprintf(line1, "Angle: %d", currentAngle);
    sprintf(line2, "Modality: %d", currentModality);
    hw->lcd->printTwoLines(line1, line2);
}

int charToInt(char c) {
    return c - '0';
}