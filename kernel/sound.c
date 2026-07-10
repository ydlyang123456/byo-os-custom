/* BYO-OS PC Speaker Sound Driver - x86_64 */
#include <kernel.h>

/* PIT channel 2 is on port 0x42, command port 0x43 */
#define PIT_CMD_PORT   0x43
#define PIT_CH2_PORT   0x42
#define SPEAKER_PORT   0x61
#define PIT_FREQ       1193180

/* Note frequencies for octave 4 (C4-B4, A4 = 440 Hz) */
static const uint32_t note_freq[12] = {
    262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494
};

/* Melody entry: frequency + duration in ms */
typedef struct {
    uint32_t freq;
    uint32_t dur;
} melody_note_t;

/* Startup melody -- ascending arpeggio then descending fanfare */
static const melody_note_t startup_melody[] = {
    { 262, 150 }, { 330, 150 }, { 392, 150 }, { 523, 200 },
    { 392, 100 }, { 523, 100 }, { 659, 100 }, { 784, 300 },
    { 0, 100 },
    { 659, 100 }, { 784, 100 }, { 880, 200 }, { 784, 200 },
    { 0, 0 }
};

void sound_init(void)
{
    /* Ensure speaker starts off */
    outb(SPEAKER_PORT, inb(SPEAKER_PORT) & ~0x03);
}

void sound_play(uint32_t frequency)
{
    if (frequency == 0) {
        sound_stop();
        return;
    }

    /* Calculate PIT divisor */
    uint32_t divisor = PIT_FREQ / frequency;
    if (divisor < 1) divisor = 1;
    if (divisor > 65535) divisor = 65535;

    /* Configure PIT channel 2: mode 3 (square wave), lobyte/hibyte */
    outb(PIT_CMD_PORT, 0xB6);

    /* Write divisor (LSB then MSB) */
    outb(PIT_CH2_PORT, divisor & 0xFF);
    outb(PIT_CH2_PORT, (divisor >> 8) & 0xFF);

    /* Enable speaker: bit 1 (speaker gate) and bit 0 (timer 2 gate) */
    uint8_t val = inb(SPEAKER_PORT);
    outb(SPEAKER_PORT, val | 0x03);
}

void sound_stop(void)
{
    uint8_t val = inb(SPEAKER_PORT);
    outb(SPEAKER_PORT, val & ~0x03);
}

void sound_beep(void)
{
    sound_play(440);
    timer_sleep(200);
    sound_stop();
}

void sound_play_note(int note)
{
    int semitone = note & 0x0F;
    int octave   = (note >> 4) & 0x0F;

    if (semitone > 11) semitone = 0;
    if (octave == 0)   octave   = 4;

    uint32_t freq;
    if (octave >= 4) {
        freq = note_freq[semitone] << (octave - 4);
    } else {
        freq = note_freq[semitone] >> (4 - octave);
    }

    sound_play(freq);
}

void sound_play_melody(void)
{
    for (int i = 0; ; i++) {
        uint32_t freq = startup_melody[i].freq;
        uint32_t dur  = startup_melody[i].dur;

        if (dur == 0 && freq == 0) break;

        if (freq == 0) {
            sound_stop();
        } else {
            sound_play(freq);
        }

        timer_sleep(dur);
    }

    sound_stop();
}
