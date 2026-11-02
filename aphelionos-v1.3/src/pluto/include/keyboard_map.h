#pragma once

unsigned char keyboard_map[128] = {
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8', //9
  '9', '0', '-', '=', '\b', //backspace
  '\t',         //tab
  'q', 'w', 'e', 'r',   //19
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', //enter key
    0,          // 29 - control
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', //39
 '\'', '`',  0,         //left shift
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',            //49
  'm', ',', '.', '/',   0,          //right shift
  '*',          //<3 :3 :3 :3
    0,          //alt
  ' ',          //space bar
    0,          //caps lock
    0,          //59 - f1 key
    0, 0, 0, 0, 0,0, 0, 0,
    0,          //F10 key
    0,          //69 - num lock
    0,          //scroll lock
    0,          //home key 
    0,          //up arrow 
    0,          //page up
  '-',
    0,          //left arrow
    0,
    0,          //right arrow
  '+',
    0,          //79 - end key
    0,          //down arrow
    0,          //page down
    0,          //insert key 
    0,          //delete key
    0, 0, 0,
    0,          //f11 key 
    0,          //f12 key 
    0,          //all other keys are undefined
};

unsigned char keyboard_map_shifted[128] = {
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*', //9
  '(', ')', '_', '+', '\b', //backspace
  '\t',         //tab
  'Q', 'W', 'E', 'R',   //19
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n', //enter key
    0,          // 29 - control
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':', //39
 '"', '~',   0,         //left shift
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',            //49
  'M', '<', '>', '?',   0,          //right shift
  '*',
    0,          //alt
  ' ',          //space bar
    0,          //caps lock
    0,          //59 - f1 key
    0, 0, 0, 0, 0,0, 0, 0,
    0,          //F10 key
    0,          //69 - num lock
    0,          //scroll lock
    0,          //home key 
    0,          //up arrow 
    0,          //page up
  '_',
    0,          //left arrow
    0,
    0,          //right arrow
  '+',
    0,          //79 - end key
    0,          //down arrow
    0,          //page down
    0,          //insert key 
    0,          //delete key
    0, 0, 0,
    0,          //f11 key 
    0,          //f12 key 
    0,          //all other keys are undefined
};