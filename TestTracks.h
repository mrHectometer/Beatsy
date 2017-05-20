void init_track0()
{
	int t = 0;
	//kick
	Track[t].setEntry(0, 0, 0xFF);
	Track[t].setEntry(10, 0, 0xFF);
	//snare
	Track[t].setEntry(4, 1, 0xFF);
	Track[t].setEntry(12, 1, 0xFF);
	//hats
	for(int i = 0; i < 16; i+=2)
	{
		Track[t].setEntry(i, 2, 0xFF);
	}
	for(int i = 1; i < 16; i+=2)
	{
		Track[t].setEntry(i, 2, 0x55);
	}
}
void init_track1()
{
	int t = 1;
	//kick
	Track[t].setEntry(0, 0, 0xFF);
	Track[t].setEntry(8, 0, 0x77);
	Track[t].setEntry(10, 0, 0xFF);
	//snare
	Track[t].setEntry(4, 1, 0xFF);
	Track[t].setEntry(11, 1, 0x44);
	Track[t].setEntry(12, 1, 0xFF);
	Track[t].setEntry(14, 1, 0xFF);
	//hats
	for(int i = 0; i < 16; i+=2)
	{
		Track[t].setEntry(i, 2, 0xFF);
	}
	for(int i = 1; i < 16; i+=2)
	{
		Track[t].setEntry(i, 2, 0x44);
	}
}
void init_track2()
{
	int t = 2;
	//kick
	Track[t].setEntry(0, 0, 0xFF);
	Track[t].setEntry(6, 0, 0xFF);
	Track[t].setEntry(10, 0, 0xFF);
	//snare
	Track[t].setEntry(4, 1, 0xFF);
	Track[t].setEntry(14, 1, 0xFF);
	//hats
	for(int i = 0; i < 16; i+=2)
	{
		Track[t].setEntry(i, 2, 0xFF);
	}
}
void init_track3()
{
	int t = 3;
	//kick
	Track[t].setEntry(0, 0, 0xFF);
	Track[t].setEntry(6, 0, 0xFF);
	//snare
	Track[t].setEntry(8, 1, 0xFF);
	Track[t].setEntry(12, 0, 0xFF);
	//hats
	for(int i = 0; i < 16; i+=2)
	{
		Track[t].setEntry(i, 2, 0xFF);
	}
}
void init_track4()
{
	int t = 4;
	//kick
	Track[t].setEntry(0, 0, 0xFF);
	Track[t].setEntry(10, 0, 0xFF);
	
	Track[t].setEntry(15, 0, 0xAA);
	Track[t].setEntry(15, 0, 0x55);
	//snare
	Track[t].setEntry(4, 1, 0xFF);
	Track[t].setEntry(12, 1, 0xFF);
	//hats
	for(int i = 0; i < 16; i+=4)
	{
		Track[t].setEntry(i, 5, 0xFF);
	}
}

void init_track5()
{
	int t = 5;
	//kick
	Track[t].setEntry(0, 0, 0xFF);
	Track[t].setEntry(2, 0, 0x55);
	Track[t].setEntry(3, 0, 0xAA);
	
	Track[t].setEntry(8, 0, 0x44);
	Track[t].setEntry(9, 0, 0x77);
	Track[t].setEntry(10, 0, 0xAA);
	Track[t].setEntry(11, 0, 0xFF);
	
	Track[t].setEntry(13, 0, 0xFF);
	Track[t].setEntry(15, 0, 0x55);
	//snare
	Track[t].setEntry(4, 1, 0xFF);
	Track[t].setEntry(12, 1, 0xFF);
	//rides
	for(int i = 0; i < 16; i+=4)
	{
		Track[t].setEntry(i, 5, 0xFF);
	}
	for(int i = 2; i < 16; i+=4)
	{
		Track[t].setEntry(i, 5, 0x77);
	}
}
void init_track6()
{
	int t = 6;
	//kick
	Track[t].setEntry(0, 0, 0xFF);
	
	
	Track[t].setEntry(10, 0, 0xFF);
	//snare
	Track[t].setEntry(4, 1, 0xFF);
	Track[t].setEntry(12, 1, 0xFF);
	//hats
	for(int i = 0; i < 16; i+=2)
	{
		Track[t].setEntry(i, 2, 0xFF);
	}
	for(int i = 1; i < 16; i+=2)
	{
		Track[t].setEntry(i, 2, 0x66);
	}
	Track[t].setEntry(7, 1, 0x66);
	Track[t].setEntry(9, 1, 0x66);
}
void init_track7()
{
	int t = 7;
	//kick
	Track[t].setEntry(0, 0, 0xFF);
	Track[t].setEntry(4, 0, 0xFF);
	Track[t].setEntry(8, 0, 0xFF);
	Track[t].setEntry(12, 0, 0xFF);
	//hats
	for(int i = 2; i < 16; i+=4)
	{
		Track[t].setEntry(i, 2, 0xFF);
	}
}
void init_track8()
{
	int t = 8;
	//kick
	Track[t].setEntry(0, 0, 0xFF);
	Track[t].setEntry(4, 0, 0xFF);
	Track[t].setEntry(8, 0, 0xFF);
	Track[t].setEntry(12, 0, 0xFF);
}
void init_track9()
{
	int t = 9;
	//kick
	Track[t].setEntry(0, 1, 1);
	Track[t].setEntry(1, 0, 1);
	Track[t].setEntry(2, 0, 1);
	Track[t].setEntry(4, 1, 1);
	Track[t].setEntry(6, 0, 1);
	Track[t].setEntry(7, 0, 1);
	Track[t].setEntry(8, 1, 1);
	Track[t].setEntry(10, 0, 1);
	Track[t].setEntry(12, 1, 1);
	Track[t].setEntry(13, 0, 1);
	Track[t].setEntry(15, 0, 1);
	//rides
	for(int i = 0; i < 16; i+=4)
	{
		Track[t].setEntry(i, 5, 1);
	}
}
void init_track10()
{
	int t = 10;
	//hats
	for(int i = 0; i < 16; i+=2)
	{
		Track[t].setEntry(i, 2, 0x55);
	}
	for(int i = 1; i < 16; i+=2)
	{
		Track[t].setEntry(i, 2, 0x33);
	}
}