/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
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
 */

#include <zephyr.h>
#include <device.h>
#include <gpio.h>


void main(void)
{
	struct device *gpiob = device_get_binding("GPIOB");

	gpio_pin_configure(gpiob, 5, GPIO_DIR_OUT);
	gpio_pin_configure(gpiob, 0, GPIO_DIR_OUT);

	int cnt = 0;
	while (1) {
		gpio_pin_write(gpiob, 5, cnt % 2);
		gpio_pin_write(gpiob, 0, (cnt + 1) % 2);
		task_sleep(SECONDS(1));
		cnt++;
	}
}
