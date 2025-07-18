#include "filesys/free-map.h"
#include <bitmap.h>
#include <debug.h>
#include "filesys/file.h"
#include "filesys/filesys.h"
#include "filesys/inode.h"
#include "threads/synch.h"

static struct file *free_map_file;   /* Free map file. */
static struct bitmap *free_map;      /* Free map, one bit per disk sector. */
struct lock free_map_lock; 

/* Initializes the free map. */
void
free_map_init (void)
{
  free_map = bitmap_create (disk_size (filesys_disk));
  if (free_map == NULL)
    PANIC ("bitmap creation failed--disk is too large");
  bitmap_mark (free_map, FREE_MAP_SECTOR);
  bitmap_mark (free_map, ROOT_DIR_SECTOR);
  lock_init(&free_map_lock); 
}

/* Allocates CNT consecutive sectors from the free map and stores
   the first into *SECTORP.
   Returns true if successful, false if all sectors were
   available. */
bool
free_map_allocate (size_t cnt, disk_sector_t *sectorp)
{
  lock_acquire(&free_map_lock); 
  disk_sector_t sector;

  sector = bitmap_scan_and_flip (free_map, 0, cnt, false);
  if (sector != BITMAP_ERROR
      && free_map_file != NULL
      && !bitmap_write (free_map, free_map_file))
    {
      bitmap_set_multiple (free_map, sector, cnt, false);
      sector = BITMAP_ERROR;
    }

  if (sector != BITMAP_ERROR)
    *sectorp = sector;
  lock_release(&free_map_lock);   
  return sector != BITMAP_ERROR;
}

/* Makes CNT sectors starting at SECTOR available for use. */
void
free_map_release (disk_sector_t sector, size_t cnt)
{
  lock_acquire(&free_map_lock);
  ASSERT (bitmap_all (free_map, sector, cnt));
  bitmap_set_multiple (free_map, sector, cnt, false);
  bitmap_write (free_map, free_map_file);
  lock_release(&free_map_lock); 
}

/* Opens the free map file and reads it from disk. */
void
free_map_open (void)
{
  free_map_file = file_open (inode_open (FREE_MAP_SECTOR));
  if (free_map_file == NULL)
    PANIC ("can't open free map");
  if (!bitmap_read (free_map, free_map_file))
    PANIC ("can't read free map");
}

/* Writes the free map to disk and closes the free map file. */
void
free_map_close (void)
{
  file_close (free_map_file);
}

/* Deallocates the free-map before system shutdown. */
void
free_map_destroy (void)
{
  bitmap_destroy (free_map);
}

/* Creates a new free map file on disk and writes the free map to
   it. */
void
free_map_create (void)
{
  /* Create inode. */
  if (!inode_create (FREE_MAP_SECTOR, bitmap_file_size (free_map)))
    PANIC ("free map creation failed");

  /* Write bitmap to file. */
  free_map_file = file_open (inode_open (FREE_MAP_SECTOR));
  if (free_map_file == NULL)
    PANIC ("can't open free map");
  if (!bitmap_write (free_map, free_map_file))
    PANIC ("can't write free map");
}
