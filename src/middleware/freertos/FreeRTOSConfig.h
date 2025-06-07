/*
 * FreeRTOS Kernel Configuration for LPC2292
 * Copyright (C) 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * SPDX-License-Identifier: MIT
 */

#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

#include "lpc2292.h"

/* LPC2292-specific timer definitions */
#define T0_PR  T0PR
#define T0_IR  T0IR
#define T0_MR0 T0MR0
#define T0_MCR T0MCR
#define T0_TCR T0TCR

/* Hardware-specific settings */
#define configCPU_CLOCK_HZ                    60000000UL
#define configTICK_RATE_HZ                    1000
#define configUSE_PREEMPTION                  1
#define configMAX_PRIORITIES                  5
#define configMINIMAL_STACK_SIZE              128
#define configTOTAL_HEAP_SIZE                 (1024 * 4)
#define configTICK_TYPE_WIDTH_IN_BITS         TICK_TYPE_WIDTH_32_BITS
#define configUSE_IDLE_HOOK                   0
#define configUSE_TICK_HOOK                   0
#define configKERNEL_PROVIDED_STATIC_MEMORY   1

/* Task behavior */
#define configUSE_TIME_SLICING                0
#define configIDLE_SHOULD_YIELD               1
#define configUSE_PORT_OPTIMISED_TASK_SELECTION 0

/* Memory management */
#define configSUPPORT_STATIC_ALLOCATION       1
#define configSUPPORT_DYNAMIC_ALLOCATION      1
#define configAPPLICATION_ALLOCATED_HEAP      1
#define configSTACK_ALLOCATION_FROM_SEPARATE_HEAP 0

/* Interrupt configuration */
#define configKERNEL_INTERRUPT_PRIORITY       0xFF
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 0x01
#define configMAX_API_CALL_INTERRUPT_PRIORITY configMAX_SYSCALL_INTERRUPT_PRIORITY

/* Features */
#define configUSE_TICKLESS_IDLE               0
#define configUSE_TIMERS                      1
#define configTIMER_TASK_PRIORITY             (configMAX_PRIORITIES - 1)
#define configTIMER_TASK_STACK_DEPTH          configMINIMAL_STACK_SIZE
#define configTIMER_QUEUE_LENGTH              5
#define configUSE_MUTEXES                     1
#define configUSE_RECURSIVE_MUTEXES           1
#define configUSE_COUNTING_SEMAPHORES         1
#define configUSE_TASK_NOTIFICATIONS          1
#define configUSE_EVENT_GROUPS                1
#define configUSE_STREAM_BUFFERS              1

/* Debugging */
#define configCHECK_FOR_STACK_OVERFLOW        2
#define configASSERT(x)                       if ((x) == 0) { taskDISABLE_INTERRUPTS(); for (;;); }

/* Optional features */
#define configUSE_TRACE_FACILITY              0
#define configUSE_STATS_FORMATTING_FUNCTIONS  0
#define configGENERATE_RUN_TIME_STATS         0
#define configUSE_CO_ROUTINES                 0
#define configUSE_QUEUE_SETS                  0
#define configUSE_APPLICATION_TASK_TAG        0

/* Include/exclude API functions */
#define INCLUDE_vTaskPrioritySet              1
#define INCLUDE_uxTaskPriorityGet             1
#define INCLUDE_vTaskDelete                   1
#define INCLUDE_vTaskSuspend                  1
#define INCLUDE_vTaskDelayUntil               1
#define INCLUDE_vTaskDelay                    1
#define INCLUDE_xTaskGetSchedulerState        1
#define INCLUDE_xTaskGetCurrentTaskHandle     1
#define INCLUDE_xTaskResumeFromISR            1

/* Disable features not relevant for LPC2292 */
#define configENABLE_MPU                      0
#define configENABLE_FPU                      0
#define configENABLE_TRUSTZONE                0
#define configENABLE_MVE                      0

#endif /* FREERTOS_CONFIG_H */