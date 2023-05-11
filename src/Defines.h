#pragma once
// Keep all defines (#define), and other constant variables that need to be
// accessed across the program, in this file. Do not have any includes in this
// file, so it can be included anywhere without any issues.

// doing updates once every tick_speed milliseconds (has to be less than 16.67 - more than 60 updates per second)
// but that might be only if updates are tied to FPS
#define tick_speed 10
#define input_speed 10
