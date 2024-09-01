#include<bits/stdc++.h>
#include <stdint.h>

using namespace std;


/*
 * The Dan Bernstein popuralized hash..  See
 * https://github.com/pjps/ndjbdns/blob/master/cdb_hash.c#L26 Due to hash
 * collisions it seems to be replaced with "siphash" in n-djbdns, see
 * https://github.com/pjps/ndjbdns/commit/16cb625eccbd68045737729792f09b4945a4b508
 */
uint32_t djb33_hash(const char* s, size_t len)
{
    uint32_t h = 5381;
    while (len--) {
        /* h = 33 * h ^ s[i]; */
        h += (h << 5);  
        h ^= *s++;
    }
    return h;
}
uint32_t djb33_hash(const string str)
{
    uint32_t h = 5381;
    for(int i = 0; i < str.size(); i++){
        /* h = 33 * h ^ s[i]; */
        h += (h << 5);  
        h ^= str[i];
    }
    return h;
}


/*
 *
 * The Java hash, but really no-one seems to know where it came from, see
 * https://bugs.java.com/bugdatabase/view_bug.do?bug_id=4045622
 */
uint32_t h31_hash(const char* s, size_t len)
{
    uint32_t h = 0;
    while (len) {
        h = 31 * h + *s++;
        --len;
    }
    return h;
}

uint32_t h31_hash(const string &str)
{
    uint32_t hesh = 0;
    for(int i = 0; i < str.size(); i++) {
        hesh = 31 * hesh + str[i];
    }
    return hesh;
}

/*
 * The FNV Hash, or more precisely the "FNV-1a alternate algorithm"
 * See: http://www.isthe.com/chongo/tech/comp/fnv/
 *      https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
 */

uint32_t fnv32_a_hash(const char *str, size_t len)
{
    unsigned char *s = (unsigned char *)str;	/* unsigned string */

    /* See the FNV parameters at www.isthe.com/chongo/tech/comp/fnv/#FNV-param */
    const uint32_t FNV_32_PRIME = 0x01000193; /* 16777619 */

    uint32_t h = 0x811c9dc5; /* 2166136261 */
    while (len--) {
        /* xor the bottom with the current octet */
        h ^= *s++;
        /* multiply by the 32 bit FNV magic prime mod 2^32 */
        h *= FNV_32_PRIME;
    }

    return h;
}

uint32_t fnv32_a_hash(const string &str)
{
    /* See the FNV parameters at www.isthe.com/chongo/tech/comp/fnv/#FNV-param */
    const uint32_t FNV_32_PRIME = 0x01000193; /* 16777619 */
    uint32_t h = 0x811c9dc5; /* 2166136261 */
    for(int i = 0; i < str.size(); i++) {
        /* xor the bottom with the current octet */
        h ^= str[i];
        /* multiply by the 32 bit FNV magic prime mod 2^32 */
        h *= FNV_32_PRIME;
    }
    return h;
}


/*
 * "This came from ejb's hsearch."
 */
uint32_t ejb_hash(const char *s, size_t len)
{
	unsigned char *key = (unsigned char*) s;
	const uint32_t PRIME1 = 37;
	const uint32_t PRIME2 = 1048583;
	uint32_t h = 0;

	while (len--) {
		h = h * PRIME1 ^ (*key++ - ' ');
	}
	h %= PRIME2;

	return h;
}

uint32_t ejb_hash(string &str){
	const uint32_t PRIME1 = 37;
	const uint32_t PRIME2 = 1048583;
	uint32_t h = 0;
	for(int i = 0; i < str.size(); i++) {
		h = h * PRIME1 ^ (str[i] - ' ');
	}
	h %= PRIME2;
	return h;
}

/*
 * Bob Jenkins "One-at-a-time" hash
 */
uint32_t oat_hash(const char *s, size_t len)
{
    unsigned char *p = (unsigned char*) s;
    uint32_t h = 0;

    while(len--) {
        h += *p++;
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h;
}
uint32_t oat_hash(string &str){
    uint32_t h = 0;
    for(int i = 0; i < str.size(); i++) {
        h += str[i];
        h += (h << 10);
        h ^= (h >> 6);
    }

    h += (h << 3);
    h ^= (h >> 11);
    h += (h << 15);

    return h;
}


int main(){
    string s = "abcde";
    int h1 = fnv32_a_hash(s);
    int h2 = djb33_hash(s);
    cout << h1 << endl;
    cout << h2 << endl;
    cout << fnv32_a_hash("abcde", 5) << endl;
    cout << djb33_hash("abcde", 5) << endl;
}