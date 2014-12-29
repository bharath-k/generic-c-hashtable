/*
 * Author: Bharath Kumaran
 * Licensing: GNU General Public License (http://www.gnu.org/copyleft/gpl.html)
 * Description: sample usage of generic hashtable
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <lber.h>
#include <ldap.h>
#include "generichash.h"

int main(int argc, char **argv)
{
    /* assuming that a user developing service director code has u/<username> directory */
    HT *ht = ht_create();

    int i;
    for(i= 0; i < 100; i++)
    {
        char *key = calloc(4, sizeof(char));
        sprintf(key, "%d", i);
        ht_put(ht, key, &i);
        free(key);
    }

    for(i = 0; i < 100; i++)
    {
        char *key = calloc(4,sizeof(char));
        sprintf(key, "%d", i);
        int *intptr = (int *)ht_get(ht, key);
        fprintf(stderr, "key:%s and value:%d\n", key, *intptr);
        free(key);
    }

    /* get_keys should have the added entry */
    char **keys = ht_get_keys(ht);
    for(i = 0; i < 100; i++)
    {
        char *key = calloc(4,sizeof(char));
        sprintf(key, "%d", i);
        ht_remove(ht, key);
        void *intptr = (void *)ht_get(ht, key);
        if (intptr == NULL )
        {
            fprintf(stderr, "key:%s successfully removed\n", key);
        }
    }

    /* free the keys */
    free(keys);

    /* free hashtable */
    ht_destroy(ht);
}
