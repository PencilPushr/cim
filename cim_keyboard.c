#include "cim_keyboard.h"

static size_t max_buffer_size = 32;

CIM_GENERIC_STATIC_QUEUE_DEF(char, uint8_t, 32)
CIM_GENERIC_STATIC_QUEUE_DEF(key_event, uint8_t, 32)
CIM_GENERIC_BITSET_DEF(state, uint16_t, 256)

void init_cim_keyboard(cim_keyboard* keyboard)
{
	cim_state_bitset_zero(keyboard->__key_states);
	keyboard->__auto_repeat_enabled = false;
	cim_init_static_char_queue(&keyboard->__char_buffer);
	cim_init_static_key_event_queue(&keyboard->__key_event_buffer);
	init_cim_keyboard_keys(&keyboard->k);
	init_cim_keyboard_event(&keyboard->event);

	keyboard->clear_state = __cim_clear_key_state;
	keyboard->pressed = __cim_key_pressed;
	keyboard->cim_set_auto_repeat = __cim_set_key_auto_repeat;
	keyboard->auto_repeat_enabled = __cim_key_auto_repeat_enabled;
	keyboard->has_event = __cim_has_key_event;
	keyboard->has_char = __cim_has_key_char;
	keyboard->read_event = __cim_read_key_event;
	keyboard->read_char = __cim_read_key_char;
}

void init_cim_keyboard_keys(cim_keyboard_key* keys)
{
	keys->ONE = 0x31; keys->TWO = 0x32; keys->THREE = 0x33; keys->FOUR = 0x34; keys->FIVE = 0x35;
	keys->SIX = 0x36; keys->SEVEN = 0x37; keys->EIGHT = 0x38; keys->NINE = 0x39; keys->ZERO = 0x30;

	keys->A = 0x41; keys->B = 0x42; keys->C = 0x43; keys->D = 0x44; keys->E = 0x45; keys->F = 0x46; keys->G = 0x47;
	keys->H = 0x48; keys->I = 0x49; keys->J = 0x4A; keys->K = 0x4B; keys->L = 0x4C; keys->M = 0x4D; keys->N = 0x4E;
	keys->O = 0x4F; keys->P = 0x50; keys->Q = 0x51; keys->R = 0x52; keys->S = 0x53; keys->T = 0x54; keys->U = 0x55;
	keys->V = 0x56; keys->W = 0x57; keys->X = 0x58; keys->Y = 0x59; keys->Z = 0x5A;
}

void init_cim_keyboard_event(cim_keyboard_event* types)
{
	types->K_PRESSED = 0;
	types->K_RELEASED = 1;
}

void __on_win32_key_down(uint16_t* key_state, static_key_event_queue* event_buffer, uint8_t keycode)
{
	cim_state_bitset_set(key_state, keycode);
	cim_keyboard_event event;
	cim_static_key_event_queue_push(event_buffer, &event.K_PRESSED);
	while (event_buffer->count > max_buffer_size - 1)
		cim_static_key_event_queue_pop(event_buffer);
	
}

void __on_win32_key_up(uint16_t* key_state, static_key_event_queue* event_buffer, uint8_t keycode)
{
	cim_state_bitset_clear(key_state, keycode);
	cim_keyboard_event event;
	cim_static_key_event_queue_push(event_buffer, &event.K_RELEASED);
	while (event_buffer->count > max_buffer_size - 1)
		cim_static_key_event_queue_pop(event_buffer);
}

void __on_win32_char(static_char_queue* char_buffer, uint8_t ch)
{
	cim_static_char_queue_push(char_buffer, &ch);
	while (char_buffer->count > max_buffer_size - 1)
		cim_static_char_queue_pop(char_buffer);
}

void __cim_clear_key_state(cim_keyboard* keyboard)
{
	cim_state_bitset_zero(keyboard->__key_states);
}

bool __cim_key_pressed(cim_keyboard* keyboard, uint8_t key_code)
{
	return cim_state_bitset_check(keyboard->__key_states, key_code);
}

void __cim_set_key_auto_repeat(cim_keyboard* keyboard, bool repeat)
{
	keyboard->__auto_repeat_enabled = repeat;
}

bool __cim_key_auto_repeat_enabled(cim_keyboard* keyboard)
{
	return keyboard->__auto_repeat_enabled;
}

bool __cim_has_key_event(cim_keyboard* keyboard)
{
	return keyboard->__key_event_buffer.count != 0;
}

bool __cim_has_key_char(cim_keyboard* keyboard)
{
	return keyboard->__char_buffer.count != 0;
}

uint8_t __cim_read_key_char(cim_keyboard* keyboard)
{
	return *cim_static_char_queue_pop(&keyboard->__char_buffer);
}

uint8_t __cim_read_key_event(cim_keyboard* keyboard)
{
	return *cim_static_key_event_queue_pop(&keyboard->__key_event_buffer);
}
