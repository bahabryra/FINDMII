#include <wut.h>
#include <vpad/input.h>
#include <coreinit/screen.h>
#include <coreinit/speaker.h>
#include <coreinit/thread.h>

static OSScreenID screen = SCREEN_TV;

void draw_ui(void) {
    OSScreenClearBufferEx(screen, 0);
    OSScreenPutFontEx(screen, 10, 12, "┌────────────────────┐");
    OSScreenPutFontEx(screen, 10, 13, "|      FINDMII       |");
    OSScreenPutFontEx(screen, 10, 14, "└────────────────────┘");
    OSScreenPutFontEx(screen, 10, 16, "Press + to ping GamePad");
    OSScreenFlipBuffersEx(screen);
}

int main(int argc, char **argv) {
    VPADStatus vpad;
    VPADReadError err;

    VPADInit();
    OSScreenInit();
    OSScreenSetBufferEx(screen, (void*)0xF4000000);
    OSScreenEnableEx(screen, 1);
    SpeakerInit();

    while (1) {
        draw_ui();
        VPADRead(0, &vpad, 1, &err);

        if (vpad.btns_d & VPAD_BUTTON_PLUS) {
            // Vibrate GamePad
            VPADControlMotor(0, 1);
            OSSleepTicks(OSMillisecondsToTicks(800));
            VPADControlMotor(0, 0);

            // Beep from GamePad speaker
            SpeakerSetVolume(1.0f);
            SpeakerPlayTone(440, 200);
        }

        OSSleepTicks(OSMillisecondsToTicks(100));
    }

    return 0;
}
