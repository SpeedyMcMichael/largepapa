#ifndef IO_H
#define IO_H

#include <stdint.h>

/* ---- Port I/O ---- */

static inline void outb(uint16_t port, uint8_t val) {
    __asm__ volatile ("outb %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outw(uint16_t port, uint16_t val) {
    __asm__ volatile ("outw %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint16_t inw(uint16_t port) {
    uint16_t ret;
    __asm__ volatile ("inw %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

static inline void outl(uint16_t port, uint32_t val) {
    __asm__ volatile ("outl %0, %1" : : "a"(val), "Nd"(port));
}

static inline uint32_t inl(uint16_t port) {
    uint32_t ret;
    __asm__ volatile ("inl %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}

/* Short delay for slow legacy hardware (PIC, etc). Port 0x80 is unused. */
static inline void io_wait(void) {
    outb(0x80, 0);
}

/* ---- 16550 UART (COM1) ---- */

#define COM1            0x3F8

#define UART_DATA       0   /* RX/TX buffer, or divisor low when DLAB=1 */
#define UART_IER        1   /* interrupt enable, or divisor high when DLAB=1 */
#define UART_FCR        2   /* FIFO control */
#define UART_LCR        3   /* line control */
#define UART_MCR        4   /* modem control */
#define UART_LSR        5   /* line status */

#define UART_LSR_RX_READY   0x01
#define UART_LSR_TX_EMPTY   0x20

/* Returns 0 on success, -1 if the loopback self-test fails (no UART). */
static inline int init_serial(void) {
    outb(COM1 + UART_IER, 0x00);    /* disable interrupts */
    outb(COM1 + UART_LCR, 0x80);    /* DLAB on */
    outb(COM1 + UART_DATA, 0x03);   /* divisor 3 -> 38400 baud */
    outb(COM1 + UART_IER, 0x00);
    outb(COM1 + UART_LCR, 0x03);    /* 8N1, DLAB off */
    outb(COM1 + UART_FCR, 0xC7);    /* enable + clear FIFOs, 14-byte threshold */
    outb(COM1 + UART_MCR, 0x1E);    /* loopback mode for the self-test */

    outb(COM1 + UART_DATA, 0xAE);
    if (inb(COM1 + UART_DATA) != 0xAE)
        return -1;

    outb(COM1 + UART_MCR, 0x0F);    /* normal operation */
    return 0;
}

static inline int is_transmit_empty(void) {
    return inb(COM1 + UART_LSR) & UART_LSR_TX_EMPTY;
}

static inline int serial_received(void) {
    return inb(COM1 + UART_LSR) & UART_LSR_RX_READY;
}

static inline void write_serial(char a) {
    /* Bounded spin so a dead UART can't hang the kernel (or a panic). */
    for (uint32_t i = 0; i < 1000000 && !is_transmit_empty(); i++)
        ;
    outb(COM1 + UART_DATA, (uint8_t)a);
}

static inline char read_serial(void) {
    while (!serial_received())
        ;
    return (char)inb(COM1 + UART_DATA);
}

static inline void kprint_serial(const char *str) {
    while (*str) {
        if (*str == '\n')
            write_serial('\r');     /* terminals want CRLF */
        write_serial(*str++);
    }
}

#endif
