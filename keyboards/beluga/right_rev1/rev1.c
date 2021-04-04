#include "beluga.h"
// #include "usb_mouse.h"

// void matrix_init_kb(void) {
//   matrix_init_user();
//   //matrix_init_mouse_user();
// };


#include "print.h"
#include "pointing_device.h"

#define CURSOR_TIMEOUT 10
#define BASE_MOVE_PIXELS 5

int current_actionsX[2] = { 0, 0 };
int current_actionsY[2] = { 0, 0 };
int last_actionsX[2] = { 0, 0 };
int last_actionsY[2] = { 0, 0 };
int pinsX[] = {D3, D2};
int pinsY[] = {F4, D1};
uint16_t lastCursor = 0;
int move_multiplyX = 1;
int move_multiplyY = 1;

void keyboard_pre_init_user(void) {
  debug_enable=true;
  uprintf("EN: index: %d, clockwise: %d\n", 11, 22);
}

// void keyboard_post_init_user(void) {
//   // Customise these values to desired behaviour
//   debug_enable=true;
//   debug_matrix=true;
//   //debug_keyboard=true;
//   //debug_mouse=true;
//   uprintf("EN: index: %d, clockwise: %d\n", 11, 22);
// }


void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable=true;
  //debug_keyboard=true;
  //debug_mouse=true;
  uprintf("EN: index: %d, clockwise: %d\n", 11, 22);
  print("string");
  timer_init();
  //setPinInput(B0);
}

void pointing_device_task(void) {
  report_mouse_t report;
  report.x = 0;
  report.y = 0;
  report.h = 0;
  report.v = 0;
  report.buttons = 0;
  
  for(int i = 0; i < 2; ++i) {
    current_actionsX[i] = readPin(pinsX[i]);
    if (current_actionsX[i] != last_actionsX[i]) {
      last_actionsX[i] = current_actionsX[i];
      move_multiplyX += 10;
      if (move_multiplyX > 100) {
        move_multiplyX = 100;
      }
      if (i == 0) {
        report.x = BASE_MOVE_PIXELS * (move_multiplyX / 10 + 1);
      } else {
        report.x = -1 * BASE_MOVE_PIXELS * (move_multiplyX / 10 + 1);
      }
    }
  }
  for(int i = 0; i < 2; ++i) {
    current_actionsY[i] = readPin(pinsY[i]);
    if (current_actionsY[i] != last_actionsY[i]) {
      last_actionsY[i] = current_actionsY[i];
      move_multiplyY += 10;
      if (move_multiplyY > 100) {
        move_multiplyY = 100;
      }
      if (i == 0) {
        report.y = BASE_MOVE_PIXELS *  (move_multiplyY / 10 + 1);
      } else {
        report.y = -1 * BASE_MOVE_PIXELS * (move_multiplyY / 10 + 1);
      }
      uprintf("X: %d\n", report.x);
    }
  }
  
  if (timer_elapsed(lastCursor) > CURSOR_TIMEOUT) {
    lastCursor = timer_read();
    move_multiplyX--;
    if (move_multiplyX <= 0) {
      move_multiplyX = 1;
    }
    move_multiplyY--;
    if (move_multiplyY <= 0) {
      move_multiplyY = 1;
    }
  }

  pointing_device_set_report(report);
  pointing_device_send();
}
