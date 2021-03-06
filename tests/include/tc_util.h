/* tc_utilities.h - testcase utilities header file */

/*
 * Copyright (c) 2012-2015 Wind River Systems, Inc.
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

#ifndef __TC_UTIL_H__
#define __TC_UTIL_H__

#include <zephyr.h>

#include <misc/printk.h>
#include <string.h>

#define PRINT_DATA(fmt, ...) printk(fmt, ##__VA_ARGS__)

/**
 * @def TC_PRINT_RUN_ID
 * @brief Report a Run ID
 *
 * When the CPP symbol \c TC_RUNID is defined (for example, from the
 * compile environment), print the defined string ``RunID:
 * <TC_RUNID>`` when called (TC_END_REPORT() will also call it).
 *
 * This is used mainly when automating the execution and running of
 * multiple test cases, to verify that the expected image is being
 * executed (as sometimes the targets fail to flash or reset
 * properly).
 *
 * TC_RUNID is any string, that will be converted to a string literal.
 */
#define __str(x) #x
#define _str(x) __str(x)
#ifdef TC_RUNID
#define TC_PRINT_RUNID PRINT_DATA("RunID: " _str(TC_RUNID) "\n")
#else
#define TC_PRINT_RUNID do {} while (0)
#endif

#define PRINT_LINE							\
	PRINT_DATA(                                                        \
		"============================================================" \
		"=======\n")

/* stack size and priority for test suite task */
#define TASK_STACK_SIZE (1024 * 2)

#define FAIL "FAIL"
#define PASS "PASS"
#define FMT_ERROR "%s - %s@%d. "

#define TC_PASS 0
#define TC_FAIL 1

#define TC_ERROR(fmt, ...)                               \
	do {                                                 \
		PRINT_DATA(FMT_ERROR, FAIL, __func__, __LINE__); \
		PRINT_DATA(fmt, ##__VA_ARGS__);                  \
	} while (0)

#define TC_PRINT(fmt, ...) PRINT_DATA(fmt, ##__VA_ARGS__)
#define TC_START(name) PRINT_DATA("tc_start() - %s\n", name)
#define TC_END(result, fmt, ...) PRINT_DATA(fmt, ##__VA_ARGS__)

/* prints result and the function name */
#define TC_END_RESULT(result)                           \
	do {                                                \
		PRINT_LINE;                                     \
		TC_END(result, "%s - %s.\n",                    \
			result == TC_PASS ? PASS : FAIL, __func__); \
	} while (0)

#define TC_END_REPORT(result)                               \
	do {                                                    \
		PRINT_LINE;                                         \
		TC_PRINT_RUNID;                                         \
		TC_END(result,                                      \
			"PROJECT EXECUTION %s\n",               \
			result == TC_PASS ? "SUCCESSFUL" : "FAILED");   \
	} while (0)

#endif /* __TC_UTIL_H__ */
