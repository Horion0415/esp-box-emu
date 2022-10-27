/**
 * @file lv_port_fs.c
 * @brief LVGL file system support
 * @version 0.1
 * @date 2021-03-20
 * 
 * @copyright Copyright 2021 Espressif Systems (Shanghai) Co. Ltd.
 *
 *      Licensed under the Apache License, Version 2.0 (the "License");
 *      you may not use this file except in compliance with the License.
 *      You may obtain a copy of the License at
 *
 *               http://www.apache.org/licenses/LICENSE-2.0
 *
 *      Unless required by applicable law or agreed to in writing, software
 *      distributed under the License is distributed on an "AS IS" BASIS,
 *      WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *      See the License for the specific language governing permissions and
 *      limitations under the License.
 */

#if 1

/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include <dirent.h>
#include <unistd.h>

#include "lv_port_fs.h"

#include "esp_err.h"
#include "esp_log.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/* Create a type to store the required data about your file.
 * If you are using a File System library
 * it already should have a File type.
 * For example FatFS has `FIL`. In this case use `typedef FIL file_t`*/
typedef  FILE * file_t;

/*Similarly to `file_t` create a type for directory reading too */
typedef  DIR * dir_t;


/**********************
 *  STATIC PROTOTYPES
 **********************/
static void fs_init(void);

static const char *TAG = "lv_fs";

static void * fs_open (lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode);
static lv_fs_res_t fs_close (lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_read (lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br);
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw);
static lv_fs_res_t fs_seek (lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence);
static lv_fs_res_t fs_size (lv_fs_drv_t * drv, void * file_p, uint32_t * size_p);
static lv_fs_res_t fs_tell (lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p);
static lv_fs_res_t fs_remove (lv_fs_drv_t * drv, const char *path);
static lv_fs_res_t fs_trunc (lv_fs_drv_t * drv, void * file_p);
static lv_fs_res_t fs_rename (lv_fs_drv_t * drv, const char * oldname, const char * newname);
static lv_fs_res_t fs_free (lv_fs_drv_t * drv, uint32_t * total_p, uint32_t * free_p);
static void * fs_dir_open (lv_fs_drv_t * drv, const char *path);
static lv_fs_res_t fs_dir_read (lv_fs_drv_t * drv, void * rddir_p, char *fn);
static lv_fs_res_t fs_dir_close (lv_fs_drv_t * drv, void * rddir_p);

/**********************
 *  STATIC VARIABLES
 **********************/
static esp_err_t lv_fs_init_result = LV_FS_RES_HW_ERR;
static char f_path[256];
/**********************
 * GLOBAL PROTOTYPES
 **********************/

/**********************
 *      MACROS
 **********************/
#define LV_FS_PATH_PREFIX   "/littlefs"

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
esp_err_t lv_port_fs_init(void)
{
    fs_init();

    return ESP_OK;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/* Initialize your Storage device and File system. */
static void fs_init(void)
{
	/*---------------------------------------------------
	 * Register the file system interface  in LittlevGL
	 *--------------------------------------------------*/

	/* Add a simple drive to open images */
	static lv_fs_drv_t fs_drv;                         /*A driver descriptor*/
	lv_fs_drv_init(&fs_drv);

    /*Set up fields...*/
	fs_drv.letter = CONFIG_LV_FS_POSIX_LETTER;
	fs_drv.open_cb = fs_open;
	fs_drv.close_cb = fs_close;
	fs_drv.read_cb = fs_read;
	fs_drv.write_cb = fs_write;
	fs_drv.seek_cb = fs_seek;
	fs_drv.tell_cb = fs_tell;

	fs_drv.dir_close_cb = fs_dir_close;
	fs_drv.dir_open_cb = fs_dir_open;
	fs_drv.dir_read_cb = fs_dir_read;

	lv_fs_drv_register(&fs_drv);
}

/**
 * Open a file
 * @param drv pointer to a driver where this function belongs
 * @param path path to the file beginning with the driver letter (e.g. S:/folder/file.txt)
 * @param mode read: FS_MODE_RD, write: FS_MODE_WR, both: FS_MODE_RD | FS_MODE_WR
 * @return file pointer to the opened file.
 */
static void *fs_open (lv_fs_drv_t * drv, const char * path, lv_fs_mode_t mode)
{
    const char * flags = "";

    if(mode == LV_FS_MODE_WR) flags = "wb";
	else if(mode == LV_FS_MODE_RD) flags = "rb";
	else if(mode == (LV_FS_MODE_WR | LV_FS_MODE_RD)) flags = "rb+";


    sprintf(f_path, LV_FS_PATH_PREFIX "/%s", path);
    
    file_t f = fopen(f_path, flags);

    if (NULL == f) {
        return NULL;
    }

    fseek(f, 0, SEEK_SET);

    int * fp = lv_mem_alloc(sizeof(int));
    if(fp == NULL) return NULL;
    *fp = f;

    return fp;
}


/**
 * Close an opened file
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable. (opened with lv_ufs_open)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_close (lv_fs_drv_t * drv, void * file_p)
{
    (void) drv;		/*Unused*/
	file_t * fp = file_p;        /*Just avoid the confusing casings*/

    if (NULL == fp) {
        ESP_LOGE(TAG, "NULL file pointer");
        return LV_FS_RES_NOT_EX;
    }

    if (EOF == fclose(* fp)) {
        lv_mem_free(file_p);
        ESP_LOGE(TAG, "Failed close file pointer");
        return LV_FS_RES_NOT_EX;
    }

    lv_mem_free(file_p);
    return LV_FS_RES_OK;
}

/**
 * Read data from an opened file
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable.
 * @param buf pointer to a memory block where to store the read data
 * @param btr number of Bytes To Read
 * @param br the real number of read bytes (Byte Read)
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_read (lv_fs_drv_t * drv, void * file_p, void * buf, uint32_t btr, uint32_t * br)
{
    (void) drv;		/*Unused*/
    file_t * fp = file_p;        /*Just avoid the confusing casings*/
	*br = fread(buf, 1, btr, *fp);
    return LV_FS_RES_OK;
}

/**
 * Write into a file
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable
 * @param buf pointer to a buffer with the bytes to write
 * @param btr Bytes To Write
 * @param br the number of real written bytes (Bytes Written). NULL if unused.
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_write(lv_fs_drv_t * drv, void * file_p, const void * buf, uint32_t btw, uint32_t * bw)
{
    (void) drv;		/*Unused*/
    file_t * fp = file_p;        /*Just avoid the confusing casings*/
	*bw = fwrite(buf, 1, btw, *fp);
    return LV_FS_RES_OK;
}

/**
 * Set the read write pointer. Also expand the file size if necessary.
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable. (opened with lv_ufs_open )
 * @param pos the new position of read write pointer
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_seek (lv_fs_drv_t * drv, void * file_p, uint32_t pos, lv_fs_whence_t whence)
{
    (void) drv;     /*Unused*/
	file_t * fp = file_p;        /*Just avoid the confusing casings*/
    // int * fp = file_p;
    // lseek(*fp, pos, whence);
    fseek(*fp, pos, whence);
    return LV_FS_RES_OK;
}

/**
 * Give the size of a file bytes
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable
 * @param size pointer to a variable to store the size
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_size (lv_fs_drv_t * drv, void * file_p, uint32_t * size_p)
{
    (void) drv;		/*Unused*/

    file_t * fp = file_p;        /*Just avoid the confusing casings*/
    
    uint32_t cur = ftell(*fp);

	fseek(*fp, 0L, SEEK_END);
	*size_p = ftell(*fp);

	/*Restore file pointer*/
	fseek(*fp, cur, SEEK_SET);

    return LV_FS_RES_OK;
}
/**
 * Give the position of the read write pointer
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to a file_t variable.
 * @param pos_p pointer to to store the result
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_tell (lv_fs_drv_t * drv, void * file_p, uint32_t * pos_p)
{
    (void) drv;		/*Unused*/

    file_t * fp = file_p;        /*Just avoid the confusing casings*/
	*pos_p = ftell(*fp);

    return LV_FS_RES_OK;
}

/**
 * Delete a file
 * @param drv pointer to a driver where this function belongs
 * @param path path of the file to delete
 * @return  LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_remove (lv_fs_drv_t * drv, const char *path)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /* Add your code here*/

    return res;
}

/**
 * Truncate the file size to the current position of the read write pointer
 * @param drv pointer to a driver where this function belongs
 * @param file_p pointer to an 'ufs_file_t' variable. (opened with lv_fs_open )
 * @return LV_FS_RES_OK: no error, the file is read
 *         any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_trunc (lv_fs_drv_t * drv, void * file_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /* Add your code here*/

    return res;
}

/**
 * Rename a file
 * @param drv pointer to a driver where this function belongs
 * @param oldname path to the file
 * @param newname path with the new name
 * @return LV_FS_RES_OK or any error from 'fs_res_t'
 */
static lv_fs_res_t fs_rename (lv_fs_drv_t * drv, const char * oldname, const char * newname)
{   
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /* Add your code here*/

    return res;
}

/**
 * Get the free and total size of a driver in kB
 * @param drv pointer to a driver where this function belongs
 * @param letter the driver letter
 * @param total_p pointer to store the total size [kB]
 * @param free_p pointer to store the free size [kB]
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_free (lv_fs_drv_t * drv, uint32_t * total_p, uint32_t * free_p)
{
    lv_fs_res_t res = LV_FS_RES_NOT_IMP;

    /* Add your code here*/

    return res;
}

/**
 * Initialize a 'fs_read_dir_t' variable for directory reading
 * @param drv pointer to a driver where this function belongs
 * @param dir_p pointer to a 'fs_read_dir_t' variable
 * @param path path to a directory
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static void * fs_dir_open (lv_fs_drv_t * drv, const char *path)
{
    (void) drv;		/*Unused*/

    return opendir(path);
}

/**
 * Read the next filename form a directory.
 * The name of the directories will begin with '/'
 * @param drv pointer to a driver where this function belongs
 * @param rddir_p pointer to an initialized 'fs_read_dir_t' variable
 * @param fn pointer to a buffer to store the filename
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_read (lv_fs_drv_t * drv, void * rddir_p, char *fn)
{
    struct dirent *entry;
	do {
		entry = readdir(rddir_p);

		if(entry) {
			if(entry->d_type == DT_DIR) sprintf(fn, "/%s", entry->d_name);
			else strcpy(fn, entry->d_name);
		} else {
			strcpy(fn, "");
		}
	} while(strcmp(fn, "/.") == 0 || strcmp(fn, "/..") == 0);

    return LV_FS_RES_OK;
}

/**
 * Close the directory reading
 * @param drv pointer to a driver where this function belongs
 * @param rddir_p pointer to an initialized 'fs_read_dir_t' variable
 * @return LV_FS_RES_OK or any error from lv_fs_res_t enum
 */
static lv_fs_res_t fs_dir_close (lv_fs_drv_t * drv, void * rddir_p)
{
    (void) drv;		/*Unused*/
    closedir(rddir_p);

    return LV_FS_RES_OK;
}

#else /* Enable this file at the top */

/* This dummy typedef exists purely to silence -Wpedantic. */
typedef int keep_pedantic_happy;
#endif
