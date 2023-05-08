/*
	M3 DS Real
	Card IO routines

	Copyright (C) 2023 lifehackerhansol

	SPDX-License-Identifier: Zlib
*/

#pragma once

#include <nds/ndstypes.h>
#include "iom3.h"

#ifndef NULL
 #define NULL 0
#endif

// M3 defines
// M3 MCCNT1 flags
#define IOM3_CTRL_BASE                MCCNT1_ENABLE | MCCNT1_RESET_OFF | MCCNT1_CMD_SCRAMBLE | MCCNT1_CLOCK_SCRAMBLER | MCCNT1_READ_DATA_DESCRAMBLE
#define IOM3_CTRL_GENERAL             IOM3_CTRL_BASE | MCCNT1_LATENCY2(24) | MCCNT1_LEN_4 | MCCNT1_LATENCY1(0)
#define IOM3_CTRL_SD_READ             IOM3_CTRL_BASE | MCCNT1_LATENCY2(24) | MCCNT1_LEN_512 | MCCNT1_LATENCY1(0)
#define IOM3_CTRL_SD_WRITE            IOM3_CTRL_BASE | MCCNT1_DIR_WRITE | MCCNT1_LATENCY2(24) | MCCNT1_LEN_512 | MCCNT1_LATENCY1(256)
#define IOM3_CTRL_SD_MULTI_SECTOR_END IOM3_CTRL_BASE | MCCNT1_LATENCY2(8) | MCCNT1_LEN_0 | MCCNT1_LATENCY1(256)

// M3 MCCMDs
#define IOM3_CMD_CARD_INFO                  (0xB0ull << 56)
#define IOM3_CMD_SD_MULTI_RW_END            (0xB3ull << 56)
#define IOM3_CMD_SD_READ_DATA               (0xBAull << 56)

static inline u64 IOM3_CMD_SD_MULTI_READ_REQUEST(u32 sector)
{
	return (0xB1ull << 56) | ((u64)sector << 24);
}

static inline u64 IOM3_CMD_SD_MULTI_READ_REQUEST_NEXT(u32 sector)
{
	return (0xB2ull << 56) | ((u64)sector << 24);
}

static inline u64 IOM3_CMD_SD_MULTI_WRITE_START(u32 sector)
{
	return (0xB4ull << 56) | ((u64)sector << 24);
}

static inline u64 IOM3_CMD_SD_MULTI_WRITE_START_NEXT(u32 sector)
{
	return (0xB5ull << 56) | ((u64)sector << 24);
}

static inline u64 IOM3_CMD_SD_MULTI_WRITE_STAT(u32 sector)
{
	return (0xB6ull << 56) | ((u64)sector << 24);
}

static inline u64 IOM3_CMD_SD_SINGLE_READ_REQUEST(u32 sector)
{
	return (0xBDull << 56) | ((u64)sector << 24);
}

static inline u64 IOM3_CMD_SD_SINGLE_WRITE_START(u32 sector)
{
	return (0xBEull << 56) | ((u64)sector << 24);
}

static inline u64 IOM3_CMD_SD_SINGLE_WRITE_STAT(u32 sector)
{
	return (0xBCull << 56) | ((u64)sector << 24);
}

// user API
u32 ioM3SendCommand(u64 command);
void ioM3SDReadSingleSector(u32 sector, void* buffer);
void ioM3SDReadMultiSector(u32 sector, void *buffer, u32 num_sectors);
void ioM3SDWriteSingleSector(u32 sector, const void* buffer);
void ioM3SDWriteMultiSector(u32 sector, const void *buffer, u32 num_sectors);

