#ifndef IRUTILS_H
#define IRUTILS_H

#include "remotes.h"

void irReceiver_init(void);
void irReceiver_handler(void);

void irTransmitter_init(void);
void transmit(IrCommand cmd);

#endif