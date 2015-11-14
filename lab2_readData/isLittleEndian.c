long isLittleEndian(void){
	int x = 0x192334E9; //any arbitrary value will do
	
	unsigned char *p = &x;
	
	long n = 0;
	
	// if the least sig byte of x appears at lowest memory of p, it's
	// little endian, otherwise it's big endian
	if(*p==0xE9){
		n=1;
	}
	return n;
}
