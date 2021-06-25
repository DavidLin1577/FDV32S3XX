/**
 * @file lib_include.h
 * @author David Lin
 * @brief
 * @version 0.1
 * @date 2021-05-17
 *
 * @copyright Fanhai Data Tech. (c) 2021
 *
 */

#ifndef __LIB_INCLUDE_H__
#define __LIB_INCLUDE_H__

// firmware include file
#include "../../FDV32S305/drivers/efc.h"
#include "../../FDV32S305/drivers/iom.h"
#include "../../FDV32S305/drivers/lptimer.h"
#include "../../FDV32S305/drivers/sysc.h"
#include "../../FDV32S305/drivers/timer.h"
#include "../../FDV32S305/drivers/uart.h"
#include "../../FDV32S305/drivers/wdt.h"
#include "../../FDV32S305/drivers/anac.h"
#include "../../FDV32S305/drivers/adc.h"

#ifdef _DEBUG
extern int __wrap_printf(const char *fmt, ...);
#define printf(...) __wrap_printf(__VA_ARGS__)
#else
#define printf(...)
#endif

#endif/*__LIB_INCLUDE_H__*/
