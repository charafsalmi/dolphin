// Copyright 2013 Dolphin Emulator Project
// Licensed under GPLv2
// Refer to the license.txt file included.

#pragma once

#include <deque>
#include <queue>

#include "Core/HW/EXI_Device.h"

class CEXIAgp
	: public IEXIDevice
{
public:
	CEXIAgp(const int index);
	virtual ~CEXIAgp() override;
	bool IsPresent() override { return true; }
	void ImmWrite(u32 _uData, u32 _uSize) override;
	u32  ImmRead(u32 _uSize) override;
	void DoState(PointerWrap &p) override;

private:
	enum
	{
		EE_READ   = 0x80
	};

	int m_slot;

	//! ROM
	u32 m_rom_size = 0;
	u32 m_rom_mask = 0;
	u32 m_eeprom_size = 0;
	u32 m_eeprom_mask = 0;
	std::vector<u8> m_rom;
	std::vector<u8> m_eeprom;

	//! Helper
	u32 m_position = 0;
	u32 m_address = 0;
	u32 m_rw_offset = 0;
	u64 m_eeprom_data = 0;
	u8  m_eeprom_pos = 0;
	u16 m_eeprom_cmd = 0;

	void LoadFileToROM(const std::string& filename);
	void LoadFileToEEPROM(const std::string& filename);
	void SaveFileFromEEPROM(const std::string& filename);
	void LoadRom();
	void CRC8(u8* data, u32 size);

	u8 m_hash = 0;
	u32 m_current_cmd = 0;
	u32 m_return_pos = 0;
};
