/*
 * Copyright [2016] [Riccardo Pozza]
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Authors:
 * Riccardo Pozza <r.pozza@surrey.ac.uk>
 */

#include "n25q.h"

int main(void) {
	//NB: comment out protected: in classes before trying test programs!

	//----- FIRST TEST PROGRAM - READ IDENTIFICATION ID STRING ------
	printf("----------------------- TEST PROGRAM - FLASH PROGRAM/ERASE ---------------------------\r\n");
	N25Q *flash = new N25Q();

	int ID_string[READ_ID_LEN];
	flash->ReadID(ID_string);

	int data[PAGE_SIZE];
	int i;

	flash->ReadDataFromAddress(data,0x000000,PAGE_SIZE);

	flash->SubSectorErase(0x000000);

	flash->ReadDataFromAddress(data,0x000000,PAGE_SIZE);


	for (i=0; i<PAGE_SIZE; i++){
		data[i] = i;
	}

	flash->ReadLockRegister(0x000000);

	flash->ProgramFromAddress(data, 0x000000, PAGE_SIZE);

	flash->ReadFlagStatusRegister();

	for (i=0; i<PAGE_SIZE; i++){
		data[i] = 0;
	}

	flash->ReadDataFromAddress(data,0x000000,PAGE_SIZE);

	flash->SectorErase(0x000000);

	flash->ReadDataFromAddress(data,0x000000,PAGE_SIZE);

	flash->BulkErase();

	printf("-------------------- END OF TEST PROGRAM - FLASH PROGRAM/ERASE  ----------------------\r\n");

}
