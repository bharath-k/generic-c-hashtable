/*
 * Author: Bharath Kumaran
 * Licensing: GNU General Public License (http://www.gnu.org/copyleft/gpl.html)
 * Description: generic hashtable
 */

#ifndef _GENERICHASH_H
#define _GENERICHASH_H

typedef struct ht {
    /* The end user need not be aware of the type of actual hashtable */
    void *actualHT;
    void *actualPool;
} HT;

/*
 * ht_create - creates and allocates memory for a new hashtable
 *
 */
HT *ht_create();

/*
 * ht_destroy - frees hashtable memory
 *
 * @ht: hashtable
 */
void ht_destroy(HT *ht);

/*
 * ht_get - retrieves value corresponding to provided key.
 *
 * @ht: hashtable
 * @key: string key
 */
void *ht_get(HT *ht, const char *key);

/*
 * ht_put - stores entry and value in hashtable.
 *
 * @ht: hashtable
 * @key: key
 * @value: value
 */
void ht_put(HT *ht, const char *key, void *val);

/*
 * ht_remove - removes entry from hashtable.
 *
 * @ht: hashtable
 * @key: key
 */
void ht_remove(HT *ht, char *key);

/*
 * ht_get_keys - Fetches all the keys of hashtable.
 *
 * @ht: hashtable
 * @key: key
 */
char **ht_get_keys(HT *ht);

/*
 * ht_get_count - Count of number of items stored in hashtable.
 *
 * @ht: hashtable
 */
int ht_get_count(HT *ht);

#endif
