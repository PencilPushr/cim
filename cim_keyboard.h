#pragma once

#include <inttypes.h>
#include <stdbool.h>

#include "cim_generic_static_queue.h"
#include "cim_generic_bitset.h"

//char queue with size of 32
CIM_GENERIC_STATIC_QUEUE_DECL(char, uint8_t, 32)

//bitset with underlying type of uint_16 with 256 bits
//for 32 bit system, uint8_t would be better
CIM_GENERIC_BITSET_DECL(state, uint16_t, 256)

//cim_keyboard_event_types queue with size of 32
CIM_GENERIC_STATIC_QUEUE_DECL(key_event, uint8_t, 32);

typedef struct cim_keyboard_key
{
	uint8_t ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE,
	A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z;
} cim_keyboard_key;

typedef struct cim_keyboard_event
{
	uint8_t K_PRESSED, K_RELEASED;
} cim_keyboard_event;

typedef struct cim_keyboard
{
	cim_keyboard_key k;
	cim_keyboard_event event;

	bool __auto_repeat_enabled;

	//enum { __n_key_states = 256u / 16u };
	uint16_t __key_states[256u / 16u];//we want 256 bits

	static_char_queue __char_buffer;
	static_key_event_queue __key_event_buffer;

	void (*clear_state)(struct cim_keyboard* keyboard);
	bool (*pressed)(struct cim_keyboard* keyboard, uint8_t key_code);
	void (*cim_set_auto_repeat)(struct cim_keyboard* keyboard, bool repeat);
	bool (*auto_repeat_enabled)(struct cim_keyboard* keyboard);
	bool (*has_event)(struct cim_keyboard* keyboard);
	bool (*has_char)(struct cim_keyboard* keyboard);
	uint8_t (*read_char)(struct cim_keyboard* keyboard);
	uint8_t (*read_event)(struct cim_keyboard* keyboard);

} cim_keyboard;

void init_cim_keyboard(cim_keyboard* keyboard);
void init_cim_keyboard_keys(cim_keyboard_key* keys);
void init_cim_keyboard_event(cim_keyboard_event* types);

////win32 interface
void __on_win32_key_down(uint16_t* key_state, static_key_event_queue* event_buffer, uint8_t keycode);
void __on_win32_key_up(uint16_t* key_state, static_key_event_queue* event_buffer, uint8_t keycode);
void __on_win32_char(static_char_queue* char_buffer, uint8_t ch);

//client interface
void __cim_clear_key_state(cim_keyboard* keyboard);
bool __cim_key_pressed(cim_keyboard* keyboard, uint8_t key_code);
void __cim_set_key_auto_repeat(cim_keyboard* keyboard, bool repeat);
bool __cim_key_auto_repeat_enabled(cim_keyboard* keyboard);
bool __cim_has_key_event(cim_keyboard* keyboard);
bool __cim_has_key_char(cim_keyboard* keyboard);
uint8_t __cim_read_key_char(cim_keyboard* keyboard);
uint8_t __cim_read_key_event(cim_keyboard* keyboard);


