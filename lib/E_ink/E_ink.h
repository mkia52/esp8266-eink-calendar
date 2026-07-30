#ifndef E_INK_H
#define E_INK_H

#include "dtime.h"

#include <SPI.h>
#include <GxEPD2_3C.h>
#include <GxEPD2.h>
#include <Fonts/FreeMonoBold12pt7b.h>

extern GxEPD2_3C<GxEPD2_290_C90c, GxEPD2_290_C90c::HEIGHT> display;

void drawCalender();

#endif