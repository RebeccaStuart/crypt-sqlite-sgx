#ifndef _ENCRYPTION_H
#define _ENCRYPTION_H
#ifdef __cplusplus
extern "C" {
#endif
void phex(uint8_t* str);

void phex_to_string(uint8_t* str, char* out);

void encrypt_str(uint8_t* str, uint8_t* out, int iter, uint8_t* key);

void decrypt_str(uint8_t* str, uint8_t* out, int iter, uint8_t* key);

int find_iterations(uint8_t* str);

int hex_to_int(char c);

int hex_to_ascii(char c, char d);

void convert_hex_str_to_asc(char* str, char* done);

int testall(void);
char* encry(char* enc);
char* decry(char* dec);
int test(char*  enc);
void encrypp(uint8_t* str, uint8_t* enc,uint8_t* key);
void decrypp(uint8_t* str, uint8_t* dec,uint8_t* key);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif //_ENCRYPTION_H
