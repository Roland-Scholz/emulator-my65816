/*
 * Kestrel 2 Baseline Emulator
 * Release 1p1
 *
 * Copyright (c) 2006 Samuel A. Falvo II
 * All Rights Reserved
 */

#include <stdio.h>
#include <lib65816/cpu.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <SDL.h>

byte *ram = NULL;

/* The Kestrel 2 will use the Xess series of FPGA developer toolkits,
 * which comes standard with 32MB of SDRAM.  However, in the emulator,
 * the CPU can only see the first 16MB, because I have not yet
 * implemented the MMU for the CPU yet.
 */

#define MEMSIZE     (16*1048576L)

int
ram_initialize( void )
{
	char* filename = "rtest.a";
	char* myosName = "..\\atari-my65816\\release\\obj\\myos_01.a";

	FILE *f;

	if (ram == NULL) {
	    ram = (byte *)( malloc( MEMSIZE ) );
	}

    if( !ram ) goto no_memory;
    //memset(ram, 0x00 , MEMSIZE);

    /*
    for(i = 0x00; i < 0x100; i++) {
    	ram[0xb000+i] = (byte) i;
    } */


    f = fopen(filename, "rb");
    if (f != NULL) {
    	printf("%s read: %d\n", filename, fread(&(ram[0x0000]), 1, 128*1024, f));
    	fclose(f);
    }

	f = fopen(myosName, "rb");
    if (f != NULL) {
    	printf("%s read: %d\n", myosName, fread(&(ram[0xC000]), 1, 8*1024, f));
    	fclose(f);
    }

    return 1;

no_memory:
    fprintf( stderr, "Not enough ram for RAM emulation\n" );
    return 0;
}

void
ram_expunge( void )
{
    if( ram )    free( ram );
    ram = 0;
}

byte
ram_read( word32 address, word32 unusedTimestamp )
{
	/*
	if ( (address >= 0xB800 && address < 0xFFFF) || (address >= 0x800000 && address < 0xFFB000) ) {
		SDL_Log("RAM read access @ %04X P: %02X:%04X\n", (unsigned int)address, PC.B.PB, PC.W.PC);
		//exit(0);
	} */

    return (byte)( ram[ address ] );
}

void
ram_write( word32 address, byte b, word32 timestamp )
{
/*
	if (address == 0x2B4E8 && address < 0xFFFF) {
		SDL_Log("RAM write access @%08X PC: %02X:%04X\n", (unsigned int)address, PC.B.PB, PC.W.PC);
		getchar();
		//exit(0);
	}
*/
    ram[address] = b;
}

