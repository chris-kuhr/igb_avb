/*******************************************************************************

  Intel(R) Gigabit Ethernet Linux driver
  Copyright(c) 2007-2015 Intel Corporation.

  This program is free software; you can redistribute it and/or modify it
  under the terms and conditions of the GNU General Public License,
  version 2, as published by the Free Software Foundation.

  This program is distributed in the hope it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  The full GNU General Public License is included in this distribution in
  the file called "COPYING".

  Contact Information:
  Linux NICS <linux.nics@intel.com>
  e1000-devel Mailing List <e1000-devel@lists.sourceforge.net>
  Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497

*******************************************************************************/

/*
 * net/core/ethtool.c - Ethtool ioctl handler
 * Copyright (c) 2003 Matthew Wilcox <matthew@wil.cx>
 *
 * This file is where we call all the ethtool_ops commands to get
 * the information ethtool needs.  We fall back to calling do_ioctl()
 * for drivers which haven't been converted to ethtool_ops yet.
 *
 * It's GPL, stupid.
 *
 * Modification by sfeldma@pobox.com to work as backward compat
 * solution for pre-ethtool_ops kernels.
 * 	- copied struct ethtool_ops from ethtool.h
 * 	- defined SET_ETHTOOL_OPS
 * 	- put in some #ifndef NETIF_F_xxx wrappers
 * 	- changes refs to dev->ethtool_ops to ethtool_ops
 * 	- changed dev_ethtool to ethtool_ioctl
 *      - remove EXPORT_SYMBOL()s
 *      - added _kc_ prefix in built-in ethtool_op_xxx ops.
 */

#ifndef _KCOMPAT_ETHTOOL_H_
#define _KCOMPAT_ETHTOOL_H_

#include <linux/module.h>
#include <linux/types.h>
#include <linux/errno.h>
#include <linux/mii.h>
#include <linux/ethtool.h>
#include <linux/netdevice.h>
#include <asm/uaccess.h>

#include "kcompat.h"


#undef ethtool_ops
#define ethtool_ops _kc_ethtool_ops

struct _kc_ethtool_ops {
	int  (*get_settings)(struct net_device *, struct ethtool_cmd *);
	int  (*set_settings)(struct net_device *, struct ethtool_cmd *);
	void (*get_drvinfo)(struct net_device *, struct ethtool_drvinfo *);
	int  (*get_regs_len)(struct net_device *);
	void (*get_regs)(struct net_device *, struct ethtool_regs *, void *);
	void (*get_wol)(struct net_device *, struct ethtool_wolinfo *);
	int  (*set_wol)(struct net_device *, struct ethtool_wolinfo *);
	u32  (*get_msglevel)(struct net_device *);
	void (*set_msglevel)(struct net_device *, u32);
	int  (*nway_reset)(struct net_device *);
	u32  (*get_link)(struct net_device *);
	int  (*get_eeprom_len)(struct net_device *);
	int  (*get_eeprom)(struct net_device *, struct ethtool_eeprom *, u8 *);
	int  (*set_eeprom)(struct net_device *, struct ethtool_eeprom *, u8 *);
	int  (*get_coalesce)(struct net_device *, struct ethtool_coalesce *);
	int  (*set_coalesce)(struct net_device *, struct ethtool_coalesce *);
	void (*get_ringparam)(struct net_device *, struct ethtool_ringparam *);
	int  (*set_ringparam)(struct net_device *, struct ethtool_ringparam *);
	void (*get_pauseparam)(struct net_device *,
	                       struct ethtool_pauseparam*);
	int  (*set_pauseparam)(struct net_device *,
	                       struct ethtool_pauseparam*);
	u32  (*get_rx_csum)(struct net_device *);
	int  (*set_rx_csum)(struct net_device *, u32);
	u32  (*get_tx_csum)(struct net_device *);
	int  (*set_tx_csum)(struct net_device *, u32);
	u32  (*get_sg)(struct net_device *);
	int  (*set_sg)(struct net_device *, u32);
	u32  (*get_tso)(struct net_device *);
	int  (*set_tso)(struct net_device *, u32);
	int  (*self_test_count)(struct net_device *);
	void (*self_test)(struct net_device *, struct ethtool_test *, u64 *);
	void (*get_strings)(struct net_device *, u32 stringset, u8 *);
	int  (*phys_id)(struct net_device *, u32);
	int  (*get_stats_count)(struct net_device *);
	void (*get_ethtool_stats)(struct net_device *, struct ethtool_stats *,
	                          u64 *);
} *ethtool_ops = NULL;

#undef SET_ETHTOOL_OPS
#define SET_ETHTOOL_OPS(netdev, ops) (ethtool_ops = (ops))

#endif /* _KCOMPAT_ETHTOOL_H_ */
