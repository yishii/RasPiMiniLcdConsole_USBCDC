/*
 * io handler
 *
 * Auther : Yasuhiro ISHII
 */

int __sys_seek(int fd, int position) {
	return 0;
}

int __sys_istty(int handle) {
	return 0;
}

int __sys_flen(int handle) {
	return 0;

}

int __sys_write(int iFileHandle, char *pcBuffer, int iLength) {
	return 0;

}

void __sys_appexit(void) {
}

void *_sbrk(void) {
	return (void*) 0;
}

int __sys_readc(void) {
	return 0;
}


int __sys_read(int iFileHandle, char *pcBuffer, int iLen){
	return 0;
}
