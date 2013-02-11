/* drivers/misc/zerojpegcompression.c
 *
 * Copyright 2012  Stefano Gottardo (alias CastagnaIT)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/module.h>
#include <linux/kobject.h>
#include <linux/sysfs.h>
#include <linux/kernel.h> /* printk() */
#include <linux/zerojpegcompression.h>

int zero_jpeg_compression;

/* sysfs interface */
static ssize_t zero_jpeg_compression_show(struct kobject *kobj, struct kobj_attribute *attr, char *buf)
{
return sprintf(buf, "%d\n", zero_jpeg_compression);
}

static ssize_t zero_jpeg_compression_store(struct kobject *kobj, struct kobj_attribute *attr, const char *buf, size_t count)
{
sscanf(buf, "%du", &zero_jpeg_compression);
return count;
}

static struct kobj_attribute zero_jpeg_compression_attribute =
__ATTR(zero_jpeg_compression, 0666, zero_jpeg_compression_show, zero_jpeg_compression_store);

static struct attribute *attrs[] = {
&zero_jpeg_compression_attribute.attr,
NULL,
};

static struct attribute_group attr_group = {
.attrs = attrs,
};

static struct kobject *zero_jpeg_compression_kobj;

int zero_jpeg_compression_init(void)
{
	int retval;

	zero_jpeg_compression = 1;

        zero_jpeg_compression_kobj = kobject_create_and_add("jpeg_compression", kernel_kobj);
        if (!zero_jpeg_compression_kobj) {
                return -ENOMEM;
        }
        retval = sysfs_create_group(zero_jpeg_compression_kobj, &attr_group);
        if (retval)
                kobject_put(zero_jpeg_compression_kobj);
        return retval;
}
/* end sysfs interface */

void zero_jpeg_compression_exit(void)
{
	kobject_put(zero_jpeg_compression_kobj);
}

module_init(zero_jpeg_compression_init);
module_exit(zero_jpeg_compression_exit);

