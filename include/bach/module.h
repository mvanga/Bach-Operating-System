#ifndef BACH_MODULE_H
#define BACH_MODULE_H

typedef int (*initcall_t)(void);
typedef void (*exitcall_t)(void);

#define driver_init(x) \
	static initcall_t __initcall_##x __driver_init_call = x;
#define driver_exit(x) \
	static exitcall_t __exitcall_##x __driver_exit_call = x;

#define __driver_init_call \
	__attribute__ ((__used__)) \
	__attribute__ ((__section__(".initcall0.init")))
#define __driver_exit_call \
	__attribute__ ((__used__)) \
	__attribute__ ((__section__(".exitcall0.exit")))

#endif
