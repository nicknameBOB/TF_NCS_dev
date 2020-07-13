
/* auto-generated by gen_syscalls.py, don't edit */
#ifndef Z_INCLUDE_SYSCALLS_NET_IF_H
#define Z_INCLUDE_SYSCALLS_NET_IF_H


#ifndef _ASMLANGUAGE

#include <syscall_list.h>
#include <syscall.h>

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic push
#endif

#ifdef __GNUC__
#pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif

#ifdef __cplusplus
extern "C" {
#endif

extern int z_impl_net_if_ipv6_addr_lookup_by_index(const struct in6_addr * addr);
static inline int net_if_ipv6_addr_lookup_by_index(const struct in6_addr * addr)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke1(*(uintptr_t *)&addr, K_SYSCALL_NET_IF_IPV6_ADDR_LOOKUP_BY_INDEX);
	}
#endif
	compiler_barrier();
	return z_impl_net_if_ipv6_addr_lookup_by_index(addr);
}


extern bool z_impl_net_if_ipv6_addr_add_by_index(int index, struct in6_addr * addr, enum net_addr_type addr_type, u32_t vlifetime);
static inline bool net_if_ipv6_addr_add_by_index(int index, struct in6_addr * addr, enum net_addr_type addr_type, u32_t vlifetime)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (bool) arch_syscall_invoke4(*(uintptr_t *)&index, *(uintptr_t *)&addr, *(uintptr_t *)&addr_type, *(uintptr_t *)&vlifetime, K_SYSCALL_NET_IF_IPV6_ADDR_ADD_BY_INDEX);
	}
#endif
	compiler_barrier();
	return z_impl_net_if_ipv6_addr_add_by_index(index, addr, addr_type, vlifetime);
}


extern bool z_impl_net_if_ipv6_addr_rm_by_index(int index, const struct in6_addr * addr);
static inline bool net_if_ipv6_addr_rm_by_index(int index, const struct in6_addr * addr)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (bool) arch_syscall_invoke2(*(uintptr_t *)&index, *(uintptr_t *)&addr, K_SYSCALL_NET_IF_IPV6_ADDR_RM_BY_INDEX);
	}
#endif
	compiler_barrier();
	return z_impl_net_if_ipv6_addr_rm_by_index(index, addr);
}


extern int z_impl_net_if_ipv4_addr_lookup_by_index(const struct in_addr * addr);
static inline int net_if_ipv4_addr_lookup_by_index(const struct in_addr * addr)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (int) arch_syscall_invoke1(*(uintptr_t *)&addr, K_SYSCALL_NET_IF_IPV4_ADDR_LOOKUP_BY_INDEX);
	}
#endif
	compiler_barrier();
	return z_impl_net_if_ipv4_addr_lookup_by_index(addr);
}


extern bool z_impl_net_if_ipv4_addr_add_by_index(int index, struct in_addr * addr, enum net_addr_type addr_type, u32_t vlifetime);
static inline bool net_if_ipv4_addr_add_by_index(int index, struct in_addr * addr, enum net_addr_type addr_type, u32_t vlifetime)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (bool) arch_syscall_invoke4(*(uintptr_t *)&index, *(uintptr_t *)&addr, *(uintptr_t *)&addr_type, *(uintptr_t *)&vlifetime, K_SYSCALL_NET_IF_IPV4_ADDR_ADD_BY_INDEX);
	}
#endif
	compiler_barrier();
	return z_impl_net_if_ipv4_addr_add_by_index(index, addr, addr_type, vlifetime);
}


extern bool z_impl_net_if_ipv4_addr_rm_by_index(int index, const struct in_addr * addr);
static inline bool net_if_ipv4_addr_rm_by_index(int index, const struct in_addr * addr)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (bool) arch_syscall_invoke2(*(uintptr_t *)&index, *(uintptr_t *)&addr, K_SYSCALL_NET_IF_IPV4_ADDR_RM_BY_INDEX);
	}
#endif
	compiler_barrier();
	return z_impl_net_if_ipv4_addr_rm_by_index(index, addr);
}


extern bool z_impl_net_if_ipv4_set_netmask_by_index(int index, const struct in_addr * netmask);
static inline bool net_if_ipv4_set_netmask_by_index(int index, const struct in_addr * netmask)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (bool) arch_syscall_invoke2(*(uintptr_t *)&index, *(uintptr_t *)&netmask, K_SYSCALL_NET_IF_IPV4_SET_NETMASK_BY_INDEX);
	}
#endif
	compiler_barrier();
	return z_impl_net_if_ipv4_set_netmask_by_index(index, netmask);
}


extern bool z_impl_net_if_ipv4_set_gw_by_index(int index, const struct in_addr * gw);
static inline bool net_if_ipv4_set_gw_by_index(int index, const struct in_addr * gw)
{
#ifdef CONFIG_USERSPACE
	if (z_syscall_trap()) {
		return (bool) arch_syscall_invoke2(*(uintptr_t *)&index, *(uintptr_t *)&gw, K_SYSCALL_NET_IF_IPV4_SET_GW_BY_INDEX);
	}
#endif
	compiler_barrier();
	return z_impl_net_if_ipv4_set_gw_by_index(index, gw);
}


#ifdef __cplusplus
}
#endif

#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 6)
#pragma GCC diagnostic pop
#endif

#endif
#endif /* include guard */
