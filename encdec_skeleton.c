#include <linux/ctype.h>
#include <linux/config.h>
#include <linux/module.h>
#include <linux/kernel.h>  	
#include <linux/slab.h>
#include <linux/fs.h>       		
#include <linux/errno.h>  
#include <linux/types.h> 
#include <linux/proc_fs.h>
#include <linux/fcntl.h>
#include <asm/system.h>
#include <asm/uaccess.h>
#include <linux/string.h>

#include "encdec.h"

#define MODULE_NAME "encdec"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("YOUR NAME");

int 	encdec_open(struct inode *inode, struct file *filp);
int 	encdec_release(struct inode *inode, struct file *filp);
int 	encdec_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg);

ssize_t encdec_read_caesar( struct file *filp, char *buf, size_t count, loff_t *f_pos );
ssize_t encdec_write_caesar(struct file *filp, const char *buf, size_t count, loff_t *f_pos);

ssize_t encdec_read_xor( struct file *filp, char *buf, size_t count, loff_t *f_pos );
ssize_t encdec_write_xor(struct file *filp, const char *buf, size_t count, loff_t *f_pos);

int memory_size = 0;

MODULE_PARM(memory_size, "i");

int major = 0;

struct file_operations fops_caesar = {
	.open 	 =	encdec_open,
	.release =	encdec_release,
	.read 	 =	encdec_read_caesar,
	.write 	 =	encdec_write_caesar,
	.llseek  =	NULL,
	.ioctl 	 =	encdec_ioctl,
	.owner 	 =	THIS_MODULE
};

struct file_operations fops_xor = {
	.open 	 =	encdec_open,
	.release =	encdec_release,
	.read 	 =	encdec_read_xor,
	.write 	 =	encdec_write_xor,
	.llseek  =	NULL,
	.ioctl 	 =	encdec_ioctl,
	.owner 	 =	THIS_MODULE
};

// Implemetation suggestion:
// -------------------------
// Use this structure as your file-object's private data structure
typedef struct {
	unsigned char key;
	int read_state;
} encdec_private_date;

typedef struct private_data *privatePointer;

char *caesarBuffer = NULL;
char *xorBuffer = NULL;

int init_module(void)
{
	major = register_chrdev(major, MODULE_NAME, &fops_caesar);
	if(major < 0)
	{	
		return major;
	}

	// Implemetation suggestion:
	// -------------------------
	// 1. Allocate memory for the two device buffers using kmalloc (each of them should be of size 'memory_size')
	caesarBuffer = (char *)kmalloc(memory_size * sizeof(char), GFP_KERNEL);
	xorBuffer = (char *)kmalloc(memory_size * sizeof(char), GFP_KERNEL);

	if (caesarBuffer==NULL || xorBuffer==NULL) 
		return -1;

	return 0;
}

void cleanup_module(void)
{
	// Implemetation suggestion:
	// -------------------------	
	// 1. Unregister the device-driver
	// 2. Free the allocated device buffers using kfree
	unregister_chrdev(major, MODULE_NAME);
	kfree(caesarBuffer);
	kfree(xorBuffer);
}

int encdec_open(struct inode *inode, struct file *filp){

	int minor = MINOR(inode->i_rdev);
	

	// Implemetation suggestion:
	// -------------------------
	// 1. Set 'filp->f_op' to the correct file-operations structure (use the minor value to determine which)
	// 2. Allocate memory for 'filp->private_data' as needed (using kmalloc)
	filp->private_data = allocatePrivateData(); 

	if (!(filp->private_data))
		return -1; 

	if(minor==0){
		filp->f_op = &fops_caesar;
	}

	else if(minor==1){
		filp->f_op = &fops_xor;
	}

	else{
		return -ENODEV;
	}

	return 0;
}

int encdec_release(struct inode *inode, struct file *filp)
{
	// Implemetation suggestion:
	// -------------------------
	// 1. Free the allocated memory for 'filp->private_data' (using kfree)
	kfree(filp->private_data); 
	return 0;
}

int encdec_ioctl(struct inode *inode, struct file *filp, unsigned int cmd, unsigned long arg)
{
	// Implemetation suggestion:
	// -------------------------
	// 1. Update the relevant fields in 'filp->private_data' according to the values of 'cmd' and 'arg'
	int minor = -1;
	char *buffer = NULL;
	privatePointer tempPointer =(privatePointer)filp->private_data ;
	
	if(cmd==ENCDEC_CMD_CHANGE_KEY)
		tempPointer->key = arg;
	else if(ENCDEC_CMD_SET_READ_STATE)
		tempPointer->read_state = arg;
	else if(ENCDEC_CMD_ZERO){
		minor = MINOR(inode->i_rdev);

		if (minor == 0)		
			buffer = caesarBuffer; 

		else if (minor == 1) 
			buffer = xorBuffer; 

		else
			return -ENODEV;

		memset(buff, arg, memory_size);
	}
	else{
		return -EINVAL;
	}

	return 0;
}

// Add implementations for:
// ------------------------
// 1. ssize_t encdec_read_caesar( struct file *filp, char *buf, size_t count, loff_t *f_pos );
ssize_t encdec_read_caesar(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	int i, failure = 0;
	int available = memory_size - *f_pos; 
	privatePointer tempPointer = (privatePointer)filp->private_data;;

	if (*f_pos == memory_size) //Error return when trying to read from the end of the buffer.
		return -EINVAL;

	if (count > available) //If the size for reading is greater than the size of the free space in the buffer then read to the end of the buffer.
		count = available;

	if (temp->read_state == ENCDEC_READ_STATE_RAW)					  
		failure = copy_to_user(buf, caesarBuffer + (*f_pos), count); 

	if (temp->read_state == ENCDEC_READ_STATE_DECRYPT){ 
		failure = copy_to_user(buf, caesarBuffer + (*f_pos), count); 
		for (i = 0; i < count; i++)
			buf[i] = ((buf[i] - tempPointer->key) + 128) % 128;
	}

	*f_pos = *f_pos + count; 
	return count - failure; 
}
// 2. ssize_t encdec_write_caesar(struct file *filp, const char *buf, size_t count, loff_t *f_pos);
ssize_t encdec_write_caesar(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
	int i = 0, position = (int)*f_pos, failure = 0;
	privatePointer tempPointer = filp->private_data;

	if (position + count <= memory_size){ 
		failure = copy_from_user(caesarBuffer + position, buf, count * sizeof(char));
		for (i = position; i < position + count; i++){
			caesar_buff[i] = (caesar_buff[i] + tempPointer->key) % 128;
		}
		*f_pos = *f_pos + count; 
	}

	else{
		return -ENOSPC;
	} 
	
	return count - failure; 
}
// 3. ssize_t encdec_read_xor( struct file *filp, char *buf, size_t count, loff_t *f_pos );
ssize_t encdec_read_xor(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	/*Internal variables*/
	int i = 0, failure = 0;
	int available = memory_size - *f_pos; //Preserves the value of the remaining free space in the buffer.

	/*Pointer to private_data data structure*/
	privatePointer tempPointer;
	tempPointer = (privatePointer)filp->private_data;

	if (*f_pos == memory_size) //Error return when trying to read from the end of the buffer.
		return -EINVAL;

	if (count > available) 
		count = available;

	if (tempPointer->read_state == ENCDEC_READ_STATE_RAW)				
		failure = copy_to_user(buf, xorBuffer + (*f_pos), count); 

	if (tempPointer->read_state == ENCDEC_READ_STATE_DECRYPT){
		failure = copy_to_user(buf, xorBuffer + (*f_pos), count); 
		for (i = 0; i < count; i++){
			buf[i] = buf[i] ^ tempPointer->key;
		}	
	}

	*f_pos = *f_pos + count;
	return count - failure;
}

// 4. ssize_t encdec_write_xor(struct file *filp, const char *buf, size_t count, loff_t *f_pos);
ssize_t encdec_write_xor(struct file *filp, const char *buf, size_t count, loff_t *f_pos){
	int i = 0, posirion = (int)*f_pos, failure = 0;
	privatePointer tempPointer = filp->private_data;

	if (posirion + count <= memory_size){
		failure = copy_from_user(xorBuffer + posirion, buf, count * sizeof(char)); 
		for (i = posirion; i < posirion + count; i++){
			xor_buff[i] = (xor_buff[i] ^ temp->key);
		}	
		*f_pos = *f_pos + count; 
	}
	else{
		return -ENOSPC;
	}
	return count - failure; 
}

privatePointer allocatePrivateData(){
	privatePointer new = (privatePointer)kmalloc(sizeof(encdec_private_date), GFP_KERNEL);
	if (new==NULL)
		return NULL;
	new->key = 0;
	new->read_state = 0;
	return new;
}