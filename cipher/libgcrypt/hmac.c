#include <stdio.h>
#include <stdlib.h>
#include <gcrypt.h>

int main(void)
{
        int i, nhash;
        const char *key, *buff;
        unsigned char *hmac;
        gcry_error_t gcryrc;
        gcry_md_hd_t gcryhd;

        key = "encrypt key";
        buff = "plain text";

        nhash = gcry_md_get_algo_dlen(GCRY_MD_SHA256);
        printf("SHA256 hash length: %d\n", nhash);

        gcryrc = gcry_md_open(&gcryhd, GCRY_MD_SHA256, GCRY_MD_FLAG_HMAC);
        if (gcryrc) {
                fprintf(stderr, "gcrypt open failed, %s/%s\n",
                        gcry_strsource(gcryrc), gcry_strerror(gcryrc));
                return -1;
        }
        gcry_md_reset(gcryhd);

        gcryrc = gcry_md_setkey(gcryhd, key, strlen(key));
        if (gcryrc) {
                fprintf(stderr, "gcrypt setkey failed, %s/%s\n",
                        gcry_strsource(gcryrc), gcry_strerror(gcryrc));
                gcry_md_close(gcryhd);
                return -1;
        }
        gcry_md_write(gcryhd, buff, strlen(buff));

        hmac = gcry_md_read(gcryhd, GCRY_MD_SHA256);
        if (hmac == NULL) {
                fprintf(stderr, "gcrypt open failed, %s/%s\n",
                        gcry_strsource(gcryrc), gcry_strerror(gcryrc));
                gcry_md_close(gcryhd);
                return -1;
        }

        /*
         * result: "55b5149108b25dd7db932116ac333bc96985d58dfec92177ad773cf176e796bc"
         * https://1024tools.com/hmac
         */
        for (i = 0; i < nhash; i++)
                printf("%02x", (unsigned char)hmac[i]);
        puts("");

        gcry_md_close(gcryhd);

        return 0;
}
