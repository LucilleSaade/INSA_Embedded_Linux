/*
 *  led.h - the header file with the ioctl definitions.
 *
 *  The declarations here have to be in a header file, because
 *  they need to be known both to the kernel module
 *  (in chardev.c) and the process calling ioctl (ioctl.c)
 */

#ifndef LEDDEV_H
#define LEDDEV_H

#include <linux/ioctl.h>

/* 
 * The major device number. We can't rely on dynamic 
 * registration any more, because ioctls need to know 
 * it. 
 */
#define MAJOR_NUM 101

#define IOCTL_GET_VALUE _IOR(MAJOR_NUM, 0, int)

#define IOCTL_SET_VALUE _IOW(MAJOR_NUM, 1, int)


/* 
 * The name of the device file 
 */
#define DEVICE_FILE_NAME "led_dev"

#endif
