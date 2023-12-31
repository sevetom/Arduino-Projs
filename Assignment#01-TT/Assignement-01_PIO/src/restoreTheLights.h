#ifndef RESTORE_THE_LIGHTS_H
    #define RESTORE_THE_LIGHTS_H
    // Standard arduino library
    #include <Arduino.h>
    // Standard C libraries
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    // Enables all pins to handle interrupts
    #include <EnableInterrupt.h>
    // Needed to use Timer
    #include <arduino-timer.h>
    // Needed to put arduino to sleep
    #include <avr/sleep.h>

    // Number of buttons and leds couples used
    #define COUPLES 4
    // Pin for the red led
    #define REDLED 6
    // Pins for the green leds
    #define GREENLED1 12
    #define GREENLED2 11
    #define GREENLED3 10
    #define GREENLED4 9
    // Pins for the buttons
    #define BUTTON1 5
    #define BUTTON2 4
    #define BUTTON3 3
    #define BUTTON4 2
    // Pin for the potentiometer
    #define POTENTIOMETER A0
    /* How many variables that are needed to take track of time
        in the differents parts of the game */
    #define TIMERS 3
    // Minum time given fro an action (milliseconds)
    #define MIN_TIME 1000
    // Maximum time given for an action (milliseconds)
    #define MAX_TIME 3000
    // The difference in time from one action to the next (milliseconds)
    #define TIME_INCREASE 3000
    // Quantity for how much the led shifts in light while fading
    #define FADE 5
    // Simbolic for variables waiting to have a valid number assigned
    #define UNDEFINED -1
    // Frequently used value when waiting (milliseconds)
    #define DELAY 1000
    // Time before going to sleep (milliseconds)
    #define SLEEP_TIME 10 * 1000
    // Time before getting another try (milliseconds)
    #define MISTAKE_TIME 10 * 1000
    /* This are not standard potentiometer values but
        the one we are using is of really poor quality */
    #define POT_MIN 20
    #define POT_MAX 900
    // Levels of difficulty of the game
    #define MIN_DIFF 1
    #define MAX_DIFF 4
    // Used to avoid buttons bouncing (milliseconds)
    #define BUTTONS_BOUNCING 100
    // Used to set a period for the led feading (milliseconds)
    #define FADE_PERIOD 30

    /**
     * This struct couples all the buttons with their respective leds. 
     * Also maintains their turn in the game.
    */
    typedef struct {
        int buttonPin;
        int ledPin;
        int turn;
    } buttonLed;

    /**
     * This is used to define the states the game can assume.
    */
    typedef enum {
        settingUp,
        starting,
        showingOrder,
        waitingPlayer,
        madeMistake,
        sleeping
    } gameState;

    /**
     * t1 [0] is the time elapsed to start the game
     * t2 [1] is time elapsed to turn on the leds
     * t3 [2] is the time to wait for the player
    */
    int times[TIMERS];

    /**
     * The main function executed before everything else 
     * used to set up the variables.
    */
    void setup();

    /**
     * The main function that handles all the program while looping.
    */
    void loop();

    /**
     * Sets the state of the game.
     * @param newState the new state the game should assume.
    */
    void setConcurrentState(gameState newState);

    /**
     * Attaches a function to the buttons' interrupt.
     * @param function the function to be attached.
    */
    void enableButtonsInterrupt(interruptFunctionType function);

    /**
     * Disables the buttons' interrupt.
    */
    void disableButtonsInterrupt();

    /**
     * Checks if enough time has passed since the last button press.
     * @return true if enough time has passed, false otherwise.
    */
    bool avoidButtonsBouncing();

    /**
     * Handles the setting up of the game.
    */
    void setupStart();

    /**
     * Waits for the player to press the button to start the game.
    */
    void waitingStart();

    /**
     * Starts the game.
    */
    void startGame();

    /**
     * Handles the time out of the time given to player.
     * @param arg the argument passed to the function.
     * @return true if it has to repeat the function, false otherwise.
    */
    bool timeOutGuess(void* arg);

    /**
     * Handles the resetting of the game.
    */
    void restart();

    /**
     * Switches off the leds in the reverse order they should be pressed.
    */
    void startTurningOffLeds();

    /**
     * Sets up everything needed to turn off the leds in order.
     * @param arr the array maintaining each led turn.
    */
    void setupTurningOffLeds(int* arr); 

    /**
     * Generates a random order for the leds.
     * @param arr the array maintaining each led turn.
     * @return the index of the first led to be turned on.
    */
    int randomLedOrder(int *arr);

    /**
     * Handles the button presses.
    */
    void buttonPressed();

    /**
     * Handles the correct guesses of the player.
     * @param index the index of the button pressed.
    */
    void correctGuess(int index);

    /**
     * Switches on or off all the green leds.
     * @param state false is they should be turned off, true otherwise.
    */
    void switchGreens(bool state);

    /**
     * Switches every led off.
    */
    void switchOff();

    /**
     * Generates a random integer between min and max.
     * @param min the minimum value the integer can assume.
     * @param max the maximum value the integer can assume.
     * @return the random integer generated.
    */
    int randomInt(int min, int max);

    /**
     * Generates a random float between min and max.
     * @param min the minimum value the float can assume.
     * @param max the maximum value the float can assume.
     * @return the random float generated.
    */
    float randomFloat(float min, float max);

    /**
     * Checks if a number is present in an array.
     * @param arr the array to be checked.
     * @param num the number to be checked.
     * @return true if the number is present, false otherwise.
    */
    bool isPresent(int *arr, int num);

    /**
     * Generates random times for the game.
    */
    void generateTimes();

    /**
     * Sets the times for the game descreasing them 
     * basing on the difficulty level.
    */
    void reduceTimes();

    /**
     * Gets the arduino to sleep.
     * @param arg the argument passed to the function.
     * @return true if it has to repeat the function, false otherwise.
    */
    bool powerDown(void* arg);

    /**
     * Wakes up the arduino.
    */
    void wakeUp();

    // The state the game is currently in
    volatile gameState state;
    // The led that should be lit next while playing
    volatile int currentTurn;
    // Used to maintain the current time to avoid buttons bouncing
    volatile long prevts;
    buttonLed buttonLedArr[COUPLES];
    volatile float score;
    volatile float difficulty;
    // Used to maintain the potentiometer value
    volatile float potVal;
    // Used to maintain the brightness of the red led
    int brightness;
    // Used to maintain the amount of light the red led is shifting
    int fadeAmount;
    // Timer handler
    Timer<> timer;
#endif