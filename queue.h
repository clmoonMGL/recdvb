/*
 * recdvb - record tool for linux DVB driver.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef RECDVB_QUEUE_H
#define RECDVB_QUEUE_H

#include <stdint.h>
#include <stddef.h>
#include <pthread.h>

#define MAX_READ_SIZE           (188 * 87) // 188 * 87 = 16356

typedef struct _BUFSZ {
	ssize_t size;
	uint8_t buffer[MAX_READ_SIZE];
} BUFSZ;

typedef struct _QUEUE_T {
	unsigned int in;           // index for input
	unsigned int out;          // index for output
	size_t size;               // queue size
	size_t num_avail;          // when fill queue, set to zero.
	size_t num_used;           // when become empty, set to zero.
	pthread_mutex_t mutex;
	pthread_cond_t cond_avail; // cond for waiting when fill queue
	pthread_cond_t cond_used;  // cond for waiting when become empty queue
	BUFSZ *buffer[1];          // buffer pointer
} QUEUE_T;

QUEUE_T *create_queue(size_t size);
void destroy_queue(QUEUE_T *p_queue);
int enqueue(QUEUE_T *p_queue, BUFSZ *data);
int dequeue(QUEUE_T *p_queue, BUFSZ **data);

#endif

