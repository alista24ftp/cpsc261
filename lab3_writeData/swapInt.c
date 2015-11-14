int swapInt(int x){
	return (((x>>24)&0xff)|((x>>8)&0xff00)|((x<<8)&0xff0000)|((x<<24)&0xff000000));
}
