/*
 * CircularBuffer.c
 *
 *  Created on: Feb 2, 2021
 *      Author: alexk
 */

#include "CircularBuffer.h"

void initBuffer(commBuffer_t* comm, uint8_t Type) {
	comm->type = Type;
	comm->head = 0;
	comm->tail = 0;
	comm->MessageCount = 0;
	comm->buffer[0] = 0;
	comm->bufferSize = 0;
	comm->fullFlag = 0;
}

uint8_t haveMessage(commBuffer_t* comm) {
	return comm->MessageCount;
}

void putChar(commBuffer_t* comm, char ch) {
	if (comm->fullFlag == 0) {
		if ((comm->head < MAX_BUFFER_SIZE)) {
			comm->buffer[comm->head] = ch;
			comm->head++;
			if (ch == '\n' || ch == '\0') { comm->MessageCount++; }
		}
		if (comm->head == MAX_BUFFER_SIZE) {
			comm->buffer[comm->head] = '\n';
			ch = '\n';
			comm->fullFlag = 1;
		}
		if ((ch == '\n' || ch == '\0') && (comm->fullFlag)) {
			comm->MessageCount++;
			comm->fullFlag = 0;
			return;
		}
	}
}

char getChar(commBuffer_t* comm) {
	char ch = comm->buffer[comm->tail];
	comm->tail++;
	if (ch == '\n' || ch == '\0') {
		comm->fullFlag = 0;
		comm->MessageCount--;
	}
	if (comm->tail == comm->head) {
		if (comm->tail == MAX_BUFFER_SIZE) { ch = '\n'; }
		comm->tail = 0;
		comm->head = 0;
	}
	return ch;
}

void putMessage(commBuffer_t* comm, char* str, uint8_t length) { // length here contains the delimiter, '\n', starting at index 1
	for (int i=0; i < length+1; i++) {
		putChar(comm, str[i]);
	}
}

void getMessage(commBuffer_t* comm, char* str) {
	uint32_t bufferSize = getBufferSize(comm);
	if (bufferSize != 0) {
		for (int i=0; i < bufferSize; i++) {
			str[i] = getChar(comm);
		}
	}
	if (bufferSize == 0) {
		if (comm->head == MAX_BUFFER_SIZE) {
			for (int i=0; i < MAX_BUFFER_SIZE; i++) {
				str[i] = getChar(comm);
			}
		}
	}
}

int getBufferSize(commBuffer_t* comm) {
	comm->bufferSize = (comm->head - comm->tail + MAX_BUFFER_SIZE) % MAX_BUFFER_SIZE;
	return (comm->bufferSize);
}

