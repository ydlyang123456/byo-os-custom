/* BYO-OS - ProcFS API */
#ifndef PROCFS_H
#define PROCFS_H

/* Read a /proc virtual file - returns length or -1 */
int procfs_read(const char* path, char* buf, uint32_t max_len);

/* Initialize /proc directory structure */
void procfs_init(void);

#endif
