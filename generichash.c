/*
 * Author: Bharath Kumaran
 * Licensing: GNU General Public License (http://www.gnu.org/copyleft/gpl.html)
 * Description: generic hashtable implementation
 */

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <string.h>
#include "generichash.h"
#include "apr-1/apr.h"
#include "apr-1/apr_pools.h"
#include "apr-1/apr_hash.h"

/* Common apr pool for process. Each hashtable is created in its own subpool */
static apr_pool_t *commonpool = NULL;

HT *ht_create()
{
    HT *ht = (HT *)malloc(sizeof(HT));
    /* TODO: Definitely need some sort of a locking mechanism */
    if (commonpool == NULL)
    {
        /* Initialize apr */
        apr_initialize();
        /* make sure apr terminates when the program ends */
        /* apr_terminate2 exists to allow non-c language apps to tear down apr,
         * while apr_terminate is recommended from c language applications */
        atexit(apr_terminate2);
        apr_pool_create(&commonpool, NULL);
    }

    /* Create a subpool for each hashtable and clean up when the hashtable is
     * destroyed */
    apr_pool_t *subpool = NULL;
    apr_pool_create(&subpool, commonpool);

    apr_hash_t *apr_ht = apr_hash_make(subpool);
    ht->actualHT = apr_ht;
    ht->actualPool = subpool;
    return ht;
}

void ht_destroy(HT *ht)
{
    if (!ht) return;

    apr_hash_t *actualHT = (apr_hash_t *)ht->actualHT;
    apr_pool_t *actualPool = (apr_pool_t *)ht->actualPool;

    apr_hash_index_t *hi;
    const void *key;
    for (hi = apr_hash_first(actualPool, actualHT); hi; hi = apr_hash_next(hi)) {
        apr_hash_this(hi, &key, NULL, NULL);
        free((char *)key);
        key = NULL;
    }

    /* We are destroying the commonpool used for this hashtable */
    apr_pool_destroy(actualPool);
    free(ht);
    ht = NULL;
}

void *ht_get(HT *ht, const char * key)
{
    if (!ht) return NULL;
    apr_hash_t *actualHT = (apr_hash_t *)ht->actualHT;
    return apr_hash_get(actualHT, key, strlen(key));
}

void ht_put(HT *ht, const char * key, void *value)
{
    if (!ht) return;
    apr_hash_t *actualHT = (apr_hash_t *)ht->actualHT;
    apr_pool_t *actualPool = (apr_pool_t *)ht->actualPool;

    /* One reason why palloc is not used is that windows implementation could
     * use wchar_t instead of char. In that case, please provide a different
     * implementation of strlen (that uses wcslen) */
    /* No need to duplicate key if value is NULL the hash entry is deleted */
    char * newkey = NULL;
    if (value != NULL)
    {
        newkey = (char *)calloc(strlen(key) + 1, sizeof(char));
        strcpy(newkey, key);
    }
    else
    {
        newkey = (char *)key;
    }
    apr_hash_set(actualHT, newkey, strlen(newkey), value);
}

void ht_remove(HT *ht, char * key)
{
    /* ht_put with null value deletes the key/value pair */
    return ht_put(ht, key, NULL);
}

char **ht_get_keys(HT *ht)
{
    if (!ht) return NULL;

    apr_hash_t *actualHT = (apr_hash_t *)ht->actualHT;
    apr_pool_t *actualPool = (apr_pool_t *)ht->actualPool;
    int count = apr_hash_count(actualHT);
    char **keys = (char * *)calloc(count + 1, sizeof(char *));
    apr_hash_index_t *hi;
    const void *key;
    int i = 0;
    for (hi = apr_hash_first(actualPool, actualHT); hi; hi = apr_hash_next(hi)) {
        apr_hash_this(hi, &key, NULL, NULL);
        keys[i++] = (char *)key;
    }
    return keys;
}

int ht_get_count(HT *ht)
{
    if (!ht) return 0;
    return apr_hash_count((apr_hash_t *)ht->actualHT);
}
