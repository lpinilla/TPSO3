#ifndef _IDT_LOADER_H_
#define _IDT_LOADER_H_

#include <stdint.h>

#pragma pack(push)		/* Push de la alineación actual */
#pragma pack (1) 		/* Alinear las siguiente estructuras a 1 byte */

/* Descriptor de interrupcion */
typedef struct {
  uint16_t offset_l, selector;
  uint8_t cero, access;
  uint16_t offset_m;
  uint32_t offset_h, other_cero;
} DESCR_INT;

#pragma pack(pop)		/* Reestablece la alinceación actual */

void setup_IDT_entry (int index, uint64_t offset);
void load_idt(void);

#endif
